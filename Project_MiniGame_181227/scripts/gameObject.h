#pragma once
#include "gameNode.h"
#include "image.h"



enum eOBJECT_TYPE
{
	eOBJECT_CHAIR,
	eOBJECT_COIN,
	eOBJECT_CHARM,

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
	image* _img;
	POINTF _position;
	POINT _size;
	D2D1_RECT_F _collision;
	
public:
	gameObject();
	~gameObject();

	HRESULT init();

};