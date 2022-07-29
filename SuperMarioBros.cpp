// SuperMarioBros.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "Include/SystemH.h"
#include "Include/UserDefine.h"
#include "Include/UserType.h"
#include "GameCore/GameMain.h"

//System
#include "System/Timer/TimeManager.h"

// 전역 변수:
HWND		hWnd;
HINSTANCE	hInst;

//
LPCTSTR		lpString = TEXT("Win32API");

//
GameMain	game;

// 함수의 선언
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	hInst = hInstance;

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// 게임 로직 객체 초기화
	if (game.Init() != true)
		return false;

	HDC hdc = GetDC(hWnd);
	assert(hdc != NULL);

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			TimeManager::GetInstance()->Update();
			game.Update();
			game.Render(hdc);
		}
	}

	// 게임 로직 객체 정리
	game.Release();

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = lpString;
	wcex.hIconSm = wcex.hIcon;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.


	RECT client = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
	AdjustWindowRect(&client, WS_OVERLAPPEDWINDOW, false);
	hWnd = CreateWindow(lpString, lpString, WS_OVERLAPPEDWINDOW,
		50, 50, client.right - client.left, client.bottom - client.top,
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	//UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return game.MainProc(hWnd, message, wParam, lParam);
}

