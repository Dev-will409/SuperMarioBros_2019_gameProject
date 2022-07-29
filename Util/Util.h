#pragma once

#include <Windows.h>
#include "../Include/UserType.h"

inline POINT PointMake(const int x, const int y)
{
	return POINT({ x, y });
}

inline RECT RectMake(const int x, const int y, const int width, const int height)
{
	return RECT({ x, y, x + width, y + height });
}

inline RECT RectMakeCenter(const int x, const int y, const int width, const int height)
{
	return RECT({ x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) });
}

inline TRect TRectMakeCenter(const float x, const float y, const float width, const float height)
{
	return TRect((x - (width / 2)), (y - (height / 2)), (x + (width / 2)), (y + (height / 2)));
}
