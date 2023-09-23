#include "pch.h"
#include "D2D1Core.h"
#include "Bitmap.h"

D2D1Core* D2D1Core::_instance = nullptr;

void D2D1Core::Init()
{
	CoInitialize(NULL);
	CoCreateInstance(CLSID_WICImagingFactory, NULL,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_WICFactory));
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

void D2D1Core::CreateTextBoldFormat(IDWriteTextFormat** textFormat, const WCHAR* fontName, const FLOAT fontSize)
{
	_D2D1WriteFactory->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"en-us", textFormat);
	(*textFormat)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
}

void D2D1Core::CreateBrush(D2D1::ColorF color, ID2D1BitmapRenderTarget* rt, ID2D1SolidColorBrush** brush)
{
	rt->CreateSolidColorBrush(D2D1::ColorF(color), brush);
}

Bitmap* D2D1Core::LoadBitmapByFilename(ID2D1HwndRenderTarget** rt, const WCHAR* fileName)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = nullptr;
	_WICFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
	
	if (FAILED(hr))
		return nullptr;

	IWICBitmapFrameDecode* pFrame = nullptr;

	hr = pDecoder->GetFrame(0, &pFrame);

	if (FAILED(hr))
		return nullptr;

	BYTE* dataPtr = ConvertFrameToBitmap(pFrame);
	IWICFormatConverter* pConverter = nullptr;
	hr = _WICFactory->CreateFormatConverter(&pConverter);

	if (FAILED(hr))
		return nullptr;

	hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	UINT width = 0;
	UINT height = 0;
	pConverter->GetSize(&width, &height);

	if (FAILED(hr))
		return nullptr;

	ID2D1Bitmap* temp;
	hr = (*rt)->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		&temp
	);

	if (FAILED(hr))
		return nullptr;

	if (pConverter) pConverter->Release();
	if (pFrame) pFrame->Release();
	if (pDecoder) pDecoder->Release();

	Bitmap* b = new Bitmap(temp, dataPtr, width, height, 4);
	return b;
}

BYTE* D2D1Core::ConvertFrameToBitmap(IWICBitmapFrameDecode* frame)
{
	IWICBitmapSource* bitmapSource = frame;

	if (FAILED(WICConvertBitmapSource(GUID_WICPixelFormat32bppPBGRA, frame, &bitmapSource)))
	{
		// could not convert bitmap
		return nullptr;
	}

	UINT width = 0;
	UINT height = 0;

	if (FAILED(bitmapSource->GetSize(&width, &height)) || width == 0 || height == 0)
	{
		// could not get image size
		return nullptr;
	}

	const int buffSize = width * height * 4 /* bitCount */;
	BYTE* buffer = new BYTE[width * height * 4];

	if (FAILED(bitmapSource->CopyPixels(NULL, width * 4, buffSize, buffer)))
	{
		// could not get image size
		return nullptr;
	}

	bitmapSource->Release();
	return buffer;
}