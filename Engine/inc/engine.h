#pragma once

#include <string>
#include <SDL\SDL.h>

class Engine
{
public:
	Engine();
	~Engine();

	int init(const std::string& title, int width, int height);
	int pollEvents();
	void draw();
	int quit();

private:
	int screenWidth;
	int screenHeight;

	SDL_Window* window;
	SDL_GLContext context;
};