#include "pch.h"
#include "SingleGameScene.h"
#include "Bitmap.h"
#include "Wnd.h"
#include "ResourceManager.h"
#include "D2D1Core.h"
#include "Button.h"
#include "SceneManager.h"

SingleGameScene::SingleGameScene(Wnd* wnd)
{
	Bitmap* bitmap = D2D1Core::GetInstance()->LoadBitmapByFilename(wnd->GetPRT(), L"single.png");
	ResourceManager::InsertBitmap(static_cast<int>(BitmapName::SingGameBg), bitmap);

	_button = new Button(SingleGameBackBtn, 21, 14, 203, 59);
}

SingleGameScene::~SingleGameScene()
{
	ResourceManager::RemoveBitmap(static_cast<int>(BitmapName::SingGameBg));
	if (_button)
		delete _button;
}

void SingleGameScene::Init(Wnd* _wnd)
{
	for (int i = 0; i < 19683; i++)
		dp[i] = DEFAULT;

	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++)
			_board[y][x] = TileType::None;

	_nowTurn = TileType::P1O;
}

void SingleGameScene::Update(Wnd* _wnd)
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

	if (_button->Clicked())
	{
		SceneManager::GetInstance()->ChangeScene(SceneType::Menu, _wnd);
	}
	
	if (_nowTurn == TileType::P2X) 
	{
		std::vector<Pos> job;

		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (_board[y][x] != None)
					continue;

				Pos pos{ x,y };
				if (CanWin(pos, TileType::P2X))
					job.push_back(pos);
			}
		}

		if (job.empty()) 
		{
			// 패배했으므로 아무곳이나 착수한다.
			Pos nullPos = { -1, -1 };
			Pos randomPos = nullPos;
			for (int y = 0; y < 3; y++) 
			{
				for (int x = 0; x < 3; x++) 
				{
					if (_board[y][x] != TileType::None)
						randomPos = { x, y };
				}
			}

			if (randomPos != nullPos) 
			{
				_board[randomPos.y][randomPos.x] = TileType::P2X;
			}
		}
		else
		{
			Pos pos = job.front();
			_board[pos.y][pos.x] = TileType::P2X;
		}

		_nowTurn = TileType::P1O;
	}
	
	_gameResult = IsEnd();

	if (_gameResult != ResultType::DEFAULT) 
	{
		_resultState = true;
	}
}

void SingleGameScene::Render(Wnd* _wnd)
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
				_wnd->GetBRT()->DrawBitmap(ResourceManager::GetBitmap(static_cast<int>(BitmapName::P1OBg))->GetBitmap(), boardIndexRect[index],1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
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
		swprintf_s(text, _countof(text), L"플레이어 승리!");
		_wnd->GetBRT()->DrawTextW(text, wcslen(text), _wnd->GetTextResultFormat(), _resultTextRect, _wnd->GetYellowColor());
		break;

	case LOSE:
		swprintf_s(text, _countof(text), L"플레이어 패배!");
		_wnd->GetBRT()->DrawTextW(text, wcslen(text), _wnd->GetTextResultFormat(), _resultTextRect, _wnd->GetYellowColor());
		break;

	case DRAW:
		swprintf_s(text, _countof(text), L"무승부!");
		_wnd->GetBRT()->DrawTextW(text, wcslen(text), _wnd->GetTextResultFormat(), _resultTextRect, _wnd->GetYellowColor());
		break;
	}
}

void SingleGameScene::MouseClickEvent(int x, int y)
{
	if (_resultState)
		return;

	_button->OnClick(x, y);

	for (int i = 0; i < 9; i++) 
	{
		D2D1_RECT_F bound = boardIndexRect[i];
		if (x >= bound.left && x <= bound.right && y >= bound.top && y <= bound.bottom)
		{
			int y = i / 3;
			int x = i % 3;

			if (_board[y][x] != TileType::None) 
				break;

			_board[y][x] = TileType::P1O;
		
			ResultType result = IsEnd();

			if (result == DEFAULT)
				_nowTurn = TileType::P2X;

			break;
		}
	}
}

TileType SingleGameScene::OtherTurn(TileType turn)
{
	if (turn == TileType::P1O)
		return TileType::P2X;

	else
		return TileType::P1O;

}

int SingleGameScene::Hash()
{
	int ret = 0;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			ret *= 3;

			switch (_board[y][x])
			{
			case TileType::None:
				ret += 0;
				break;

			case TileType::P1O:
				ret += 1;
				break;

			case TileType::P2X:
				ret += 2;
				break;
			}
		}
	}

	return ret;

}

bool SingleGameScene::IsFinished(TileType turn)
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

ResultType SingleGameScene::IsEnd()
{
	if (IsFinished(TileType::P1O)) 
	{
		// Player 승리
		return ResultType::WIN;
	}

	else if (IsFinished(TileType::P2X)) 
	{
		// CPU 승리
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
		// 비겼음
		return ResultType::DRAW;
	}

	return ResultType::DEFAULT;
}

bool SingleGameScene::CanWin(const Pos& pos, TileType turn)
{
	_board[pos.y][pos.x] = turn;

	int isWin = CanWin(OtherTurn(turn));

	_board[pos.y][pos.x] = TileType::None;

	if (isWin == WIN) return false;
	else if (isWin == DRAW) return true;
	else return true;

}

int SingleGameScene::CanWin(TileType turn)
{
	int minValue = DEFAULT;

	if (IsFinished(turn))
		return WIN;

	if (IsFinished(OtherTurn(turn)))
		return LOSE;

	int key = Hash();
	int& ret = dp[key];

	if (ret != DEFAULT)
		return ret;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (_board[y][x] != TileType::None)
				continue;

			_board[y][x] = turn;

			minValue = min(minValue, CanWin(OtherTurn(turn)));

			_board[y][x] = TileType::None;
		}
	}

	if (minValue == DRAW || minValue == DEFAULT)
		return ret = DRAW;

	return ret = -minValue;

}
