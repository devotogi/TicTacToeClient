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
		className, // ������ Ŭ���� �̸� (���� Ŭ���� �̸��� ��Ȯ�� ��ġ�ؾ���)
		title, // ������ Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW, // ������ ��Ÿ��
		_posX, _posY, // ������ ��ġ x ��ǥ, ������ ��ġ y ��ǥ
		_width, _height, // width, height 
		NULL, // �θ� ������ �ڵ� 
		NULL, // �޴� �ڵ�
		hInstance, // ���� ���α׷� ID (WinMAIN���� �Ű������� �Ѿ�� hInstance ��)
		NULL // ������ ������ ����
	);

	if (!_hWnd) // ���� ������ ������ �����ߴٸ� �Ʒ��� �ڵ尡 ����˴ϴ�.
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Windows Desktop Guided Tour",
			NULL);
	}

	D2D1Core::GetInstance()->CreateRenderTarget(_hWnd, &_rt);
	D2D1Core::GetInstance()->CreateRenderTarget(_rt, &_brt);

	ShowWindow(_hWnd, 10); // ������ ������ ȭ�� ���
	UpdateWindow(_hWnd);  // ������ �ü���� WM_PAINT �޼��� ����(�̺�Ʈ ����)
}

Wnd::~Wnd()
{

}
