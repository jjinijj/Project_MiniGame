#include "stdafx.h"
#include "player.h"

player::player()
{
}

player::~player()
{
}



HRESULT player::init()
{
	int frameCycle = 5;
	_dir_LR = eDIRECTION_RIGHT;

	// animation idle
	{
		image* img = IMAGEMANAGER->findImage("knight_idle");

		animation* anim = new animation;
		anim->init(img, true, 0, img->GetMaxFrameX(), 10, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_IDLE, anim));
	}

	// animation attack down
	{
		image* img = IMAGEMANAGER->findImage("knight_attack_down");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), frameCycle, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_DOWN, anim));
	}

	// animation attack up
	{
		image* img = IMAGEMANAGER->findImage("knight_attack_up");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), frameCycle, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_UP, anim));
	}

	// animation attack 1 : 근접
	{
		image* img = IMAGEMANAGER->findImage("knight_attack1");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), frameCycle, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_1, anim));
	}

	// animation attack 2 : 근접
	{
		image* img = IMAGEMANAGER->findImage("knight_attack2");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), frameCycle, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_2, anim));
	}

	// animation attack 3 : 원거리
	{
		image* img = IMAGEMANAGER->findImage("knight_attack3");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), frameCycle, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_ATTACK_3, anim));
	}

	// animation dead
	{
		image* img = IMAGEMANAGER->findImage("knight_dead");

		animation* anim = new animation;
		anim->init(img, false, 0, img->GetMaxFrameX(), frameCycle, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_DEAD, anim));
	}

	// animation jump, flying, falling, land
	{
		image* img = IMAGEMANAGER->findImage("knight_jump");

		{
			animation* anim = new animation;
			anim->init(img, false, 0, 2, frameCycle, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_JUMP, anim));
		}
		{
			animation* anim = new animation;
			anim->init(img, true, 3, 4, frameCycle, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_FLYING, anim));
		}
		{
			animation* anim = new animation;
			anim->init(img, true, 5, 7, frameCycle, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_FALLING, anim));
		}
		{
			animation* anim = new animation;
			anim->init(img, false, 8, img->GetMaxFrameX(), frameCycle, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_LAND, anim));
		}
	}

	// animation look up
	{
		image* img = IMAGEMANAGER->findImage("knight_lookup");

		animation* anim = new animation;
		anim->init(img, true, 0, img->GetMaxFrameX() - 1, frameCycle, (int)_dir_LR, 1);
		_animMap.insert(make_pair(ePLAYER_STATE_LOOK_UP, anim));
	}

	// animation look down
	{
		image* img = IMAGEMANAGER->findImage("knight_lookdown");

		animation* anim = new animation;
		anim->init(img, true, 0, img->GetMaxFrameX(), 10, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_LOOK_DOWN, anim));
	}

	// animation sit, drowse
	{
		image* img = IMAGEMANAGER->findImage("knight_sitAnddrowse");

		{
			animation* anim = new animation;
			anim->init(img, false, 0, 2, frameCycle, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_SIT, anim));
		}

		{
			animation* anim = new animation;
			anim->init(img, false, 2, 3, frameCycle, (int)_dir_LR);
			_animMap.insert(make_pair(ePLAYER_STATE_DROWSE, anim));
		}
	}

	// animation walking
	{
		animation* anim = new animation;
		image* img = IMAGEMANAGER->findImage("knight_walk");

		anim->init(img, true, 0, img->GetMaxFrameX(), frameCycle, (int)_dir_LR);
		_animMap.insert(make_pair(ePLAYER_STATE_WALK, anim));
	}


	_anim = _animMap[ePLAYER_STATE_IDLE];
	_anim->start();

	return S_OK;
}

void player::release()
{
}

void player::update()
{

	// 이동
	if (!isStateCheck_Attack())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			changeState(ePLAYER_STATE_WALK);
			_dir_LR = eDIRECTION_LEFT;
			if (_anim)
				_anim->SetFrameY(_dir_LR);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			changeState(ePLAYER_STATE_WALK);
			_dir_LR = eDIRECTION_RIGHT;
			if (_anim)
				_anim->SetFrameY(_dir_LR);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_dir_UD = eDIRECTION_UP;
			if (ePLAYER_STATE_IDLE == _state)
			{
				changeState(ePLAYER_STATE_LOOK_UP);
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_dir_UD = eDIRECTION_DOWN;
			if (ePLAYER_STATE_IDLE == _state)
			{
				changeState(ePLAYER_STATE_LOOK_DOWN);
			}
		}
		else if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			if (ePLAYER_STATE_IDLE == _state)
			{
				changeState(ePLAYER_STATE_JUMP);
				_nextState = ePLAYER_STATE_FLYING;
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_position.x -= 5;
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_position.x += 5;
		}
	}

	// 정지
	if (ePLAYER_STATE_WALK == _state)
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && eDIRECTION_LEFT == _dir_LR)
		{
			changeState(ePLAYER_STATE_IDLE);
		}

		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && eDIRECTION_RIGHT == _dir_LR)
		{
			changeState(ePLAYER_STATE_IDLE);
		}
	}
	if (eDIRECTION_UP == _dir_UD && KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_dir_UD = eDIRECTION_NONE;
		if (ePLAYER_STATE_LOOK_UP == _state)
		{
			changeState(ePLAYER_STATE_IDLE);
		}
	}
	else if (eDIRECTION_DOWN == _dir_UD && KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_dir_UD = eDIRECTION_NONE;
		if (ePLAYER_STATE_LOOK_DOWN == _state)
		{
			changeState(ePLAYER_STATE_IDLE);
		}
	}



	// 공격
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// 근접
		if (ePLAYER_STATE_ATTACK_1 == _state)
		{
			_nextState = ePLAYER_STATE_ATTACK_2;
		}
		else
		{
			changeState(ePLAYER_STATE_ATTACK_1);
		}

		// 상하, 스킬
		if (ePLAYER_STATE_JUMP == _state || ePLAYER_STATE_FLYING == _state || ePLAYER_STATE_FALLING == _state)
		{
			// 스킬사용
			//if()
			//else
			// 상하
			if(eDIRECTION_UP == _dir_UD)
				changeState(ePLAYER_STATE_ATTACK_UP);
			else if(eDIRECTION_DOWN)
				changeState(ePLAYER_STATE_ATTACK_DOWN);
		}
	}

	// 점프
	if (ePLAYER_STATE_JUMP == _state)
	{
		if (KEYMANAGER->isOnceKeyUp('Z'))
		{
		}
	}
	else if (ePLAYER_STATE_FLYING == _state)
	{
		if (KEYMANAGER->isOnceKeyUp('Z'))
		{
			changeState(ePLAYER_STATE_FALLING);
		}

		++_jumpCount;
		if (50 < _jumpCount)
		{
			changeState(ePLAYER_STATE_FALLING);
			_jumpCount = 0;
		}
	}
	else if (ePLAYER_STATE_FALLING == _state)
	{
		--_jumpCount;
		if (_jumpCount < 0)
		{
			changeState(ePLAYER_STATE_LAND);
			_jumpCount = 0;
		}
	}

	






	if (_anim)
	{
		if (!_anim->IsPlayingAnimation())
		{
			if ((ePLAYER_STATE_ATTACK_1 == _state))
			{
				if (ePLAYER_STATE_NONE != _nextState)
				{
					changeState(_nextState);
					_nextState = ePLAYER_STATE_NONE;
				}
				else
				{
					changeState(ePLAYER_STATE_IDLE);
				}
			}
			else if(isStateCheck_Attack()) // 공격 끝난 후 idle
			{
				changeState(ePLAYER_STATE_IDLE);
			}
			else if (ePLAYER_STATE_JUMP == _state)
			{
				changeState(_nextState);
				_nextState = ePLAYER_STATE_NONE;
			}
			else if (ePLAYER_STATE_FLYING == _state)
			{
				changeState(ePLAYER_STATE_FALLING);
			}
			else if (ePLAYER_STATE_FALLING == _state)
			{
				changeState(ePLAYER_STATE_LAND);
			}
			else if (ePLAYER_STATE_LAND == _state)
			{
				changeState(ePLAYER_STATE_IDLE);
			}
		}

		_anim->play();
	}
}

void player::render()
{
	if (_anim)
		_anim->render(_position.x, _position.y);

	WCHAR str[128];

	swprintf_s(str, L"[state :%d] [jumpCount : %d]", _state, _jumpCount);
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"나눔고딕", 15.0f
							, str
							, CAMERA->getPosX() + 500
							, CAMERA->getPosY()
							, CAMERA->getPosX() + 300
							, CAMERA->getPosY() + 100);
}

void player::move()
{
}

void player::changeState(ePLAYER_STATE state)
{
	if (_state == state || state < 0 || ePLAYER_STATE_COUNT <= _state )
		return;
	
	if(_anim)
		_anim->end();

	_beforeState = _state;
	_state = state;
	_anim = _animMap[_state];
	_anim->SetFrameY(_dir_LR);
	_anim->start();
	
}
