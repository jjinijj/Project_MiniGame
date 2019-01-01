#include "stdafx.h"
#include "gruzzer.h"
#include "ObjectManager.h"

HRESULT gruzzer::init(POINTF position, unsigned int uid)
{
	enemy::init(position, uid);

	{
		animation* anim = new animation;
		image* img = IMAGEMANAGER->findImage("gruzzer_move");
		anim->init(img, true, 0, img->GetMaxFrameX(), 10, _dir);
		_animMap.insert(make_pair(eMOVE, anim));

		_imgSize.x = img->GetFrameWidth();
		_imgSize.y = img->GetFrameWidth();
		_imgSizeHalf.x = img->GetFrameWidth() / 2;
		_imgSizeHalf.y = img->GetFrameWidth() / 2;
	}

	{
		animation* anim = new animation;
		image* img = IMAGEMANAGER->findImage("gruzzer_dead");
		anim->init(img, false, 0, img->GetMaxFrameX(), 10, _dir);
		_animMap.insert(make_pair(eDEAD, anim));
	}

	_colSize.x = _imgSize.x - 30;
	_colSize.y = _imgSize.y - 30;
	_anim = _animMap[eMOVE];
	_anim->start();
	_hp = 1;
	_speed = 1;

	_type = eENEMY_GRUZZER;

	_dirUD = (eDIRECTION)RND->getFromIntTo(eUP, eDIRECTION_NONE);
	_collision = {   (int)_position.x - _colSize.x / 2, (int)_position.y - _colSize.y
					,(int)_position.x + _colSize.x / 2, (int)_position.y};

	return S_OK;
}

void gruzzer::update()
{
	enemy::update();

	if (_isAlive)
		move();
}

void gruzzer::move()
{
	if( eRIGHT == _dir)
		_position.x += _speed;
	else
		_position.x -= _speed;

	if(eUP == _dirUD )
		_position.y -= _speed;
	else
		_position.y += _speed;

	_collision = {   (int)_position.x - _colSize.x / 2, (int)_position.y - _colSize.y
					,(int)_position.x + _colSize.x / 2, (int)_position.y};

	if(nullptr == _objM)
		return;

	lObject* objList = _objM->getObjectList(eOBJECT_GROUND);

	if(objList->size() == 0)
		return;

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

		offsetX = GetIntersectOffsetX_doNotBoard(_collision, objCol);
		offsetY = GetIntersectOffsetY_doNotBoard(_collision, objCol);

		// ����
		if ( objCol.left <= _collision.left && _collision.right < objCol.right )
		{
			_dirUD = (eDIRECTION)(eDOWN - _dirUD + eUP);

			_position.y += offsetY;
		} 
		// �¿�
		else if ( objCol.top <= _collision.top && _collision.bottom <= objCol.bottom )
		{
			_dir = (eDIRECTION)(eLEFT - _dir);

			_position.x += offsetX;
		}
		// �𼭸�
		else if ( abs(offsetX) < abs(offsetY) )
		{
			_dir = (eDIRECTION)(eLEFT - _dir);
			_position.x += offsetX;
		}
		// �𼭸�
		else
		{
			_dirUD = (eDIRECTION)(eDOWN - _dirUD + eUP);
			_position.y += offsetY;
		}
	}

	_anim->SetFrameY(_dir);
}

void gruzzer::dead()
{
	enemy::dead();
	changeState(eDEAD);
}
