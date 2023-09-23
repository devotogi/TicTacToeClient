#pragma once
#include "UI.h"
class Button : public UI
{
private:
	bool _clicked = false;
public:
	Button(UIType type, int x, int y, int width, int height);
	~Button();

	bool OnClick(int x, int y);
	bool Clicked();
};

