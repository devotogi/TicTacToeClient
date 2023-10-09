#include "pch.h"
#include "App.h"
#include "Wnd.h"
#include "FPS.h"
#include "SceneManager.h"
#include "D2D1Core.h"
#include "MenuScene.h"
#include "SingleGameScene.h"
#include "ResourceManager.h"
#include "TCPNetwork.h"
#include "PacketHandler.h"

static WCHAR szWindowClass[] = L"TicTacToeClient";
static WCHAR szTitle[] = L"TicTacToeClient";

App::App(HINSTANCE hInstance, int posX, int posY, int width, int height)
{
	TCPNetwork tcpNetwork;

    _wnd = new Wnd(hInstance,0,0,976,579, szTitle, szWindowClass, WndProc, this);
	
	_menuScene = new MenuScene(_wnd);
	_singleGameScene = new SingleGameScene(_wnd);

	SceneManager::GetInstance()->Add(static_cast<int>(SceneType::Menu), reinterpret_cast<Scene*>(_menuScene));
	SceneManager::GetInstance()->Add(static_cast<int>(SceneType::SingelGame), reinterpret_cast<Scene*>(_singleGameScene));


	Bitmap* p1o = D2D1Core::GetInstance()->LoadBitmapByFilename(_wnd->GetPRT(), L"P1O.png");
	ResourceManager::InsertBitmap(static_cast<int>(BitmapName::P1OBg), p1o);

	Bitmap* p2x = D2D1Core::GetInstance()->LoadBitmapByFilename(_wnd->GetPRT(), L"P2X.png");
	ResourceManager::InsertBitmap(static_cast<int>(BitmapName::P2XBg), p2x);
	FPS fps;

	MSG msg;
	while (true)
	{
		tcpNetwork.Recv();

		while (PacketQueue::GetInstance()->GetQueue().empty() == false)
		{
			shared_ptr<Packet> packet = PacketQueue::GetInstance()->GetQueue().front();
			PacketQueue::GetInstance()->GetQueue().pop();

			PacketHandler::HandlePacket(packet);
		}

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (fps.Ok())
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

	if (_menuScene)
		delete _menuScene;
}

void App::MouseMoveEvent(int x, int y)
{
	_wnd->MouseMoveEvent(x, y);
}

void App::MouseClickEvent(int x, int y)
{
	SceneManager::GetInstance()->MouseClickEvent(x, y);
}

LRESULT App::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	App* pApp = nullptr;

	if (message == WM_NCCREATE)
	{
		LPCREATESTRUCT pCS = (LPCREATESTRUCT)lParam;
		SetLastError(0);
		pApp = reinterpret_cast<App*>(pCS->lpCreateParams);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp)))
		{
			if (GetLastError() != 0) return E_FAIL;
		}
	}
	else
	{
		pApp = reinterpret_cast<App*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (message == WM_GETMINMAXINFO && pApp == nullptr)
		return S_OK;

	return pApp->Dispatch(hWnd, message, wParam, lParam);
}

LRESULT App::Dispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_KEYUP:
		break;

	case WM_KEYDOWN:
		break;

	case WM_CHAR:
		break;

	case WM_TIMER:
		break;

	case WM_SIZE:
		break;

	case WM_COMMAND:
		break;

	case WM_LBUTTONDOWN:
		MouseClickEvent(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_MOUSEMOVE:
		MouseMoveEvent(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_LBUTTONUP:
		break;

	case WM_MOUSEWHEEL:
		break;

	case WM_VSCROLL:
		break;

	case WM_PAINT:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}
