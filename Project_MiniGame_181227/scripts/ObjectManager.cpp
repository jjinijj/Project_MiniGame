#include "stdafx.h"
#include "ObjectManager.h"

void objectManager::init()
{
	// 땅 생성
	{

	}
}

void objectManager::update()
{
	for (_iobjList = _objList.begin(); _objList.end() != _iobjList; ++_iobjList)
	{
		(*_iobjList)->update();
	}
}

void objectManager::render()
{
	for (_iobjList = _objList.begin(); _objList.end() != _iobjList; ++_iobjList)
	{
		(*_iobjList)->render();
	}
}

void objectManager::release()
{
	for (_iobjList = _objList.begin(); _objList.end() != _iobjList; ++_iobjList)
	{
		(*_iobjList)->release();
	}

	_objList.clear();

	releaseSingleton();
}

void objectManager::pushBackObject(gameObject* gObject)
{
	for (_iobjList = _objList.begin(); _objList.end() != _iobjList; ++_iobjList)
	{
		// 중복체크
		if((*_iobjList) == gObject)
			return;
	}

	_objList.push_back(gObject);
}

list<gameObject*>* objectManager::getObjectList(eOBJECT_TYPE type)
{
	lObject* objList = new lObject;

	for (_iobjList = _objList.begin(); _objList.end() != _iobjList; ++_iobjList)
	{
		if (type == (*_iobjList)->getType())
			objList->push_back(*_iobjList);
	}

	return objList;
}
