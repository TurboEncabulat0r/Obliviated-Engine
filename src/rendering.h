#pragma once
#include "window.h"
#include <d3d11.h>
#include <vector>

namespace obvl
{


	class Renderable {
		public:
			virtual void render() = 0;
	};

	class Renderable2D : public Renderable {
		public:
			virtual void render() = 0;
	};

	class Renderable3D : public Renderable {
		public:
			virtual void render() = 0;
	};

	struct Vertex {
		float x, y, z;
	};

	struct Color {
		float r, g, b, a;
	};

	struct Texture {
		ID3D11ShaderResourceView* texture;
	};

	struct Vertex2D {
		float x, y;
	};

	struct Shader {
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
	};

	// renderer base class for all renderers
	class Renderer {
		Window* window;
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
		IDXGISwapChain* swapChain;
		ID3D11RenderTargetView* renderTargetView;
		ID3D11Buffer* vertexBuffer;

		// list of all staged renderables
		std::vector<Renderable*> renderables;

		public:
			Renderer(Window* window);

			~Renderer();

			void addRenderable(Renderable* renderable);

			void removeRenderable(Renderable* renderable);

			void render();

			void clear();

			void present();

			void setRenderTarget();

			void setVertexBuffer(Vertex* vertices, int size);



	};

}