#pragma once
class Wnd;

class App
{
private:
	Wnd* _wnd;
	
public:
	App(HINSTANCE hInstance, int posX, int posY, int width, int height);
	~App();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

