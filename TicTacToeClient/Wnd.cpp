#include "pch.h"
#include "Wnd.h"
#include "D2D1Core.h"

Wnd::Wnd(HINSTANCE hInstance, int posX, int posY, int width, int height, const WCHAR* title, const WCHAR* className, WNDPROC proc) : _posX(posX), _posY(posY), _width(width), _height(height)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			L"Call to RegisterClassEx failed!",
			L"Windows Desktop Guided Tour",
			NULL);
	}

	_hWnd = CreateWindow(
		className, // 윈도우 클래스 이름 (위의 클래스 이름과 정확히 일치해야함)
		title, // 윈도우 타이틀 이름
		WS_OVERLAPPEDWINDOW, // 윈도우 스타일
		_posX, _posY, // 윈도우 위치 x 좌표, 윈도우 위치 y 좌표
		_width, _height, // width, height 
		NULL, // 부모 윈도우 핸들 
		NULL, // 메뉴 핸들
		hInstance, // 응용 프로그램 ID (WinMAIN에서 매개변수로 넘어온 hInstance 값)
		NULL // 생성된 윈도우 정보
	);

	if (!_hWnd) // 만약 윈도우 생성에 실패했다면 아래의 코드가 실행됩니다.
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Windows Desktop Guided Tour",
			NULL);
	}

	D2D1Core::GetInstance()->CreateRenderTarget(_hWnd, &_rt);
	D2D1Core::GetInstance()->CreateRenderTarget(_rt, &_brt);

	ShowWindow(_hWnd, 10); // 생성된 윈도우 화면 출력
	UpdateWindow(_hWnd);  // 윈도우 운영체제에 WM_PAINT 메세지 전송(이벤트 전송)
}

Wnd::~Wnd()
{

}
