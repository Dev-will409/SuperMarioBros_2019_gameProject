#pragma once

class Timer
{
	__int64				current_time;
	__int64				last_time;
	__int64				period_friquency;

	float				time_scale;
	float				time_elapsed;

	float				world_time;
	float				fps_time_elapsed;

	unsigned long		frame_rate;
	unsigned long		fps_frame_count;

public:
	Timer();
	~Timer() = default;

	void Tick(const float lock_fps = 0.f);

	inline unsigned long GetFrameRate() const { return frame_rate; }

	inline float GetElapsedTime() const { return time_elapsed; }
	inline float GetWorldTime() const { return world_time; }
};