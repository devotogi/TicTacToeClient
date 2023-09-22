#pragma once
#include "Scene.h"
class Bitmap;
class Wnd;

class MenuScene : public Scene
{
private:
	Bitmap* _menuBitmap = nullptr;

public:
	MenuScene(Wnd* wnd);
	~MenuScene();

	virtual void	Init(Wnd* _wnd) override;
	virtual void	Update(Wnd* _wnd) override;
	virtual void	Render(Wnd* _wnd) override;
};

