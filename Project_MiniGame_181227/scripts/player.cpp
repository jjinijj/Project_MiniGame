#include "stdafx.h"
#include "player.h"
#include "ObjectManager.h"
#include "enemyManager.h"

player::player()
{
}

player::~player()
{
}



HRESULT player::init()
{
	// animation idle
	{
		image* img = IMAGEMANAGER->findImage("knight_idle");

		animation* anim = new animation;
		anim->init(img, true, 0, img->GetMaxFrameX(), PLAYER_IDLE_SPEED, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_IDLE, anim));
	}

	// animation attack down
	{
		image* img = IMAGEMANAGER->findImage("knight_attack_down");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), PLAYER_ATTACK_SPEED, (int)_dir_LR);
		anim->SetEventFrameX(1);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_DOWN, anim));
	}

	// animation attack up
	{
		image* img = IMAGEMANAGER->findImage("knight_attack_up");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), PLAYER_ATTACK_SPEED, (int)_dir_LR);
		anim->SetEventFrameX(1);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_UP, anim));
	}

	// animation attack 1 : 근접
	{
		image* img = IMAGEMANAGER->findImage("knight_attack1");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), PLAYER_ATTACK_SPEED, (int)_dir_LR);
		anim->SetEventFrameX(2);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_1, anim));
	}

	// animation attack 2 : 근접
	{
		image* img = IMAGEMANAGER->findImage("knight_attack2");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), PLAYER_ATTACK_SPEED, (int)_dir_LR);
		anim->SetEventFrameX(1);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_2, anim));
	}

	// animation attack 3 : 원거리
	{
		image* img = IMAGEMANAGER->findImage("knight_attack3");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), PLAYER_ATTACK_SPEED, (int)_dir_LR);
		anim->SetEventFrameX(4);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_3, anim));
	}

	// animation dead
	{
		image* img = IMAGEMANAGER->findImage("knight_dead");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), PLAYER_IDLE_SPEED, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_DEAD, anim));
	}

	// animation jump, flying, falling, land
	{
		image* img = IMAGEMANAGER->findImage("knight_jump");

		{
			animation* anim = new animation;
			anim->init(img, false, 0, 2, PLAYER_MOVE_SPEED, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_JUMP, anim));
		}
		{
			animation* anim = new animation;
			anim->init(img, false, 3, 4, PLAYER_MOVE_SPEED, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_FLYING, anim));
		}
		{
			animation* anim = new animation;
			anim->init(img, true, 5, 7, PLAYER_MOVE_SPEED, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_FALLING, anim));
		}
		{
			animation* anim = new animation;
			anim->init(img, false, 8, img->GetMaxFrameX(), PLAYER_MOVE_SPEED, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_LAND, anim));
		}
	}

	// animation look up
	{
		image* img = IMAGEMANAGER->findImage("knight_lookup");

		animation* anim = new animation;
		anim->init(img, true, 0, img->GetMaxFrameX() - 1, PLAYER_IDLE_SPEED, (int)_dir_LR, 1);
		_animMap.insert(make_pair(ePLAYER_STATE_LOOK_UP, anim));
	}

	// animation look down
	{
		image* img = IMAGEMANAGER->findImage("knight_lookdown");

		animation* anim = new animation;
		anim->init(img, true, 0, img->GetMaxFrameX(), PLAYER_IDLE_SPEED, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_LOOK_DOWN, anim));
	}

	// animation sit, drowse
	{
		image* img = IMAGEMANAGER->findImage("knight_sitAnddrowse");

		{
			animation* anim = new animation;
			anim->init(img, false, 0, 2, PLAYER_MOVE_SPEED, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_SIT, anim));
		}

		{
			animation* anim = new animation;
			anim->init(img, false, 2, 3, PLAYER_MOVE_SPEED, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_DROWSE, anim));
		}
	}

	// animation walking
	{
		animation* anim = new animation;
		image* img = IMAGEMANAGER->findImage("knight_walk");

		anim->init(img, true, 0, img->GetMaxFrameX(), PLAYER_MOVE_SPEED, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_WALK, anim));
	}


	resetPlayer();

	return S_OK;
}

void player::release()
{
	for (_ianiMap = _animMap.begin(); _animMap.end() != _ianiMap; ++_ianiMap)
	{
		(*_ianiMap).second->release();
	}

	_animMap.clear();
}

void player::update()
{
	// 테스트용
	if(KEYMANAGER->isStayKeyDown('Q') )
		_showRect = true;
	else
		_showRect = false;
	if ( KEYMANAGER->isOnceKeyDown('W') )
	{
		changeState(ePLAYER_STATE_DEAD);
		_isAlive = false;
	}
	if ( KEYMANAGER->isOnceKeyDown('E') )
	{
		//changeState(ePLAYER_STATE_HIT);
		_invinCntDown = PLAYER_INVINCIBILITY_TIME;
	}
	if( _invinCntDown == 0 )
		_invinCntDown = -1;
	else if(0 < _invinCntDown )
		--_invinCntDown;

	if ( _pushedCntDown == 0 )
	{
		_dir_pushed = eDIRECTION_NONE;
		_pushedCntDown = -1;
	}
	else if(0 < _pushedCntDown )
		--_pushedCntDown;


	if ( _isAlive )
	{
		// 이동
		if ( !isStateCheck_Attack() )
		{
			if ( KEYMANAGER->isOnceKeyDown(VK_LEFT) )
			{
				if ( !isStateFloating() )
					changeState(ePLAYER_STATE_WALK);
				_dir_LR = eDIRECTION_LEFT;
				if ( _anim )
					_anim->SetFrameY(_dir_LR);

				if ( ePLAYER_STATE_DROWSE == _state )
				{
					changeState(ePLAYER_STATE_SIT);
				}
			}
			else if ( KEYMANAGER->isOnceKeyDown(VK_RIGHT) )
			{
				if ( !isStateFloating() )
					changeState(ePLAYER_STATE_WALK);
				_dir_LR = eDIRECTION_RIGHT;
				if ( _anim )
					_anim->SetFrameY(_dir_LR);

				if ( ePLAYER_STATE_DROWSE == _state )
				{
					changeState(ePLAYER_STATE_SIT);
				}
			}
			else if ( KEYMANAGER->isOnceKeyDown(VK_UP) )
			{
				_dir_UD = eDIRECTION_UP;

				if ( ePLAYER_STATE_DROWSE == _state )
				{
					changeState(ePLAYER_STATE_SIT);
				}
				else if ( checkInteractionObject() )
				{

				}
				else if ( ePLAYER_STATE_IDLE == _state )
				{
					changeState(ePLAYER_STATE_LOOK_UP);
				}
			}
			else if ( KEYMANAGER->isOnceKeyDown(VK_DOWN) )
			{
				_dir_UD = eDIRECTION_DOWN;

				if ( ePLAYER_STATE_DROWSE == _state )
				{
					changeState(ePLAYER_STATE_SIT);
				}
				else if ( ePLAYER_STATE_SIT == _state ) // 의자에서 내려옴
				{
					changeState(ePLAYER_STATE_IDLE);
				}
				else if ( ePLAYER_STATE_IDLE == _state )
				{
					changeState(ePLAYER_STATE_LOOK_DOWN);
				}
			}
			//점프
			else if ( KEYMANAGER->isOnceKeyDown('Z') )
			{
				if ( ePLAYER_STATE_IDLE == _state || ePLAYER_STATE_WALK == _state )
				{
					_isFloating = true;
					_isJumpKeyUp = false;
					_jumpPower = (float)PLAYER_JUMP_POWER;
					_jumpHeight = 0.f;
					changeState(ePLAYER_STATE_JUMP);
				}
			}

			if ( KEYMANAGER->isStayKeyDown(VK_LEFT) )
			{
				if (isMoveable())
				{
					_position.x -= 5;
					if(_position.x < 0)
						_position.x = 0;
				}

				if (ePLAYER_STATE_WALK != _state)
				{
					_dir_LR = eDIRECTION_LEFT;
					if (_anim)
						_anim->SetFrameY(_dir_LR);

					if (ePLAYER_STATE_NONE == _state || ePLAYER_STATE_IDLE == _state || ePLAYER_STATE_LAND == _state)
						changeState(ePLAYER_STATE_WALK);
				}
			}

			if ( KEYMANAGER->isStayKeyDown(VK_RIGHT) )
			{
				if (isMoveable())
				{
					_position.x += 5;
					if (WINSIZEX < _position.x)
						_position.x = 0;
				}

				if (ePLAYER_STATE_WALK != _state)
				{
					_dir_LR = eDIRECTION_RIGHT;
					if (_anim)
						_anim->SetFrameY(_dir_LR);

					if (ePLAYER_STATE_NONE == _state || ePLAYER_STATE_IDLE == _state || ePLAYER_STATE_LAND == _state)
						changeState(ePLAYER_STATE_WALK);
				}
			}
		}



		// 정지
		if ( ePLAYER_STATE_WALK == _state )
		{
			if ( KEYMANAGER->isOnceKeyUp(VK_LEFT) && eDIRECTION_LEFT == _dir_LR )
			{
				changeState(ePLAYER_STATE_IDLE);
			}

			if ( KEYMANAGER->isOnceKeyUp(VK_RIGHT) && eDIRECTION_RIGHT == _dir_LR )
			{
				changeState(ePLAYER_STATE_IDLE);
			}
		}
		if ( KEYMANAGER->isOnceKeyUp(VK_UP) )
		{
			_dir_UD = eDIRECTION_NONE;
			if ( ePLAYER_STATE_LOOK_UP == _state )
			{
				changeState(ePLAYER_STATE_IDLE);
			}
		}
		else if ( KEYMANAGER->isOnceKeyUp(VK_DOWN) )
		{
			_dir_UD = eDIRECTION_NONE;
			if ( ePLAYER_STATE_LOOK_DOWN == _state )
			{
				changeState(ePLAYER_STATE_IDLE);
			}
		}



		// 공격
		if ( KEYMANAGER->isOnceKeyDown('X') )
		{
			// 공중에서 공격
			if ( isStateFloating() )
			{
				// 아래공격
				if ( eDIRECTION_DOWN == _dir_UD && ePLAYER_STATE_ATTACK_DOWN != _state )
				{
					changeState(ePLAYER_STATE_ATTACK_DOWN);
				}

			}

			// 근접
			if ( ePLAYER_STATE_ATTACK_1 == _state )
			{
				// 두번째 공격 준비
				_isAttack2Ready = true;
			}
			else if ( eDIRECTION_UP == _dir_UD && ePLAYER_STATE_ATTACK_UP != _state )
			{
				changeState(ePLAYER_STATE_ATTACK_UP);
			}
			else if ( !isStateCheck_Attack() )
			{
				changeState(ePLAYER_STATE_ATTACK_1);
			}
		}
		// 원거리 공격
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			// 조건체크
			//if()
			{
				changeState(ePLAYER_STATE_ATTACK_3);
				//todo : 스킬게이지 소모
			}
		}

		// 점프
		if ( ePLAYER_STATE_JUMP == _state )
		{
			if (!KEYMANAGER->isStayKeyDown('Z'))
				_isJumpKeyUp = true;
		
			_position.y -= _jumpPower;
			_jumpHeight += _jumpPower;
		}
		else if ( ePLAYER_STATE_FLYING == _state )
		{
			if ( KEYMANAGER->isStayKeyDown('Z') && !_isJumpKeyUp)
			{
				if( _jumpHeight < PLAYER_COL_SIZE_HEIGHT * 1.5f)
					_jumpPower = (float)PLAYER_JUMP_POWER;
			}
			else
				_isJumpKeyUp = true;

			_position.y -= _jumpPower;
			_jumpPower -= _gravity;

			_jumpHeight += _jumpPower;

			if(_jumpPower < 0)
				changeState(ePLAYER_STATE_FALLING);
		}
		else if ( ePLAYER_STATE_FALLING == _state )
		{
			_position.y -= _jumpPower;
			_jumpPower -= _gravity;
			if(_jumpPower < -PLAYER_JUMP_POWER)
				_jumpPower = -(float)PLAYER_JUMP_POWER;

			if (WINSIZEY < _position.y)
			{
				_position.x = 0;
				_position.y = 0;
			}
		}
		else if ( _isFloating )
		{
			if (ePLAYER_STATE_ATTACK_3 != _state)
			{
				_position.y -= _jumpPower;
				_jumpPower -= _gravity;
				if (_jumpPower < -PLAYER_JUMP_POWER)
					_jumpPower = -(float)PLAYER_JUMP_POWER;

				if (WINSIZEY < _position.y)
				{
					_position.x = 0;
					_position.y = 0;
				}
			}
		}

		if ( ePLAYER_STATE_NONE == _state )
			changeState(ePLAYER_STATE_IDLE);
		else if ( ePLAYER_STATE_SIT == _state )
		{
			--_drowsingCntDown;
			if ( _drowsingCntDown < 0 )
				changeState(ePLAYER_STATE_DROWSE);
		}

		move();
		updateCollision();
		evaluateEvent();

		if (checkFloating())
		{
			if (!_isFloating)
			{
				changeState(ePLAYER_STATE_FALLING);
				_isFloating = true;
			}
		}
		else if(_isFloating)
		{
			_isFloating = false;
			changeState(ePLAYER_STATE_LAND);
		}

		if ( checkIntersectEnemy() )
		{
			takeDamage();
		}

	}

	// 애니메이션
	if (_anim)
	{
		if (!_anim->IsPlayingAnimation())
		{
			if ((ePLAYER_STATE_ATTACK_1 == _state))
			{
				if ( _isAttack2Ready )
				{
					changeState(ePLAYER_STATE_ATTACK_2);
					_isAttack2Ready = false;
				}
				else
				{
					changeState(ePLAYER_STATE_IDLE);
				}
			}
			else if(isStateCheck_Attack()) // 공격 끝난 후 idle
			{
				if(_isFloating )
					changeState(ePLAYER_STATE_FALLING);
				else
					changeState(ePLAYER_STATE_IDLE);
			}
			else if (ePLAYER_STATE_JUMP == _state)
			{
				changeState(ePLAYER_STATE_FLYING);
			}
			else if ( ePLAYER_STATE_LAND == _state )
			{
				changeState(ePLAYER_STATE_IDLE);
			}
			else if ( ePLAYER_STATE_DEAD == _state )
			{
				resetPlayer();
				return;
			}
		}
		_anim->update();
	}


}

void player::render()
{

	WCHAR str[128];
	swprintf_s(str, L"[%d][%d] [state :%d] [hp : %d]", _position.x, _position.y, _state, _hpCnt);
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"나눔고딕", 15.0f
							, str
							, CAMERA->getPosX() + 500
							, CAMERA->getPosY()
							, CAMERA->getPosX() + 300
							, CAMERA->getPosY() + 100);
	//if ( _showRect )
	{
		D2DMANAGER->drawRectangle(D2DMANAGER->_defaultBrush
								  , _collision.left, _collision.top
								  , _collision.right, _collision.bottom);

		D2DMANAGER->drawRectangle(D2DMANAGER->_defaultBrush
								  , _collisionAtk.left, _collisionAtk.top
								  , _collisionAtk.right, _collisionAtk.bottom);

		D2DMANAGER->drawRectangle(D2DMANAGER->_defaultBrush
								  , _collisionChair.left, _collisionChair.top
								  , _collisionChair.right, _collisionChair.bottom);
	}

	if ( _anim )
	{
		if(0 < _invinCntDown )
			_anim->render(_position.x - PLAYER_SIZE_WIDE_HALF, _position.y - PLAYER_SIZE_HEIGHT, 1 - (_invinCntDown % 10 * 0.1));
		else
			_anim->render(_position.x - PLAYER_SIZE_WIDE_HALF, _position.y - PLAYER_SIZE_HEIGHT);
	}

}

void player::resetPlayer()
{
	_collisionChair = { 500, 400, 700, 500 };

	_dir_LR = eDIRECTION_RIGHT;

	_position.x = 100;
	_position.y = 500;

	_size = { PLAYER_SIZE_WIDE, PLAYER_SIZE_HEIGHT };
	_atkRange = { 100, 25 };

	_anim = _animMap[ePLAYER_STATE_IDLE];
	_anim->start();

	_gravity = (float)PLAYER_GRAVITY;

	_hpCnt = 5;
	_isAlive = true;
}

void player::move()
{
	if ( eDIRECTION_NONE != _dir_pushed )
	{
		switch ( _dir_pushed )
		{
			case eDIRECTION_LEFT:	{ _position.x -= PLAYER_PUSHED_POW;  break; }
			case eDIRECTION_RIGHT:	{ _position.x += PLAYER_PUSHED_POW;  break; }
			case eDIRECTION_UP:		{ _position.y -= PLAYER_PUSHED_POW;  break; }
			case eDIRECTION_DOWN:	{ _position.y += PLAYER_PUSHED_POW;  break; }

			default:
				break;
		}
	}
}

void player::changeState(ePLAYER_STATE state)
{
	if (_state == state || state < 0 || ePLAYER_STATE_COUNT < state)
		return;

	if(_anim)
		_anim->end();

	_state = state;

	if ( ePLAYER_STATE_NONE == _state )
		return;

	_anim = _animMap[_state];
	_anim->SetFrameY(_dir_LR);
	_anim->start();

	if(ePLAYER_STATE_SIT == _state )
		_drowsingCntDown = 200;
	
}

void player::updateCollision()
{
	// 플레이어
	_collision = {  _position.x - PLAYER_COL_SIZE_WIDE_HALF, _position.y - PLAYER_COL_SIZE_HEIGHT
				  , _position.x + PLAYER_COL_SIZE_WIDE_HALF, _position.y};

	// 공격범위
	if ( ePLAYER_STATE_ATTACK_1 == _state || ePLAYER_STATE_ATTACK_2 == _state )
	{
		if ( eDIRECTION_RIGHT == _dir_LR )
			_collisionAtk = { _collision.right, _position.y - PLAYER_COL_SIZE_HEIGHT_HALF - _atkRange.y
							, _collision.right + _atkRange.x, _position.y - PLAYER_COL_SIZE_HEIGHT_HALF + _atkRange.y };
		else if ( eDIRECTION_LEFT == _dir_LR )
			_collisionAtk = { _collision.left - _atkRange.x, _position.y - PLAYER_COL_SIZE_HEIGHT_HALF - _atkRange.y
							, _collision.left, _position.y - PLAYER_COL_SIZE_HEIGHT_HALF + _atkRange.y };
	}
	else if ( ePLAYER_STATE_ATTACK_UP == _state )
	{
		_collisionAtk = { _position.x - _atkRange.y, _collision.top - _atkRange.x
						, _position.x + _atkRange.y, _collision.top };
	}
	else if(ePLAYER_STATE_ATTACK_DOWN == _state )
	{
		_collisionAtk = { _position.x - _atkRange.y, _collision.bottom
						, _position.x + _atkRange.y, _collision.bottom + _atkRange.x };
	}
	else
		_collisionAtk = {};

}

void player::evaluateEvent()
{
	if (_anim->IsEventFrame() && !_anim->isDoEvent())
	{
		switch (_state)
		{
			case ePLAYER_STATE_ATTACK_1:
			case ePLAYER_STATE_ATTACK_2:
			case ePLAYER_STATE_ATTACK_UP:
			case ePLAYER_STATE_ATTACK_DOWN:
			{
				attackUseSword();
				_anim->SetEventFlag(true);
				break;
			}

			case ePLAYER_STATE_ATTACK_3:
			{
				attackUseBullet();
				_anim->SetEventFlag(true);
				break;
			}
		}
	}
}

void player::takeDamage()
{
	_hpCnt -= 1;

	if ( _hpCnt <= 0 )
	{
		_isAlive = false;
		changeState(ePLAYER_STATE_DEAD);
	}
	else
	{
		_invinCntDown = PLAYER_INVINCIBILITY_TIME;
	}
}

void player::attackUseSword()
{
	if( nullptr == _enemyM )
		return;

	const lEnemy& enemyList = _enemyM->getEnemyList();
	if( 0 == enemyList.size())
		return;

	list<int> hitEnemyVector;
	cilEnemy end = enemyList.end();
	for ( cilEnemy iter = enemyList.begin(); end != iter; ++iter )
	{
		enemy* em = *iter;
		RECT col = em->getCollision();
		if( CheckIntersectRect(_collisionAtk, col) )
		{
			if( ePLAYER_STATE_ATTACK_1 == _state || ePLAYER_STATE_ATTACK_2 == _state )
				_dir_pushed = (eDIRECTION)(eDIRECTION_LEFT - _dir_LR);
			else if (ePLAYER_STATE_ATTACK_UP)
				_dir_pushed = eDIRECTION_DOWN;
			else if ( ePLAYER_STATE_ATTACK_DOWN )
			{
				_dir_pushed = eDIRECTION_UP;
				_isFloating = true;
			}

			_pushedCntDown = PLAYER_PUSHED_TIME;
			hitEnemyVector.push_back(em->getUid());
		}
	}

	for( list<int>::iterator it = hitEnemyVector.begin(); hitEnemyVector.end() != it; ++it )
		_enemyM->hitEnemy(*it);
}

void player::attackUseBullet()
{
}



bool player::checkInteractionObject()
{
	// 임시 구현
	// rectf로 교체할 것
	RECT temp;
	RECT col = {_collision.left, _collision.top, _collision.right, _collision.bottom};
	RECT colChair = { _collisionChair.left, _collisionChair.top, _collisionChair.right, _collisionChair.bottom};

	if ( IntersectRect(&temp, &col, &colChair) )
	{
		if (PLAYER_COL_SIZE_WIDE_HALF <= temp.right - temp.left)
		{
			changeState(ePLAYER_STATE_SIT);
			return true;
		}
	}

	return false;
}

bool player::checkIntersectEnemy()
{
	if( nullptr == _enemyM )
		return false;

	const lEnemy& enemyList = _enemyM->getEnemyList();
	if( 0 == enemyList.size())
		return false;

	if(0 < _invinCntDown )
		return false;

	if( !_isAlive )
		return false;

	cilEnemy end = enemyList.end();
	for ( cilEnemy iter = enemyList.begin(); end != iter; ++iter )
	{
		enemy* em = *iter;
		RECT col = em->getCollision();
		if( CheckIntersectRect(_collision, col) )
		{
			if(_collision.left < col.left )
				_dir_pushed = eDIRECTION_LEFT;
			else 
				_dir_pushed = eDIRECTION_RIGHT;

			_pushedCntDown = 50;
			return true;
		}
	}

	return false;
}

bool player::checkFloating()
{
	if(nullptr == _objM)
		return false;

	lObject* objList = _objM->getObjectList(eOBJECT_GROUND);
	
	if(objList->size() == 0)
		return true;

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

		offsetX = GetIntersectOffsetX(_collision, objCol);
		offsetY = GetIntersectOffsetY(_collision, objCol);
		
		// 상하
		if ( objCol.left <= _collision.left && _collision.right < objCol.right )
		{
			_position.y += offsetY;
			if ( offsetY <= 0 )
				isFloating = false;
		} 
		// 좌우
		else if ( objCol.top <= _collision.top && _collision.bottom <= objCol.bottom)
			_position.x += offsetX;
		// 모서리
		else if (abs(offsetX) < abs(offsetY))
			_position.x += offsetX;
		// 모서리
		else
		{
			// 정확히 모서리
			if ( _collision.bottom == objCol.top )
			{
				if ( _collision.left == objCol.right || _collision.right == objCol.left )
				{
					isFloating = true;
					continue;
				}
			}

			_position.y += offsetY;
			if ( offsetY <= 0 )
				isFloating = false;
		}
	}

	return isFloating;
}
