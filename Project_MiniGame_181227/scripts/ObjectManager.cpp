#include "stdafx.h"
#include "ObjectManager.h"

void objectManager::init()
{
	// 맵 테두리
	{
		createGround(MAPSIZEX / 2, 10, MAPSIZEX, 10);
		createGround(MAPSIZEX / 2, MAPSIZEY, MAPSIZEX, 10);
		createGround(5, MAPSIZEY, 10, MAPSIZEY);
		createGround(MAPSIZEX - 5, MAPSIZEY, 10, MAPSIZEY);
	}
	//////////////////////////////////////////////////////////
	// 블록
	{
		createGround(100, 600, 500, 100);
		createGround(240, 400, 100, 100);
		createGround(600, 600, 200, 100);
		createGround(700, 800, 100, 100);
		createGround(300, 800, 500, 100);
		createGround(600, 1000, 500, 100);
	}
	///////////////////////////////////////////////////////////////
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

void objectManager::createGround(int x, int y, int width, int height)
{
	objectGround* ground = new objectGround;
	ground->init(x, y, width, height, _objCnt);
	pushBackObject(ground);
	++_objCnt;
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
