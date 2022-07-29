#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"

#include "MotionList.h"
#include "Animation.h"

#include "../Timer/TimeManager.h"

MotionList::MotionList() : currentKey(-1)
{
}

MotionList::~MotionList()
{
	for (auto& a : motion_list)
		SAFE_DELETE(a.second);

	motion_list.clear();
}

MotionList::MotionList(const MotionList& other)
{
	*this = other;
}

MotionList& MotionList::operator=(const MotionList& other)
{
	for (auto a : other.motion_list)
		motion_list.insert(a);

	currentKey = -1;

	return *this;
}

void MotionList::Update()
{
	if (currentKey == -1)
		return;

	motion_list[currentKey]->FrameUpdate(TimeManager::GetInstance()->GetElapsedTime());
}

void MotionList::Render()
{
}

Animation* MotionList::FindMotion(const int key)
{
	auto it = motion_list.find(key);
	if (it != motion_list.end())
		return it->second;

	return nullptr;
}

void MotionList::AddMotion(const int key, const Animation* ani)
{
	assert(ani != nullptr);

	if (FindMotion(key) == nullptr)
		motion_list.insert({ key, const_cast<Animation*>(ani) });
}

void MotionList::DelMotion(const int key)
{
	auto it = motion_list.find(key);
	if (it != motion_list.end())
	{
		SAFE_DELETE(it->second);
		motion_list.erase(it);
	}
}

void MotionList::Play(const int key)
{
	if (currentKey == key)
		return;

	currentKey = key;
	motion_list[key]->Start();
}

void MotionList::Stop(const int key)
{
	motion_list[key]->Stop();
}

bool MotionList::IsPlay(const int key)
{
	return motion_list[key]->isPlay();
}
