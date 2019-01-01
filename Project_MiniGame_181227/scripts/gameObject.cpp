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

HRESULT gameObject::init(float x, float y, int width, unsigned int uid, const char* imgName)
{
	_image = IMAGEMANAGER->findImage(imgName);
	
	assert(_image != nullptr);

	int height = _image->GetHeight();

	_uid = uid;

	_position = { x, y };
	_size = { width, height };
	_collision = { (int)(x - width / 2), (int)y - height, (int)x + width / 2, (int)y };

	_type = eOBJECT_TYPE_NONE;
	_subType = -1;

	_loopCnt = 1;
	_offcut = 0;

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

	if ( _image )
	{
		
		for ( int ii = 0; ii < _loopCnt; ++ii )
		{
			_image->render(_image->GetWidth() * ii + _collision.left, (float)_collision.top);
		}

		if( 0 != _offcut)
			_image->render(_image->GetWidth() * _loopCnt + _collision.left, (float)_collision.top
						   , 0, 0
						   ,_offcut, _image->GetHeight());
	}
}

void gameObject::update()
{
}





HRESULT objectGround::init(float x, float y, int width, unsigned int uid, const char* imgName)
{
	gameObject::init(x, y, width, uid, imgName);

	int imgWidth = _image->GetWidth();

	_loopCnt = width / imgWidth;
	_offcut = width % imgWidth;

	_type = eOBJECT_GROUND;
	_subType = -1;

	return S_OK;
}

HRESULT objectGround::init(float x, float y, int width, int height, unsigned int uid, const char * imgName)
{
	init(x, y, width, uid, imgName);
	_collision = { (int)(x - width / 2), (int)y - height, (int)x + width / 2, (int)y };
	return S_OK;
}
