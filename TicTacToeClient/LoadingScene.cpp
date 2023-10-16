#include "pch.h"
#include "LoadingScene.h"
#include "Wnd.h"
#include "D2D1Core.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "Button.h"
#include "SceneManager.h"
#include "TCPNetwork.h"
#include "UDPNetwork.h"
LoadingScene::LoadingScene(Wnd* wnd)
{
	Bitmap* bitmap = D2D1Core::GetInstance()->LoadBitmapByFilename(wnd->GetPRT(), L"LoadingBg.png");
	ResourceManager::InsertBitmap(static_cast<int>(BitmapName::LoadingBg), bitmap);
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::Init(Wnd* _wnd)
{
	_wantPing = true;
}

void LoadingScene::Update(Wnd* _wnd)
{
	if (_wantPing) 
	{
		int currentTick = ::GetTickCount64();
		int deltaTick = currentTick - _wantLastTick;

		_wantSumTick += deltaTick;

		if (_wantLastTick > 1000) 
		{
			_wantSumTick = 0;
			// TCP에 방잡아달라고 요청 보내기
			{
				char sendBuffer[1000] = { 0 };
				char* bufferPtr = (char*)sendBuffer;

				*(__int16*)bufferPtr = 4;				bufferPtr += 2; // packetSize
				*(__int16*)bufferPtr = C2S_CLIENTREADY; bufferPtr += 2; // packetType

				SceneManager::GetInstance()->GetTCP()->Send(sendBuffer, 4);
			}
		}
		_wantLastTick = currentTick;
	}
}

void LoadingScene::Render(Wnd* _wnd)
{
	Scene::Render(_wnd);

	RECT rect;
	GetClientRect(_wnd->GetHWND(), &rect);
	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };

	_wnd->GetBRT()->DrawBitmap(ResourceManager::GetBitmap(static_cast<int>(BitmapName::LoadingBg))->GetBitmap());
	WCHAR text[1000] = { 0 };
	swprintf_s(text, _countof(text), L"%d%%", _percent);
	_wnd->GetBRT()->DrawTextW(text, wcslen(text), _wnd->GetTextResultFormat(), D2D1::RectF(330.f, 311.f, 649, 391.f), _wnd->GetWhtieColor());
}

void LoadingScene::MouseClickEvent(int x, int y)
{

}
