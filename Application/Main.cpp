#include "Engine.h" 
#include <iostream> 
#define POST_PROCESS

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

	//create framebuffer texture
	auto texture = std::make_shared<boogleborg::Texture>();
	texture->CreateTexture(1024, 1024);
	boogleborg::g_resources.Add<boogleborg::Texture>("fb_texture", texture);

	//create framebuffer
	auto framebuffer = boogleborg::g_resources.Get<boogleborg::FrameBuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();

	//load scene
	auto scene = boogleborg::g_resources.Get<boogleborg::Scene>("scenes/postProcess.scn");

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

		auto program = boogleborg::g_resources.Get<boogleborg::Program>("shaders/POST_PROCESS/postproces.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("offset", boogleborg::g_time.time);
		}


		ImGui::Begin("Yoyo");
		//ImGui::Button("Click Button");
		ImGui::DragFloat3("Rotation", &rot[0]); //x,y,z sliders
		ImGui::DragFloat("Interpolation", &interP, 0.05f, 0, 1); //x,y,z sliders
		ImGui::DragFloat("Refraction Index", &refractionInd, 0.05f, 1, 4.1f); //x,y,z sliders		
		ImGui::End();

		scene->Update();

#ifdef POST_PROCESS
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		
		//render pass 1
		boogleborg::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		boogleborg::g_renderer.BeginFrame();
		scene->PreRender(boogleborg::g_renderer);
		scene->Render(boogleborg::g_renderer);
		framebuffer->Unbind();

		boogleborg::g_renderer.RestoreViewport();
		boogleborg::g_renderer.BeginFrame();
		scene->PreRender(boogleborg::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(boogleborg::g_renderer);
			}
		}
#else 
		boogleborg::g_renderer.BeginFrame();
		scene->PreRender(boogleborg::g_renderer);
		scene->Render(boogleborg::g_renderer);
#endif // POST_PROCESS

		boogleborg::g_gui.Draw();

		boogleborg::g_renderer.EndFrame();
		boogleborg::g_gui.EndFrame();
	}
	scene->RemoveAll();
	boogleborg::Engine::Instance().Shutdown();

	return 0;
}