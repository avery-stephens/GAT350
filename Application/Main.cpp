#include "Engine.h" 
#include <iostream> 

int main(int argc, char** argv)
{
	boogleborg::InitializeMemory();

	boogleborg::Engine::Instance().Initialize();
	boogleborg::Engine::Instance().Register();

	boogleborg::g_renderer.CreateWindow("Triangulator", 800, 800);

	float angle = 0;
	boogleborg::Vector2 position;

	bool quit = false;
	while (!quit)
	{
		boogleborg::Engine::Instance().Update();

		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_escape) == boogleborg::InputSystem::KeyState::Pressed) quit = true;

		boogleborg::g_renderer.BeginFrame();

		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_left) == boogleborg::InputSystem::KeyState::Held)
		{
			position.x -= boogleborg::g_time.deltaTime;
		}
		
		if (boogleborg::g_inputSystem.GetKeyState(boogleborg::key_right) == boogleborg::InputSystem::KeyState::Held)
		{
			position.x += boogleborg::g_time.deltaTime;
		}

		angle += 90.0f * boogleborg::g_time.deltaTime;

		glPushMatrix();

		glScalef(0.5f,0.5f,0.5f);
		//glRotatef(angle, 0, 0, 1);
		glTranslatef(position.x, position.y, 0);

		glBegin(GL_TRIANGLES);

		//glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-1.0f, -1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);

		glEnd();

		glPopMatrix();

		boogleborg::g_renderer.EndFrame();
	}

	boogleborg::Engine::Instance().Shutdown();

	return 0;
}