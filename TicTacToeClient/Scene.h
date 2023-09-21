#pragma once
class Wnd;

class Scene
{
private:
	Scene() {};
	virtual ~Scene() { };

public:
	virtual void	Init(Wnd* _wnd) abstract;
	virtual void	Update(Wnd* _wnd) abstract;
	virtual void	Render(Wnd* _wnd) abstract;
};

