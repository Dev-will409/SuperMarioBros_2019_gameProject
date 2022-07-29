#pragma once

#include "../../BaseObject/BaseObject.h"

class Image;


class Map : public BaseObject
{
	Image*		background;

	int			offsetX;

public:
	Map() = delete;
	Map(const std::string& tag, const TPoint& pos, const TSize& size);
	Map(const Map& other);

	~Map() = default;

	Map& operator=(const Map& other);

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void Render(HDC hdc, const TPoint* ptCamera);
};

