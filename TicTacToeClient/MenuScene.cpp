#include "pch.h"
#include "MenuScene.h"
#include "Wnd.h"
#include "D2D1Core.h"
#include "ResourceManager.h"

MenuScene::MenuScene(Wnd* wnd)
{
	Bitmap* bitmap = D2D1Core::GetInstance()->LoadBitmapByFilename(wnd->GetPRT(), L"menuBg.png");
	ResourceManager::InsertBitmap(static_cast<int>(BitmapName::MenuBg), bitmap);
}

MenuScene::~MenuScene()
{
	ResourceManager::RemoveBitmap(static_cast<int>(BitmapName::MenuBg));
}

void MenuScene::Init(Wnd* _wnd)
{
}

void MenuScene::Update(Wnd* _wnd)
{
}

void MenuScene::Render(Wnd* _wnd)
{
	Scene::Render(_wnd);
}
