#pragma once
#include "../BaseObject/BaseObject.h"

class Image;
class Animation;

class Effect : public BaseObject
{
	Image*			image;
	Animation*		effect;


	bool			isRunning;

public:
	Effect() = delete;
	~Effect() = default;

	Effect(const std::string& tag, const TPoint& pos, const TSize& size, FrameDesc& desc);

	Effect(const Effect& other);
	Effect& operator=(const Effect& other);

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Render(HDC hdc, const TPoint * ptCamera);

	void StartEffect(const TPoint& pos);
	void KillEffect();

	bool IsRunning() const { return isRunning; }
};