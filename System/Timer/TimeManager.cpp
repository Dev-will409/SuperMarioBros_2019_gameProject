#include "../../Include/SystemH.h"
#include "TimeManager.h"
#include "Timer.h"


TimeManager* TimeManager::instance = nullptr;

TimeManager::TimeManager() : fps(0.f)
{
	timer = new Timer;
}

TimeManager::~TimeManager()
{
	if (timer)
	{
		delete timer;
		timer = nullptr;
	}
}

TimeManager* TimeManager::GetInstance()
{
	assert(instance != nullptr);
	return instance;
}

void TimeManager::Create()
{
	assert(instance == nullptr);
	instance = new TimeManager;
}

void TimeManager::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool TimeManager::Init(const float _fps)
{
	fps = _fps;

	return true;
}

void TimeManager::Release()
{
}

void TimeManager::Update()
{
	if (timer)
		timer->Tick(fps);
}

void TimeManager::Render(HDC hdc)
{
#if defined(DEBUG) || defined(_DEBUG)
	std::string str = "FPS : ";
	str += std::to_string(timer->GetFrameRate());

	SetBkMode(hdc, TRANSPARENT);
	TextOutA(hdc, 5, 5, str.c_str(), static_cast<int>(str.size()));
#endif // #if defined(DEBUG) || defined(_DEBUG)
}

float TimeManager::GetElapsedTime() const
{
	return timer->GetElapsedTime();
}

float TimeManager::GetWorldTime() const
{
	return timer->GetWorldTime();
}

unsigned int TimeManager::GetFrameRate() const
{
	return timer->GetFrameRate();
}
