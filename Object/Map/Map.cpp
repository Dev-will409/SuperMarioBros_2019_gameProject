#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"
#include "../../Include/UserType.h"

#include "Map.h"

#include "../../System/Image/Image.h"
#include "../../System/Image/ImageManager.h"

Map::Map(const std::string& tag, const TPoint& pos, const TSize& size)
	: BaseObject(tag, pos, size)
{
	background = ImageManager::GetInstance()->AddImage("Map", "Resource/Map.bmp",
		static_cast<int>(size.width), static_cast<int>(size.height));
	assert(background != nullptr);

	offsetX = 0;
}

Map::Map(const Map& other)
	: BaseObject(other)
{
	*this = other;
}


Map & Map::operator=(const Map& other)
{
	background = other.background;
	return *this;
}

bool Map::Init()
{
	return true;
}

void Map::Release()
{
}

void Map::Update()
{
	offsetX += 2;
}

void Map::Render(HDC hdc)
{
	background->Render(hdc, 0, 0);
}

void Map::Render(HDC hdc, const TPoint* ptCamera)
{
	if (ptCamera)
		background->Render(hdc, 0, 0,
			static_cast<int>(ptCamera->x), static_cast<int>(ptCamera->y),
			GAME_WIDTH, GAME_HEIGHT);
	else
		background->Render(hdc, 0, 0);
}
