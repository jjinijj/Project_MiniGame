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

HRESULT gameObject::init(float x, float y, int width, int height, unsigned int uid)
{
	_uid = uid;

	_position = { x, y };
	_collision = { (int)(x - width / 2), (int)y - height, (int)x + width / 2, (int)y };
	_size = { width, height };

	return S_OK;
}

void gameObject::render()
{
	WCHAR str[128];
	swprintf_s(str, L"[UID : %d]", _uid);
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"³ª´®°íµñ", 15.0f
							, str
							, _position.x - 50
							, _position.y - 50
							, _position.x + 50
							, _position.y + 50);

	D2DMANAGER->drawRectangle(D2DMANAGER->_defaultBrush
							  , (float)_collision.left,  (float)_collision.top
							  , (float)_collision.right, (float)_collision.bottom);
}

void gameObject::update()
{
}






HRESULT objectGround::init(float x, float y, int width, int height, unsigned int uid)
{
	gameObject::init(x, y, width, height, uid);

	_type = eOBJECT_GROUND;
	_subType = -1;


	return S_OK;
}
