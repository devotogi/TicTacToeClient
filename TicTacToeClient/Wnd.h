#pragma once
class App;

class Wnd
{
private:
	int _posX;
	int _posY;
	int _width;
	int _height;
	ID2D1HwndRenderTarget* _rt;
	ID2D1BitmapRenderTarget* _brt;
	IDWriteTextFormat* _textFormat;
	IDWriteTextFormat* _resultTextFormat;
	ID2D1SolidColorBrush* _red;
	ID2D1SolidColorBrush* _black;
	ID2D1SolidColorBrush* _white;
	ID2D1SolidColorBrush* _yellow;
	HWND _hWnd;

	int _mx;
	int _my;

public:
	Wnd(HINSTANCE hInstance, int posX, int posY, int width, int height, const WCHAR* title, const WCHAR* className, WNDPROC proc, App* app);
	~Wnd();

public:
	ID2D1BitmapRenderTarget* GetBRT() { return _brt; }
	ID2D1HwndRenderTarget* GetRT() { return _rt; }
	ID2D1HwndRenderTarget** GetPRT() { return &_rt; }
	ID2D1SolidColorBrush* GetBlackColor() { return _black; }
	ID2D1SolidColorBrush* GetRedColor() { return _red; }
	ID2D1SolidColorBrush* GetWhtieColor() { return _white; }
	ID2D1SolidColorBrush* GetYellowColor() { return _yellow; }
	IDWriteTextFormat* GetTextFormat() { return _textFormat; }
	IDWriteTextFormat* GetTextResultFormat() { return _resultTextFormat; }
	HWND GetHWND() { return _hWnd; }
	void DebugRender();
	void MouseMoveEvent(int x, int y);
};

