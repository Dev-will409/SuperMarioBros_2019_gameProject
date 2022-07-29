#include "../Include/SystemH.h"
#include "../Include/UserDefine.h"

#include "ObjectManager.h"
#include "BaseObject.h"


ObjectManager* ObjectManager::instance = nullptr;

ObjectManager::ObjectManager() : id(0)
{
}

ObjectManager::~ObjectManager()
{
	for (auto& a : objectList)
		SAFE_DELETE(a);

	objectList.clear();
}

ObjectManager * ObjectManager::GetInstance()
{
	assert(instance != nullptr);
	return instance;
}

void ObjectManager::Create()
{
	assert(instance == nullptr);
	instance = new ObjectManager;
}

void ObjectManager::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void ObjectManager::Update()
{
	for (auto a : objectList)
	{
		a->Update();
		CheckCollision(a);
	}
}

void ObjectManager::Render(HDC hdc)
{
	for (auto a : objectList)
	{
		a->Render(hdc);
	}
}

void ObjectManager::Render(HDC hdc, const TPoint* pt)
{
	for (auto a : objectList)
	{
		a->Render(hdc, pt);
	}
}

void ObjectManager::CheckCollision(BaseObject* obj)
{
	for (auto a : objectList)
	{
		if (obj == a)
			continue;

		if (obj->IsLeftCollision(a))
		{
			obj->GetNowPosX(obj->GetPosition()->x);
			obj->SetLeftCollision(true);
			return;
		}
		else if (obj->IsRightCollision(a))
		{
			obj->GetNowPosX(obj->GetPosition()->x);
			obj->SetRightCollision(true);
			return;
		}
		else if (obj->IsBottomCollision(a))
		{
			obj->GetNowPosY(obj->GetPosition()->y);
			obj->SetBottomCollision(true);
			return;
		}
		else if (obj->IsTopCollision(a))
		{
			obj->SetTopCollision(true);
			return;
		}
	}
}

void ObjectManager::LateUpdate()
{
	/*Objects::iterator it = objectList.begin();

	for (; it != objectList.end();)
	{
		if ((*it)->GetBottomCollision())
		{
			(*it)->Release();
			SAFE_DELETE((*it));
			it = objectList.erase(it);
		}
		else
			++it;
	}*/
}

void ObjectManager::AddObject(BaseObject* obj)
{
	std::string tag = obj->GetTag() + std::to_string(id);
	obj->SetTag(tag);
	objectList.push_back(obj);
	++id;
}

BaseObject* ObjectManager::FindObject(const std::string& tag)
{
	for (auto a : objectList)
	{
		if (a->GetTag() == tag)
			return a;
	}

	return nullptr;
}

void ObjectManager::DelObject(const std::string& tag)
{
	Objects::iterator it = objectList.begin();

	for (; it != objectList.end();)
	{
		if ((*it)->GetTag() == tag)
		{
			(*it)->Release();
			SAFE_DELETE((*it));
			it = objectList.erase(it);
		}
		else
			++it;
	}
}