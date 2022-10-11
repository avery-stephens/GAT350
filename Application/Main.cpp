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

const char* vertex_shader =
"#version 430 core\n"
"in vec3 position;"
"void main() {"
"  gl_Position = vec4(position, 1.0);"
"}";

const char* fragment_shader =
"#version 430 core\n"
"out vec4 color;"
"void main() {"
"  color = vec4(1.0, 1.0, 1.0, 1.0);"
"}";

int main(int argc, char** argv)
{
	boogleborg::InitializeMemory();

	boogleborg::Engine::Instance().Initialize();
	boogleborg::Engine::Instance().Register();

	boogleborg::g_renderer.CreateWindow("Triangulator", 800, 800);

	//float angle = 0;
	//boogleborg::Vector2 position;

	// create vertex buffer
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	// create program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
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