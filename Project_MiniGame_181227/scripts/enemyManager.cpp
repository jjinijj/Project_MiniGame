#include "stdafx.h"
#include "enemyManager.h"
#include "ObjectManager.h"
#include "tiktik.h"
#include "gruzzer.h"
#include "primalAspid.h"
#include "mawlek.h"

HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::update()
{
	for ( _iter = _enemyList.begin(); _enemyList.end() != _iter; ++_iter )
	{
		(*_iter)->update();
	}

	for ( _iter = _deadEnemyList.begin(); _deadEnemyList.end() != _iter;)
	{
		if ( !( *_iter )->isAppear() )
		{
			(*_iter)->release();
			_deadEnemyList.remove(*_iter);
			break;
		}
		else
		{
			(*_iter)->update();
			++_iter;
		}
	}

	if ( _enemyList.size() < 1 )
	{
		if ( _enemyCnt < ENEMY_COUNT_NEED_EXIST_BOSS )
		{
			// 물렉(보스)를 제외한
			eENEMY_TYPE type = (eENEMY_TYPE)RND->getInt((int)eENEMY_MAWLEK);
			createEnemy(type);
		}
		else if( !_isExistBoss )
			createEnemy(eENEMY_MAWLEK);
	}
}

void enemyManager::render()
{
	WCHAR str[128];
	swprintf_s(str, L"[enemyCnt : %d / %d] [curEnemy : %d] ", _enemyCnt, ENEMY_COUNT_NEED_EXIST_BOSS, _enemyList.size());
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"나눔고딕", 15.0f
							, str
							, 10
							, 100
							, 500
							, 500);


	for ( _iter = _enemyList.begin(); _enemyList.end() != _iter; ++_iter )
	{
		(*_iter)->render();
	}

	for ( _iter = _deadEnemyList.begin(); _deadEnemyList.end() != _iter; ++_iter)
	{
		(*_iter)->render();
	}
}

void enemyManager::release()
{
	for ( _iter = _enemyList.begin(); _enemyList.end() != _iter; ++_iter )
	{
		(*_iter)->release();
	}

	for ( _iter = _deadEnemyList.begin(); _deadEnemyList.end() != _iter; ++_iter )
	{
		(*_iter)->release();
	}

	_enemyList.clear();
	_deadEnemyList.clear();
}

void enemyManager::setEnemys()
{
	for ( int ii = 0; ii < 1; ++ii )
	{
		eENEMY_TYPE type = eENEMY_MAWLEK;//(eENEMY_TYPE)RND->getInt((int)eENEMY_MAWLEK);
		createEnemy(type);
	}
}

void enemyManager::createEnemy(eENEMY_TYPE type)
{
	bool isCreate = false;
	switch ( type )
	{
		case eENEMY_TIKTIK:
		{	
			if(nullptr != _objM)
			{
				lObject* objList = _objM->getObjectList(eOBJECT_GROUND);

				if ( objList->size() != 0 )
				{
					// 맵 테두리를 제외한 땅에서만 생성
					int idx = RND->getFromIntTo(4, objList->size());

					gameObject* obj = nullptr;
					RECT objCol = {};
					ilObject end = objList->end();

					for ( ilObject iter = objList->begin(); end != iter, 0 <= idx; ++iter, --idx )
					{
						obj = ( *iter );
						objCol = ( obj->getCollision() );
					}

					if ( obj )
					{
						enemy* em = new tiktik;
						POINTF pos;

						pos.x = RND->getFromIntTo(objCol.left, objCol.right);
						pos.y = objCol.top;

						em->setManagerLink(_objM);
						em->init(pos, _enemyCnt);

						_enemyList.push_back(em);
					}

					isCreate = true;
				}
			}

			break;
		}
		case eENEMY_GRUZZER:
		{
			POINTF position;
			position.x = RND->getFromIntTo(100, WINSIZEX - 100);
			position.y = RND->getFromIntTo(100, WINSIZEY - 100);

			enemy* em = new gruzzer;
			em->init(position, _enemyCnt);

			em->setManagerLink(_objM);
			_enemyList.push_back(em);

			break;
		}
		case eENEMY_PRIMALASPID:
		{
			POINTF position;
			position.x = RND->getFromIntTo(100, WINSIZEX - 100);
			position.y = RND->getFromIntTo(100, WINSIZEY - 100);

			primalAspid* em = new primalAspid;
			em->init(position, _enemyCnt);

			em->setManagerLink(_objM);
			em->setPlayerLink(_target);
			em->setBulletMLink(_bulletM);
			em->setBulletImgNames("bullet_fire","bullet_pang");

			_enemyList.push_back(em);

			break;
		}
		case eENEMY_MAWLEK:
		{
			if( _isExistBoss )
				return;

			POINTF position;
			position.x = 1000;
			position.y = WINSIZEY - 20;

			mawlek* mk = new mawlek;
			mk->init(position, _enemyCnt);

			mk->setManagerLink(_objM);
			mk->setPlayerLink(_target);

			_enemyList.push_back(mk);

			_isExistBoss = true;
			break;
		}
	}

	++_enemyCnt;
}

void enemyManager::removeEnemy(int uid)
{
	for ( _iter = _enemyList.begin(); _enemyList.end() != _iter; ++_iter )
	{
		enemy* em = *_iter;
		if( em->getUid() != uid )
			continue;

		em->release();
		_enemyList.remove(em);

		break;
	}
}

void enemyManager::hitEnemy(int uid)
{
	enemy* em = findEnemy(uid);
	if(nullptr == em )
		return;

	em->takeDamage();

	if ( !em->isAlive() )
	{
		em->dead();
		_deadEnemyList.push_back(em);
		_enemyList.remove(em);
	}
}

enemy * enemyManager::findEnemy(int uid)
{
	for ( _iter = _enemyList.begin(); _enemyList.end() != _iter; ++_iter )
	{
		if( (*_iter)->getUid() == uid )
			return *_iter;
	}

	return nullptr;
}
