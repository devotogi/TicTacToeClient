#pragma once
#include "Scene.h"
class Bitmap;
class Wnd;
class Button;

class MenuScene : public Scene
{
private:
	Bitmap* _menuBitmap = nullptr;
	Button* _singleGameBtn = nullptr;
	Button* _multiGameBtn = nullptr;

public:
	MenuScene(Wnd* wnd);
	~MenuScene();

	virtual void	Init(Wnd* _wnd) override;
	virtual void	Update(Wnd* _wnd) override;
	virtual void	Render(Wnd* _wnd) override;
	virtual void	MouseClickEvent(int x, int y) override;
	virtual void	Clear(Wnd* wnd) override;
};