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
#include "DataManager.h"
#include "Session.h"
LoadingScene::LoadingScene(Wnd* wnd)
{
	Bitmap* bitmap = D2D1Core::GetInstance()->LoadBitmapByFilename(wnd->GetPRT(), L"LoadingBg.png");
	ResourceManager::InsertBitmap(static_cast<int>(BitmapName::LoadingBg), bitmap);
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::AddPercent()
{
	_percent += 25;

	if (_percent >= 100)
	{
		_percent = 100;

		char buffer[100] = { 0 };
		char* bufferPtr = reinterpret_cast<char*>(buffer);

		*(__int16*)bufferPtr = 4;						bufferPtr += 2;
		*(__int16*)bufferPtr = UDP_PING_COMPLETE;		bufferPtr += 2;

		DataManager::GetInstance()->Session->Send(buffer, 4);
	}
}

void LoadingScene::CanComplete()
{
	if (DataManager::GetInstance()->PlayerNumber == 1 && _percent >= 100) 
	{
		char buffer[100] = { 0 };
		char* bufferPtr = reinterpret_cast<char*>(buffer);

		*(__int16*)bufferPtr = 4;						bufferPtr += 2;
		*(__int16*)bufferPtr = UDP_PING_GAMESTART;		bufferPtr += 2;

		DataManager::GetInstance()->Session->Send(buffer, 4);

		GameStart();
	}
}

void LoadingScene::GameStart()
{
	_state = END;
}

void LoadingScene::Init(Wnd* _wnd)
{
	_percent = 0;
	_state = WANTPING;
}

void LoadingScene::Update(Wnd* _wnd)
{
	if (_state == WANTPING)
	{
		int currentTick = ::GetTickCount64();
		int deltaTick = currentTick - _wantLastTick;

		_wantSumTick += deltaTick;

		if (_wantLastTick > 3000) 
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
	else if (_state == UDPHOLEPUNCH) 
	{
		int currentTick = ::GetTickCount64();
		int deltaTick = currentTick - _wantLastTick;

		_wantSumTick += deltaTick;

		if (_wantLastTick > 1000) 
		{
			_wantSumTick = 0;
			{
				char sendBuffer[100] = {};
				char* bufferPtr = (char*)sendBuffer;

				*(__int16*)bufferPtr = 4;				bufferPtr += 2; // packetSize
				*(__int16*)bufferPtr = UDP_PING_SEND;	bufferPtr += 2; // packetType

				// SceneManager::GetInstance()->GetUDP()->Send(sendBuffer, 4);
				DataManager::GetInstance()->Session->Send(bufferPtr, 4);
			}
		}
		_wantLastTick = currentTick;
	}
	else if (_state == END) 
	{
		SceneManager::GetInstance()->ChangeScene(SceneType::MultiGame, _wnd);
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

void LoadingScene::Clear(Wnd* wnd)
{
	_percent = 0;
	_state = WANTPING;
}
