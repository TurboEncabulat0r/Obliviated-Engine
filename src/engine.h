#pragma once
#include "editor.h"
#include "window.h"
#include "input.h"
#include "rendering.h"


namespace obvl 
{


	class Engine {
	public:
		Window window;
		Renderer renderer;
		Editor* editor;



		Engine(char* windowName);

		Engine();

		float getFramerate();

		float getFrameTime();

		void setFramerateLimit(float fps);

		void runSyncronous();

	};

	void handleResizeWindow();

}