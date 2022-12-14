#include "LightComponent.h"
#include "Engine.h"

namespace boogleborg
{
	void LightComponent::Update()
	{
		//	
	}
	void LightComponent::SetProgram(std::shared_ptr<Program> program, int index)
	{
		// transform the light position by the view, puts light in model view space 
		glm::vec4 position = g_renderer.GetView() * glm::vec4(m_owner -> m_transform.position, 1);
		glm::vec3 direction = m_owner->m_transform.getForward();
		std::string lightName = "lights[" + std::to_string(index) + "]";

		// get all programs in the resource system
		auto programs = g_resources.Get<Program>();
		// set programs light properties
		//for (auto& program : programs)
		//{
			program->Use();
			program->SetUniform(lightName + ".type", (int)type);
			//program->SetUniform("light.ambient", glm::vec3{ 0.2f });
			program->SetUniform(lightName + ".color", color);
			program->SetUniform(lightName + ".position", position);
			program->SetUniform(lightName + ".direction", direction);
			program->SetUniform(lightName + ".cutoff", glm::radians(cutoff));
			program->SetUniform(lightName + ".exponent", exponent);
		//}
		// create array light name from index (lights[0], ...) 

	}

	bool LightComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool LightComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, color);
		READ_DATA(value, cutoff);
		READ_DATA(value, exponent);

		std::string type_name;
		READ_DATA(value, type_name);
		if (CompareIgnoreCase(type_name, "directional"))
		{
			type = Type::Directional;
		}
		else if (CompareIgnoreCase(type_name, "spot"))
		{
			type = Type::Spot;
		}
		else
		{
			type = Type::Point;
		}
		/*READ_DATA(value, diffuse);
		READ_DATA(value, specular);*/

		return true;
	}


}