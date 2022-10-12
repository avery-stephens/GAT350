#include "Engine.h" 
#include <iostream> 

float points[] = {
	-0.5f, -0.5f,  0.0f,
	-0.5f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f,

	-0.5f,  0.5f,  0.0f,
	0.5f,  0.5f,  0.0f,
	0.5f,  -0.5f,  0.0f
};

boogleborg::Vector3 color[] =
{
	{ 0, 0, 1}, //rgb
	{ 1, 0, 1},
	{ 0, 1, 0},
	{ 0, 0, 1},
	{ 0, 1, 1},
	{ 1, 1, 1}
};

int main(int argc, char** argv)
{
	boogleborg::InitializeMemory();
	boogleborg::SetFilePath("../Assets");

	boogleborg::Engine::Instance().Initialize();
	boogleborg::Engine::Instance().Register();

	boogleborg::g_renderer.CreateWindow("Triangulator", 800, 800);

	//float angle = 0;
	//boogleborg::Vector2 position;

	// create vertex buffer
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(boogleborg::Vector3), color, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// position
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	// color
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader
	std::shared_ptr<boogleborg::Shader> vs = boogleborg::g_resources.Get<boogleborg::Shader>("Shaders/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<boogleborg::Shader> fs = boogleborg::g_resources.Get<boogleborg::Shader>("Shaders/basic.frag", GL_FRAGMENT_SHADER);

	/*GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);*/

	// create program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs->m_shader);
	glAttachShader(program, vs->m_shader);
	glLinkProgram(program);
	glUseProgram(program);

	bool quit = false;
	while (!quit)
	{
		boogleborg::Engine::Instance().Update();

		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_escape) == boogleborg::InputSystem::KeyState::Pressed) quit = true;

		boogleborg::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		boogleborg::g_renderer.EndFrame();
	}

	boogleborg::Engine::Instance().Shutdown();

	return 0;
}