#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"
#include "../../Include/UserType.h"

#include "Camera.h"

Camera* Camera::instance = nullptr;

Camera::~Camera()
{
}

Camera * Camera::GetInstance()
{
	assert(instance != nullptr);
	return instance;
}

void Camera::Create()
{
	assert(instance == nullptr);
	instance = new Camera;
}

void Camera::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool Camera::Init(TPoint* const target, const TSize& client, const TSize& world)
{
	if (target == nullptr)
		return false;

	pTarget = target;

	rcClient = client;
	rcWorld = world;

	pCamera = new TPoint;

	return true;
}

void Camera::Update()
{
	if (pTarget == nullptr)
	{
		pCamera->x = 0;
		return;
	}

	pCamera->x = pTarget->x - (rcClient.width * 0.5f);

	if (pCamera->x < 0)
		pCamera->x = 0;
	if (pCamera->x > rcWorld.width - rcClient.width)
		pCamera->x = rcWorld.width - rcClient.width;
}
