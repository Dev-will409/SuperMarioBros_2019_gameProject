#pragma once

class BaseObject;

using Objects = std::list<BaseObject*>;

class ObjectManager
{
	static ObjectManager* instance;

	unsigned int	id;
	Objects			objectList;

	ObjectManager();
	~ObjectManager();

	ObjectManager(const ObjectManager& other) = delete;
	ObjectManager& operator=(const ObjectManager& other) = delete;

public:
	static ObjectManager* GetInstance();
	static void Create();
	static void Delete();

	void Update();
	void CheckCollision(BaseObject* obj);
	void LateUpdate();
	void Render(HDC hdc);
	void Render(HDC hdc, const TPoint* pt);

	void AddObject(BaseObject* obj);
	BaseObject* FindObject(const std::string& tag);
	void DelObject(const std::string& tag);
};

