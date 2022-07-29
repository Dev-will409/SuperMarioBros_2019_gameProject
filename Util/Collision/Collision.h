#pragma once


class Collision
{


	TRect			temp;


	static Collision* instance;

	Collision() = default;
	~Collision() = default;

	Collision(const Collision& other) = delete;
	Collision& operator=(const Collision& other) = delete;


public:

	static Collision* GetInstance();

	static void Create();
	static void Delete();

	bool SideCollision(const TRect& object, const TRect& subject);
	bool TopCollision(const TRect& object, const TRect& subject);
	bool BottomCollision(const TRect& object, const TRect& subject);
	bool LeftCollision(const TRect& object, const TRect& subject);
	bool RightCollision(const TRect& object, const TRect& subject);
};