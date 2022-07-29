#include "../../Include/SystemH.h"

#include "Timer.h"


Timer::Timer()
{
	assert(QueryPerformanceFrequency((LARGE_INTEGER*)&period_friquency));

	QueryPerformanceCounter((LARGE_INTEGER*)&last_time);
	time_scale = 1.f / period_friquency;

	frame_rate = 0;
	fps_frame_count = 0;

	fps_time_elapsed = 0.f;
	world_time = 0.f;
}

void Timer::Tick(const float lock_fps)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&current_time);
	time_elapsed = (current_time - last_time) * time_scale;

	if (lock_fps > 0.f)
	{
		while (time_elapsed < 1.f / lock_fps)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&current_time);
			time_elapsed = (current_time - last_time) * time_scale;
		}
	}

	last_time = current_time;
	world_time += time_elapsed;

	fps_time_elapsed += time_elapsed;
	++fps_frame_count;

	if (fps_time_elapsed > 1.f)
	{
		frame_rate = fps_frame_count;
		fps_frame_count = 0;
		fps_time_elapsed = 0.f;
	}
}
