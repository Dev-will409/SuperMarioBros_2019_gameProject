#pragma once

#include "../../BaseObject/BaseObject.h"

class Image;

class Brick : public BaseObject
{
	Image*			image;

public:
	Brick() = delete;
	explicit Brick(const std::string& tag, const TPoint& pos, const TSize& size);
	Brick(const Brick& other);

	Brick& operator=(const Brick& other);

	~Brick() = default;

	void Update();
	void Render(HDC hdc);

	void Render(HDC hdc, const TPoint * pt);


	bool SetSideCollision(const bool flag);
	bool SetTopCollision(const bool flag);
	bool SetBottomCollision(const bool flag);

	bool IsSideCollision(BaseObject * obj);
	bool IsBottomCollision(BaseObject * obj);
	bool IsTopCollision(BaseObject * obj);
};