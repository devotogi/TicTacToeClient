#include "pch.h"
#include "MenuScene.h"
#include "Wnd.h"
#include "D2D1Core.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "Button.h"
#include "SceneManager.h"
MenuScene::MenuScene(Wnd* wnd)
{
	Bitmap* bitmap = D2D1Core::GetInstance()->LoadBitmapByFilename(wnd->GetPRT(), L"menuBg.png");
	ResourceManager::InsertBitmap(static_cast<int>(BitmapName::MenuBg), bitmap);

	_button = new Button(SingleGameBtn,325,353,322,72);
}

MenuScene::~MenuScene()
{
	ResourceManager::RemoveBitmap(static_cast<int>(BitmapName::MenuBg));
	if (_button)
		delete _button;
}

void MenuScene::Init(Wnd* _wnd)
{
}

void MenuScene::Update(Wnd* _wnd)
{
	if (_button->Clicked())
	{
		SceneManager::GetInstance()->ChangeScene(SceneType::SingelGame, _wnd);
	}
}

void MenuScene::Render(Wnd* _wnd)
{
	Scene::Render(_wnd);

	RECT rect;
	GetClientRect(_wnd->GetHWND(), &rect);
	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };

	_wnd->GetBRT()->DrawBitmap(ResourceManager::GetBitmap(static_cast<int>(BitmapName::MenuBg))->GetBitmap());
}

void MenuScene::MouseClickEvent(int x, int y)
{
	_button->OnClick(x, y);
}
