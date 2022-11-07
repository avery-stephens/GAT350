#include "Engine.h" 
#include <iostream> 


int main(int argc, char** argv)
{
	LOG("Application Started...");
	boogleborg::InitializeMemory();
	boogleborg::SetFilePath("../Assets");

	boogleborg::Engine::Instance().Initialize();
	boogleborg::Engine::Instance().Register();

	LOG("Engine Initialized...");

	boogleborg::g_renderer.CreateWindow("This thing makes 3d shapes!?!?!??!!?!", 800, 800);
	LOG("Window Initialized...");

	//load scene
	auto scene = boogleborg::g_resources.Get<boogleborg::Scene>("scenes/texture.scn");

	bool quit = false;
	while (!quit)
	{
		boogleborg::Engine::Instance().Update();
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_escape) == boogleborg::InputSystem::KeyState::Pressed) quit = true;

		//model = glm::eulerAngleXYZ(0.0f, boogleborg::g_time.time, 0.0f);

		auto material = boogleborg::g_resources.Get<boogleborg::Material>("Materials/ogre.mtrl");
		if (material)
		{
			//material->uv_offset += glm::vec2(boogleborg::g_time.deltaTime);
		}

		scene->Update();
		
		boogleborg::g_renderer.BeginFrame();

		auto actor = scene->GetActorFromName("Ogre");
		if (actor)
		{
			actor->m_transform.rotation.y += 45.0f * boogleborg::g_time.deltaTime;
		}

		scene->Draw(boogleborg::g_renderer);

		boogleborg::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	boogleborg::Engine::Instance().Shutdown();

	return 0;
}