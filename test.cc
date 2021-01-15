#include "base.hh"

#include <windows.h>


#include "asset/image.hh"
#include "asset/model.hh"

#include "io/reader.hh"
#include "io/writer.hh"

#include "video/base/device.hh"
#include "video/base/shader.hh"
#include "video/base/vertex.hh"



#include <sstream>
#include <iostream>

#define WINDOW_X CW_USEDEFAULT
#define WINDOW_Y CW_USEDEFAULT
#define WINDOW_W 800
#define WINDOW_H 600

LRESULT CALLBACK Proc(HWND, UINT, WPARAM, LPARAM);
HRESULT CALLBACK Init(HWND);

int main()
{
	WNDCLASS g_class = {};

	g_class.lpfnWndProc   = Proc;
	g_class.lpszClassName = TEXT("render_window");
	g_class.hInstance     = GetModuleHandle(NULL);

	if (!RegisterClass(&g_class))
	{
		
		//!
		//!

		return LOG_FAIL("Failed to RegisterClass()"), EXIT_FAILURE;
	}

	PIXELFORMATDESCRIPTOR l_pfd =
	{
		sizeof PIXELFORMATDESCRIPTOR, 1, PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL, PFD_TYPE_RGBA,
		24, 0, 0, 0, 0, 0, 0, 8, 0,
		 0, 0, 0, 0, 0,
		 0, 0, 0,
		PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	HWND l_hwnd = CreateWindow(TEXT("render_window"), TEXT("D3D11"), WS_VISIBLE,
		WINDOW_X, WINDOW_Y,
		WINDOW_W, WINDOW_H, NULL, NULL, NULL, NULL);

	if (!l_hwnd)
	{
		return LOG_FAIL("Cannot open window"), EXIT_FAILURE;
	}

	HDC l_hdc = GetDC(l_hwnd);

	if (!SetPixelFormat(l_hdc, ChoosePixelFormat(l_hdc, &l_pfd), &l_pfd))
	{
		//!
		//!

		return LOG_FAIL("Failed to SetPixelFormat()"), EXIT_FAILURE;
	}

	HGLRC l_glc = wglCreateContext(l_hdc);

	if (wglMakeCurrent(l_hdc, l_glc))
	{
		shape::video::cBaseDevice{}.init();
	}

	shape::video::cBaseVertex l_vertex;

	if (l_vertex.init())
	{
		l_vertex.enable_nor();
		l_vertex.enable_tex();
		l_vertex.enable_skn();
	}

	//!
	//! TEST HACK
	//!

	MSG l_msg;
	INT l_run = TRUE;

	glClearColor(1, 0, 0, 0);

	do
	{
		while(PeekMessage(&l_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (l_msg.message == WM_QUIT)
			{
				l_run = FALSE;
			}

			 DispatchMessage(&l_msg);
			TranslateMessage(&l_msg);
		}

		glClear(GL_COLOR_BUFFER_BIT);

		SwapBuffers(l_hdc);
	} while(l_run);



	return 0;
}

LRESULT CALLBACK Proc(HWND a, UINT b, WPARAM c, LPARAM d)
{
	if (b == WM_CLOSE)
	{
		PostQuitMessage(0);
	}

	//!
	//!

	return DefWindowProc(a, b, c, d);
}
