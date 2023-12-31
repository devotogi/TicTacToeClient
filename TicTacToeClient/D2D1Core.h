#pragma once
class Bitmap;

class D2D1Core
{
private:
	static D2D1Core* _instance;
	ID2D1Factory* _D2D1Factory = nullptr;
	IDWriteFactory* _D2D1WriteFactory = nullptr;
	IWICImagingFactory* _WICFactory = nullptr;

private:
	BYTE* ConvertFrameToBitmap(IWICBitmapFrameDecode* frame);

public:
	static D2D1Core* GetInstance() 
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
	void CreateTextFormat(IDWriteTextFormat** textFormat, const WCHAR* fontName, const FLOAT fontSize);
	void CreateTextBoldFormat(IDWriteTextFormat** textFormat, const WCHAR* fontName, const FLOAT fontSize);
	void CreateBrush(D2D1::ColorF color, ID2D1BitmapRenderTarget* rt, ID2D1SolidColorBrush** brush);
	Bitmap* LoadBitmapByFilename(ID2D1HwndRenderTarget** rt, const WCHAR* fileName);
};

