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
	auto scene = boogleborg::g_resources.Get<boogleborg::Scene>("scenes/cubeMap.scn");

	glm::vec3 rot = { 0, 0, 0 };
	float interP = 1;
	float refractionInd = 1;
	//float ri = 1;
	//float x = 0;
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
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}

		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave 
			//actor->m_transform.position = pos;
		}

		auto program = boogleborg::g_resources.Get<boogleborg::Program>("shaders/fx/reflection_refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("i", interP);
			program->SetUniform("ri", refractionInd);
		}


		ImGui::Begin("Yoyo");
		//ImGui::Button("Click Button");
		ImGui::DragFloat3("Rotation", &rot[0]); //x,y,z sliders
		ImGui::DragFloat("Interpolation", &interP, 0.05f, 0, 1); //x,y,z sliders
		ImGui::DragFloat("Refraction Index", &refractionInd, 0.05f, 1, 4.1f); //x,y,z sliders		
		ImGui::End();

		scene->Update();
		
		boogleborg::g_renderer.BeginFrame();

		scene->PreRender(boogleborg::g_renderer);
		scene->Render(boogleborg::g_renderer);

		//scene->Draw(boogleborg::g_renderer);
		boogleborg::g_gui.Draw();

		boogleborg::g_renderer.EndFrame();
		boogleborg::g_gui.EndFrame();
	}
	scene->RemoveAll();
	boogleborg::Engine::Instance().Shutdown();

	return 0;
}