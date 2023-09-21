#pragma once
class D2D1Core
{
private:
	static D2D1Core* _instance;
	ID2D1Factory* _D2D1Factory = nullptr;
	ID2D1RenderTarget* _D2D1Rt = nullptr;

public:
	D2D1Core* GetInstance() 
	{
		if (_instance == nullptr)
		{
			_instance = new D2D1Core();
		}
		
		return _instance;
	}

	void Init();
	void CreateRenderTarget(HWND hWnd, ID2D1HwndRenderTarget** rt);
	void CreateRenderTarget(ID2D1HwndRenderTarget* rt, ID2D1BitmapRenderTarget** crt);
};

