#pragma once
//SystemDef.h
//사용자 정의 헤더 인클루드
//사용자 정의 매크로 정의..




//사용자 정의 헤더
#include "../System/BackBuffer/BackBuffer.h"
#include "../Util/Util.h"
#include "../Util/Collision/Collision.h"

//Extern 변수들
extern		HWND		hWnd;
extern		HINSTANCE	hInst;

//사용자 정의 상수들
const unsigned int GAME_WIDTH = 600;
const unsigned int GAME_HEIGHT = 440;
const unsigned int GAME_GROUND = 384;
const unsigned int FIRST_BLOCK = 289;




//사용자 정의 매크로
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }} 
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }} 
