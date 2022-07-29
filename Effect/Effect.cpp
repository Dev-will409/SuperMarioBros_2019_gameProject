#include "../Include/SystemH.h"
#include "../Include/UserDefine.h"

#include "Effect.h"

#include "../System/Image/Image.h"
#include "../System/Animation/Animation.h"

#include "../System/Image/ImageManager.h"
#include "../System/Timer/TimeManager.h"


Effect::Effect(const std::string & tag, const TPoint & pos, const TSize & size, FrameDesc & desc) : BaseObject(tag, pos, size), isRunning(false)
{
	image = ImageManager::GetInstance()->AddFrameImage("Effect", "Resource/CoinEffect.bmp",
		static_cast<int>(desc.imageSize.width), static_cast<int>(desc.imageSize.height), desc.frameX, desc.frameY, true, RGB(255, 255, 255));
	assert(image != nullptr);

	effect = new Animation;
	effect->Init(image);
	effect->SetPlayFrame(false, false);
	effect->SetFPS(30);
	effect->Stop();
}

Effect::Effect(const Effect & other) : BaseObject(other)
{
	*this = other;
}

Effect & Effect::operator=(const Effect & other)
{
	BaseObject::operator=(other);

	image = other.image;

	effect = new Animation(*(other.effect));

	isRunning = false;

	return *this;
}

bool Effect::Init()
{

	return true;
}

void Effect::Release()
{
}

void Effect::Update()
{
	if (!isRunning)
		return;
	effect->FrameUpdate(TimeManager::GetInstance()->GetElapsedTime());
	rect = TRectMakeCenter(pos.x, pos.y, size.width, size.height);

	if (!effect->isPlay())
		KillEffect();
}

void Effect::Render(HDC hdc)
{
	image->Render(hdc, static_cast<int>(rect.left),
		static_cast<int>(rect.top),
		static_cast<int>(effect->GetFramePos().x),
		static_cast<int>(effect->GetFramePos().y),
		effect->GetFrameWidht(),
		effect->GetFrameHeight());
}

void Effect::Render(HDC hdc, const TPoint* ptCamera)
{
	image->Render(hdc, static_cast<int>(rect.left - ptCamera->x),
		static_cast<int>(rect.top - ptCamera->y),
		static_cast<int>(effect->GetFramePos().x),
		static_cast<int>(effect->GetFramePos().y),
		effect->GetFrameWidht(),
		effect->GetFrameHeight());
}

void Effect::StartEffect(const TPoint & pos)
{
	if (image == nullptr || effect == nullptr)
		return;

	SetPosition(pos);


	isRunning = true;
	effect->Start();

}

void Effect::KillEffect()
{
	isRunning = false;
}
