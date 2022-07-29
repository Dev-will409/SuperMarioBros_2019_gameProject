#include "../Include/SystemH.h"
#include "../Include/UserDefine.h"
#include "../Include/UserType.h"

#include "GameBase.h"

#include "../System/BackBuffer/BackBuffer.h"
#include "../System/Timer/TimeManager.h"
#include "../System/Input/Input.h"


void GameBase::SetBackBuffer()
{
	backBuffer = new BackBuffer;
	backBuffer->Init(GAME_WIDTH, GAME_HEIGHT);
}

GameBase::GameBase() : bInit(false)
{
}

GameBase::~GameBase()
{
}

bool GameBase::Init()
{
	SetBackBuffer();

	//Create Input
	Input::Create();
	//Create Timer
	TimeManager::Create();
	TimeManager::GetInstance()->Init(60.f);

	bInit = true;

	return true;
}

void GameBase::Release()
{
	bInit = false;

	//Delete Input
	Input::GetInstance()->Delete();
	//Delete Timer
	TimeManager::GetInstance()->Delete();

	GetBackBuffer()->Release();
}

void GameBase::Update()
{
}

void GameBase::Render(HDC hdc)
{
}

LRESULT GameBase::MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC			hdc;

	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
