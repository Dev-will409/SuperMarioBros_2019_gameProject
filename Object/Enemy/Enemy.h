#pragma once

#include "../../BaseObject/BaseObject.h"

enum class EnemyState
{
	MOVE_LEFT,
	MOVE_RIGHT,
	DEAD,
	MOVE_END,
};

class Image;
class MotionList;

class Enemy : public BaseObject
{
	MotionList*			motion;
	Image*				image;

	//Object 상태
	EnemyState			state;

	int					dead[1];
	int					move[2];

	//FrameRender 관련 속성
	FrameDesc			desc;

public:

	Enemy() = delete;
	~Enemy() = default;

	Enemy(const std::string& tag, const TPoint& pos, const TSize& size, const FrameDesc& desc);
	Enemy(const Enemy& other);

	Enemy& operator=(const Enemy& other);

	void Update();
	void Render(HDC hdc, const TPoint* ptCamera);


	void SetState(const EnemyState& _state);
	EnemyState GetState() const { return state; }


	bool SetSideCollision(const bool flag);
	bool SetTopCollision(const bool flag);

	bool IsSideCollision(BaseObject * obj);
	bool IsTopCollision(BaseObject * obj);

};
;