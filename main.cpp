#include <memory>
#include <stdexcept>
#include <vector>
#include <iostream>

#include <windows.h>
#include <shellscalingapi.h>

#include <GL/glew.h>
#include <gl/gl.h>

#include <glm/glm.hpp>

#include "ogl/oglHelpers.hpp"

#include "tools/utility.hpp"
#include "tools/glmHelpers.hpp"

const bool fullScreen = false;
const bool console = true;
const glm::ivec2 windowRes = { 1600, 1600 };

glm::ivec2 mousePos{ 0 };
glm::ivec2 mouseDelta{ 0 };
bool rmb = false;
bool lmb = false;
bool mmb = false;
bool xmb1 = false;
bool xmb2 = false;
int mouseWheel = 0;

glm::ivec2 windowLocation{ 0 };
glm::ivec2 windowCenter{ 0 };
glm::ivec2 windowSize{ 0 };

void OGLInitialize()
{
	const GLenum glewInitResult = glewInit();
	assert(GLEW_OK == glewInitResult);

	Tools::VSync(true);
	glEnable(GL_CULL_FACE);
}

void Initialize()
{
	if (console) Tools::RedirectIOToConsole({ 2000, 10 });
	Tools::RandomInit();
	OGLInitialize();
}

void RenderScene()
{
	const glm::vec4 clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PrepareFrame()
{
	RenderScene();
}

void HandleKeyboard(bool const* const keys)
{
}

void ResetMousePosition()
{
	Tools::SetMousePos(windowCenter);
	mousePos = windowCenter;
}

void HandleMouse()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	const auto prevMousePos = ::mousePos;
	::mousePos = { mousePos.x, mousePos.y };
	mouseDelta = ::mousePos - prevMousePos;

	ResetMousePosition();
}

void ChangeWindowSize(glm::ivec2 size)
{
	windowSize = size;
	windowCenter = { windowLocation + windowSize / 2 };

	glViewport(0, 0, size.x, size.y);
}

void ChangeWindowLocation(glm::ivec2 location)
{
	windowLocation = location;
	windowCenter = { location + windowSize / 2 };
}

void SetDCPixelFormat(HDC hDC);

static bool keys[256];
static bool quit;
static bool focus;
static bool resetMousePositionRequired;
static HDC hDC;

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	static HGLRC hRC;

	switch(message)
	{
		case WM_CREATE:
		{
			hDC = GetDC(hWnd);
			SetDCPixelFormat(hDC);
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);
			try
			{
				Initialize();
			}
			catch (const std::runtime_error & error)
			{
				MessageBox(nullptr, error.what(), "Runtime error",
					MB_OK | MB_ICONEXCLAMATION);
				ExitProcess(0);
			}
			break;
		}
		case WM_DESTROY:
			wglMakeCurrent(hDC, nullptr);
			wglDeleteContext(hRC);
			PostQuitMessage(0);
			quit = true;
			break;
		case WM_SIZE:
		{
			const glm::ivec2 size{ LOWORD(lParam), HIWORD(lParam) };
			ChangeWindowSize(size);
			break;
		}
		case WM_MOVE:
		{
			const glm::ivec2 location{ LOWORD(lParam), HIWORD(lParam) };
			ChangeWindowLocation(location);
			break;
		}
		case WM_SETFOCUS:
			ShowCursor(false);
			focus = true;
			resetMousePositionRequired = true;
			break;
		case WM_KILLFOCUS:
			ShowCursor(true);
			focus = false;
			break;
		case WM_KEYDOWN:
			keys[wParam] = true;
			break;
		case WM_KEYUP:
			keys[wParam] = false;
			break;
		case WM_RBUTTONDOWN:
			rmb = true;
			break;
		case WM_RBUTTONUP:
			rmb = false;
			break;
		case WM_LBUTTONDOWN:
			lmb = true;
			break;
		case WM_LBUTTONUP:
			lmb = false;
			break;
		case WM_MBUTTONDOWN:
			mmb = true;
			break;
		case WM_MBUTTONUP:
			mmb = false;
			break;
		case WM_XBUTTONDOWN:
			switch (HIWORD(wParam))
			{
				case XBUTTON1: xmb1 = true; break;
				case XBUTTON2: xmb2 = true; break;
			}
			break;
		case WM_XBUTTONUP:
			switch (HIWORD(wParam))
			{
				case XBUTTON1: xmb1 = false; break;
				case XBUTTON2: xmb2 = false; break;
			}
			break;
		case WM_MOUSEWHEEL:
			if ((int)wParam > 0) ++mouseWheel;
			else if ((int)wParam < 0) --mouseWheel;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0l;
}

void SetDCPixelFormat(HDC hDC)
{
	const PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0, 0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	const int pixelFormt = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormt, &pfd);
}

int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	const LPCTSTR lpszAppName = "OpenGL window";
	const int winPosX = 10, winPosY = 10;

	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = lpszAppName;
	
	if(!RegisterClass(&wc))
	{
		MessageBox(nullptr, "Window class registration failed.", "Error",
			MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	HWND hWnd = CreateWindow(
		lpszAppName,
		lpszAppName,
		fullScreen ? WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP | WS_MAXIMIZE : 
		WS_OVERLAPPEDWINDOW,
		winPosX, winPosY,
		windowRes.x, windowRes.y,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if(!hWnd)
	{
		MessageBox(nullptr, "Window creation failed.", "Error",
			MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	
	MSG msg{};

	while (!keys[VK_ESCAPE] && !quit)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(focus)
		{
			if (resetMousePositionRequired)
			{
				ResetMousePosition();
				resetMousePositionRequired = false;
			}
			HandleKeyboard(keys);
			HandleMouse();
			PrepareFrame();

			glFinish(); //It helps with stuttering in some scenarios.
			SwapBuffers(hDC);
		}
	}
	
	return (int)msg.wParam;
}
