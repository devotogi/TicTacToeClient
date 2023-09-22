#pragma once
class UI
{
protected:
	UIType _type;
	int _x;
	int _y;
	int _width;
	int _height;

public:
	UI(UIType type, int x, int y, int width, int height) : _type(type), _x(x), _y(y), _width(width), _height(height) {};
	~UI() {};

	bool OnClick(int x, int y);
};

