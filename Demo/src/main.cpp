#include <iostream>
#include "engine.h"

int main(int argc, char** argv)
{
	Engine engine;

	engine.init("YOLO", 800, 600);

	while (engine.pollEvents())
	{
		engine.draw();
	}

	engine.quit();

	return 0;
}