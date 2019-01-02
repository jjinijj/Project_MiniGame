#include "stdafx.h"
#include "gameObject.h"


gameObject::gameObject()
{
}

gameObject::~gameObject()
{
}

HRESULT gameObject::init()
{
	return S_OK;
}

HRESULT gameObject::init(float x, float y, unsigned int uid, const char* imgName)
{
	_image = IMAGEMANAGER->findImage(imgName);
	
	assert(_image != nullptr);

	int width = _image->GetWidth();
	int height = _image->GetHeight();

	//PostQuitMessage

	_uid = uid;

	_position = { x, y };
	_size = { width, height };
	_collision = { (int)(x - width / 2), (int)y - height, (int)x + width / 2, (int)y };

	_type = eOBJECT_TYPE_NONE;
	_subType = -1;

	_loopCnt = {1, 1};
	_offcut = {0, 0};

	_isMoveable = false;
	_isInteractionable = false;

	return S_OK;
}

void gameObject::render()
{
	WCHAR str[128];
	swprintf_s(str, L"[UID : %d]", _uid);
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"�������", 15.0f
							, str
							, _position.x - 50
							, _position.y - 50
							, _position.x + 50
							, _position.y + 50);

	D2DMANAGER->drawRectangle(D2DMANAGER->_defaultBrush
							  , (float)_collision.left,  (float)_collision.top
							  , (float)_collision.right, (float)_collision.bottom);


	// �ִϸ��̼��� ������ �ִϸ��̼� ����
	if (_anim)
	{
		_anim->render(_position.x - _size.x * 0.5, _position.y - _size.y);
	}
	// �ִϸ��̼� ���ٸ�, �̹��� ����
	else if (_image)
	{
		for (int ii = 0; ii < _loopCnt.y; ++ii)
		{
			for (int jj = 0; jj < _loopCnt.x; ++jj)
			{
				_image->render(_image->GetWidth()  * jj + _collision.left
							   , _image->GetHeight() * ii + _collision.top);
			}

			if (0 != _offcut.x)
			{
				_image->render(_image->GetWidth()  * _loopCnt.x + _collision.left
							   , _image->GetHeight() * ii + _collision.top
							   , 0, 0
							   , _offcut.x, _image->GetHeight());
			}
		}

		if (0 != _offcut.y)
		{
			for (int ii = 0; ii < _loopCnt.x; ++ii)
			{
				_image->render(_image->GetWidth() * ii + _collision.left
							   , _image->GetHeight() * _loopCnt.y + _collision.top
							   , 0, 0
							   , _image->GetWidth(), _offcut.y);
			}

			if (0 != _offcut.x)
			{
				_image->render(_image->GetWidth() * _loopCnt.x + _collision.left
							   , _image->GetHeight() * _loopCnt.y + _collision.top
							   , 0, 0
							   , _offcut.x, _offcut.y);
			}
		}
	}
}

void gameObject::release()
{
	_iter_end = _animMap.end();
	for (_iter = _animMap.begin(); _iter_end != _iter; ++_iter)
	{
		SAFE_RELEASE((*_iter).second);
		SAFE_RELEASE((*_iter).second);
	}

	if (_anim)
	{
		SAFE_RELEASE(_anim);
		SAFE_RELEASE(_anim);
	}

	_animMap.clear();
}

void gameObject::update()
{
	if(_anim)
		_anim->update();
}

void gameObject::hitObject()
{
}

void gameObject::move()
{
}

void gameObject::pushObject(float offsetX, float offsetY)
{
	_position.x += offsetX;
	_position.y += offsetY;
	_collision = { (int)(_position.x - _size.x / 2), (int)_position.y - _size.y
				  ,(int)(_position.x + _size.x / 2), (int)_position.y };
}



////////////////////////////////////////////////////////////////////////////////////
//									 GROUND
////////////////////////////////////////////////////////////////////////////////////
HRESULT objectGround::init(float x, float y, unsigned int uid, const char* imgName)
{
	gameObject::init(x, y, uid, imgName);

	_type = eOBJECT_GROUND;

	return S_OK;
}

HRESULT objectGround::init(float x, float y, int width, int height, unsigned int uid, const char* imgName)
{
	init(x, y, uid, imgName);

	int imgWidth = _image->GetWidth();
	int imgHeight = _image->GetHeight();

	_size.x = width < 0 ? imgWidth : width;
	_size.y = height < 0 ? _image->GetHeight() : height;

	_loopCnt.x = _size.x / imgWidth;
	_offcut.x	 = _size.x % imgWidth;

	_loopCnt.y = _size.y / imgHeight;
	_offcut.y = _size.y % imgHeight;

	_collision = { (int)(x - _size.x / 2), (int)y - _size.y, (int)x + _size.x / 2, (int)y };
	return S_OK;
}



////////////////////////////////////////////////////////////////////////////////////
//									 CHAIR
////////////////////////////////////////////////////////////////////////////////////
HRESULT objectChair::init(float x, float y, unsigned int uid, const char * imgName)
{
	gameObject::init(x, y, uid, imgName);
	_type = eOBJECT_CHAIR;

	return S_OK;
}


////////////////////////////////////////////////////////////////////////////////////
//									 GOLD ROCK
////////////////////////////////////////////////////////////////////////////////////
HRESULT objectGoldRock::init(float x, float y, unsigned int uid, const char* imgName)
{
	gameObject::init(x, y, uid, imgName);
	_type = eOBJECT_GOLDROCK;

	{
		animation* anim = new animation;
		anim->init(_image, true, 0, 5, 10, 0);
		_animMap.insert(make_pair(eGOLDROCK_STATE_IDLE, anim));
	}
	{
		animation* anim = new animation;
		anim->init(_image, false, 6, 6, 10, 0);
		_animMap.insert(make_pair(eGOLDROCK_STATE_CRASH, anim));
	}

	_anim = _animMap[eGOLDROCK_STATE_IDLE];
	_anim->start();

	_size = { _image->GetFrameWidth(), _image->GetFrameHeight() };
	_collision = {	 (int)(x - _size.x / 2), (int)y - _size.y
					,(int)(x + _size.x / 2), (int)y };

	_crashCount = 5;
	_dir = 1;

	return S_OK;
}

void objectGoldRock::update()
{
	gameObject::update();

	if(_isCrash)
		return;

	if (0 < _quakeCnt)
	{
		--_quakeCnt;
		if (_quakeCnt % 4 == 0)
		{
			_dir *= -1;
			_position.x += _dir * 5;
		}

		if (_quakeCnt < 0)
		{
			_quakeCnt = -1;
		}
	}
}

void objectGoldRock::hitObject()
{
	if(_isCrash)
		return;

	if(0 < _quakeCnt)
		return;

	_quakeCnt = QUAKE_TIME;
	--_crashCount;
	if (_crashCount <= 0)
	{
		if (_anim)
			_anim->end();
		_anim = _animMap[eGOLDROCK_STATE_CRASH];
		_anim->start();

		_isCrash = true;
	}
}

////////////////////////////////////////////////////////////////////////////////////
//									 COIN
////////////////////////////////////////////////////////////////////////////////////
HRESULT objectCoin::init(float x, float y, unsigned int uid, const char * imgName)
{
	gameObject::init(x, y, uid, imgName);
	_type = eOBJECT_COIN;

	_anim = new animation;
	_anim->init(_image, true, 0, _image->GetMaxFrameX(), 5, 0);
	_anim->start();

	_size = { _image->GetFrameWidth(), _image->GetFrameHeight() };
	_collision = { (int)(x - _size.x / 2), (int)y - _size.y
				  ,(int)(x + _size.x / 2), (int)y };


	_isMoveable = true;
	_isInteractionable = true;

	_vecX = RND->getFromIntTo(1, 10);
	_vecY = RND->getFromIntTo(5, 20);

	int value = RND->getInt(2);
	if(0 == value)
		_vecX *= -1;

	_gravity = 0.5f;
	_value = 1;

	return S_OK;
}

void objectCoin::update()
{
	gameObject::update();
	move();
}

void objectCoin::move()
{
	if(!_isMoveable)
		return;
	_time += 0.5f;
	_position.x += _vecX;
	_position.y -= _vecY;

	//if(-10 < _vecY)
		_vecY -= _gravity;

	_collision = {	 (int)(_position.x - _size.x / 2), (int)_position.y - _size.y
					,(int)(_position.x + _size.x / 2), (int)_position.y };
}

void objectCoin::intersectWithObject(gameObject* obj)
{
	if(nullptr ==  obj)
		return;


	RECT objCol = obj->getCollision();

	float offsetX = GetIntersectOffsetX(_collision, objCol);
	float offsetY = GetIntersectOffsetY(_collision, objCol);

	// ����
	if (objCol.left <= _collision.left && _collision.right < objCol.right)
	{
		pushObject(0.f, offsetY);

		if (_position.y < obj->getPosition().y)
		{
			if (obj->getType() == eOBJECT_GROUND)
			{
				_position.y = objCol.top;
				_isMoveable = false;
			}
		}
		else
		{
			_vecY = 0;
		}
	}
	// �¿�
	else if (objCol.top <= _collision.top && _collision.bottom <= objCol.bottom)
	{
		pushObject(offsetX, 0.f);
		pushObject(offsetX, 0.f);
		if (_position.x < obj->getPosition().x)
		{
			if( 0 < _vecX)
				_vecX *= -1;
		}
		else
		{
			if (_vecX < 0)
				_vecX *= -1;
		}
	}
	// �𼭸�
	else if (abs(offsetX) < abs(offsetY))
	{
		pushObject(offsetX, 0.f);
		pushObject(offsetX, 0.f);
		if (1 < abs(_vecY))
			_vecY -= 1;
		if (_position.x < obj->getPosition().x)
		{
			if (0 < _vecX)
				_vecX *= -1;
		}
		else
		{
			if (_vecX < 0)
				_vecX *= -1;
		}
	}
	// �𼭸�
	else
	{
		if (_position.y < obj->getPosition().y)
		{
			if (obj->getType() == eOBJECT_GROUND)
			{
				_isMoveable = false;
			}
		}
		else
		{
			if (_vecY < 0)
				_vecY = 0;
		}
	}
}

