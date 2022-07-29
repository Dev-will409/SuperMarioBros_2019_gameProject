#pragma once

class BackBuffer
{
	struct BackBufferInfo
	{
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOldBit;

		float		x;
		float		y;

		int			width;
		int			height;

		BackBufferInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			x = 0.f;
			y = 0.f;
			width = 0;
			height = 0;
		}
	};

	BackBufferInfo*		backBufferInfo;

	BackBuffer(const BackBuffer& obj) = delete;
	BackBuffer& operator=(const BackBuffer& obj) = delete;

public:
	BackBuffer() : backBufferInfo(nullptr) {}
	~BackBuffer() = default;

	bool Init(const int width, const int height);
	void Release();
	void Render(const HDC& hdc, const int destX, const int destY);

	const HDC GetMemDC() const;
};

