#pragma once
class Wnd;
class Scene;

class SceneManager
{
private:
	static SceneManager* _instance;
	map<int, Scene*> _scenes;
	int	_nowScene = 0;

public:
	static SceneManager* GetInstance() 
	{
		if (_instance == nullptr)
			_instance = new SceneManager();

		return _instance;
	}
	
	Scene* GetScene();
	void Update(Wnd* wnd);
	void Render(Wnd* wnd);
	void Add(int sceneType, Scene* scene);
};

