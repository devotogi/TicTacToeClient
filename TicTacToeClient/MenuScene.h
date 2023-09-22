#pragma once
#include "Scene.h"
class Wnd;

class MenuScene : public Scene
{
private:


public:
	MenuScene();
	~MenuScene();

	virtual void	Init(Wnd* _wnd) override;
	virtual void	Update(Wnd* _wnd) override;
	virtual void	Render(Wnd* _wnd) override;
};

