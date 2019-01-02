#pragma once
#include "singletonBase.h"
#include "gameObject.h"
#include <list>
#include <map>
using namespace std;


typedef list<gameObject*>					lObject;
typedef list<gameObject*>::iterator			ilObject;
typedef list<gameObject*>::const_iterator	cilObject;

class player;
class objectManager : public singletonBase<objectManager>
{
private:
	lObject		_objList;
	lObject		_pushList;
	ilObject	_iter;
	ilObject	_iter_end;

	player* _player;

	int _objCnt;
	bool _isPushbacking;

public:

	void init();
	void update();
	void render();
	void release();

	void setLinkPlayer(player* target) {_player = target;}

	//
	void createGround(int x, int y, const char* imgName);
	void createGround(int x, int y, int width, int height, const char* imgName);
	void createGameObject(int x, int y, eOBJECT_TYPE type);
	void hitGameObject(int uid);
	void intersectObject(int uid);
	void pushBackObject(gameObject* gObject);
	void removeGameObject(int uid);

	gameObject* findGameObject(int uid);
	lObject* getObjectList(eOBJECT_TYPE type);

private:
	void intersectObjectWithObject(gameObject* obj);
};