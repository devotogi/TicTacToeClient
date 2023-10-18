#pragma once
#include "Scene.h"
class Bitmap;
class Wnd;
class Button;

class LoadingScene : public Scene
{
private:
	LoadingState _state = WANTPING;
	int _wantLastTick = 0;
	int _wantSumTick = 0;
	int _percent = 0;
	Bitmap* _loadingBitmap = nullptr;
	IDWriteTextFormat* _textFormat;

public:
	LoadingScene(Wnd* wnd);
	~LoadingScene();

	void SetState(LoadingState state) { _state = state; }
	void AddPercent();
	void CanComplete();
	void GameStart();

	virtual void	Init(Wnd* _wnd) override;
	virtual void	Update(Wnd* _wnd) override;
	virtual void	Render(Wnd* _wnd) override;
	virtual void	MouseClickEvent(int x, int y) override;
	virtual void	Clear(Wnd* wnd) override;
};

