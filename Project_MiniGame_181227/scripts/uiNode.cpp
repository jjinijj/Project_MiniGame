#include "stdafx.h"
#include "uiNode.h"

HRESULT uiNode::init(float x, float y)
{
	_position = {x, y};
	_isRender = true;
	return S_OK;
}




HRESULT uiImage::init(const char* imgName, float x, float y)
{
	uiNode::init(x, y);
	_image = IMAGEMANAGER->findImage(imgName);
	
	assert( nullptr != _image);

	_size = {_image->GetWidth(), _image->GetHeight()};
	_sizeOrigin = _size;

	return S_OK;
}

void uiImage::release()
{
	_image = nullptr;
}

void uiImage::update()
{
}

void uiImage::render()
{
	_image->render(	CAMERA->getPosX() + _position.x
				   ,CAMERA->getPosY() + _position.y + _sizeOrigin.y - _size.y
				   ,0, _sizeOrigin.y - _size.y
				   ,_size.x, _size.y);
}

void uiSprite::release()
{
	for (_iter = _animMap.begin(); _animMap.end() != _iter; ++_iter)
	{
		animation* anim = (*_iter).second;
		SAFE_RELEASE(anim);
		SAFE_DELETE(anim);
	}

	SAFE_RELEASE(_anim);
	SAFE_DELETE(_anim);

	_animMap.clear();
}

void uiSprite::update()
{
	if(_anim)
		_anim->update();
}

void uiSprite::render()
{
	if(_anim)
		_anim->render(	CAMERA->getPosX() + _position.x
					  , CAMERA->getPosY() + _position.y);
}

void uiSprite::pushBackAnim(int key, animation* anim)
{
	if(_animMap.find(key) != _animMap.end())
		return;

	_animMap.insert(make_pair(key, anim));
}

void uiSprite::setSpriteAnim(int key)
{
	if (_animMap.find(key) == _animMap.end())
		return;

	if(_anim)
		_anim->end();
	_anim = _animMap[key];
	_anim->start();
}



HRESULT uiProgressbar::init(const char* frontName, const char* backName, float x, float y)
{
	_back	= new uiImage;
	_front	= new uiImage;

	_back->init(backName, x, y);
	_front->init(frontName, x, y);

	return S_OK;
}

void uiProgressbar::release()
{
	_back->release();
	_front->release();
}

void uiProgressbar::update()
{
	_back->update();
	_front->update();
}

void uiProgressbar::render()
{
	_back->render();
	_front->render();
}

void uiProgressbar::setProgressbarX(int cur, int max)
{

}

void uiProgressbar::setProgressbarY(int cur, int max)
{
	int originSize = _front->getOriginSize().y;
	int value = originSize / max * cur;
	_front->setSizeY(value);
}




HRESULT uiNumText::init(float x, float y)
{
	uiImage::init("number", x, y);

	return S_OK;
}

void uiNumText::release()
{
	_image = nullptr;
}

void uiNumText::update()
{
}

void uiNumText::render()
{
	if(_image)
	_image->frameRender(  CAMERA->getPosX() + _position.x
						, CAMERA->getPosY() + _position.y
						, _value, 0);
}

void uiNumText::setText(int value)
{
	if(value < 0 || 10 < value)
		return;

	_value = value;
}

