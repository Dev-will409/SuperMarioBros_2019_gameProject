#pragma once

class BackBuffer;

class GameBase
{
	BackBuffer*			backBuffer;

	bool				bInit;

	void SetBackBuffer();

public:
	GameBase();
	virtual ~GameBase();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	BackBuffer* GetBackBuffer() const { return backBuffer; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

