#pragma once
#include "window.h"
#include <d3d11.h>
#include <vector>
#include "Vector2.h"

namespace obvl
{

	struct Color {
		float r, g, b, a;
	};

	struct Vertex {
		float x, y, z;
		float u, v;
		Color color;
	};

	struct Vertex2D {
		float x, y;
		float u, v;
		Color color;
	};

	struct Shader {
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
	};

	void rendererResizeWindow();

	class Renderable {
		public:
			Renderable();
			~Renderable();

			Renderable::Renderable(const Renderable& other);

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

	struct Texture {
		float width = 0;
		float height = 0;
		ID3D11Texture2D* texture2D;
		ID3D11ShaderResourceView* texture;

		Texture(const Texture& other);

		Texture(float width, float height, ID3D11Texture2D* texture2D, ID3D11ShaderResourceView* texture);

		Texture();
	};

	class Sprite : public Renderable2D {
		public:
			Color color;

			Texture texture;

			Vector2 position;

			Sprite(Texture texture);
			Sprite();
			~Sprite();

			Sprite(const Sprite& other);

			void render();
	};	





	class Renderer {
		Window* window;


		// list of all staged renderables
		std::vector<Renderable*> renderables;

		public:
			Renderer(Window* window);

			Renderer();

			~Renderer();

			void addRenderable(Renderable* renderable);

			void removeRenderable(Renderable* renderable);

			void render();

			void clear();

			void present();

			void setRenderTarget();

			static void setVertexBuffer(Vertex* vertices, int size);



	};

}