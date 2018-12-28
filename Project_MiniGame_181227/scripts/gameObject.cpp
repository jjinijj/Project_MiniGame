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

void gameObject::render()
{
	//IMAGEMANAGER->frameRender()

	D2DMANAGER->drawRectangle(D2DMANAGER->_defaultBrush
							  , _collision.left, _collision.top
							  , _collision.right, _collision.bottom);
	D2DMANAGER->drawRectangle(D2DMANAGER->_defaultBrush
							  , _collisionPoint.left, _collisionPoint.top
							  , _collisionPoint.right, _collisionPoint.bottom);
}

void gameObject::update()
{
}






HRESULT objectGround::init(float x, float y, int width, int height)
{
	_position = { x, y };
	_collision = { (int)(x - width / 2), (int)y - height, (int)x + width / 2, (int)y };
	_collisionPoint = {_collision.left + 1, _collision.top - 2, _collision.right - 1, _collision.top};
	_size = { width, height };

	_type = eOBJECT_GROUND;
	_subType = -1;


	return S_OK;
}
