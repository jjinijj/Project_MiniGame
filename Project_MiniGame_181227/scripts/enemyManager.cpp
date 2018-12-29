#include "stdafx.h"
#include "enemyManager.h"

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
}

void enemyManager::render()
{
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
	{
		enemy* em = new tiktik;
		POINT pos = {500, 500};
		em->setManagerLink(_objM);
		em->init(pos, _enemyCnt);

		_enemyList.push_back(em);

		++_enemyCnt;
	}
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
