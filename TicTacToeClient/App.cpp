#include "pch.h"
#include "App.h"
#include "Wnd.h"
#include "FPSManager.h"
#include "SceneManager.h"
#include "D2D1Core.h"

static WCHAR szWindowClass[] = L"TicTacToeClient";
static WCHAR szTitle[] = L"TicTacToeClient";

App::App(HINSTANCE hInstance, int posX, int posY, int width, int height)
{
    _wnd = new Wnd(hInstance,0,0,700,700, szTitle, szWindowClass, WndProc);

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (FPSManager::GetInstnace()->Ok())
		{
			SceneManager::GetInstance()->Update(_wnd);
			SceneManager::GetInstance()->Render(_wnd);
		}
		Sleep(1);
	}
}

App::~App()
{
    if (_wnd)
        delete _wnd;
}

LRESULT App::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static bool GameEnd;
	MSG msg; // ¸Þ¼¼Áö °´Ã¼
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}
