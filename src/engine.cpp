#include "engine.h"
#include <iostream>
#include "rendering.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

namespace obvl
{


	bool running;

	void handleQuit() {
		running = false;
	}

	Engine* main = nullptr;

	Engine::Engine(char* windowName) {
		Window window = Window(windowName, 1200, 1200);
		this->window = window;
		this->renderer = Renderer(&window);
		running = true;
		window.setOnQuit(&handleQuit);
		main = this;
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


	void drawMainMenu()
	{
		ImGui::Begin("Obliviated <0.3>");
		ImGui::Text("data");
		ImGui::End();
	}

	void drawGui()
	{
		// start new imgui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();

		drawMainMenu();
		



		
	}

	void Engine::runSyncronous() 
	{
		while (running) {

			bool res = this->window.Update();

			if (!running) {
				break;
			}
			drawGui();




			this->renderer.render();
		}

	}

	void handleResizeWindow()
	{
		rendererResizeWindow();
	}




}