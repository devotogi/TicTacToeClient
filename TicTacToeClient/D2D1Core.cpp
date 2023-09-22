#include "pch.h"
#include "D2D1Core.h"

D2D1Core* D2D1Core::_instance = nullptr;

void D2D1Core::Init()
{
	CoInitialize(NULL);
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_D2D1Factory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&_D2D1WriteFactory));
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

void D2D1Core::CreateTextFormat(IDWriteTextFormat** textFormat, const WCHAR* fontName, const FLOAT fontSize)
{
	_D2D1WriteFactory->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"en-us", textFormat);
}

void D2D1Core::CreateBrush(D2D1::ColorF color, ID2D1BitmapRenderTarget* rt, ID2D1SolidColorBrush** brush)
{
	rt->CreateSolidColorBrush(D2D1::ColorF(color), brush);
}
