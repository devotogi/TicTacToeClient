#include "pch.h"
#include "D2D1Core.h"

D2D1Core* D2D1Core::_instance = nullptr;

void D2D1Core::Init()
{
	CoInitialize(NULL);
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_D2D1Factory);
}

void D2D1Core::CreateRenderTarget(HWND hWnd, ID2D1HwndRenderTarget** rt)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	_D2D1Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE),
		D2D1::HwndRenderTargetProperties(hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		rt
	);
}

void D2D1Core::CreateRenderTarget(ID2D1HwndRenderTarget* rt, ID2D1BitmapRenderTarget** crt)
{
	rt->CreateCompatibleRenderTarget(crt);
}
