#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"
#include "../../Include/UserType.h"

#include "Mario.h"

#include "../../System/Camera/Camera.h"
#include "../../System/Input/Input.h"
#include "../../System/Image/Image.h"
#include "../../System/Image/ImageManager.h"
#include "../../System/Timer/TimeManager.h"

#include "../../System/Animation/Animation.h"
#include "../../System/Animation/MotionList.h"


Mario::Mario(const std::string& tag, const TPoint& pos, const TSize& size, const FrameDesc& desc)
	: BaseObject(tag, pos, size)
{
	state = MarioState::MOVE_RIGHT_IDLE;

	image = ImageManager::GetInstance()->AddFrameImage("Mario", "Resource/Mario.bmp",
		static_cast<int>(desc.imageSize.width), static_cast<int>(desc.imageSize.height),
		desc.frameX, desc.frameY, true, RGB(255, 255, 255));
	assert(image != nullptr);

	left_idle[0] = 0;
	right_idle[0] = 3;
	jump_left[0] = 12;
	jump_right[0] = 15;

	jumpPower = 0.f;
	gravity = 0.1f;
	isJump = false;

	motion = new MotionList;
	assert(motion != nullptr);

	Animation* ani = nullptr;

	{
		ani = new Animation;
		ani->Init(image);
		ani->SetPlayFrame(left_idle, 1, true);
		ani->SetFPS(100);

		motion->AddMotion(0, ani);
	}

	{
		ani = new Animation;
		ani->Init(image);
		ani->SetPlayFrame(right_idle, 1, true);
		ani->SetFPS(100);

		motion->AddMotion(1, ani);
	}

	int index = 6;
	for (int i = 2; i < desc.frameY - 2; ++i, index += desc.frameX)
	{
		ani = new Animation;
		ani->Init(image);
		ani->SetPlayFrame(index , index + (desc.frameX), false, true);
		ani->SetFPS(100);

		motion->AddMotion(i, ani);
	}

	{
		ani = new Animation;
		ani->Init(image);
		ani->SetPlayFrame(jump_left, 1, true);
		ani->SetFPS(100);

		motion->AddMotion(4, ani);
	}


	{
		ani = new Animation;
		ani->Init(image);
		ani->SetPlayFrame(jump_right, 1, true);
		ani->SetFPS(100);

		motion->AddMotion(5, ani);
	}

	{
		ani = new Animation;
		ani->Init(image);
		ani->SetPlayFrame(jump_left, 1, true);
		ani->SetFPS(100);

		motion->AddMotion(6, ani);
	}


	{
		ani = new Animation;
		ani->Init(image);
		ani->SetPlayFrame(jump_right, 1, true);
		ani->SetFPS(100);

		motion->AddMotion(7, ani);
	}


	motion->Play(static_cast<int>(state));
}

Mario::Mario(const Mario& other)
	: BaseObject(other)
{
	*this = other;
}

Mario& Mario::operator=(const Mario & other)
{
	BaseObject::operator=(other);

	state = MarioState::MOVE_RIGHT_IDLE;

	desc = other.desc;

	image = other.image;

	jumpPower = other.jumpPower;
	gravity = other.gravity;
	isJump = false;

	motion = new MotionList;
	assert(motion != nullptr);

	for (auto a : *(other.motion->GetMap()))
		motion->GetMap()->insert(a);

	return *this;
}

void Mario::Update()
{
	rect = TRectMakeCenter(pos.x, pos.y, size.width, size.height);

	if (Input::GetInstance()->Press(VK_LEFT))
	{
		if (state == MarioState::JUMP_LEFT_UP || state == MarioState::JUMP_LEFT_DOWN)
		{
			pos.x -= 2.f;
		}
		else if (state == MarioState::JUMP_RIGHT_UP || state == MarioState::JUMP_RIGHT_DOWN)
		{
			pos.x -= 2.f;
		}
		else
		{
			pos.x -= 2.f;
			SetState(MarioState::MOVE_LEFT);
		}
		
	}
	if (Input::GetInstance()->Up(VK_LEFT))
	{
		if (state == MarioState::JUMP_LEFT_UP || state == MarioState::JUMP_LEFT_DOWN)
		{

		}
		else
		{
			SetState(MarioState::MOVE_LEFT_IDLE);
		}
	}
	if (Input::GetInstance()->Press(VK_RIGHT))
	{
		if (state == MarioState::JUMP_RIGHT_UP || state == MarioState::JUMP_RIGHT_DOWN)
		{
			pos.x += 2.f;
		}
		else if (state == MarioState::JUMP_LEFT_UP || state == MarioState::JUMP_LEFT_DOWN)
		{
			pos.x += 2.f;
		}
		else
		{
			pos.x += 2.f;
			SetState(MarioState::MOVE_RIGHT);
		}
	}
	if (Input::GetInstance()->Up(VK_RIGHT))
	{
		if (state == MarioState::JUMP_RIGHT_UP || state == MarioState::JUMP_RIGHT_DOWN)
		{

		}
		else
		{
			SetState(MarioState::MOVE_RIGHT_IDLE);
		}
	}
	if (Input::GetInstance()->Down(VK_SPACE))
	{
		if (state == MarioState::MOVE_LEFT || state == MarioState::MOVE_LEFT_IDLE)
		{
			SetState(MarioState::JUMP_LEFT_UP); 
			jumpPower = 6.f;
		}
		if (state == MarioState::MOVE_RIGHT || state == MarioState::MOVE_RIGHT_IDLE)
		{
			
			SetState(MarioState::JUMP_RIGHT_UP);
			jumpPower = 6.f;
		}
	}

	

	if ((state == MarioState::MOVE_LEFT || state == MarioState::MOVE_LEFT_IDLE) && (pos.y < GAME_GROUND) && !isBottomCollision)
	{ 
		if (state == MarioState::JUMP_LEFT_DOWN)
		{

		}
		else
		{
			jumpPower += gravity;
			pos.y += jumpPower;

			if (pos.y >= GAME_GROUND)
			{
				pos.y = GAME_GROUND;
				state = MarioState::MOVE_LEFT_IDLE;
			}
		}
	}
	if ((state == MarioState::MOVE_RIGHT || state == MarioState::MOVE_RIGHT_IDLE) && (pos.y < GAME_GROUND) && !isBottomCollision)
	{
		if (state == MarioState::JUMP_RIGHT_DOWN)
		{

		}
		else
		{
			jumpPower += gravity;
			pos.y += jumpPower;

			if (pos.y >= GAME_GROUND)
			{
				pos.y = GAME_GROUND;
				state = MarioState::MOVE_RIGHT_IDLE;
			}
		}
	}

	if (state == MarioState::JUMP_LEFT_UP || state == MarioState::JUMP_RIGHT_UP || state == MarioState::JUMP_LEFT_DOWN || state == MarioState::JUMP_RIGHT_DOWN)
	{
		if (!isJump)
		{
			Jump();
		}
	}

	if (isTopCollision)
	{
		if (state == MarioState::JUMP_LEFT_UP)
			state = MarioState::JUMP_LEFT_DOWN;
		if (state == MarioState::JUMP_RIGHT_UP)
			state = MarioState::JUMP_RIGHT_DOWN;
		isTopCollision = false;
	}
	else if (isRightCollision)
	{
		if (state == MarioState::MOVE_LEFT || state == MarioState::JUMP_LEFT_DOWN || state == MarioState::JUMP_LEFT_UP)
		{
			this->pos.x = nowPosX;
		}
		isRightCollision = false;
	}
	else if (isLeftCollision)
	{
		if (state == MarioState::MOVE_RIGHT || state == MarioState::JUMP_RIGHT_DOWN || state == MarioState::JUMP_RIGHT_UP)
		{
			this->pos.x = nowPosX;
		}
		isLeftCollision = false;
	}
	else if (isBottomCollision)
	{
		if (state == MarioState::JUMP_LEFT_UP || state == MarioState::JUMP_RIGHT_UP)
		{

		}
		else
		{
			this->pos.y = nowPosY;
		}
		if (state == MarioState::JUMP_LEFT_DOWN)
			state = MarioState::MOVE_LEFT_IDLE;
		if (state == MarioState::JUMP_RIGHT_DOWN)
			state = MarioState::MOVE_RIGHT_IDLE;
		isBottomCollision = false;
	}

	motion->Update();
	

}

void Mario::Render(HDC hdc, const TPoint* ptCamera)
{
	image->Render(hdc, static_cast<int>(rect.left - ptCamera->x),
		static_cast<int>(rect.top - ptCamera->y),
		static_cast<int>(motion->FindMotion(static_cast<int>(state))->GetFramePos().x),
		static_cast<int>(motion->FindMotion(static_cast<int>(state))->GetFramePos().y),
		motion->FindMotion(static_cast<int>(state))->GetFrameWidht(),
		motion->FindMotion(static_cast<int>(state))->GetFrameHeight());
}

void Mario::Jump()
{
	if (state == MarioState::JUMP_LEFT_UP)
	{
		jumpPower -= gravity;
		pos.y -= jumpPower;

		if (jumpPower < 0.f)
		{
			jumpPower = 0.f;
			state = MarioState::JUMP_LEFT_DOWN;
		}
	}
	if (state == MarioState::JUMP_RIGHT_UP)
	{
		jumpPower -= gravity;
		pos.y -= jumpPower;

		if (jumpPower < 0.f)
		{
			jumpPower = 0.f;
			state = MarioState::JUMP_RIGHT_DOWN;
		}
	}
	if (state == MarioState::JUMP_LEFT_DOWN)
	{
		jumpPower += gravity;
		pos.y += jumpPower;

		if (pos.y >= GAME_GROUND)
		{
			pos.y = GAME_GROUND;
			state = MarioState::MOVE_LEFT_IDLE;
		}
	}
	if (state == MarioState::JUMP_RIGHT_DOWN)
	{
		jumpPower += gravity;
		pos.y += jumpPower;

		if (pos.y >= GAME_GROUND)
		{
			pos.y = GAME_GROUND;
			state = MarioState::MOVE_RIGHT_IDLE;
		}
	}
}

void Mario::SetState(const MarioState & _state)
{
	state = _state;
	motion->Play(static_cast<int>(state));
}

bool Mario::SetSideCollision(const bool flag)
{
	return isSideCollision = flag;
}

bool Mario::SetTopCollision(const bool flag)
{
	return isTopCollision = flag;
}

bool Mario::SetBottomCollision(const bool flag)
{
	return isBottomCollision = flag;
}

bool Mario::SetLeftCollision(const bool flag)
{
	return isLeftCollision = flag;
}

bool Mario::SetRightCollision(const bool flag)
{
	return isRightCollision = flag;
}

bool Mario::IsSideCollision(BaseObject* obj)
{
	return Collision::GetInstance()->SideCollision(this->rect, obj->GetRect());
}

bool Mario::IsBottomCollision(BaseObject* obj)
{
	return Collision::GetInstance()->BottomCollision(this->rect, obj->GetRect());
}

bool Mario::IsTopCollision(BaseObject* obj)
{
	return Collision::GetInstance()->TopCollision(this->rect, obj->GetRect());
}

bool Mario::IsLeftCollision(BaseObject * obj)
{
	return Collision::GetInstance()->LeftCollision(this->rect,obj->GetRect());
}

bool Mario::IsRightCollision(BaseObject * obj)
{
	return Collision::GetInstance()->RightCollision(this->rect, obj->GetRect());
}
