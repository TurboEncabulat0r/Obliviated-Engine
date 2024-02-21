#pragma once
#include "window.h"
#include "input.h"
#include "rendering.h"


namespace obvl 
{


	class Engine {
		Window window;
		Renderer renderer;

	public:
		Engine(char* windowName);

		Engine();

		float getFramerate();

		float getFrameTime();

		void setFramerateLimit(float fps);

		void runSyncronous();

	};

	void handleResizeWindow();

}