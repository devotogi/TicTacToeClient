#pragma once
class Wnd;
class MenuScene;
class SingleGameScene;
class TCPNetwork;
class UDPNetwork;
class LoadingScene;

class App
{
private:
	Wnd* _wnd = nullptr;
	MenuScene* _menuScene = nullptr;
	SingleGameScene* _singleGameScene = nullptr;
	LoadingScene* _loadingScene = nullptr;
	TCPNetwork* _tcpNetwork;
	UDPNetwork* _udpNetwork;

public:
	App(HINSTANCE hInstance, int posX, int posY, int width, int height, TCPNetwork* tcpNetwork, UDPNetwork* udpNetwork);
	~App();

	void MouseMoveEvent(int x, int y);
	void MouseClickEvent(int x, int y);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT	Dispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};