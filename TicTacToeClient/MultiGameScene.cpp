#include "pch.h"
#include "MultiGameScene.h"
#include "Bitmap.h"
#include "Wnd.h"
#include "ResourceManager.h"
#include "D2D1Core.h"
#include "Button.h"
#include "SceneManager.h"
#include "DataManager.h"
#include "Session.h"

MultiGameScene::MultiGameScene(Wnd* wnd)
{
	_button = new Button(SingleGameBackBtn, 21, 14, 203, 59);
}

MultiGameScene::~MultiGameScene()
{
	if (_button)
		delete _button;
}

bool MultiGameScene::IsFinished(TileType turn)
{
	for (int y = 0; y < 3; y++)
	{
		if (turn == _board[y][0] && turn == _board[y][1] && turn == _board[y][2])
			return true;
	}

	for (int x = 0; x < 3; x++)
	{
		if (turn == _board[0][x] && turn == _board[1][x] && turn == _board[2][x])
			return true;
	}

	if (turn == _board[0][0] && turn == _board[1][1] && turn == _board[2][2])
		return true;

	if (turn == _board[0][2] && turn == _board[1][1] && turn == _board[2][0])
		return true;

	return false;
}

TileType MultiGameScene::OtherTurn(TileType turn)
{
	if (turn == TileType::P1O)
		return TileType::P2X;

	else
		return TileType::P1O;
}

ResultType MultiGameScene::IsEnd()
{
	TileType my = static_cast<TileType>(DataManager::GetInstance()->PlayerNumber);
	TileType other = OtherTurn(my);

	if (IsFinished(my))
	{
		return ResultType::WIN;
	}

	else if (IsFinished(other))
	{
		return ResultType::LOSE;
	}

	bool draw = true;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (_board[y][x] == TileType::None)
			{
				draw = false;
			}
		}
	}

	if (draw)
	{
		// 厚板澜
		return ResultType::DRAW;
	}

	return ResultType::DEFAULT;
}

void MultiGameScene::SetStone(int y, int x)
{
	TileType otherTurn = OtherTurn(static_cast<TileType>(DataManager::GetInstance()->PlayerNumber));
	_board[y][x] = otherTurn;
	
	_nowTurn = OtherTurn(_nowTurn);
	
	if (DataManager::GetInstance()->PlayerNumber == 1)
	{
		_gameResult = IsEnd();

		if (_gameResult == ResultType::WIN || _gameResult == ResultType::LOSE)
		{
			_resultState = true;

			{
				char sendBuffer[100] = {};
				char* bufferPtr = reinterpret_cast<char*>(sendBuffer);

				*(__int16*)bufferPtr = 8;							bufferPtr += 2;
				*(__int16*)bufferPtr = UDP_PING_RESULT;				bufferPtr += 2;
				*(int*)bufferPtr = static_cast<int>(_gameResult);	bufferPtr += 4;

				DataManager::GetInstance()->Session->Send(sendBuffer, 8);
			}

			return;
		}
	}
}

void MultiGameScene::GameResult(ResultType resultType)
{
	_gameResult = resultType;
	_resultState = true;
}

void MultiGameScene::Init(Wnd* _wnd)
{
	_nowTurn = P1O;
	_gameResult = DEFAULT;

	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++)
			_board[y][x] = TileType::None;
}

void MultiGameScene::Update(Wnd* _wnd)
{
	if (_resultState)
	{
		int currentTick = ::GetTickCount64();
		_lastTick = _lastTick == 0 ? currentTick : _lastTick;

		_sumTick += currentTick - _lastTick;
		_lastTick = currentTick;

		if (_sumTick >= 3000)
		{
			_resultState = false;
			_lastTick = 0;
			_sumTick = 0;
			Init(_wnd);
		}

		return;
	}
}

void MultiGameScene::Render(Wnd* _wnd)
{
	Scene::Render(_wnd);

	RECT rect;
	GetClientRect(_wnd->GetHWND(), &rect);
	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };

	_wnd->GetBRT()->DrawBitmap(ResourceManager::GetBitmap(static_cast<int>(BitmapName::SingGameBg))->GetBitmap());

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			TileType type = _board[y][x];

			int index = (y * 3) + x;

			switch (type)
			{
			case P1O:
				_wnd->GetBRT()->DrawBitmap(ResourceManager::GetBitmap(static_cast<int>(BitmapName::P1OBg))->GetBitmap(), boardIndexRect[index], 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
				break;

			case P2X:
				_wnd->GetBRT()->DrawBitmap(ResourceManager::GetBitmap(static_cast<int>(BitmapName::P2XBg))->GetBitmap(), boardIndexRect[index], 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
				break;
			}
		}
	}

	WCHAR text[256] = { 0 };
	switch (_gameResult)
	{
	case WIN:
		swprintf_s(text, _countof(text), L"O 铰府");
		_wnd->GetBRT()->DrawTextW(text, wcslen(text), _wnd->GetTextResultFormat(), _resultTextRect, _wnd->GetYellowColor());
		break;

	case LOSE:
		swprintf_s(text, _countof(text), L"X 铰府!");
		_wnd->GetBRT()->DrawTextW(text, wcslen(text), _wnd->GetTextResultFormat(), _resultTextRect, _wnd->GetYellowColor());
		break;

	case DRAW:
		swprintf_s(text, _countof(text), L"公铰何!");
		_wnd->GetBRT()->DrawTextW(text, wcslen(text), _wnd->GetTextResultFormat(), _resultTextRect, _wnd->GetYellowColor());
		break;
	}
}

void MultiGameScene::MouseClickEvent(int x, int y)
{
	if (_resultState)
		return;

	_button->OnClick(x, y);
	
	int playerTrun = static_cast<int>(_nowTurn);
	
	if (DataManager::GetInstance()->PlayerNumber == playerTrun) 
	{
		for (int i = 0; i < 9; i++)
		{
			D2D1_RECT_F bound = boardIndexRect[i];
			if (x >= bound.left && x <= bound.right && y >= bound.top && y <= bound.bottom)
			{
				int y = i / 3;
				int x = i % 3;

				if (_board[y][x] != TileType::None)
					break;

				_board[y][x] = _nowTurn;
				
				{
					char sendBuffer[100] = {};
					char* bufferPtr = reinterpret_cast<char*>(sendBuffer);

					*(__int16*)bufferPtr = 12;						bufferPtr += 2;
					*(__int16*)bufferPtr = UDP_PING_SETSTONE;       bufferPtr += 2;
					*(int*)bufferPtr = y;							bufferPtr += 4;
					*(int*)bufferPtr = x;							bufferPtr += 4;
					
					DataManager::GetInstance()->Session->Send(sendBuffer, 12);
				}	
				
				if (DataManager::GetInstance()->PlayerNumber == 1) 
				{
					_gameResult = IsEnd();

					if (_gameResult == ResultType::WIN || _gameResult == ResultType::LOSE)
					{
						_resultState = true;

						{
							char sendBuffer[100] = {};
							char* bufferPtr = reinterpret_cast<char*>(sendBuffer);

							*(__int16*)bufferPtr = 8;							bufferPtr += 2;
							*(__int16*)bufferPtr = UDP_PING_RESULT;				bufferPtr += 2;
							*(int*)bufferPtr = static_cast<int>(_gameResult);	bufferPtr += 4;

							DataManager::GetInstance()->Session->Send(sendBuffer, 8);
						}

						_nowTurn = OtherTurn(_nowTurn);

						return;
					}
				}

				_nowTurn = OtherTurn(_nowTurn);

				break;
			}
		}
	}
}

void MultiGameScene::Clear(Wnd* wnd)
{
}
