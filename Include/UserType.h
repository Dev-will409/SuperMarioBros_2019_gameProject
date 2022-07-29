#pragma once
#include <string>


//tstring Á¤ÀÇ
#ifdef UNICODE
using tstring = std::wstring;
#else
using tstring = std::string;
#endif // #ifdef UNICODE

//
struct TSize
{
	float width;
	float height;

	TSize() : width(0), height(0) {}
	~TSize() = default;
	TSize(const float w, const float h) : width(w), height(h) {}
	TSize(const TSize& size) : width(size.width), height(size.height) {}
	TSize& operator=(const TSize& size)
	{
		width = size.width;
		height = size.height;

		return *this;
	}
};

struct TPoint
{
	float x;
	float y;

	TPoint() : x(0), y(0) {}
	~TPoint() = default;
	explicit TPoint(const float x, const float y) : x(x), y(y) {}
	TPoint(const TPoint& other)
	{
		*this = other;
	}

	TPoint& operator=(const TPoint& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}
};

struct TRect
{
	float left;
	float top;
	float right;
	float bottom;

	TRect() : left(0), top(0), right(0), bottom(0) {}
	~TRect() = default;
	explicit TRect(const float l, const float t, const float r, const float b)
		: left(l), top(t), right(r), bottom(b) {}

	TRect(const TRect& other)
	{
		*this = other;
	}

	TRect& operator=(const TRect& other)
	{
		left = other.left;
		top = other.top;
		right = other.right;
		bottom = other.bottom;

		return *this;
	}
};

struct FrameDesc
{
	TSize	imageSize;
	int		frameX;
	int		frameY;
	bool	isEnable;

	FrameDesc() : imageSize({ 0.f, 0.f }), frameX(0), frameY(0), isEnable(false) {}
	FrameDesc(const TSize& size, int fX, int fY)
		: imageSize(size), frameX(fX), frameY(fY), isEnable(true) {}
};