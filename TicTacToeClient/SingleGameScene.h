#pragma once
#include "Scene.h"
class Bitmap;
class Button;

class SingleGameScene : public Scene
{
private:
	Button* _button = nullptr;
	
private:
	D2D1_RECT_F boardIndexRect[9] =
	{
		{ 284.f, 76.f, 284.f+123.f,76.f+123.f },
		{ 415.f, 76.f, 415.f+123.f,76.f+123.f },
		{ 546.f, 76.f, 546.f+123.f,76.f+123.f },
		{ 284.f, 206.f, 284.f+123.f,206.f+123.f },
		{ 415.f, 206.f, 415.f+123.f,206.f+123.f },
		{ 546.f, 206.f, 546.f+123.f,206.f+123.f },
		{ 284.f, 339.f, 284.f+123.f,339.f+123.f },
		{ 415.f, 339.f, 415.f+123.f,339.f+123.f },
		{ 546.f, 339.f, 546.f+123.f,339.f+123.f },
	};

	TileType _board[3][3] =
	{
		{TileType::None, TileType::None, TileType::None},
		{TileType::None, TileType::None, TileType::None},
		{TileType::None, TileType::None, TileType::None}
	};

	TileType _nowTurn = TileType::P1O;
	int dp[19683];
	D2D1_RECT_F _resultTextRect = { 283.f,207.f,672.f, 335.f };
	ResultType _gameResult = ResultType::DEFAULT;
	bool _resultState = false;

private:
	int _lastTick = 0;
	int _sumTick = 0;

public:
	SingleGameScene(Wnd* wnd);
	~SingleGameScene();

	virtual void	Init(Wnd* _wnd) override;
	virtual void	Update(Wnd* _wnd) override;
	virtual void	Render(Wnd* _wnd) override;
	virtual void	MouseClickEvent(int x, int y) override;

private:
	TileType OtherTurn(TileType turn);
	int Hash();
	bool IsFinished(TileType turn);
	ResultType IsEnd();
	bool CanWin(const Pos& pos, TileType turn);
	int CanWin(TileType turn);
};