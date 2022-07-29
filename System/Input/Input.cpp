#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"

#include "Input.h"


Input* Input::instance = nullptr;

Input::Input()
{
	up.reset();
	down.reset();
}

Input::~Input()
{
}

Input* Input::GetInstance()
{
	assert(instance != nullptr);
	return instance;
}

void Input::Create()
{
	assert(instance == nullptr);
	instance = new Input;
}

void Input::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool Input::Down(const int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!down[key])
		{
			down.set(key, true);
			return true;
		}
	}
	else
	{
		down.set(key, false);
	}

	return false;
}

bool Input::Up(const int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		up.set(key, true);
	}
	else
	{
		if (up[key])
		{
			up.set(key, false);
			return true;
		}
	}

	return false;
}

bool Input::Press(const int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	return false;
}

bool Input::Toggle(const int key)
{
	if (GetKeyState(key) & 0x0001)
		return true;

	return false;
}
