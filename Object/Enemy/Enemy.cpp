#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"
#include "../../Include/UserType.h"

#include "Enemy.h"

#include "../../System/Camera/Camera.h"
#include "../../System/Image/Image.h"
#include "../../System/Image/ImageManager.h"
#include "../../System/Timer/TimeManager.h"

#include "../../System/Animation/Animation.h"
#include "../../System/Animation/MotionList.h"

Enemy::Enemy(const std::string & tag, const TPoint & pos, const TSize & size, const FrameDesc & desc)
	: BaseObject(tag, pos, size)
{
	state = EnemyState::MOVE_RIGHT;

	image = ImageManager::GetInstance()->AddFrameImage("Enemy", "Resource/Enemy.bmp",
		static_cast<int>(desc.imageSize.width), static_cast<int>(desc.imageSize.height),
		desc.frameX, desc.frameY, true, RGB(255, 255, 255));
	assert(image != nullptr);

	move[0] = 0;
	move[1] = 1;
	dead[0] = 2;

	motion = new MotionList;
	assert(motion != nullptr);

	Animation* ani = nullptr;


	{
		ani = new Animation;
		ani->Init(image);
		ani->SetPlayFrame(move, 2, true);
		ani->SetFPS(100);

		motion->AddMotion(0, ani);
	}

	{
		ani = new Animation;
		ani->Init(image);
		ani->SetPlayFrame(move, 2, true);
		ani->SetFPS(100);

		motion->AddMotion(1, ani);
	}

	{
		ani = new Animation;
		ani->Init(image);
		ani->SetPlayFrame(dead, 1, true);
		ani->SetFPS(100);

		motion->AddMotion(2, ani);
	}


	motion->Play(static_cast<int>(state));
}

Enemy::Enemy(const Enemy & other)
	: BaseObject(other)
{
	*this = other;
}

Enemy & Enemy::operator=(const Enemy & other)
{
	BaseObject::operator=(other);

	state = EnemyState::MOVE_RIGHT;

	desc = other.desc;

	image = other.image;


	motion = new MotionList;
	assert(motion != nullptr);

	for (auto a : *(other.motion->GetMap()))
		motion->GetMap()->insert(a);

	return *this;
}

void Enemy::Update()
{
	rect = TRectMakeCenter(pos.x, pos.y, size.width, size.height);

	if (state == EnemyState::MOVE_RIGHT)
	{
		pos.x += 1.f;
		SetState(EnemyState::MOVE_RIGHT);
		if (isLeftCollision)
		{
			SetState(EnemyState::MOVE_LEFT);
			isLeftCollision = false;
		}
	}

	if (state == EnemyState::MOVE_LEFT)
	{
		pos.x -= 1.f;
		SetState(EnemyState::MOVE_LEFT);
		if (isRightCollision)
		{
			SetState(EnemyState::MOVE_RIGHT);
			isRightCollision = false;
		}
	}

	motion->Update();

}


void Enemy::Render(HDC hdc, const TPoint* ptCamera)
{
	image->Render(hdc, static_cast<int>(rect.left - ptCamera->x),
		static_cast<int>(rect.top - ptCamera->y),
		static_cast<int>(motion->FindMotion(static_cast<int>(state))->GetFramePos().x),
		static_cast<int>(motion->FindMotion(static_cast<int>(state))->GetFramePos().y),
		motion->FindMotion(static_cast<int>(state))->GetFrameWidht(),
		motion->FindMotion(static_cast<int>(state))->GetFrameHeight());
}

void Enemy::SetState(const EnemyState & _state)
{
	state = _state;
	motion->Play(static_cast<int>(state));
}

bool Enemy::SetSideCollision(const bool flag)
{
	return isSideCollision = flag;
}

bool Enemy::SetTopCollision(const bool flag)
{
	return isTopCollision = flag;
}


bool Enemy::IsSideCollision(BaseObject* obj)
{
	return Collision::GetInstance()->SideCollision(this->rect, obj->GetRect());
}


bool Enemy::IsTopCollision(BaseObject* obj)
{
	return obj->GetTopCollision();
}
