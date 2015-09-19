#include "engine.h"

#include <GL\glew.h>
#include <iostream>
#include <cassert>

Engine::Engine()
{
}

Engine::~Engine()
{
}

int Engine::init(const std::string& title, int width, int height)
{
	int SDLResult = SDL_Init(SDL_INIT_VIDEO);
	assert(SDLResult == 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	assert(window != nullptr);

	context = SDL_GL_CreateContext(window);

	assert(context != nullptr);

	glewExperimental = GL_FALSE;
	const GLenum glewResult = glewInit();
	assert(glewResult == GLEW_OK);
	glGetError();

	int versionMajor = 0;
	int versionMinor = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
	std::cout << "OpenGL context version: " << versionMajor << "." << versionMinor << std::endl;

	int parameter;
	glGetIntegerv(GL_SAMPLES, &parameter);
	std::cout << "Multisampling samples: " << parameter << '\n';

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	glClearColor(0.5f, 0.0f, 0.75f, 1.0f);

	return 1;
}

int Engine::pollEvents()
{
	SDL_Event event;
	int returnValue = 1;

	while (SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_QUIT)
		{
			returnValue = 0;
		}
	}

	return returnValue;
}

void Engine::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(window);
}

int Engine::quit()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}