#pragma once

#include "../../BaseObject/BaseObject.h"

class Image;

enum class CoinBlockState
{
	UNHITTED,
	HITTED,
};

class CoinBlock : public BaseObject
{
	Image*			image;

	CoinBlockState	state;

public:
	CoinBlock() = delete;
	explicit CoinBlock(const std::string& tag, const TPoint& pos, const TSize& size);
	CoinBlock(const CoinBlock& other);

	CoinBlock& operator=(const CoinBlock& other);

	~CoinBlock() = default;

	void Update();
	void Render(HDC hdc);

	void Render(HDC hdc, const TPoint * pt);

	bool SetSideCollision(const bool flag);
	bool SetTopCollision(const bool flag);
	bool SetBottomCollision(const bool flag);

	bool IsSideCollision(BaseObject * obj);
	bool IsBottomCollision(BaseObject * obj);
	bool IsTopCollision(BaseObject * obj);

	CoinBlockState GetState() const { return state; }
};