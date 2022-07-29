#include "../../Include/SystemH.h"
#include "../../Include/UserDefine.h"

#include "ImageManager.h"
#include "Image.h"

ImageManager* ImageManager::instance = nullptr;

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
	OutputDebugStringA("Call ImageManager::~ImageManager()...................Start//\n");
	for (auto& it : imageList)
	{
		if (it.second != nullptr)
		{
			delete (it.second);
			it.second = nullptr;
		}
	}
	OutputDebugStringA("Call ImageManager::~ImageManager()....................End//\n");
	imageList.clear();
}

ImageManager* ImageManager::GetInstance()
{
	assert(instance != nullptr);
	return instance;
}

void ImageManager::Create()
{
	assert(instance == nullptr);
	instance = new ImageManager;
}

void ImageManager::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool ImageManager::Init()
{
	return true;
}

void ImageManager::Release()
{
}

Image* ImageManager::AddImage(const std::string& key, const int width, const int height)
{
	Image* image = FindImage(key);
	if (image != nullptr)
		return image;

	image = new Image;
	if (!image->Init(width, height))
	{
		SAFE_DELETE(image);
		return nullptr;
	}

	imageList.insert({ key, image });

	return image;
}

Image* ImageManager::AddImage(const std::string& key, const char* file, const int width, const int height, bool trans, const COLORREF & color)
{
	Image* image = FindImage(key);
	if (image != nullptr)
		return image;

	image = new Image;
	if (!image->Init(file, width, height, trans, color))
	{
		SAFE_DELETE(image);
		return nullptr;
	}

	imageList.insert({ key, image });

	return image;
}

Image* ImageManager::AddImage(const std::string& key, const char* file, const float x, const float y, const int width, const int height, bool trans, const COLORREF & color)
{
	Image* image = FindImage(key);
	if (image != nullptr)
		return image;

	image = new Image;
	if (!image->Init(file, x, y, width, height, trans, color))
	{
		SAFE_DELETE(image);
		return nullptr;
	}

	imageList.insert({ key, image });

	return image;
}

Image* ImageManager::AddFrameImage(const std::string& key, const char* file, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool trans, const COLORREF & color)
{
	Image* image = FindImage(key);
	if (image != nullptr)
		return image;

	image = new Image;
	if (!image->Init(file, x, y, width, height, frameX, frameY, trans, color))
	{
		SAFE_DELETE(image);
		return nullptr;
	}

	imageList.insert({ key, image });

	return image;
}

Image* ImageManager::AddFrameImage(const std::string& key, const char* file, const int width, const int height, const int frameX, const int frameY, bool trans, const COLORREF & color)
{
	Image* image = FindImage(key);
	if (image != nullptr)
		return image;

	image = new Image;
	if (!image->Init(file, width, height, frameX, frameY, trans, color))
	{
		SAFE_DELETE(image);
		return nullptr;
	}

	imageList.insert({ key, image });

	return image;
}

Image* ImageManager::FindImage(const std::string & key)
{
	auto it = imageList.find(key);
	if (it != imageList.end())
	{
		return it->second;
	
	}

	return nullptr;
}

void ImageManager::DelImage(const std::string & key)
{
	auto it = imageList.find(key);
	if (it != imageList.end())
	{
		(it->second)->Release();
		SAFE_DELETE(it->second);
		it = imageList.erase(it);
	}
}


