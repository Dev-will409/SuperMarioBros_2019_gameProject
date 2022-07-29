#pragma once

#include "GameBase.h"

class Map;
class Mario;
class Enemy;
class Block;
class CoinBlock;
class Brick;
class Pipe;
class Effect;

class GameMain : public GameBase
{
	Map*		background;

	Mario*		mario;

	Effect*		coineffect;

	Block*		block;
	Block*		block1;
	Block*		block2;
	Block*		block3;

	CoinBlock*	coinblock;
	CoinBlock*	coinblock1;
	CoinBlock*	coinblock2;
	CoinBlock*	coinblock3;
	Brick*		brick;
	Pipe*		pipe;

	Enemy*		enemy;
	Enemy*		enemy1;

	//
	TSize			world;
	TSize			client;

public:
	GameMain();
	~GameMain();

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};