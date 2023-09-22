#pragma once
class Wnd;

class Scene
{
protected:

public:
	Scene() {};
	virtual ~Scene() { };

	virtual void	Init(Wnd* _wnd);
	virtual void	Update(Wnd* _wnd);
	virtual void	Render(Wnd* _wnd);
};

