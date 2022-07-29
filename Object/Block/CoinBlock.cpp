#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"
#include "../../Include/UserType.h"

#include "CoinBlock.h"

#include "../../System/Image/Image.h"
#include "../../System/Image/ImageManager.h"
#include "../../Effect/Effect.h"

CoinBlock::CoinBlock(const std::string & tag, const TPoint & pos, const TSize & size) : BaseObject(tag, pos, size)
{
	image = ImageManager::GetInstance()->AddImage("CoinBlock", "Resource/CoinBlock.bmp", 32, 32, true, RGB(255, 255, 255));
	assert(image != nullptr);
	state = CoinBlockState::UNHITTED;

}

CoinBlock::CoinBlock(const CoinBlock & other) : BaseObject(other)
{
	*this = other;
}

CoinBlock & CoinBlock::operator=(const CoinBlock & other)
{
	BaseObject::operator=(other);

	image = other.image;
	state = CoinBlockState::UNHITTED;

	return *this;
}


void CoinBlock::Update()
{
	if (isBottomCollision)
	{
		ImageManager::GetInstance()->DelImage("CoinBlock");
		image = ImageManager::GetInstance()->AddImage("CoinBlock", "Resource/HitCoinBlock.bmp", 32, 32, true, RGB(255, 255, 255));
		assert(image != nullptr);
		state = CoinBlockState::HITTED;
	}
}

void CoinBlock::Render(HDC hdc)
{
	image->Render(hdc, static_cast<int>(rect.left),
		static_cast<int>(rect.top));
}

void CoinBlock::Render(HDC hdc, const TPoint* pt)
{
	image->Render(hdc,
		static_cast<int>(rect.left - pt->x),
		static_cast<int>(rect.top - pt->y));
}


bool CoinBlock::SetSideCollision(const bool flag)
{
	return isSideCollision = flag;
}

bool CoinBlock::SetTopCollision(const bool flag)
{
	return isTopCollision = flag;
}

bool CoinBlock::SetBottomCollision(const bool flag)
{
	return isBottomCollision = flag;
}

bool CoinBlock::IsSideCollision(BaseObject* obj)
{
	return obj->GetSideCollision();
}

bool CoinBlock::IsBottomCollision(BaseObject* obj)
{
	return obj->GetBottomCollision();
}

bool CoinBlock::IsTopCollision(BaseObject* obj)
{
	return obj->GetTopCollision();
}
