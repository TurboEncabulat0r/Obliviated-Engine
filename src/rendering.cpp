#include "rendering.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>


namespace obvl {

	Renderable::Renderable()
	{
	}

	Renderable::Renderable(const Renderable& other)
	{
	}

	Renderable::~Renderable()
	{
	}

	void Renderable::render()
	{
	}

	Renderer::Renderer(Window* window)
	{
		this->window = window;
		RenderInformation renderInformation = window->getRenderInformation();
		this->device = renderInformation.device;
		this->deviceContext = renderInformation.deviceContext;
		this->swapChain = renderInformation.swapChain;
		this->renderTargetView = renderInformation.renderTargetView;
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::render()
	{
		// clear the back buffer to a deep blue
		float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
		deviceContext->ClearRenderTargetView(renderTargetView, color);

		// render all renderables
		for (int i = 0; i < renderables.size(); i++) {
			renderables[i]->render();
		}

		// swap the back buffer and the front buffer
		swapChain->Present(0, 0);
	}
}


