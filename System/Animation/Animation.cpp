#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"

#include "Animation.h"

#include "../Image/Image.h"


Animation::Animation() : frame_number(0), frame_width(0), frame_height(0),
loop(false), play(false), frame_update_time(0.f), elapsed_time(0.f), now_play_index(0)
{
}

Animation::~Animation()
{
}

Animation::Animation(const Animation& other)
{
	*this = other;
}

Animation& Animation::operator=(const Animation& other)
{
	frame_list.assign(other.frame_list.size(), TPoint());
	std::copy(other.frame_list.begin(), other.frame_list.end(), frame_list.begin());

	play_list.assign(other.play_list.size(), int(0));
	std::copy(other.play_list.begin(), other.play_list.end(), play_list.begin());

	frame_number = other.frame_number;
	frame_width = other.frame_width;
	frame_height = other.frame_height;

	loop = other.loop;
	play = false;

	frame_update_time = other.frame_update_time;
	elapsed_time = other.elapsed_time;

	now_play_index = 0;

	return *this;
}

bool Animation::Init(const float width, const float height, const float frame_w, const float frame_h)
{
	frame_width = static_cast<int>(frame_w);
	int frame_x = static_cast<int>(width) / static_cast<int>(frame_w);

	frame_height = static_cast<int>(frame_h);
	int frame_y = static_cast<int>(height) / static_cast<int>(frame_h);

	frame_number = frame_x * frame_y;

	for (int i = 0; i < frame_y; ++i)
	{
		for (int j = 0; j < frame_x; ++j)
		{
			TPoint frame_pos;
			frame_pos.x = j * frame_w;
			frame_pos.y = i * frame_h;
			frame_list.push_back(frame_pos);
		}
	}

	SetPlayFrame();

	return true;
}

bool Animation::Init(Image* image)
{
	Init(static_cast<float>(image->GetWidth()), static_cast<float>(image->GetHight()),
		static_cast<float>(image->GetFrameWidth()), static_cast<float>(image->GetFrameHight()));

	return true;
}

void Animation::Release()
{
}

void Animation::SetPlayFrame(const bool reverse, const bool loop)
{
	this->loop = loop;

	play_list.clear();

	for (int i = 0; i < frame_number; ++i)
		play_list.push_back(i);

	if (reverse)
	{
		for (int i = frame_number - 1; i >= 0; --i)
			play_list.push_back(i);
	}
}

void Animation::SetPlayFrame(const int* play_index, const int size, const bool loop)
{
	this->loop = loop;

	play_list.clear();

	for (int i = 0; i < size; ++i)
		play_list.push_back(play_index[i]);
}

void Animation::SetPlayFrame(const int start, const int end, const bool reverse, const bool loop)
{
	this->loop = loop;

	play_list.clear();

	if (start == end)
	{
		Stop();
		return;
	}

	if (start > end)
	{
		for (int i = start; i >= end; --i)
			play_list.push_back(i);

		if (reverse)
		{
			for (int i = end + 1; i < start; ++i)
				play_list.push_back(i);
		}
	}
	else
	{
		for (int i = start; i < end; ++i)
			play_list.push_back(i);

		if (reverse)
		{
			for (int i = end - 1; i > start; --i)
				play_list.push_back(i);
		}
	}
}

void Animation::SetFPS(const int frame_time)
{
	frame_update_time = static_cast<float>(frame_time) * 0.001f;
}

void Animation::FrameUpdate(const float _elapsed_time)
{
	if (play)
	{
		elapsed_time += _elapsed_time;
		if (elapsed_time >= frame_update_time)
		{
			elapsed_time -= frame_update_time;
			++now_play_index;

			if (now_play_index == play_list.size())
			{
				if (loop)
					now_play_index = 0;
				else
				{
					--now_play_index;
					play = false;
				}
			}
		}
	}
}

void Animation::Start()
{
	play = true;
	now_play_index = 0;
}

void Animation::Stop()
{
	play = false;
	now_play_index = 0;
}

void Animation::Pause()
{
	play = false;
}

void Animation::Resume()
{
	play = true;
}
