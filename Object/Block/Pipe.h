#pragma once

#include "../../BaseObject/BaseObject.h"

class Image;

class Pipe : public BaseObject
{
	Image*			image;

public:
	Pipe() = delete;
	explicit Pipe(const std::string& tag, const TPoint& pos, const TSize& size);
	Pipe(const Pipe& other);

	Pipe& operator=(const Pipe& other);

	~Pipe() = default;

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