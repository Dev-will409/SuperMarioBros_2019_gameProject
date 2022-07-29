#pragma once

class Animation;

class MotionList
{
	using MotionMap = std::map<int, Animation*>;

private:
	MotionMap		motion_list;

	int				currentKey;

public:
	MotionList();
	~MotionList();

	MotionList(const MotionList& other);
	MotionList& operator=(const MotionList& other);

	void Update();
	void Render();

	Animation* FindMotion(const int key);
	void AddMotion(const int key, const Animation* ani);
	void DelMotion(const int key);

	void Play(const int key);
	void Stop(const int key);

	bool IsPlay(const int key);

	MotionMap* GetMap() { return &motion_list; }
};