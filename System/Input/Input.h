#pragma once

#include <bitset>

//#define KEYMAX 256
const UINT KEYMAX = 256;

class Input
{
	std::bitset<KEYMAX> up;
	std::bitset<KEYMAX> down;

	static Input* instance;

	Input();
	~Input();
public:

	static Input* GetInstance();

	static void Create();
	static void Delete();

	bool Down(const int key);
	bool Up(const int key);
	bool Press(const int key);

	bool Toggle(const int key);
};

