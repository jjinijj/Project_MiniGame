#pragma once
#include "singletonBase.h"
#include "gameObject.h"
#include <list>
#include <map>
using namespace std;


typedef list<gameObject*>::iterator		ilObject;
typedef list<gameObject*>				lObject;

class objectManager : public singletonBase<objectManager>
{
private:
	lObject		_objList;
	ilObject	_iobjList;

	int _objCnt;

public:

	void init();
	void update();
	void render();
	void release();

	void createGround(int x, int y, int width, int height);
	void pushBackObject(gameObject* gObject);
	lObject* getObjectList(eOBJECT_TYPE type);


};