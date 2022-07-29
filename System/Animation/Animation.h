#pragma once

class Image;

class Animation
{
	using FrameList = std::vector<TPoint>;
	using PlayList = std::vector<int>;

private:
	FrameList frame_list;
	PlayList  play_list;

	int frame_number;
	int frame_width;
	int frame_height;

	bool loop;
	bool play;

	float frame_update_time;
	float elapsed_time;

	UINT  now_play_index;

public:
	Animation();
	~Animation();

	Animation(const Animation& other);
	Animation& operator=(const Animation& other);

	bool Init(const float width, const float height, const float frame_width, const float frame_height);
	bool Init(Image* image);

	void Release();

	void SetPlayFrame(const bool reverse = false, const bool loop = false);
	void SetPlayFrame(const int* play_index, const int size, const bool loop = false);
	void SetPlayFrame(const int start, const int end, const bool reverse = false, const bool loop = false);

	void SetFPS(const int frame_time);

	void FrameUpdate(const float _elapsed_time);

	void Start();
	void Stop();
	void Pause();
	void Resume();

	bool	isPlay() const { return play; }
	TPoint	GetFramePos() const { return frame_list[play_list[now_play_index]]; }
	int		GetFrameWidht() const { return frame_width; }
	int		GetFrameHeight() const { return frame_height; }


};