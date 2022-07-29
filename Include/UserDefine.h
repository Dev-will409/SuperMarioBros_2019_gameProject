#pragma once
//SystemDef.h
//����� ���� ��� ��Ŭ���
//����� ���� ��ũ�� ����..




//����� ���� ���
#include "../System/BackBuffer/BackBuffer.h"
#include "../Util/Util.h"
#include "../Util/Collision/Collision.h"

//Extern ������
extern		HWND		hWnd;
extern		HINSTANCE	hInst;

//����� ���� �����
const unsigned int GAME_WIDTH = 600;
const unsigned int GAME_HEIGHT = 440;
const unsigned int GAME_GROUND = 384;
const unsigned int FIRST_BLOCK = 289;




//����� ���� ��ũ��
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }} 
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }} 
