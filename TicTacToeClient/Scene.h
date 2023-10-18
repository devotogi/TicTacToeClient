#pragma once
class Wnd;

class Scene
{
protected:
	SceneType _sceneType;

public:
	Scene(SceneType sceneType) : _sceneType(sceneType) {};
	virtual ~Scene() { };

	SceneType		GetSceneType() { return _sceneType; }

	virtual void	Init(Wnd* _wnd);
	virtual void	Update(Wnd* _wnd);
	virtual void	Render(Wnd* _wnd);
	virtual void	MouseClickEvent(int x, int y);
	virtual void	Clear(Wnd* _wnd);
};

