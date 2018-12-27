#include "stdafx.h"
#include "player.h"
#include "gameObject.h"

player::player()
{
}

player::~player()
{
}



const int testY = 500;

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
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_DOWN, anim));
	}

	// animation attack up
	{
		image* img = IMAGEMANAGER->findImage("knight_attack_up");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), PLAYER_ATTACK_SPEED, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_UP, anim));
	}

	// animation attack 1 : 근접
	{
		image* img = IMAGEMANAGER->findImage("knight_attack1");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), PLAYER_ATTACK_SPEED, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_1, anim));
	}

	// animation attack 2 : 근접
	{
		image* img = IMAGEMANAGER->findImage("knight_attack2");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), PLAYER_ATTACK_SPEED, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_2, anim));
	}

	// animation attack 3 : 원거리
	{
		image* img = IMAGEMANAGER->findImage("knight_attack3");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), PLAYER_ATTACK_SPEED, (int)_dir_LR);
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
			anim->init(img, true, 3, 4, PLAYER_MOVE_SPEED, (int)_dir_LR);
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
		_invinCntDown = 100;
	}
	if( _invinCntDown == 0 )
		_invinCntDown = -1;
	else if(0 < _invinCntDown )
		--_invinCntDown;




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
			else if ( KEYMANAGER->isOnceKeyDown('Z') )
			{
				if ( ePLAYER_STATE_IDLE == _state || ePLAYER_STATE_WALK == _state )
				{
					_isFloating = true;
					_beforeState = _state;
					changeState(ePLAYER_STATE_JUMP);
				}
			}

			if ( KEYMANAGER->isStayKeyDown(VK_LEFT) )
			{
				_position.x -= 5;

				if ( ePLAYER_STATE_NONE == _state || ePLAYER_STATE_IDLE == _state || ePLAYER_STATE_LAND == _state )
					changeState(ePLAYER_STATE_WALK);
			}

			if ( KEYMANAGER->isStayKeyDown(VK_RIGHT) )
			{
				_position.x += 5;
				if ( ePLAYER_STATE_NONE == _state || ePLAYER_STATE_IDLE == _state || ePLAYER_STATE_LAND == _state )
					changeState(ePLAYER_STATE_WALK);
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
		if ( eDIRECTION_UP == _dir_UD && KEYMANAGER->isOnceKeyUp(VK_UP) )
		{
			_dir_UD = eDIRECTION_NONE;
			if ( ePLAYER_STATE_LOOK_UP == _state )
			{
				changeState(ePLAYER_STATE_IDLE);
			}
		}
		else if ( eDIRECTION_DOWN == _dir_UD && KEYMANAGER->isOnceKeyUp(VK_DOWN) )
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

		// 점프
		if ( ePLAYER_STATE_JUMP == _state )
		{
			_position.y -= 5;
		}
		else if ( ePLAYER_STATE_FLYING == _state )
		{
			// 점프키를 누르고 있지 않다면
			if ( !KEYMANAGER->isStayKeyDown('Z') )
			{
				changeState(ePLAYER_STATE_FALLING);
			}
			_position.y -= 5;
		}
		else if ( ePLAYER_STATE_FALLING == _state )
		{
			_position.y += 5;
			if ( testY < _position.y )
			{
				_position.y = testY;
				_isFloating = false;

				changeState(ePLAYER_STATE_LAND);
			}
		}
		else if ( _isFloating )
		{
			_position.y += 5;
			if ( testY < _position.y )
			{
				_position.y = testY;
				_isFloating = false;
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
			else if (ePLAYER_STATE_FLYING == _state)
			{
				changeState(ePLAYER_STATE_FALLING);
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
		_anim->play();
	}

	updateCollision();
}

void player::render()
{

	WCHAR str[128];
	swprintf_s(str, L"[%.2f][%.2f] [state :%d] [jumpCount : %d] [%d]", _position.x, _position.y, _state, _jumpCount, _isAttack2Ready);
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
			_anim->render(_position.x - PLAYER_SIZE_WIDE_HALF, _position.y - PLAYER_SIZE_HEIGHT, 0.5f);
		else
			_anim->render(_position.x - PLAYER_SIZE_WIDE_HALF, _position.y - PLAYER_SIZE_HEIGHT);
	}

}

void player::move()
{
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
	_collision = {	  _position.x - PLAYER_COL_SIZE_WIDE_HALF, _position.y - PLAYER_COL_SIZE_HEIGHT
					, _position.x + PLAYER_COL_SIZE_WIDE_HALF, _position.y};

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

bool player::checkInteractionObject()
{
	// 임시 구현
	// rectf로 교체할 것
	RECT temp;
	RECT col = {_collision.left, _collision.top, _collision.right, _collision.bottom};
	RECT colChair = { _collisionChair.left, _collisionChair.top, _collisionChair.right, _collisionChair.bottom};

	if ( IntersectRect(&temp, &col, &colChair) )
	{
		changeState(ePLAYER_STATE_SIT);
		return true;
	}

	return false;
}

void player::resetPlayer()
{
	_collisionChair = { 500, 400, 700, 500 };

	_dir_LR = eDIRECTION_RIGHT;

	_position.x = 100;
	_position.y = testY;

	_size = { PLAYER_SIZE_WIDE, PLAYER_SIZE_HEIGHT };
	_atkRange = { 100, 25 };

	_anim = _animMap[ePLAYER_STATE_IDLE];
	_anim->start();

	_isAlive = true;
}
