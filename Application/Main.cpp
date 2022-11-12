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
	boogleborg::g_gui.Initialize(boogleborg::g_renderer);

	//load scene
	auto scene = boogleborg::g_resources.Get<boogleborg::Scene>("scenes/texture.scn");

	glm::vec3 pos(0, 0, 0);
	float x = 0;
	bool quit = false;
	while (!quit)
	{
		boogleborg::Engine::Instance().Update();
		boogleborg::g_gui.BeginFrame(boogleborg::g_renderer);
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_escape) == boogleborg::InputSystem::KeyState::Pressed) quit = true;

		//model = glm::eulerAngleXYZ(0.0f, boogleborg::g_time.time, 0.0f);
		auto actor = scene->GetActorFromName("Unicorn");
		if (actor)
		{
			actor->m_transform.rotation.y += 45.0f * boogleborg::g_time.deltaTime;
		}

		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave 
			actor->m_transform.position = pos;
		}

		ImGui::Begin("Yoyo");
		ImGui::Button("Click Button");
		ImGui::SliderFloat3("Lighting", & pos[0], -5.0f, 5.0);
		ImGui::End();
		scene->Update();
		
		boogleborg::g_renderer.BeginFrame();


		scene->Draw(boogleborg::g_renderer);
		boogleborg::g_gui.Draw();


		boogleborg::g_renderer.EndFrame();
		boogleborg::g_gui.EndFrame();
	}
	scene->RemoveAll();
	boogleborg::Engine::Instance().Shutdown();

	return 0;
}