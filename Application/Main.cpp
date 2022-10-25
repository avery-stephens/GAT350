#include "Engine.h" 
#include <iostream> 

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
													  
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
													  
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
													  
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
													  
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

int main(int argc, char** argv)
{
	LOG("Application Started...");
	boogleborg::InitializeMemory();
	boogleborg::SetFilePath("../Assets");

	boogleborg::Engine::Instance().Initialize();
	boogleborg::Engine::Instance().Register();

	LOG("Engine Initialized...");

	boogleborg::g_renderer.CreateWindow("Triangulator", 800, 800);
	LOG("Window Initialized...");

	auto scene = boogleborg::g_resources.Get<boogleborg::Scene>("scenes/basic.scn");

	/*rapidjson::Document document;
	bool success = boogleborg::json::Load("scenes/basic.scn", document);
	if (!success)
	{
		LOG("error loading scene file %s.", "scenes/basic.scn");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}*/

	//auto m = boogleborg::g_resources.Get<boogleborg::Model>("models/spot.obj");

	//create material
	std::shared_ptr<boogleborg::Material> material = boogleborg::g_resources.Get<boogleborg::Material>("materials/cow.mtrl");
	material->Bind();

	/*GLint uniform1 = glGetUniformLocation(program, "scale");
	GLint uniform2 = glGetUniformLocation(program, "tint");
	GLint uniform3 = glGetUniformLocation(program, "transform");*/

	//glUniform3f(uniform2, 0, 0, 0);

	material->GetProgram()->SetUniform("tint", glm::vec3{ 1,0,0 });
	material->GetProgram()->SetUniform("scale", 0.5f);

	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, boogleborg::g_renderer.GetWidth() / (float)boogleborg::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 3 };
	float speed = 2;

	std::vector<boogleborg::Transform> transforms;
	for (size_t i = 0; i < 1; i++)
	{
		transforms.push_back({ {0, 0, 0}, {0, 0, 0} });
	}

	/*boogleborg::Transform transforms[] =
	{
		{ {boogleborg::randomf(-10, 10), boogleborg::randomf(-15, 10), boogleborg::randomf(-10, 15)}, {0, boogleborg::randomf(360), 0} },
		{ {2, 0, 0}, {0, 90, 90} },
		{ {0, 2, -2}, {45, 90, 0} },
		{ {2, -1, 0}, {90, 90, 0} }
	};*/

	bool quit = false;
	while (!quit)
	{
		boogleborg::Engine::Instance().Update();
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_escape) == boogleborg::InputSystem::KeyState::Pressed) quit = true;

		//add input to move camera
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_left) == boogleborg::InputSystem::KeyState::Held) cameraPosition.x -= speed * boogleborg::g_time.deltaTime;
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_right) == boogleborg::InputSystem::KeyState::Held) cameraPosition.x += speed * boogleborg::g_time.deltaTime;
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_up) == boogleborg::InputSystem::KeyState::Held) cameraPosition.y += speed * boogleborg::g_time.deltaTime;
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_down) == boogleborg::InputSystem::KeyState::Held) cameraPosition.y -= speed * boogleborg::g_time.deltaTime;
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_pgup) == boogleborg::InputSystem::KeyState::Held) cameraPosition.z -= speed * boogleborg::g_time.deltaTime;
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_pgdown) == boogleborg::InputSystem::KeyState::Held) cameraPosition.z += speed * boogleborg::g_time.deltaTime;
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_enter) == boogleborg::InputSystem::KeyState::Held) cameraPosition = glm::vec3{ 0, 0, 3 };

		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		scene->Update();
		//model = glm::eulerAngleXYZ(0.0f, boogleborg::g_time.time, 0.0f);
		
		boogleborg::g_renderer.BeginFrame();

		//m->m_vertexBuffer.Draw();

		for (size_t i = 0; i < transforms.size(); i++)
		{
			transforms[i].rotation += glm::vec3{ 0, boogleborg::g_time.deltaTime, 0 };
			glm::mat4 mvp = projection * view * (glm::mat4)transforms[i];
			material->GetProgram()->SetUniform("mvp", mvp);

			//vb->Draw();
		}

		scene->Draw(boogleborg::g_renderer);

		boogleborg::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	boogleborg::Engine::Instance().Shutdown();

	return 0;
}