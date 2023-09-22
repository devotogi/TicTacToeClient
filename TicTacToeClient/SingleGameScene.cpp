#include "pch.h"
#include "SingleGameScene.h"
#include "Bitmap.h"
#include "Wnd.h"
#include "ResourceManager.h"
#include "D2D1Core.h"

SingleGameScene::SingleGameScene(Wnd* wnd)
{
	Bitmap* bitmap = D2D1Core::GetInstance()->LoadBitmapByFilename(wnd->GetPRT(), L"single.png");
	ResourceManager::InsertBitmap(static_cast<int>(BitmapName::SingGameBg), bitmap);
}

SingleGameScene::~SingleGameScene()
{
}

void SingleGameScene::Init(Wnd* _wnd)
{
}

void SingleGameScene::Update(Wnd* _wnd)
{
}

void SingleGameScene::Render(Wnd* _wnd)
{
	Scene::Render(_wnd);

	RECT rect;
	GetClientRect(_wnd->GetHWND(), &rect);
	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };

	_wnd->GetBRT()->DrawBitmap(ResourceManager::GetBitmap(static_cast<int>(BitmapName::SingGameBg))->GetBitmap());
}
