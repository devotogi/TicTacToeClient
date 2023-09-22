#pragma once
#include "Scene.h"
class Bitmap;

class SingleGameScene : public Scene
{
private:
	Bitmap* _menuBitmap = nullptr;

public:
	SingleGameScene(Wnd* wnd);
	~SingleGameScene();

	virtual void	Init(Wnd* _wnd) override;
	virtual void	Update(Wnd* _wnd) override;
	virtual void	Render(Wnd* _wnd) override;
};