#pragma once
#include "gameNode.h"
#include "image.h"
#include "animation.h"
#include <map>

class uiNode: public gameNode
{
protected:
	POINTF _position;
	
	bool _isRender;
public:

	virtual HRESULT init(float x, float y);
	void release()	= 0;
	void update()	= 0;
	void render()	= 0;

	POINTF getPosition()	{ return _position;}
	bool isRender() { return _isRender; }
	void setIsRender(bool value) { _isRender = value; }
};

class uiImage: public uiNode
{
protected:
	image* _image;
	POINT _size;
	POINT _sizeOrigin;

	

public:

	HRESULT init(const char* imgName, float x, float y);
	void release();
	void update();
	void render();

	void setSizeX(int x)	{ _size.x = x; }
	void setSizeY(int y)	{ _size.y = y; }
	POINT getSize()			{ return _size; }
	POINT getOriginSize()	{ return _sizeOrigin; }
	
};

class uiSprite: public uiNode
{
private:
	map<int, animation*> _animMap;
	map<int, animation*>::iterator _iter;
	animation* _anim;

public:
	void release();
	void update();
	void render();

	void pushBackAnim(int key, animation* anim);
	void setSpriteAnim(int key);
};

class uiProgressbar: public uiNode
{
private:
	uiImage* _back;
	uiImage* _front;

public:
	HRESULT init(const char* frontName, const char* backName, float x, float y);
	void release();
	void update();
	void render();

	void setProgressbarX(int cur, int max);
	void setProgressbarY(int cur, int max);
};

class uiNumText: public uiImage
{
private:
	int _value;

public:

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	// 0 <= value  && value <= 9
	void setText(int value);
	int getText() {return _value;}
};