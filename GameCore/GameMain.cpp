#include "../Include/SystemH.h"
#include "../Include/UserDefine.h"
#include "../Include/UserType.h"

#include "GameMain.h"

//Manager
#include "../System/Camera/Camera.h"
#include "../System/Image/ImageManager.h"
#include "../System/Timer/TimeManager.h"
#include "../System/Input/Input.h"
#include "../BaseObject/ObjectManager.h"

//Object
#include "../Object/Mario/Mario.h"
#include "../Object/Map/Map.h"
#include "../Object/Enemy/Enemy.h"
#include "../Object/Block/Block.h"
#include "../Object/Block/CoinBlock.h"
#include "../Object/Block/Brick.h"
#include "../Object/Block/Pipe.h"
#include "../Effect/Effect.h"


GameMain::GameMain()
{
	client = TSize(static_cast<float>(GAME_WIDTH), static_cast<float>(GAME_HEIGHT));
	world = TSize(6784.f, 920.f);

	//Create Manager
	Camera::Create();
	ObjectManager::Create();
	ImageManager::Create();
	Collision::Create();

	//Create Object
	{
		background = new Map("Map", TPoint(client.width * 0.5f, client.height * 0.5f), world);
	}
	
	{
		FrameDesc desc(TSize(102.f, 204.f), 3, 6);
		mario = new Mario("Mario", TPoint(100.f, GAME_GROUND), TSize(34.f, 34.f),desc);
	}

	{
		FrameDesc desc(TSize(96.f, 32.f), 3, 1);
		enemy = new Enemy("Enemy", TPoint(150.f, GAME_GROUND), TSize(32.f, 32.f), desc);
	}


	{
		block = new Block("Block", TPoint(658.f, FIRST_BLOCK), TSize(32.f, 32.f));
		ObjectManager::GetInstance()->AddObject(block);
		block2 = new Block("Block", TPoint(722.f, FIRST_BLOCK), TSize(32.f, 32.f));
		ObjectManager::GetInstance()->AddObject(block2);
		block3 = new Block("Block", TPoint(786.f, FIRST_BLOCK), TSize(32.f, 32.f));
		ObjectManager::GetInstance()->AddObject(block3);
	}
	{

	}

	{
		coinblock = new CoinBlock("CoinBlock", TPoint(530.f, FIRST_BLOCK), TSize(32.f, 32.f));
		coinblock1 = new CoinBlock("CoinBlock", TPoint(690.f, FIRST_BLOCK), TSize(32.f, 32.f));
		//coinblock = new CoinBlock("CoinBlock", TPoint(754.f, FIRST_BLOCK), TSize(32.f, 32.f));
		//coinblock = new CoinBlock("CoinBlock", TPoint(530.f, FIRST_BLOCK), TSize(32.f, 32.f));
	}

	{
		pipe = new Pipe("Pipe", TPoint(400.f, GAME_GROUND - 15), TSize(64.f, 64.f));
		ObjectManager::GetInstance()->AddObject(pipe);
	}

	{
		brick = new Brick("Brick", TPoint(800.f, GAME_GROUND -1), TSize(32.f, 32.f));
		ObjectManager::GetInstance()->AddObject(brick);
	}
	//Create Effect
	{
		FrameDesc desc(TSize(90.f, 30.f), 3, 1);
		coineffect = new Effect("Effect", TPoint(0, 0), TSize(30.f, 30.f), desc);
	}



}

GameMain::~GameMain()
{

	SAFE_DELETE(coineffect);

	//Delete Manager
	Collision::GetInstance()->Delete();
	ImageManager::GetInstance()->Delete();
	ObjectManager::GetInstance()->Delete();
	Camera::GetInstance()->Delete();

}

bool GameMain::Init()
{
	GameBase::Init();


	Camera::GetInstance()->Init(mario->GetPosition(), client, world);

	return true;
}

void GameMain::Release()
{
	GameBase::Release();
}

void GameMain::Update()
{
	GameBase::Update();

	background->Update();
	mario->Update();
	
	// enemy
	enemy->Update();

	ObjectManager::GetInstance()->CheckCollision(enemy);
	

	// coinblock
	if (mario->IsTopCollision(coinblock))
	{
		mario->SetTopCollision(true);
		coinblock->SetBottomCollision(true);
		if (coinblock->GetState() == CoinBlockState::UNHITTED)
		{
			coineffect->StartEffect(TPoint(coinblock->GetPosition()->x, coinblock->GetPosition()->y - 32));
		}
	}
	else if (mario->IsBottomCollision(coinblock))
	{
		mario->GetNowPosY(mario->GetPosition()->y);
		mario->SetBottomCollision(true);
	}
	else if (mario->IsLeftCollision(coinblock))
	{
		mario->GetNowPosX(mario->GetPosition()->x);
		mario->SetLeftCollision(true);
	}
	else if (mario->IsRightCollision(coinblock))
	{
		mario->GetNowPosX(mario->GetPosition()->x);
		mario->SetRightCollision(true);
	}

	if (mario->IsTopCollision(coinblock1))
	{
		mario->SetTopCollision(true);
		coinblock1->SetBottomCollision(true);
		if (coinblock1->GetState() == CoinBlockState::UNHITTED)
		{
			coineffect->StartEffect(TPoint(coinblock1->GetPosition()->x, coinblock1->GetPosition()->y - 32));
		}
	}
	else if (mario->IsBottomCollision(coinblock1))
	{
		mario->GetNowPosY(mario->GetPosition()->y);
		mario->SetBottomCollision(true);
	}
	else if (mario->IsLeftCollision(coinblock1))
	{
		mario->GetNowPosX(mario->GetPosition()->x);
		mario->SetLeftCollision(true);
	}
	else if (mario->IsRightCollision(coinblock1))
	{
		mario->GetNowPosX(mario->GetPosition()->x);
		mario->SetRightCollision(true);
	}


	if (mario->IsBottomCollision(enemy))
	{
		mario->jumpPower = 6.0f;
		mario->Jump();
	}

	ObjectManager::GetInstance()->CheckCollision(mario);

	coinblock->Update();
	ObjectManager::GetInstance()->Update();
	//ObjectManager::GetInstance()->LateUpdate();
	coineffect->Update();

	Camera::GetInstance()->Update();

}

void GameMain::Render(HDC hdc)
{
	HDC backDC = GetBackBuffer()->GetMemDC();
	PatBlt(backDC, 0, 0, GAME_WIDTH, GAME_HEIGHT, WHITENESS);
	/////////////////////////////////////////////////////////////////

	background->Render(backDC,Camera::GetInstance()->GetCamera());
	mario->Render(backDC,Camera::GetInstance()->GetCamera());
	enemy->Render(backDC, Camera::GetInstance()->GetCamera());
	coinblock->Render(backDC, Camera::GetInstance()->GetCamera());

	ObjectManager::GetInstance()->Render(backDC, Camera::GetInstance()->GetCamera());
	coineffect->Render(backDC, Camera::GetInstance()->GetCamera());

	TimeManager::GetInstance()->Render(backDC);

	/////////////////////////////////////////////////////////////////
	GetBackBuffer()->Render(hdc, 0, 0);

}


