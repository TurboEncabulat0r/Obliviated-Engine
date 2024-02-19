#pragma once
#include "window.h"


namespace obvl 
{


	class Engine {
		Window window;

	public:
		Engine(char* windowName);

		Engine();

		float getFramerate();

		float getFrameTime();

		void setFramerateLimit(float fps);

		void runSyncronous();

	};

}