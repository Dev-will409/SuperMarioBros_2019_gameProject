#pragma once


class Image 
{
	enum IMAGE_LOAD_KIND
	{
		LOAD_EMPTY,
		LOAD_FILE,
		LOAD_END,
	};

	struct ImageInfo
	{
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOldBit;

		int			width;
		int			height;

		float		x;
		float		y;

		int			currentFrameX;
		int			currentFrameY;
		int			maxFrameX;
		int			maxFrameY;
		int			frameWidth;
		int			frameHeight;

		BYTE		loadType;

		ImageInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			x = 0.f;
			y = 0.f;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;

			loadType = LOAD_EMPTY;
		}
	};

	ImageInfo*		imageInfo;

	char*			fileName;

	bool			trans;
	COLORREF		transColor;

	//Alpha Blend¿ë 
	ImageInfo*		blendInfo;
	BLENDFUNCTION	blendFunc;

public:
	Image();
	~Image();

	Image(const Image& other) = delete;
	Image& operator=(const Image& other) = delete;

	//Image Init
	bool Init(const int width, const int height);
	bool Init(const char* file, const int width, const int height,
		bool trans = false, const COLORREF& color = false);
	bool Init(const char* file, const float x, const float y,
		const int width, const int height, bool trans = false,
		const COLORREF& color = false);

	//Sprite Image Init
	bool Init(const char* file, const float x, const float y,
		const int width, const int height, const int frameX, const int frameY,
		bool trans = false, const COLORREF& color = false);

	bool Init(const char* file, const int width, const int height,
		const int frameX, const int frameY,
		bool trans = false, const COLORREF& color = false);

	void Release();

	//Render Function
	void Render(HDC hdc, const int destX, const int destY);
	void Render(HDC hdc, const int destX, const int destY,
		const int srcX, const int srcY, const int srcWidth, const int srcHeight);

	//Loop Render Function
	void LoopRender(HDC hdc, const RECT* drawArea, int offsetX, int offsetY);

	//Frame Render Function
	void FrameRender(HDC hdc, const int destX, const int destY);
	void FrameRender(HDC hdc, const int destX, const int destY,
		const int currentFrameX, const int currentFrameY);

	//Alpha Render Function
	void AlphaRender(HDC hdc, const BYTE alpha);
	void AlphaRender(HDC hdc, const int destX, const int destY, const BYTE alpha);
	void AlphaRender(HDC hdc, const int destX, const int destY,
		const int currentFrameX, const int currentFrameY, const BYTE alpha);


	HDC GetMemDC() { return imageInfo->hMemDC; }
	const char* GetFileName() const { return fileName; }
	void SetTransColor(const bool trans, const COLORREF& color);

	void SetX(const float x) { imageInfo->x = x; }
	void SetY(const float y) { imageInfo->y = y; }

	float GetX() const { return imageInfo->x; }
	float GetY() const { return imageInfo->y; }

	int GetWidth() const { return imageInfo->width; }
	int GetHight() const { return imageInfo->height; }

	int GetFrameWidth() const { return imageInfo->frameWidth; }
	int GetFrameHight() const { return imageInfo->frameHeight; }

	int GetMaxFrameX() const { return imageInfo->maxFrameX; }
	int GetMaxFrameY() const { return imageInfo->maxFrameY; }

	int GetCurrentFrameX() const { return imageInfo->currentFrameX; }
	int GetCurrentFrameY() const { return imageInfo->currentFrameY; }

	void SetCurrentFrameX(const int frameX) { imageInfo->currentFrameX = frameX; }
	void SetCurrentFrameY(const int frameY) { imageInfo->currentFrameY = frameY; }
};

