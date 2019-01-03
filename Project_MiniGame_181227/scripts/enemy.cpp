#include "stdafx.h"
#include "enemy.h"
#include "ObjectManager.h"

HRESULT enemy::init(POINTF position, unsigned int uid)
{
	_position.x = (int)position.x;
	_position.y = (int)position.y;
	_uid = uid;
	_deadCnt = -1;
	_isDead = false;
	_isAlive = true;
	_isAppear = true;

	_dir = (eDIRECTION)RND->getInt(2);

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
		else if(0 < _alphaCntDown )
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
	if ( _isDebugMode )
	{
		WCHAR str[128];
		swprintf_s(str, L"[hp : %d / %d] [%d] [%d] [UID : %d] ", _hp, _hp, _dir, _dirUD, _uid);
		D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"³ª´®°íµñ", 15.0f
								, str
								, ( float )_collision.left
								, ( float )_collision.top - 50
								, ( float )_collision.right + 100
								, ( float )_collision.bottom + 100);

		D2DMANAGER->drawRectangle(D2DMANAGER->_defaultBrush
								  , ( float )_collision.left, ( float )_collision.top
								  , ( float )_collision.right, ( float )_collision.bottom);

		D2DMANAGER->drawEllipse(D2DMANAGER->_defaultBrush
								, ( float )_position.x - 1, ( float )_position.y - 2
								, ( float )_position.x + 1, ( float )_position.y);
	}

	if ( _anim )
	{
		if(0 < _alphaCntDown )
			_anim->render(_position.x - _imgSizeHalf.x, _position.y - _imgSize.y, (float)(1.f - (_alphaCntDown % 10 * 0.1)));
		else
			_anim->render(_position.x - _imgSizeHalf.x, _position.y - _imgSize.y);
	}
}

void enemy::move()
{
	_collision = {   (int)_position.x - _colSize.x / 2, (int)_position.y - _colSize.y
					,(int)_position.x + _colSize.x / 2, (int)_position.y};
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
	_anim->SetFrameY(_dir);
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
	_isDead = true;
	_deadCnt = 100;
}

bool enemy::isFire()
{
	return false;
}

void enemy::bulletFire()
{
}

POINTF enemy::getBulletFirePoint()
{
	return POINTF();
}
