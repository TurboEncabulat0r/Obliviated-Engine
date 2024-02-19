#include "engine.h"
#include <iostream>

namespace obvl
{


	bool running;

	void handleQuit() {
		running = false;
	}

	Engine::Engine(char* windowName) {
		Window window = Window(windowName, 1200, 1200);
		this->window = window;
		running = true;
		window.setOnQuit(&handleQuit);
	}

	Engine::Engine() {
		Engine("Obliviated Engine");
	}

	float getFramerate() 
	{
		return 0;
	}

	float getFrameTime() 
	{
		return 0;
	}

	void Engine::setFramerateLimit(float fps) 
	{


	}

	void Engine::runSyncronous() 
	{
		while (running) {
			this->window.Update();
		}

	}




}