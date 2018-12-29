#include "stdafx.h"
#include "enemy.h"
#include "ObjectManager.h"

HRESULT enemy::init(POINT position, unsigned int uid)
{
	_position = position;
	_uid = uid;
	_deadCnt = -1;
	_isDead = false;
	_isAlive = true;
	_isAppear = true;

	return S_OK;
}

void enemy::update()
{
	if (_anim)
		_anim->update();
	
	if (_isAlive)
	{
		if(_alphaCntDown == 0 )
			_alphaCntDown = -1;
		else
			--_alphaCntDown;

		move();
	}
	else if(_isDead)
	{
		if(0 < _deadCnt )
			--_deadCnt;
		else
			_isAppear = false;
	}
}

void enemy::release()
{
	for (_ianiMap = _animMap.begin(); _animMap.end() != _ianiMap; ++_ianiMap)
	{
		(*_ianiMap).second->release();
	}

	_animMap.clear();
}

void enemy::render()
{
	WCHAR str[128];
	swprintf_s(str, L"hp : %d / %d", _hp, _hp);
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"³ª´®°íµñ", 15.0f
							, str
							, _collision.left
							, _collision.top - 50
							, _collision.right
							, _collision.top);

	D2DMANAGER->drawRectangle( D2DMANAGER->_defaultBrush
							 , _collision.left, _collision.top
							 , _collision.right, _collision.bottom);

	if ( _anim )
	{
		if(0 < _alphaCntDown )
			_anim->render(_position.x - _imgSizeHalf.x, _position.y - _imgSize.y, 1.f - (_alphaCntDown % 10 * 0.1));
		else
			_anim->render(_position.x - _imgSizeHalf.x, _position.y - _imgSize.y);
	}
}

void enemy::move()
{
	_collision = {   _position.x - _colSize.x / 2, _position.y - _colSize.y
					,_position.x + _colSize.x / 2, _position.y};
}

void enemy::attack()
{
}

void enemy::changeState(int state)
{
	if( _state == state )
		return;

	if( state < 0 )
		return;

	if ( _animMap.find(state) == _animMap.end() )
		return;

	if(nullptr != _anim )
		_anim->end();

	_state	= state;
	_anim	= _animMap[state];
	_anim->start();
}

void enemy::takeDamage()
{
	_hp -= 1;
	_isAlive = (0 < _hp);

	_alphaCntDown = 30;
}

void enemy::dead()
{
}


HRESULT tiktik::init(POINT position, unsigned int uid)
{
	enemy::init(position, uid);
	_dir = (eDIRECTION)RND->getInt(2);

	{
		animation* anim = new animation;
		image* img = IMAGEMANAGER->findImage("tiktik_move");
		anim->init(img, true, 0, img->GetMaxFrameX(), 10, _dir);
		_animMap.insert(make_pair(eMOVE, anim));

		_imgSize.x = img->GetFrameWidth();
		_imgSize.y = img->GetFrameWidth();
		_imgSizeHalf.x = img->GetFrameWidth() / 2;
		_imgSizeHalf.y = img->GetFrameWidth() / 2;
	}

	{
		animation* anim = new animation;
		image* img = IMAGEMANAGER->findImage("tiktik_dead");
		anim->init(img, false, 0, img->GetMaxFrameX(), 20, _dir);
		_animMap.insert(make_pair(eDEAD, anim));
	}

	{
		animation* anim = new animation;
		image* img = IMAGEMANAGER->findImage("tiktik_climbup");
		anim->init(img, false, 0, img->GetMaxFrameX(), 10, _dir);
		_animMap.insert(make_pair(eCLIMBUP, anim));
	}

	{
		animation* anim = new animation;
		image* img = IMAGEMANAGER->findImage("tiktik_climbdown");
		anim->init(img, false, 0, img->GetMaxFrameX(), 10, _dir);
		_animMap.insert(make_pair(eCLIMBDOWN, anim));
	}

	{
		animation* anim = new animation;
		image* img = IMAGEMANAGER->findImage("tiktik_move");
		anim->init(img, false, 0, img->GetMaxFrameX(), 10, _dir);
		_animMap.insert(make_pair(eSIDEMOVE, anim));
	}

	{
		animation* anim = new animation;
		image* img = IMAGEMANAGER->findImage("tiktik_move");
		anim->init(img, false, 0, img->GetMaxFrameX(), 10, _dir);
		_animMap.insert(make_pair(eUNDERMOVE, anim));
	}

	_colSize = _imgSize;
	_anim = _animMap[eMOVE];
	_anim->start();
	_hp = 10;
	_speed = 1;

	_collision = {   _position.x - _colSize.x / 2, _position.y - _colSize.y
					,_position.x + _colSize.x / 2, _position.y};
	setActiveArea();

	return S_OK;
}

void tiktik::update()
{
	if (_isAlive)
		move();
}

void tiktik::move()
{
	enemy::update();

	if(nullptr == _activeArea )
		return;

	switch ( _state )
	{
		case eMOVE:
		case eUNDERMOVE:
		{
			if ( eRIGHT == _dir )
			{
				_position.x += _speed;
				if ( _activeArea->getCollision().right < _position.x )
				{
					changeState(eCLIMBDOWN);
					_dirUD = eDOWN;
				}
			}
			else
			{
				_position.x -= _speed;
				if ( _position.x < _activeArea->getCollision().left )
				{
					changeState(eCLIMBDOWN);
					_dirUD = eDOWN;
				}
			}

			break;
		}
		case eSIDEMOVE:
		{
			if ( eDOWN == _dirUD )
			{
				_position.y += _speed;
				if ( _activeArea->getCollision().bottom < _position.y )
				{
					changeState(eUNDERMOVE);
					if( eRIGHT == _dir )
						_dir = eLEFT;
					else
						_dir = eRIGHT;
				}
			}
			else
			{
				_position.y -= _speed;
				if ( _position.y < _activeArea->getCollision().top )
				{
					changeState(eMOVE);
					if( eRIGHT == _dir )
						_dir = eLEFT;
					else
						_dir = eRIGHT;
				}
			}
			break;
		}

		case eCLIMBUP:
		case eCLIMBDOWN:
		{
			if( _anim )
				if(!_anim->IsPlayingAnimation())
					changeState(eSIDEMOVE);
			break;
		}
	}
}

void tiktik::dead()
{
	changeState(eDEAD);
	_isDead = true;
	_deadCnt = 100;
}

void tiktik::setActiveArea()
{
	if(nullptr == _objM )
		return;

	lObject* objList = _objM->getObjectList(eOBJECT_GROUND);
	
	if(objList->size() == 0)
		return;

	bool isFloating = true;
	int offsetX = 0;
	int offsetY = 0;

	gameObject* obj = nullptr;
	RECT objCol = {};
	ilObject end = objList->end();

	for ( ilObject iter = objList->begin(); end != iter; ++iter )
	{
		obj		= (*iter);
		objCol	= ( obj->getCollision() );

		if( !CheckIntersectRect(_collision, objCol) )
			continue;

		int offsetY = _collision.bottom - objCol.top;
		_position.y -= offsetY;

		_activeArea = obj;

		break;
	}
}
