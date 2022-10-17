#include "Engine.h" 
#include <iostream> 

float points[] = {
	-1.0f, -1.0f,  0.0f,
	-1.0f,  1.0f,  0.0f,
	1.0f, -1.0f,  0.0f,

	-1.0f,  1.0f,  0.0f,
	1.0f,  1.0f,  0.0f,
	1.0f,  -1.0f,  0.0f
};

glm::vec3 color[] =
{
	{ 0, 0, 1}, //rgb
	{ 1, 0, 1},
	{ 1, 1, 0},
	{ 0, 0, 1},
	{ 0, 1, 1},
	{ 0, 1, 0}
};

glm::vec2 texcoords[]
{
	{0,0},
	{0,1},
	{1,0},
	{0,1},
	{1,1},
	{1,0}
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
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), color, GL_STATIC_DRAW);
	
	GLuint tvbo = 0;
	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), texcoords, GL_STATIC_DRAW);

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
	
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// create program

	/*GLuint program = glCreateProgram();
	glAttachShader(program, fs->m_shader);
	glAttachShader(program, vs->m_shader);
	glLinkProgram(program);
	glUseProgram(program);*/

	std::shared_ptr<boogleborg::Program> program = boogleborg::g_resources.Get<boogleborg::Program>("Shaders/basic.prog");
	program->Link();
	program->Use();

	
	std::shared_ptr<boogleborg::Material> material = boogleborg::g_resources.Get<boogleborg::Material>("materials/sussy.mtrl");
	material->Bind();

	/*GLint uniform1 = glGetUniformLocation(program, "scale");
	GLint uniform2 = glGetUniformLocation(program, "tint");
	GLint uniform3 = glGetUniformLocation(program, "transform");*/

	//glUniform3f(uniform2, 0, 0, 0);

	//1 0 0 0
	//0 1 0 0
	//0 0 1 0
	//0 0 0 1

	glm::mat4 mx{1};
	//mx = glm::scale(glm::vec3(0.5, 0.5, 0.5));


	bool quit = false;
	while (!quit)
	{
		boogleborg::Engine::Instance().Update();

		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_escape) == boogleborg::InputSystem::KeyState::Pressed) quit = true;

		program->SetUniform("scale", std::sin(boogleborg::g_time.time));
		program->SetUniform("transform", mx);
		
		boogleborg::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		boogleborg::g_renderer.EndFrame();
	}

	boogleborg::Engine::Instance().Shutdown();

	return 0;
}