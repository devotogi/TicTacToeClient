#include "pch.h"
#include "Button.h"

Button::Button(UIType type, int x, int y, int width, int height) : UI(type,x,y,width,height)
{
}

Button::~Button()
{
}

bool Button::OnClick(int x, int y)
{
	int left = _x;
	int top = _y;
	int right = _x + _width;
	int bottom = _y + _height;

	if (x >= left && x <= right && y >= top && y <= bottom)
	{
		_clicked = true;
		return true;
	}
	else
	{
		_clicked = false;
		return false;
	}
}

bool Button::Clicked()
{
	if (_clicked)
	{
		_clicked = false;
		return true;
	}

	return false;
}
