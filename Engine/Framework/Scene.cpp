#include "Scene.h"
#include "Factory.h"
#include "Engine.h"
#include <algorithm>
#include <iostream>

namespace boogleborg
{
	void Scene::Initialize()
	{
		for (auto& actor : m_actors) { actor->Initialize(); }
	}

	void Scene::Update()
	{
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			(*iter)->Update();
			if ((*iter)->m_destroy)
			{
				iter = m_actors.erase(iter);
			}
			else 
			{
				iter++;
			}
		}
	}

	bool Scene::Create(std::string name, ...)
	{
		rapidjson::Document document;
		bool success = boogleborg::json::Load(name, document);
		if (!success)
		{

			LOG("Could not load scene file (%s).", name.c_str());
			return false;
		}

		Read(document);
		Initialize();
		return true;
	}

	void Scene::PreRender(Renderer& renderer)
	{
		// get active camera component 
		CameraComponent* camera = nullptr;
		for (auto& actor : m_actors)
		{
			if (!actor->IsActive()) continue;

			auto component = actor->GetComponent<CameraComponent>();
			if (component != NULL)
			{
				camera = component;
				break;
			}
		}

		// get light components 
		std::vector<LightComponent*> lights;
		for (auto& actor : m_actors)
		{
			if(!actor->IsActive()) continue;

			auto component = actor->GetComponent<LightComponent>();
			if (component != NULL)
			{
				//<add(push back) component to lights vector>
				lights.push_back(component);
			}
		}

		// get all shader programs in the resource system 
		auto programs = g_resources.Get<Program>();
		// set all shader programs camera and lights uniforms 
		for (auto& program : programs)
		{
			// set camera in shader program 
			camera->SetProgram(program);

			// set lights in shader program 
			int index = 0;
			for (auto light : lights)
			{
				light->SetProgram(program, index++);
			}

			program->SetUniform("light_count", index);
			program->SetUniform("ambient_color", g_renderer.ambient_color);
		}
	}

	void Scene::Render(Renderer& renderer)
	{
		// get camera / set renderer view/projection 
		auto camera = GetActorFromName("Camera");
		if (camera)
		{
			g_renderer.SetView(camera->GetComponent<CameraComponent>() -> GetView());
			g_renderer.SetProjection(camera->GetComponent<CameraComponent>() -> GetProjection());
		}

		// draw actors 
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		for (auto& actor : m_actors) { actor->SetDestroy(); }

		m_actors.clear();
	}

	bool Scene::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool Scene::Read(const rapidjson::Value& value)
	{
		READ_NAME_DATA(value, "clear_color", g_renderer.clear_color);
		READ_NAME_DATA(value, "ambient_color", g_renderer.ambient_color);

		if (!value.HasMember("actors") || !value["actors"].IsArray())
		{
			return false;
		}

		// read actors
		for (auto& actorValue : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(actorValue, type);

			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor)
			{
				// read actor
				actor->Read(actorValue);

				bool prefab = false;
				READ_DATA(actorValue, prefab);

				if (prefab)
				{
					std::string name = actor->GetName();
					Factory::Instance().RegisterPrefab(name, std::move(actor));
				}
				else
				{
					Add(std::move(actor));
				}
			}
		}
		

		return true;
	}

}
