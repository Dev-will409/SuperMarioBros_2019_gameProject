#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"

#include "Image.h"

#pragma comment(lib, "msimg32.lib")

Image::Image() : imageInfo(nullptr), fileName(nullptr)
{
	trans = false;
	transColor = RGB(0, 0, 0);
}

Image::~Image()
{
	char temp[100] = { 0, };
	OutputDebugStringA(temp);
}

bool Image::Init(const int width, const int height)
{
	if (imageInfo != nullptr)
		Release();

	HDC hdc = GetDC(hWnd);

	imageInfo = new ImageInfo;
	imageInfo->loadType = LOAD_EMPTY;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = width;
	imageInfo->height = height;

	fileName = nullptr;

	trans = false;
	transColor = RGB(0, 0, 0);

	if (imageInfo->hBit == nullptr)
	{
		Release();
		return false;
	}

	ReleaseDC(hWnd, hdc);

	return true;
}

bool Image::Init(const char* file, const int width, const int height,
	bool trans, const COLORREF& color)
{
	if (imageInfo != nullptr)
		Release();

	HDC hdc = GetDC(hWnd);

	imageInfo = new ImageInfo;
	imageInfo->loadType = LOAD_FILE;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBit = (HBITMAP)LoadImageA(hInst, file, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = width;
	imageInfo->height = height;

	size_t size = strlen(file);
	fileName = new char[size + 1];
	strcpy_s(fileName, (size + 1), file);

	this->trans = trans;
	this->transColor = color;

	//Alpha Blend용 
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.BlendOp = AC_SRC_OVER;

	blendInfo = new ImageInfo;
	blendInfo->loadType = LOAD_EMPTY;
	blendInfo->hMemDC = CreateCompatibleDC(hdc);
	blendInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, GAME_WIDTH, GAME_HEIGHT);
	blendInfo->hOldBit = (HBITMAP)SelectObject(blendInfo->hMemDC, blendInfo->hBit);
	blendInfo->width = GAME_WIDTH;
	blendInfo->height = GAME_HEIGHT;

	if (imageInfo->hBit == nullptr)
	{
		Release();
		return false;
	}

	ReleaseDC(hWnd, hdc);

	return true;
}

bool Image::Init(const char * file, const float x, const float y, const int width, const int height, bool trans, const COLORREF & color)
{
	if (imageInfo != nullptr)
		Release();

	HDC hdc = GetDC(hWnd);

	imageInfo = new ImageInfo;
	imageInfo->loadType = LOAD_FILE;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBit = (HBITMAP)LoadImageA(hInst, file, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = width;
	imageInfo->height = height;

	imageInfo->x = x;
	imageInfo->y = y;

	size_t size = strlen(file);
	fileName = new char[size + 1];
	strcpy_s(fileName, (size + 1), file);

	this->trans = trans;
	this->transColor = color;

	//Alpha Blend용 
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.BlendOp = AC_SRC_OVER;

	blendInfo = new ImageInfo;
	blendInfo->loadType = LOAD_EMPTY;
	blendInfo->hMemDC = CreateCompatibleDC(hdc);
	blendInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, GAME_WIDTH, GAME_HEIGHT);
	blendInfo->hOldBit = (HBITMAP)SelectObject(blendInfo->hMemDC, blendInfo->hBit);
	blendInfo->width = GAME_WIDTH;
	blendInfo->height = GAME_HEIGHT;

	if (imageInfo->hBit == nullptr)
	{
		Release();
		return false;
	}

	ReleaseDC(hWnd, hdc);
	return true;
}

//Sprite Image Init
bool Image::Init(const char * file, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool trans, const COLORREF & color)
{
	if (imageInfo != nullptr)
		Release();

	HDC hdc = GetDC(hWnd);

	imageInfo = new ImageInfo;
	imageInfo->loadType = LOAD_FILE;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBit = (HBITMAP)LoadImageA(hInst, file, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = width;
	imageInfo->height = height;

	imageInfo->x = x;
	imageInfo->y = y;

	imageInfo->frameWidth = width / frameX;
	imageInfo->frameHeight = height / frameY;
	imageInfo->currentFrameX = 0;
	imageInfo->currentFrameY = 0;
	imageInfo->maxFrameX = frameX - 1;
	imageInfo->maxFrameY = frameY - 1;

	size_t size = strlen(file);
	fileName = new char[size + 1];
	strcpy_s(fileName, (size + 1), file);

	this->trans = trans;
	this->transColor = color;

	//Alpha Blend용 
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.BlendOp = AC_SRC_OVER;

	blendInfo = new ImageInfo;
	blendInfo->loadType = LOAD_EMPTY;
	blendInfo->hMemDC = CreateCompatibleDC(hdc);
	blendInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, GAME_WIDTH, GAME_HEIGHT);
	blendInfo->hOldBit = (HBITMAP)SelectObject(blendInfo->hMemDC, blendInfo->hBit);
	blendInfo->width = GAME_WIDTH;
	blendInfo->height = GAME_HEIGHT;

	if (imageInfo->hBit == nullptr)
	{
		Release();
		return false;
	}

	return true;
}

bool Image::Init(const char * file, const int width, const int height, const int frameX, const int frameY, bool trans, const COLORREF & color)
{
	if (imageInfo != nullptr)
		Release();

	HDC hdc = GetDC(hWnd);

	imageInfo = new ImageInfo;
	imageInfo->loadType = LOAD_FILE;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBit = (HBITMAP)LoadImageA(hInst, file, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = width;
	imageInfo->height = height;

	imageInfo->frameWidth = width / frameX;
	imageInfo->frameHeight = height / frameY;
	imageInfo->currentFrameX = 0;
	imageInfo->currentFrameY = 0;
	imageInfo->maxFrameX = frameX - 1;
	imageInfo->maxFrameY = frameY - 1;

	size_t size = strlen(file);
	fileName = new char[size + 1];
	strcpy_s(fileName, (size + 1), file);

	this->trans = trans;
	this->transColor = color;

	//Alpha Blend용 
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.BlendOp = AC_SRC_OVER;

	blendInfo = new ImageInfo;
	blendInfo->loadType = LOAD_EMPTY;
	blendInfo->hMemDC = CreateCompatibleDC(hdc);
	blendInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, GAME_WIDTH, GAME_HEIGHT);
	blendInfo->hOldBit = (HBITMAP)SelectObject(blendInfo->hMemDC, blendInfo->hBit);
	blendInfo->width = GAME_WIDTH;
	blendInfo->height = GAME_HEIGHT;

	if (imageInfo->hBit == nullptr)
	{
		Release();
		return false;
	}

	return true;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBit);
		DeleteDC(imageInfo->hMemDC);

		SAFE_DELETE(imageInfo);
		SAFE_DELETE(fileName);

		trans = false;
		transColor = RGB(0, 0, 0);
	}

	if (blendInfo)
	{
		SelectObject(blendInfo->hMemDC, blendInfo->hOldBit);
		DeleteObject(blendInfo->hBit);
		DeleteDC(blendInfo->hMemDC);

		SAFE_DELETE(blendInfo);
	}
}

void Image::Render(HDC hdc, const int destX, const int destY)
{
	if (trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0,
			0,
			imageInfo->width,
			imageInfo->height,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0,
			0,
			SRCCOPY);
	}
}

void Image::Render(HDC hdc, const int destX, const int destY, const int srcX, const int srcY, const int srcWidth, const int srcHeight)
{
	if (trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			srcWidth,
			srcHeight,
			imageInfo->hMemDC,
			srcX,
			srcY,
			srcWidth,
			srcHeight,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			srcWidth,
			srcHeight,
			imageInfo->hMemDC,
			srcX,
			srcY,
			SRCCOPY);
	}
}

void Image::LoopRender(HDC hdc, const RECT* drawArea, int offsetX, int offsetY)
{
	static int nLoopCount = 0;
	static int nRenderCount = 1;

	if (offsetX < 0)
		offsetX = imageInfo->width + (offsetX % imageInfo->width);
	if (offsetY < 0)
		offsetY = imageInfo->height + (offsetY % imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offsetY) % imageInfo->height;
		rcSour.bottom = imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % imageInfo->width;
			rcSour.right = imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			Render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);

			nRenderCount++;
		}
	}

	nLoopCount++;
}

void Image::FrameRender(HDC hdc, const int destX, const int destY)
{
	if (trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->currentFrameX * imageInfo->frameWidth,
			imageInfo->currentFrameY * imageInfo->frameHeight,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->currentFrameX * imageInfo->frameWidth,
			imageInfo->currentFrameY * imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::FrameRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY)
{
	imageInfo->currentFrameX = currentFrameX;
	imageInfo->currentFrameY = currentFrameY;

	if (trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->currentFrameX * imageInfo->frameWidth,
			imageInfo->currentFrameY * imageInfo->frameHeight,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->currentFrameX * imageInfo->frameWidth,
			imageInfo->currentFrameY * imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::AlphaRender(HDC hdc, const BYTE alpha)
{
	blendFunc.SourceConstantAlpha = alpha;

	if (trans)
	{
		BitBlt(
			blendInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			hdc,
			static_cast<int>(imageInfo->x),
			static_cast<int>(imageInfo->y),
			SRCCOPY);

		GdiTransparentBlt(
			blendInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			transColor);

		AlphaBlend(
			hdc,
			static_cast<int>(imageInfo->x),
			static_cast<int>(imageInfo->y),
			imageInfo->width,
			imageInfo->height,
			blendInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			blendFunc);
	}
	else
	{
		AlphaBlend(
			hdc,
			static_cast<int>(imageInfo->x),
			static_cast<int>(imageInfo->y),
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, const int destX, const int destY, const BYTE alpha)
{
	blendFunc.SourceConstantAlpha = alpha;

	if (trans)
	{
		BitBlt(
			blendInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			hdc,
			destX,
			destY,
			SRCCOPY);

		GdiTransparentBlt(
			blendInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			transColor);

		AlphaBlend(
			hdc,
			destX,
			destY,
			imageInfo->width,
			imageInfo->height,
			blendInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			blendFunc);
	}
	else
	{
		AlphaBlend(
			hdc,
			destX,
			destY,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY, const BYTE alpha)
{
	blendFunc.SourceConstantAlpha = alpha;

	imageInfo->currentFrameX = currentFrameX;
	imageInfo->currentFrameY = currentFrameY;

	if (trans)
	{
		BitBlt(
			blendInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			hdc,
			destX,
			destY,
			SRCCOPY);

		GdiTransparentBlt(
			blendInfo->hMemDC,
			0, 0,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			currentFrameX * imageInfo->frameWidth,
			currentFrameY * imageInfo->frameHeight,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			transColor);

		GdiAlphaBlend(
			hdc,
			destX,
			destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			blendInfo->hMemDC,
			0, 0,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			blendFunc);
	}
	else
	{
		GdiAlphaBlend(
			hdc,
			destX,
			destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			currentFrameX * imageInfo->frameWidth,
			currentFrameY * imageInfo->frameHeight,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			blendFunc);
	}
}

void Image::SetTransColor(const bool trans, const COLORREF& color)
{
	this->trans = trans;
	this->transColor = color;
}
