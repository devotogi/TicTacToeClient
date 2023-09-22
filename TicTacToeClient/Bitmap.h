#pragma once
class Bitmap
{
private:
	ID2D1Bitmap* _bitmap;
	int	_width;
	int _height;
	int _bitCount;
	BYTE* _dataPtr = nullptr;
	WCHAR _fileName[256] = {0};

public:
	Bitmap(ID2D1Bitmap* bitmap) : _bitmap(bitmap) {};
	Bitmap(ID2D1Bitmap* bitmap, BYTE* dataPtr, int width, int height, int bitCount) : _bitmap(bitmap), _dataPtr(dataPtr), _width(width), _height(height), _bitCount(bitCount) {};
	~Bitmap();

	WCHAR* GetFileName() { return _fileName; }
	int	GetBitCount() { return _bitCount; };
	ID2D1Bitmap* GetBitmap() { return _bitmap; };
	BYTE* GetMemory() { return _dataPtr; };
	int	GetWidht() { return _width; };
	int	GetHeight() { return _height; };
};

