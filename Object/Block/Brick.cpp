#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"
#include "../../Include/UserType.h"

#include "Brick.h"

#include "../../System/Image/Image.h"
#include "../../System/Image/ImageManager.h"

Brick::Brick(const std::string & tag, const TPoint & pos, const TSize & size) : BaseObject(tag, pos, size)
{
	image = ImageManager::GetInstance()->AddImage("Brick", "Resource/Brick.bmp", 32, 32, true, RGB(255, 255, 255));
	assert(image != nullptr);
}

Brick::Brick(const Brick & other) : BaseObject(other)
{
	*this = other;
}

Brick & Brick::operator=(const Brick & other)
{
	BaseObject::operator=(other);

	image = other.image;

	return *this;
}


void Brick::Update()
{
}

void Brick::Render(HDC hdc)
{
	image->Render(hdc, static_cast<int>(rect.left),
		static_cast<int>(rect.top));
}

void Brick::Render(HDC hdc, const TPoint* pt)
{
	image->Render(hdc,
		static_cast<int>(rect.left - pt->x),
		static_cast<int>(rect.top - pt->y));
}


bool Brick::SetSideCollision(const bool flag)
{
	return isSideCollision = flag;
}

bool Brick::SetTopCollision(const bool flag)
{
	return isTopCollision = flag;
}

bool Brick::SetBottomCollision(const bool flag)
{
	return isBottomCollision = flag;
}

bool Brick::IsSideCollision(BaseObject* obj)
{
	return obj->GetSideCollision();
}

bool Brick::IsBottomCollision(BaseObject* obj)
{
	return obj->GetBottomCollision();
}

bool Brick::IsTopCollision(BaseObject* obj)
{
	return obj->GetTopCollision();
}