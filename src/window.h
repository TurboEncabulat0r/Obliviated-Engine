#pragma once
#include <windows.h>
#include "definition.h"
#include <d3d11.h>

namespace obvl
{
	// forward renderinformation struct
	
	struct RenderInformation;

	class Window;

	class Window {
		WNDCLASSEXW wc;
		HWND m_hwnd;
		char* m_title;
		int m_width;
		int m_height;
		bool m_isRunning;

		void handleWindowQuit();


	public:

		Window(char* title, int width, int height);

		Window();

		~Window();

		HWND* getHandle();

		bool Initialize();

		void setTitle(char* title);

		char* getTitle();

		void setDimentions(const int width, const int height);

		void setHandle(HWND* hwnd);

		WNDCLASSEXW* getClass();

		void setClass(WNDCLASSEXW* wc);

		void Update();

		void close();

		void setOnQuit(fn* onQuit);

		RenderInformation getRenderInformation();


	};


	struct RenderInformation {
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
		IDXGISwapChain* swapChain;
		ID3D11RenderTargetView* renderTargetView;
	};

}