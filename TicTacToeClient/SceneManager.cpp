#include "pch.h"
#include "SceneManager.h"
#include "Wnd.h"
#include "Scene.h"

SceneManager* SceneManager::_instance = nullptr;

Scene* SceneManager::GetScene()
{
	Scene* ret = nullptr;

	auto it = _scenes.find(_nowScene);
	
	if (it != _scenes.end())
		ret = it->second;

	return ret;
}

void SceneManager::Update(Wnd* wnd)
{
	Scene* nowScene = GetScene();
	
	if (nowScene)
		nowScene->Update(wnd);
}

void SceneManager::Render(Wnd* wnd)
{
	Scene* nowScene = GetScene();

	if (nowScene)
		nowScene->Render(wnd);
}
