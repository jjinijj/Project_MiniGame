#pragma once
#include "singletonBase.h"
#include "gameObject.h"
#include <list>
#include <map>
using namespace std;

class objectManager : public singletonBase<objectManager>
{
private:
	typedef map<eOBJECT_TYPE, list<gameObject*>>			mObject;
	typedef map<eOBJECT_TYPE, list<gameObject*>>::iterator	miObject;
	typedef list<gameObject*>								lObject;
	typedef list<gameObject*>::iterator						liObject;

private:
	mObject		_objMap;
	miObject	_iter_map;
	liObject	_iter_list;

public:

	lObject* getObjectList(eOBJECT_TYPE type) 
	{ 
		if(_objMap.find(type) != _objMap.end())
			return  &_objMap[type];

		return nullptr;
	}

};