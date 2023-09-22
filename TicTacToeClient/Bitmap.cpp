#include "pch.h"
#include "Bitmap.h"

Bitmap::~Bitmap()
{
	if (_dataPtr)
		delete[] _dataPtr;
}
