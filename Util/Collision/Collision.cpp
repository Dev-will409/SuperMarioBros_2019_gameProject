#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"
#include "../../Include/UserType.h"

#include "Collision.h"



Collision* Collision::instance = nullptr;

Collision * Collision::GetInstance()
{
	assert(instance != nullptr);
	return instance;
}

void Collision::Create()
{
	assert(instance == nullptr);
	instance = new Collision;
}

void Collision::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool Collision::SideCollision(const TRect & object, const TRect & subject)
{
	float objectwidth = object.right - object.left;
	float objectheight = object.bottom - object.top;
	float objectX = (object.right + object.left) * 0.5;
	float objectY = (object.bottom + object.top) * 0.5;

	float subjectwidth = subject.right - subject.left;
	float subjectheight = subject.bottom - subject.top;
	float subjectX = (subject.right + subject.left) * 0.5;
	float subjectY = (subject.bottom + subject.top) * 0.5;

	float w = 0.5 * (objectwidth + subjectwidth);
	float h = 0.5 * (objectheight + subjectheight);
	float dx = objectX - subjectX;
	float dy = objectY - subjectY;

	if (abs(dx) <= w && abs(dy) <= h)
	{
		float wy = w * dy;
		float hx = h * dx;
		if (wy > hx) 
		{
			if (wy <= -hx)
				return true;
		}
		else
		{
			if (wy > -hx)
				return true;
		}
	}
	return false;
}

bool Collision::TopCollision(const TRect & object, const TRect & subject)
{
	float objectwidth = object.right - object.left;
	float objectheight = object.bottom - object.top;
	float objectX = (object.right + object.left) * 0.5;
	float objectY = (object.bottom + object.top) * 0.5;

	float subjectwidth = subject.right - subject.left;
	float subjectheight = subject.bottom - subject.top;
	float subjectX = (subject.right + subject.left) * 0.5;
	float subjectY = (subject.bottom + subject.top) * 0.5;

	float w = 0.5 * (objectwidth + subjectwidth);
	float h = 0.5 * (objectheight + subjectheight);
	float dx = objectX - subjectX;
	float dy = objectY - subjectY;

	if (abs(dx) <= w && abs(dy) <= h)
	{
		float wy = w * dy;
		float hx = h * dx;
		
		if (wy > hx)
			if (wy > -hx)
				return true;
	}
	return false;
}

bool Collision::BottomCollision(const TRect & object,const TRect & subject)
{
	float objectwidth = object.right - object.left;
	float objectheight = object.bottom - object.top;
	float objectX = (object.right + object.left) * 0.5;
	float objectY = (object.bottom + object.top) * 0.5;

	float subjectwidth = subject.right - subject.left;
	float subjectheight = subject.bottom - subject.top;
	float subjectX = (subject.right + subject.left) * 0.5;
	float subjectY = (subject.bottom + subject.top) * 0.5;

	float w = 0.5 * (objectwidth + subjectwidth);
	float h = 0.5 * (objectheight + subjectheight);
	float dx = objectX - subjectX;
	float dy = objectY - subjectY;

	if (abs(dx) <= w && abs(dy) <= h)
	{
		float wy = w * dy;
		float hx = h * dx;

		if (wy <= hx)
			if (wy <= -hx)
				return true;
	}
	return false;
}

bool Collision::LeftCollision(const TRect & object, const TRect & subject)
{
	float objectwidth = object.right - object.left;
	float objectheight = object.bottom - object.top;
	float objectX = (object.right + object.left) * 0.5;
	float objectY = (object.bottom + object.top) * 0.5;

	float subjectwidth = subject.right - subject.left;
	float subjectheight = subject.bottom - subject.top;
	float subjectX = (subject.right + subject.left) * 0.5;
	float subjectY = (subject.bottom + subject.top) * 0.5;

	float w = 0.5 * (objectwidth + subjectwidth);
	float h = 0.5 * (objectheight + subjectheight);
	float dx = objectX - subjectX;
	float dy = objectY - subjectY;

	if (abs(dx) <= w && abs(dy) <= h)
	{
		float wy = w * dy;
		float hx = h * dx;
		if (wy > hx)
		{
			if (wy <= -hx)
				return true;
		}
	}
	return false;
}

bool Collision::RightCollision(const TRect & object, const TRect & subject)
{
	float objectwidth = object.right - object.left;
	float objectheight = object.bottom - object.top;
	float objectX = (object.right + object.left) * 0.5;
	float objectY = (object.bottom + object.top) * 0.5;

	float subjectwidth = subject.right - subject.left;
	float subjectheight = subject.bottom - subject.top;
	float subjectX = (subject.right + subject.left) * 0.5;
	float subjectY = (subject.bottom + subject.top) * 0.5;

	float w = 0.5 * (objectwidth + subjectwidth);
	float h = 0.5 * (objectheight + subjectheight);
	float dx = objectX - subjectX;
	float dy = objectY - subjectY;

	if (abs(dx) <= w && abs(dy) <= h)
	{
		float wy = w * dy;
		float hx = h * dx;

		if (wy <= hx)
		{
			if (wy > -hx)
				return true;
		}
	}
	return false;
}

