#include "stdafx.h"
#include "ObjectManager.h"
#include "player.h"

void objectManager::init()
{
	// 벽
	{
		createGround(5, MAPSIZEY, -1, MAPSIZEY, "wall_L");
		createGround(MAPSIZEX - 5, MAPSIZEY, -1, MAPSIZEY, "wall_R");
	}
	// 바닥
	{
		createGround(MAPSIZEX / 2, 10, MAPSIZEX, -1, "floor");
		createGround(MAPSIZEX / 2, MAPSIZEY, MAPSIZEX, -1, "floor");
	}
	//////////////////////////////////////////////////////////
	// 블록
	{
		createGround(100, 600, "block");
		createGround(240, 400, "block");
		createGround(600, 600, "block");
		createGround(700, 800, "block");
		createGround(300, 800, "block");
		createGround(600, 1000, 500, -1, "block");
		
		createGround(600, MAPSIZEY - 100, 500, -1, "block");
		createGround(1100, MAPSIZEY - 200, 500, -1, "block");
		createGround(1600, MAPSIZEY - 300, 500, -1, "block");
		createGround(1100, MAPSIZEY - 400, 100, -1, "block");
		createGround(1600, MAPSIZEY - 500, 100, -1, "block");
		createGround(2100, MAPSIZEY - 200, 100, -1, "block");
	}
	///////////////////////////////////////////////////////////////
	// 의자
	{
		createGameObject(500, 530, eOBJECT_CHAIR);
	}

	/////////////////////////////////////////////////////////////
	// 돈 바위
	{
		createGameObject(180, 730, eOBJECT_GOLDROCK);
		createGameObject(180, MAPSIZEY - 100, eOBJECT_GOLDROCK);
	}
}

void objectManager::update()
{
	for (_iter = _objList.begin(); _objList.end() != _iter; ++_iter)
	{
		gameObject* obj = (*_iter);
		obj->update();
		intersectObjectWithObject(obj);
	}
}

void objectManager::render()
{
	for (_iter = _objList.begin(); _objList.end() != _iter; ++_iter)
	{
		(*_iter)->render();
	}
}

void objectManager::release()
{
	for (_iter = _objList.begin(); _objList.end() != _iter; ++_iter)
	{
		(*_iter)->release();
	}

	_objList.clear();

	releaseSingleton();
}

void objectManager::createGround(int x, int y, const char* imgName)
{
	objectGround* ground = new objectGround;
	ground->init((float)x, (float)y, _objCnt, imgName);
	pushBackObject(ground);
	++_objCnt;
}

void objectManager::createGround(int x, int y, int width, int height, const char * imgName)
{
	objectGround* ground = new objectGround;
	ground->init((float)x, (float)y, width, height, _objCnt, imgName);
	pushBackObject(ground);
	++_objCnt;
}

void objectManager::createGameObject(int x, int y, eOBJECT_TYPE type)
{
	gameObject* obj = nullptr;
	switch (type)
	{
		case eOBJECT_CHAIR:
		{
			obj = new objectChair;
			obj->init(x, y, _objCnt, "chair");
			break;
		}
		case eOBJECT_COIN:
		{
			obj = new objectCoin;
			obj->init(x, y, _objCnt, "coin");
			break;
		}
		case eOBJECT_CHARM:
		{	
			break;
		}
		case eOBJECT_GROUND:
		{
			break;
		}

		case eOBJECT_GOLDROCK:
		{
			obj = new objectGoldRock;
			obj->init(x, y, _objCnt, "goldRock");
			break;
		}
	}

	if (obj)
	{
		pushBackObject(obj);
		++_objCnt;
	}
}

void objectManager::hitGameObject(int uid)
{
	gameObject* obj = findGameObject(uid);

	if (obj)
	{
		obj->hitObject();

		switch (obj->getType())
		{
			case eOBJECT_CHAIR:	 { break; }
			case eOBJECT_COIN:	 { break; }
			case eOBJECT_CHARM:	 { break; }
			case eOBJECT_GROUND: { break; }
			case eOBJECT_GOLDROCK:
			{
				RECT col = obj->getCollision();
				POINTF pos = {(col.right - col.left) / 2 + col.left, col.top};
				if (!obj->isFin())
				{
					int coinCnt = 0;

					if (obj->isCrash())
					{
						coinCnt = RND->getFromIntTo(15, 20);
						obj->setFin(true);
					}
					else
					{
						coinCnt = RND->getFromIntTo(1, 5);
					}
					
					for (int ii = 0; ii < coinCnt; ++ii)
						createGameObject(pos.x, pos.y, eOBJECT_COIN);
				}

				break;
			}

			default:
				break;
		}
	}
}

void objectManager::intersectObject(int uid)
{
	gameObject* obj = findGameObject(uid);

	if (obj)
	{
		switch (obj->getType())
		{
			case eOBJECT_CHAIR:		{ break; }
			case eOBJECT_COIN:
			{
				_player->changeCoin(obj->getPrice());
				removeGameObject(obj->getUid());

				break;
			}
			case eOBJECT_CHARM:		{ break; }
			case eOBJECT_GROUND:	{ break; }
			case eOBJECT_GOLDROCK:	{ break; }

			default:
				break;
		}
	}
}

void objectManager::pushBackObject(gameObject* gObject)
{
	for (ilObject iter = _objList.begin(); _objList.end() != iter; ++iter)
	{
		// 중복체크
		if((*iter) == gObject)
			return;
	}

	_objList.push_back(gObject);
}

void objectManager::removeGameObject(int uid)
{
	gameObject* obj = findGameObject(uid);
	
	if(obj)
	{
		_objList.remove(obj);
		
		SAFE_RELEASE(obj);
		SAFE_DELETE(obj);
	}
}

gameObject* objectManager::findGameObject(int uid)
{
	ilObject iter_end = _objList.end();
	for (ilObject iter = _objList.begin(); iter_end != iter; ++iter)
	{
		if((*iter)->getUid() == uid)
			return (*iter);
	}

	return nullptr;
}

lObject* objectManager::getObjectList(eOBJECT_TYPE type)
{
	lObject* objList = new lObject;

	for (ilObject iter = _objList.begin(); _objList.end() != iter; ++iter)
	{
		if (type == (*iter)->getType())
			objList->push_back(*iter);
	}

	return objList;
}

void objectManager::intersectObjectWithObject(gameObject* obj)
{
	if (!obj->isMoveable())
		return;

	ilObject iter_end = _objList.end();

	RECT objCol = {};
	RECT obj2Col = {};

	float offsetX = 0.f;
	float offsetY = 0.f;

	for (ilObject iter = _objList.begin(); iter_end != iter; ++iter)
	{
		gameObject* obj2 = (*iter);

		if(obj2->isMoveable() || obj2->getType() == eOBJECT_GOLDROCK || obj2->getType() == eOBJECT_COIN)
			continue;

		objCol = obj->getCollision();
		obj2Col = obj2->getCollision();

		if (!CheckIntersectRect(objCol, obj2Col))
			continue;

		obj->intersectWithObject(obj2);
		break;
	}
}
