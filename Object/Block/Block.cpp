#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"
#include "../../Include/UserType.h"

#include "Block.h"

#include "../../System/Image/Image.h"
#include "../../System/Image/ImageManager.h"

Block::Block(const std::string & tag, const TPoint & pos, const TSize & size) : BaseObject(tag,pos,size)
{
	image = ImageManager::GetInstance()->AddImage("Block", "Resource/Block.bmp", 32, 32, true, RGB(255, 255, 255));
	assert(image != nullptr);
}

Block::Block(const Block & other) : BaseObject(other)
{
	*this = other;
}

Block & Block::operator=(const Block & other)
{
	BaseObject::operator=(other);

	image = other.image;

	return *this;
}


void Block::Update()
{
}

void Block::Render(HDC hdc)
{
	image->Render(hdc, static_cast<int>(rect.left),
		static_cast<int>(rect.top));
}

void Block::Render(HDC hdc, const TPoint* pt)
{
	image->Render(hdc,
		static_cast<int>(rect.left - pt->x),
		static_cast<int>(rect.top - pt->y));
}


bool Block::SetSideCollision(const bool flag)
{
	return isSideCollision = flag;
}

bool Block::SetTopCollision(const bool flag)
{
	return isTopCollision = flag;
}

bool Block::SetBottomCollision(const bool flag)
{
	return isBottomCollision = flag;
}

bool Block::IsSideCollision(BaseObject* obj)
{
	return obj->GetSideCollision();
}

bool Block::IsBottomCollision(BaseObject* obj)
{
	return obj->GetBottomCollision();
}

bool Block::IsTopCollision(BaseObject* obj)
{
	return obj->GetTopCollision();
}