#pragma once


class BaseObject
{
protected:
	TPoint		pos;
	TSize		size;

	TRect		rect;

	float				nowPosX;
	float				nowPosY;

	bool		isSideCollision;
	bool		isTopCollision;
	bool		isBottomCollision;
	bool		isLeftCollision;
	bool		isRightCollision;

	std::string tag;

public:
	BaseObject() = delete;
	BaseObject(const std::string& tag, float x, const float y, const float width, const float height);
	BaseObject(const std::string& tag, const TPoint& position, const TSize& size);
	BaseObject(const BaseObject& other);

	virtual ~BaseObject() = default;

	BaseObject& operator=(const BaseObject& other);

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Render(HDC hdc, const TPoint* ptCamera);

	std::string& GetTag() { return tag; }
	void SetTag(const std::string& tag) { this->tag = tag; }

	void SetPosition(const float x, const float y) { this->pos = TPoint(x, y); }
	void SetPosition(const TPoint& pos) { this->pos = pos; }

	const TPoint& GetPosition() const { return pos; }
	TPoint* GetPosition() { return &pos; }

	const TSize& GetSize() const { return size; }
	const TRect& GetRect() const { return rect; }

	virtual bool SetSideCollision(const bool flag) { isSideCollision = flag; return flag; }
	virtual bool SetBottomCollision(const bool flag) { isBottomCollision = flag; return flag; }
	virtual bool SetTopCollision(const bool flag) { isTopCollision = flag; return flag; }
	virtual bool SetLeftCollision(const bool flag) { isLeftCollision = flag; return flag; }
	virtual bool SetRightCollision(const bool flag) { isRightCollision = flag; return flag; }

	bool GetSideCollision() const { return isSideCollision; }
	bool GetBottomCollision() const { return isBottomCollision; }
	bool GetTopCollision() const { return isTopCollision; }
	bool GetLeftCollision() const { return isLeftCollision; }
	bool GetRightCollision() const { return isRightCollision; }

	virtual bool IsSideCollision(BaseObject* obj);
	virtual bool IsTopCollision(BaseObject* obj);
	virtual bool IsBottomCollision(BaseObject* obj);
	virtual bool IsLeftCollision(BaseObject* obj);
	virtual bool IsRightCollision(BaseObject* obj);

	float GetNowPosX(float x) { return nowPosX = x; }
	float GetNowPosY(float y) { return nowPosY = y; }
};

