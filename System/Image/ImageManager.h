#pragma once

class Image;


using ImageList = std::map<std::string, Image*>;

class ImageManager
{
	static ImageManager*	instance;

	ImageList				imageList;

	ImageManager();
	~ImageManager();

	Image* FindImage(const std::string& key);

public:

	ImageManager(const ImageManager& other) = delete;
	ImageManager& operator=(const ImageManager& other) = delete;

	static ImageManager* GetInstance();

	static void Create();
	static void Delete();

	bool Init();
	void Release();

	//
	void   DelImage(const std::string& key);


	Image* AddImage(const std::string& key, const int width, const int height);
	Image* AddImage(const std::string& key, const char* file, const int width, const int height,
		bool trans = false, const COLORREF& color = false);
	Image* AddImage(const std::string& key, const char* file, const float x, const float y,
		const int width, const int height, bool trans = false, const COLORREF& color = false);

	Image* AddFrameImage(const std::string& key, const char* file, const float x, const float y,
		const int width, const int height, const int frameX, const int frameY,
		bool trans = false, const COLORREF& color = false);
	Image* AddFrameImage(const std::string& key, const char* file, const int width, const int height,
		const int frameX, const int frameY, bool trans = false, const COLORREF& color = false);
};

