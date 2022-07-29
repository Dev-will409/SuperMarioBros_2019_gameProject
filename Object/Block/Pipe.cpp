#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"
#include "../../Include/UserType.h"

#include "Pipe.h"

#include "../../System/Image/Image.h"
#include "../../System/Image/ImageManager.h"

Pipe::Pipe(const std::string & tag, const TPoint & pos, const TSize & size) : BaseObject(tag, pos, size)
{
	image = ImageManager::GetInstance()->AddImage("Pipe", "Resource/Pipe.bmp", 64, 64, true, RGB(255, 255, 255));
	assert(image != nullptr);
}

Pipe::Pipe(const Pipe & other) : BaseObject(other)
{
	*this = other;
}

Pipe & Pipe::operator=(const Pipe & other)
{
	BaseObject::operator=(other);

	image = other.image;

	return *this;
}


void Pipe::Update()
{
}

void Pipe::Render(HDC hdc)
{
	image->Render(hdc, static_cast<int>(rect.left),
		static_cast<int>(rect.top));
}

void Pipe::Render(HDC hdc, const TPoint* pt)
{
	image->Render(hdc,
		static_cast<int>(rect.left - pt->x),
		static_cast<int>(rect.top - pt->y));
}


bool Pipe::SetSideCollision(const bool flag)
{
	return isSideCollision = flag;
}

bool Pipe::SetTopCollision(const bool flag)
{
	return isTopCollision = flag;
}

bool Pipe::SetBottomCollision(const bool flag)
{
	return isBottomCollision = flag;
}

bool Pipe::IsSideCollision(BaseObject* obj)
{
	return obj->GetSideCollision();
}

bool Pipe::IsBottomCollision(BaseObject* obj)
{
	return obj->GetBottomCollision();
}

bool Pipe::IsTopCollision(BaseObject* obj)
{
	return obj->GetTopCollision();
}