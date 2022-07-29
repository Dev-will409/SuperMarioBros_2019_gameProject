#pragma once

#include "../../BaseObject/BaseObject.h"

class Image;

class Block : public BaseObject
{
	Image*			image;

public:
	Block() = delete;
	explicit Block (const std::string& tag, const TPoint& pos, const TSize& size);
	Block(const Block& other);

	Block& operator=(const Block& other);

	~Block() = default;

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