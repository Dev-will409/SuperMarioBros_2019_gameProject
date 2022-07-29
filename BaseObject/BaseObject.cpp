#include "../Include/SystemH.h"
#include "../Include/UserDefine.h"
#include "../Include/UserType.h"

#include "BaseObject.h"



BaseObject::BaseObject(const std::string& tag, const float x, const float y, const float width, const float height)
	: pos(x, y), size(width, height), isSideCollision(false), isTopCollision(false), isBottomCollision(false), tag(tag)
{
	rect = TRectMakeCenter(x, y, width, height);
}

BaseObject::BaseObject(const std::string& tag, const TPoint& position, const TSize& size)
	: pos(position), size(size), isSideCollision(false), isTopCollision(false), isBottomCollision(false), tag(tag)
{
	rect = TRectMakeCenter(position.x, position.y, size.width, size.height);
}

BaseObject::BaseObject(const BaseObject& other)
	: pos(other.pos), size(other.size), isSideCollision(false), isTopCollision(false), isBottomCollision(false)
{
	rect = other.rect;
}

BaseObject & BaseObject::operator=(const BaseObject& other)
{
	pos = other.pos;
	size = other.size;
	rect = other.rect;
	isSideCollision = false;
	isTopCollision = false;
	isBottomCollision = false;
	return *this;
}

bool BaseObject::Init()
{
	return true;
}

void BaseObject::Release()
{
}

void BaseObject::Update()
{
}

void BaseObject::Render(HDC hdc)
{
}

void BaseObject::Render(HDC hdc, const TPoint * ptCamera)
{
}

bool BaseObject::IsSideCollision(BaseObject * obj)
{
	return Collision::GetInstance()->SideCollision(this->rect, obj->GetRect());
}

bool BaseObject::IsTopCollision(BaseObject * obj)
{
	return Collision::GetInstance()->TopCollision(this->rect, obj->GetRect());
}

bool BaseObject::IsBottomCollision(BaseObject * obj)
{
	return Collision::GetInstance()->BottomCollision(this->rect,obj->GetRect());
}

bool BaseObject::IsLeftCollision(BaseObject * obj)
{
	return Collision::GetInstance()->LeftCollision(this->rect, obj->GetRect());
}

bool BaseObject::IsRightCollision(BaseObject * obj)
{
	return Collision::GetInstance()->RightCollision(this->rect, obj->GetRect());
}
