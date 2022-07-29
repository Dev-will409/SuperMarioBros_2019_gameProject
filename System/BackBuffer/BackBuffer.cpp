#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"

#include "BackBuffer.h"


bool BackBuffer::Init(const int width, const int height)
{
	if (backBufferInfo != nullptr)
		Release();

	HDC hdc = GetDC(hWnd);

	backBufferInfo = new BackBufferInfo;
	backBufferInfo->hMemDC = CreateCompatibleDC(hdc);
	backBufferInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	backBufferInfo->hOldBit = (HBITMAP)SelectObject(backBufferInfo->hMemDC, backBufferInfo->hBit);
	backBufferInfo->width = width;
	backBufferInfo->height = height;

	if (backBufferInfo->hBit == nullptr)
	{
		Release();
		return false;
	}

	ReleaseDC(hWnd, hdc);

	return true;
}

void BackBuffer::Release()
{
	if (backBufferInfo)
	{
		SelectObject(backBufferInfo->hMemDC, backBufferInfo->hOldBit);
		DeleteObject(backBufferInfo->hBit);
		DeleteDC(backBufferInfo->hMemDC);

		delete backBufferInfo;
	}
}

void BackBuffer::Render(const HDC & hdc, const int destX, const int destY)
{
	BitBlt(hdc, destX, destY, backBufferInfo->width, backBufferInfo->height,
		backBufferInfo->hMemDC, 0, 0, SRCCOPY);
}

const HDC BackBuffer::GetMemDC() const
{
	assert(backBufferInfo != nullptr);
	return backBufferInfo->hMemDC;
}
