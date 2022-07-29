#pragma once

#include "../../BaseObject/BaseObject.h"

enum class MarioState
{
	MOVE_LEFT_IDLE,
	MOVE_RIGHT_IDLE,
	MOVE_LEFT,
	MOVE_RIGHT,
	JUMP_LEFT_UP,
	JUMP_RIGHT_UP,
	JUMP_LEFT_DOWN,
	JUMP_RIGHT_DOWN,
	MOVE_END,
};

class Image;
class MotionList;

class Mario : public BaseObject
{
	MotionList*			motion;
	Image*				image;


	//Object 惑怕
	MarioState			state;

	int					left_idle[1];
	int					right_idle[1];
	int					jump_left[1];
	int					jump_right[1];


	//Jump 包访 加己
	float				gravity;

	bool				isJump;

	//FrameRender 包访 加己
	FrameDesc			desc;


public:


	float				jumpPower;


	Mario() = delete;
	~Mario() = default;

	Mario(const std::string& tag, const TPoint& pos, const TSize& size, const FrameDesc& desc);
	Mario(const Mario& other);

	Mario& operator=(const Mario& other);

	void Update();
	void Render(HDC hdc, const TPoint* ptCamera);

	void Jump();

	void SetState(const MarioState& _state);

	MarioState GetState() const { return state; }

	bool SetSideCollision(const bool flag);
	bool SetTopCollision(const bool flag);
	bool SetBottomCollision(const bool flag);
	bool SetLeftCollision(const bool flag);
	bool SetRightCollision(const bool flag);

	bool IsSideCollision(BaseObject * obj);
	bool IsBottomCollision(BaseObject * obj);
	bool IsTopCollision(BaseObject * obj);
	bool IsLeftCollision(BaseObject * obj);
	bool IsRightCollision(BaseObject * obj);
};
