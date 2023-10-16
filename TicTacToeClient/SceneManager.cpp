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
	ID2D1Bitmap* bitmap;
	wnd->GetBRT()->BeginDraw();
	wnd->GetBRT()->Clear(D2D1::ColorF(D2D1::ColorF::White));

	Scene* nowScene = GetScene();

	if (nowScene)
		nowScene->Render(wnd);

	wnd->DebugRender();

	wnd->GetBRT()->EndDraw();
	wnd->GetBRT()->GetBitmap(&bitmap);

	wnd->GetRT()->BeginDraw();

	RECT rect;
	GetClientRect(wnd->GetHWND(), &rect);
	D2D1_RECT_F rtDest = { rect.left, rect.top, rect.right, rect.bottom };
	if (bitmap)
		wnd->GetRT()->DrawBitmap(bitmap, rtDest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

	wnd->GetRT()->EndDraw();
}

void SceneManager::Add(int sceneType, Scene* scene)
{
	_scenes.insert({ sceneType , scene });
}

void SceneManager::ChangeScene(SceneType type, Wnd* wnd)
{
	_nowScene = static_cast<int>(type);
	GetScene()->Init(wnd);
}

void SceneManager::MouseClickEvent(int x, int y)
{
	Scene* nowScene = GetScene();

	if (nowScene)
		nowScene->MouseClickEvent(x, y);
}
