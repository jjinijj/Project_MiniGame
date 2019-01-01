#pragma once
#include "gameNode.h"
#include "image.h"
#include <list>

enum eOBJECT_TYPE
{
	eOBJECT_CHAIR,
	eOBJECT_COIN,
	eOBJECT_CHARM,
	eOBJECT_GROUND,

	eOBJECT_TYPE_NONE,
	eOBJECT_TYPE_COUNT = eOBJECT_TYPE_NONE,
};

enum eCHARM_TYPE
{
	eCHARM_ATKRANGE,
	eCHARM_HP_UP,

	eCHARM_TYPE_NONE,
	eCHARM_TYPE_COUNT = eOBJECT_TYPE_NONE,

};

class gameObject : public gameNode
{
protected:

	image* _image;

	list<image*>::iterator _iter;
	list<image*>::iterator _iter_end;

	POINTF _position;
	POINT _size;
	RECT _collision;

	eOBJECT_TYPE _type;
	int _subType;
	unsigned int _uid;

	int _loopCnt;
	int _offcut;

public:
	gameObject();
	~gameObject();

	HRESULT init();
	virtual HRESULT init(float x, float y, int width, unsigned int uid, const char* imgName);
	void render();
	void update();
	
	const RECT& getCollision() {return _collision;}
	eOBJECT_TYPE getType() {return _type;}
	int getSubType() {return _subType;}
	int getUid() {return _uid;}
};

class objectGround: public gameObject
{
public:
	// pivot x, y : Áß½Éx, bottom y
	HRESULT init(float x, float y, int width, unsigned int uid, const char* imgName);
	HRESULT init(float x, float y, int width, int height, unsigned int uid, const char* imgName);
};
