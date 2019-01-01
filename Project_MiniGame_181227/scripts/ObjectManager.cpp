#include "stdafx.h"
#include "ObjectManager.h"

void objectManager::init()
{
	// 맵 테두리
	{
		createGround(MAPSIZEX / 2, 10, MAPSIZEX, "floor");
		createGround(MAPSIZEX / 2, MAPSIZEY, MAPSIZEX, "floor");
		createGround(5, MAPSIZEY, 10, MAPSIZEY, "floor");
		createGround(MAPSIZEX - 5, MAPSIZEY, MAPSIZEY,10, "floor");
	}
	//////////////////////////////////////////////////////////
	// 블록
	{
		createGround(100, 600, 500, "block");
		createGround(240, 400, 100, "block");
		createGround(600, 600, 200, "block");
		createGround(700, 800, 100, "block");
		createGround(300, 800, 500, "block");
		createGround(600, 1000, 500, "block");
		
		createGround(600, MAPSIZEY - 100, 500,  "block");
		createGround(1100, MAPSIZEY - 200, 500, "block");
		createGround(1600, MAPSIZEY - 300, 500, "block");
		createGround(1100, MAPSIZEY - 400, 100, "block");
		createGround(1600, MAPSIZEY - 500, 100, "block");
		createGround(2100, MAPSIZEY - 200, 100, "block");
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

void objectManager::createGround(int x, int y, int width, const char* imgName)
{
	objectGround* ground = new objectGround;
	ground->init((float)x, (float)y, width, _objCnt, imgName);
	pushBackObject(ground);
	++_objCnt;
}

void objectManager::createGround(int x, int y, int width, int height, const char * imgName)
{
	objectGround* ground = new objectGround;
	ground->init((float)x, (float)y, width, height,_objCnt, imgName);
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
