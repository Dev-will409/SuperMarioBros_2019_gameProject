#pragma once

class Timer;

class TimeManager
{
	static TimeManager* instance;

	Timer*				timer;

	float				fps;

	TimeManager();
	~TimeManager();

public:
	TimeManager(const TimeManager& other) = delete;
	TimeManager& operator=(const TimeManager& other) = delete;

	static TimeManager* GetInstance();

	static void Create();
	static void Delete();

	bool Init(const float _fps);
	void Release();
	void Update();
	void Render(HDC hdc);

	float GetElapsedTime() const;
	float GetWorldTime() const;
	unsigned int GetFrameRate() const;
};