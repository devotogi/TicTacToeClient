#include "pch.h"
#include "App.h"
#include "D2D1Core.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	D2D1Core::GetInstance()->Init();
	App app(hInstance, 0, 0, 700, 700);
}