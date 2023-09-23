#pragma once
class Wnd;
class MenuScene;
class SingleGameScene;

class App
{
private:
	Wnd* _wnd = nullptr;
	MenuScene* _menuScene = nullptr;
	SingleGameScene* _singleGameScene = nullptr;

public:
	App(HINSTANCE hInstance, int posX, int posY, int width, int height);
	~App();

	void MouseMoveEvent(int x, int y);
	void MouseClickEvent(int x, int y);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT	Dispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};