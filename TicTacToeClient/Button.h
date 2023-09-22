#pragma once
#include "UI.h"
class Button : public UI
{
private:

public:
	Button(UIType type, int x, int y, int width, int height);
	~Button();
};

