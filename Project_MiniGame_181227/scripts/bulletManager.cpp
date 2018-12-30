#include "stdafx.h"
#include "bulletManager.h"
#include "enemyManager.h"
#include "ObjectManager.h"
#include "player.h"

void bulletManager::init()
{
	for ( int ii = 0; ii < BULLET_COUNT; ++ii )
	{
		arcBullet* arc = new arcBullet;
		_arcBulletQ.push(arc);
	}

	for ( int ii = 0; ii < BULLET_COUNT; ++ii )
	{
		linearBullet* linear = new linearBullet;
		_linearbulletQ.push(linear);
	}
}

void bulletManager::update()
{
	// 이동중인 bullet
	for ( _iter = _bulletList.begin(); _bulletList.end() != _iter; ++_iter )
	{
		bullet* bt = (*_iter);
		bt->update();

		// 충돌하면 bulletPangList로
		if ( checkHitSomething(bt) )
		{
			bt->hitSomething();
			_bulletPangList.push_back(bt);
			_bulletList.remove(bt);

			break;
		}
		else if ( !checkBulletIntheField(bt) )
		{
			returnBulletQ(bt);
			break;
		}
	}

	// 터지는 중인 bullet
	for ( _iter = _bulletPangList.begin(); _bulletPangList.end() != _iter; ++_iter )
	{
		bullet* bt = (*_iter);
		if(bt->isAppear() )
			bt->update();
		else
		{
			bt->clear();
			returnBulletQ(bt);
			break;
		}
	}
}

void bulletManager::render()
{
	for ( _iter = _bulletList.begin(); _bulletList.end() != _iter; ++_iter )
	{
		(*_iter)->render();
	}

	for ( _iter = _bulletPangList.begin(); _bulletPangList.end() != _iter; ++_iter )
	{
		(*_iter)->render();
	}
}

void bulletManager::release()
{
	for ( _iter = _bulletList.begin(); _bulletList.end() != _iter; ++_iter )
	{
		(*_iter)->release();
	}

	while ( !_arcBulletQ.empty() )
	{
		arcBullet* arc = _arcBulletQ.front();
		_arcBulletQ.pop();

		arc->release();
	}

	while ( !_linearbulletQ.empty() )
	{
		linearBullet* linear = _linearbulletQ.front();
		_linearbulletQ.pop();

		linear->release();
	}

	_bulletList.clear();
}

bullet* bulletManager::createBullet(eBULLET_TYPE type)
{
	bullet* newBullet = nullptr;
	switch ( type )
	{
		case eLINEARBULLET:
		{
			if( _linearbulletQ.empty() )
				newBullet = new linearBullet;
			else
			{
				newBullet = _linearbulletQ.front();
				_linearbulletQ.pop();
			}

			_bulletList.push_back(newBullet);

			break;
		}
		case eARCBULLET:
		{
			if( _arcBulletQ.empty() )
				newBullet = new arcBullet;
			else
			{
				newBullet = _arcBulletQ.front();
				_arcBulletQ.pop();
			}

			_bulletList.push_back(newBullet);

			break;
		}
	}

	return newBullet;
}

bool bulletManager::checkHitSomething(bullet* bt)
{
	RECT collision = { bt->getPosition().x - bt->getRadius(), bt->getPosition().y - bt->getRadius()
		,bt->getPosition().x + bt->getRadius(), bt->getPosition().y + bt->getRadius()};

	if ( nullptr != _objM )
	{
		lObject* objList = _objM->getObjectList(eOBJECT_GROUND);

		// 벽 or 블록 이랑 충돌
		if ( objList->size() != 0 )
		{
			gameObject* obj = nullptr;
			RECT objCol = {};
			ilObject end = objList->end();

			for ( ilObject iter = objList->begin(); end != iter; ++iter )
			{
				obj = ( *iter );
				objCol = ( obj->getCollision() );

				// todo 충돌 수정해야하마마암아마암암아맘
				if (CheckIntersectRect(collision, objCol) )
				{
					return true;
				}
			}
		}
	}

	if ( _player )
	{
		// 플레이어가 맞음
		if ( CheckIntersectRect(collision, _player->getCollisionRECT()) )
		{
			_player->takeDamage();
			return true;
		}
	}
	return false;
}

bool bulletManager::checkBulletIntheField(bullet* bt)
{
	// 맵 안에 있는지 체크
	POINTF pos = bt->getPosition();
	if( pos.x < 0  || MAPSIZEX < pos.x)
		return false;

	if( pos.y < 0  || MAPSIZEY < pos.y)
		return false;

	return true;
}

void bulletManager::returnBulletQ(bullet * bt)
{
	// 돌려준다 bullet을 q에
	eBULLET_TYPE type = bt->getBulletType();
	if ( eLINEARBULLET == type )
	{
		linearBullet* linear = dynamic_cast<linearBullet*>(bt);
		_linearbulletQ.push(linear);
	}
	else if ( eARCBULLET == type )
	{
		arcBullet* arc = dynamic_cast<arcBullet*>(bt);
		_arcBulletQ.push(arc);
	}

	_bulletPangList.remove(bt);
}
