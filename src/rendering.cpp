#include "rendering.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>


namespace obvl {

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Buffer* vertexBuffer;

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
		device = renderInformation.device;
		deviceContext = renderInformation.deviceContext;
		swapChain = renderInformation.swapChain;
		renderTargetView = renderInformation.renderTargetView;
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

	void Renderer::addRenderable(Renderable* renderable)
	{
		renderables.push_back(renderable);
	}

	void Renderer::removeRenderable(Renderable* renderable)
	{
		for (int i = 0; i < renderables.size(); i++) {
			if (renderables[i] == renderable) {
				renderables.erase(renderables.begin() + i);
				return;
			}
		}
	}

	void Renderer::clear()
	{
		renderables.clear();
	}

	void Renderer::present()
	{
		swapChain->Present(0, 0);
	}

	Renderer::Renderer()
	{

	}

	void Renderer::setRenderTarget()
	{
		deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);
	}

	void Renderer::setVertexBuffer(Vertex* vertices, int size)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vertex) * size;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;
		device->CreateBuffer(&bd, &InitData, &vertexBuffer);

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	Texture::Texture(float width, float height, ID3D11Texture2D* texture2D, ID3D11ShaderResourceView* texture) {
		this->width = width;
		this->height = height;
		this->texture2D = texture2D;
		this->texture = texture;
	}

	Texture::Texture(const Texture& other)
	{
		width = other.width;
		height = other.height;
		texture2D = other.texture2D;
		texture = other.texture;
	}

	Texture::Texture()
	{
	}

	Sprite::Sprite()
	{
		this->texture = Texture(0, 0, NULL, NULL);
		this->position = Vector2(0, 0);
	}


	Sprite::Sprite(Texture texture)
	{
		this->texture = texture;
		this->position = Vector2(0, 0);
	}

	Sprite::~Sprite()
	{
	}

	Sprite::Sprite(const Sprite& other)
	{
		texture = other.texture;
		position = other.position;
	}

	void Sprite::render()
	{
		// set the vertex buffer
		Vertex vertices[] =
		{
			{ position.x, position.y, 0.0f, 0.0f, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f} },
			{ position.x + texture.width, position.y, 0.0f, 1.0f, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f} },
			{ position.x, position.y + texture.height, 0.0f, 0.0f, 1.0f, {1.0f, 1.0f, 1.0f, 1.0f} },
			{ position.x, position.y + texture.height, 0.0f, 0.0f, 1.0f, {1.0f, 1.0f, 1.0f, 1.0f} },
			{ position.x + texture.width, position.y, 0.0f, 1.0f, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f} },
			{ position.x + texture.width, position.y + texture.height, 0.0f, 1.0f, 1.0f, {1.0f, 1.0f, 1.0f, 1.0f} }
		};
		Renderer::setVertexBuffer(vertices, 6);

		// set the texture

		deviceContext->PSSetShaderResources(0, 1, &texture.texture);

		// draw the sprite
		deviceContext->Draw(6, 0);
	}



}


