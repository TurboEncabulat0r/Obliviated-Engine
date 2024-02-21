#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <d3d11.h>
#include "window.h"
#include "helpers.h"
#include "engine.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace obvl {
	MSG msg;
	static UINT g_ResizeWidth = 0, g_ResizeHeight = 0;
	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


	static ID3D11Device* g_pd3dDevice;
	static ID3D11DeviceContext* g_pd3dDeviceContext;

	static IDXGISwapChain* g_pSwapChain;
	static ID3D11Texture2D* pBackBuffer;
	static ID3D11RenderTargetView* g_mainRenderTargetView;

	Window* mainWindow;

	fn* onQuitSubs[10] = {};
	int quitIndex = 0;
	void quit(fn* f) {
		onQuitSubs[quitIndex] = f;
		quitIndex++;

	}

	void invokeOnQuit() {
		for (int i = 0; i < 10; i++) {
			if (onQuitSubs[i] != nullptr)
				onQuitSubs[i]();
		}
	}


	void Window::handleWindowQuit()
	{
		invokeOnQuit();
		
		// delets everything and cleans memory up
		close();

		return;

	}

	void Window::setOnQuit(fn* onQuit)
	{
		quit(onQuit);
	}

	Window::Window()
	{
		m_hwnd = NULL;
		m_width = 0;
		m_height = 0;
		m_title = "";

		ZeroMemory(&msg, sizeof(MSG));

		this->Initialize();
	}

	Window::Window(char* title, int width, int height)
	{
		m_hwnd = NULL;
		m_width = width;
		m_height = height;
		m_title = title;
		
		ZeroMemory(&msg, sizeof(MSG));

		this->Initialize();
	}

	Window::~Window()
	{
	}

	void CleanupRenderTarget()
	{
		if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
	}

	void CreateRenderTarget()
	{
		
		g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
		pBackBuffer->Release();
	}

	bool Window::Update()
	{
		while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			if (msg.message == WM_QUIT) {
				handleWindowQuit();
				return false;
			}

			if (msg.message == WM_KEYDOWN) {
				
			}

			if (msg.message == WM_KEYUP) {

			}
		}
		

		if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
		{
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
			g_ResizeWidth = g_ResizeHeight = 0;
			CreateRenderTarget();
			handleResizeWindow();
		}

		return true;
		
	}

	void Window::setTitle(char* title)
	{
		m_title = title;
	}

	char* Window::getTitle()
	{
		return m_title;
	}

	void Window::setDimentions(const int width, const int height)
	{
		m_width = width;
		m_height = height;
	}

	void Window::setHandle(HWND* hwnd)
	{
		m_hwnd = *hwnd;
	}

	HWND* Window::getHandle()
	{
		return &m_hwnd;
	}

	WNDCLASSEXW* Window::getClass()
	{
		return &wc;
	}

	void Window::setClass(WNDCLASSEXW* wc)
	{
		this->wc = *wc;
	}

	RenderInformation Window::getRenderInformation()
	{
		RenderInformation renderInformation;
		renderInformation.device = g_pd3dDevice;
		renderInformation.deviceContext = g_pd3dDeviceContext;
		renderInformation.swapChain = g_pSwapChain;
		renderInformation.renderTargetView = g_mainRenderTargetView;
		return renderInformation;
	}


	void getDeviceAndContext(RenderInformation* renderInformation)
	{
		renderInformation->device = g_pd3dDevice;
		renderInformation->deviceContext = g_pd3dDeviceContext;
		renderInformation->swapChain = g_pSwapChain;
		renderInformation->renderTargetView = g_mainRenderTargetView;
	}



	bool CreateDeviceD3D(HWND hwnd) 
	{
		// Setup swap chain
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
		HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
		if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
			res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
		if (res != S_OK)
			return false;

		CreateRenderTarget();
		return true;
	}


	void CleanupDeviceD3D()
	{
		CleanupRenderTarget();
		if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
		if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
		if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
	}

	

	void Window::close()
	{
		// Cleanup
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		CleanupDeviceD3D();
		::DestroyWindow(m_hwnd);
		::UnregisterClassW(wc.lpszClassName, wc.hInstance);
	}

	bool Window::Initialize()
	{
		wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, CharToLPWSTR(m_title), nullptr};
		::RegisterClassExW(&wc);
		m_hwnd = ::CreateWindowW(wc.lpszClassName, CharToLPWSTR(m_title), WS_OVERLAPPEDWINDOW, 100, 100, m_width, m_height, nullptr, nullptr, wc.hInstance, nullptr);

		// Initialize Direct3D
		if (!CreateDeviceD3D(m_hwnd))
		{
			CleanupDeviceD3D();
			::UnregisterClassW(wc.lpszClassName, wc.hInstance);
			return false;
		}

		// Show the window
		::ShowWindow(m_hwnd, SW_SHOWDEFAULT);
		::UpdateWindow(m_hwnd);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(m_hwnd);
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
		mainWindow = this;
		return true;
	}

	

	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_SIZE:
			if (wParam == SIZE_MINIMIZED)
				return 0;
			g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
			g_ResizeHeight = (UINT)HIWORD(lParam);
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_DESTROY:
			mainWindow->handleWindowQuit();
			return 0;
		case WM_DPICHANGED:
			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
			{
				//const int dpi = HIWORD(wParam);
				//printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
				const RECT* suggested_rect = (RECT*)lParam;
				::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
			}
			break;
		}
		return ::DefWindowProcW(hWnd, msg, wParam, lParam);
	}

}

