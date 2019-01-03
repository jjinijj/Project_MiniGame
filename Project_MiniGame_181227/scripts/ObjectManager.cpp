#include "stdafx.h"
#include "ObjectManager.h"
#include "player.h"

void objectManager::init()
{
	_objList.clear();
	_player = nullptr;
	_objCnt = 0;
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
	for (_iter = _objList.begin(); _objList.end() != _iter;)
	{
		(*_iter)->release();
		_iter = _objList.erase(_iter);
	}

	_objList.clear();

	releaseSingleton();
}

void objectManager::setMap()
{
	//////////////////////////////////////////////////////////
	// 블록
	{
		//0
		createGround(1220, 115, "block");
		createGround(450, 188, 780, -1, "block");
		createGround(300, 400, "block");
		createGround(600, 620, "block");
		createGround(100, 850, "block");
		createGround(350, 1050, 250, -1, "block");
		createGround(1350, 1050, "block");
		createGround(660, 1250, "block_big");
		createGround(1620, 1300, "block");
		createGround(1405, 1428, 100, -1, "block");
		createGround(610, 1630, 300, -1, "block");

		// 11
		createGround(1100, 1630, "block");
		createGround(800, 1850, "block");
		createGround(610, 2250, "block");
		createGround(1100, 2050, "block");
		createGround(900, 2450, "block");
		createGround(500, 2650, "block");
		createGround(1000, 2850, 780, -1, "block");
		createGround(660, 3050, "block_big");
		createGround(100, 3150, "block");
		createGround(400, 3380, 200, -1, "block");

		// 21
		createGround(700, 3500, "block");
		createGround(1400, 3380, 200, -1, "block");
		createGround(1600, 3150, "block");
	}
	///////////////////////////////////////////////////////////////
	// 의자
	{
		createGameObject(1100, 3050 - 90, eOBJECT_CHAIR);
		createGameObject(100, 1430 - 90, eOBJECT_CHAIR);
	}

	/////////////////////////////////////////////////////////////
	// 돈 바위
	{
		createGameObject(180, 730, eOBJECT_GOLDROCK);
		createGameObject(1800, MAPSIZEY - 124, eOBJECT_GOLDROCK);
	}

	/////////////////////////////////////////////////////////////
	// npc
	{
		createGameObject(900, 10, eOBJECT_NPC);
	}

	//////////////////////////////////////////////////////////////
	// 바닥, 천장
	{
		// 0
		createGround(0, -10, MAPSIZEX, -1, "floor_stone");
		createGround(0, MAPSIZEY - 20, MAPSIZEX, -1, "floor_stone");
		createGround(570, 685, (MAPSIZEX - 500), -1, "floor");
		createGround(0, 685, "floor");
	}

	// 절벽
	{
		createGround(0, 1430, "cliff_L");
		createGround(1487, 1750, "cliff_R");
		createGround(0, 2150, "cliff_L");
	}

	// 벽
	{
		createGround(-20, 0, -1, MAPSIZEY, "wall_L");
		createGround(MAPSIZEX - 85, 0, -1, MAPSIZEY, "wall_R");
	}
	// 8
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

		case eOBJECT_NPC:
		{
			obj = new objectNPC;
			obj->init(x, y, _objCnt, "npc");
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

			case eOBJECT_NPC:
			{
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

void objectManager::saveData()
{
	vector<string> data;

	// 부서진 코인바위 저장
	lObject* objList = getObjectList(eOBJECT_GOLDROCK);

	ilObject end = objList->end();
	for ( ilObject iter = objList->begin(); end != iter; ++iter )
	{
		gameObject* obj = (*iter);
		if ( obj->isCrash() )
		{
			char str[128];
			sprintf_s(str, "%d",obj->getUid());
			data.push_back(str);
		}
	}

	TXTDATA->txtSave("data/mapData.txt", data);
}

void objectManager::loadData()
{
	vector<string> data;
	data = TXTDATA->txtLoad("data/mapData.txt");

	// 부서진 코인 바위 적용
	int size = data.size();
	if (0 != size)
	{
		for ( int ii = 0; ii < size; ++ii )
		{
			int idx = atoi(data[ii].c_str());
			gameObject* obj = findGameObject(idx);
			if ( obj )
			{
				obj->setFin(true);
			}
		}
	}
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
