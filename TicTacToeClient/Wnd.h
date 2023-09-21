#pragma once
class Wnd
{
private:
	int _posX;
	int _posY;
	int _width;
	int _height;
	ID2D1HwndRenderTarget* _rt;
	ID2D1BitmapRenderTarget* _brt;
	HWND _hWnd;

public:
	Wnd(HINSTANCE hInstance, int posX, int posY, int width, int height, const WCHAR* title, const WCHAR* className, WNDPROC proc);
	~Wnd();
};

