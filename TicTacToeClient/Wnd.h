#pragma once
class Wnd
{
private:
	int _posX;
	int _posY;
	int _width;
	int _height;
	HWND _hWnd;

public:
	Wnd(HINSTANCE hInstance, int posX, int posY, int width, int height, const WCHAR* title, const WCHAR* className, WNDPROC proc);
	~Wnd();
};

