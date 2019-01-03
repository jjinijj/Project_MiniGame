#pragma once
#include "gameNode.h"
#include "image.h"
#include <map>

enum eOBJECT_TYPE
{
	eOBJECT_CHAIR,
	eOBJECT_COIN,
	eOBJECT_CHARM,
	eOBJECT_GROUND,
	eOBJECT_GOLDROCK,
	eOBJECT_NPC,

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

enum eGOLDROCK_STATE
{
	eGOLDROCK_STATE_IDLE,
	eGOLDROCK_STATE_CRASH,

	eGOLDROCK_STATE_NONE,

};

class gameObject : public gameNode
{
protected:

	image* _image;
	
	map<int, animation*>			_animMap;
	map<int, animation*>::iterator	_iter;
	map<int, animation*>::iterator	_iter_end;

	animation* _anim;

	POINTF _position;
	POINT _size;
	RECT _collision;

	eOBJECT_TYPE _type;
	int _subType;
	unsigned int _uid;
	bool _isMoveable;
	bool _isInteractionable;

	POINT _loopCnt;
	POINT _offcut;

public:
	gameObject();
	~gameObject();

	HRESULT init();
	virtual HRESULT init(float x, float y, unsigned int uid, const char* imgName);	void render();
	void release();
	void update();
	virtual void hitObject();
	virtual void move();
	virtual bool isCrash()	{ return false; }
	virtual bool isFin()	{ return false; }
	virtual void setFin(bool fin)	{ }
	virtual int getPrice() { return 0; }
	virtual void intersectWithObject(gameObject* obj) {}
	
	void pushObject(float offsetX, float offsetY);
	const RECT& getCollision()	{ return _collision;}
	POINTF getPosition()		{ return _position;}
	eOBJECT_TYPE getType()		{ return _type;}
	int getSubType()			{ return _subType;}
	int getUid()				{ return _uid;}
	bool isMoveable()			{ return _isMoveable;}
	bool isInteractionable()	{ return _isInteractionable;}
	
};

class objectGround: public gameObject
{
public:
	// pivot x, y : 중심x, bottom y, 이미지 크기에 맞춰서 생성
	HRESULT init(float x, float y, unsigned int uid, const char* imgName);

	// pivot x, y : 중심x, bottom y, 이미지 크기랑 상관없이 생성(이미지 반복)
	// witdh와 height가 -1일경우 이미지 크기에 맞춤
	HRESULT init(float x, float y, int width, int height, unsigned int uid, const char* imgName);
};

class objectChair: public gameObject
{
public:
	// pivot x, y : 중심x, bottom y, 이미지 크기에 맞춰서 생성
	HRESULT init(float x, float y, unsigned int uid, const char* imgName);
};

class objectGoldRock: public gameObject
{
	enum
	{
		QUAKE_TIME = 20,
	};


private:
	int _crashCount;	// 부셔부셔
	int _quakeCnt;		// 진동

	int _dir;			// 진동 방향
	bool _isCrash;		// 부셔졌는가.
	bool _isFin;		// 동전 다 줬는지

public:
	// pivot x, y : 중심x, bottom y, 이미지 크기에 맞춰서 생성
	HRESULT init(float x, float y, unsigned int uid, const char* imgName);
	void update();
	void hitObject();

	bool isCrash()	{ return _isCrash;}
	bool isFin()	{ return _isFin;}
	void setFin(bool fin) {_isFin = true;}
};

class objectCoin: public gameObject
{
private:
	
	int _value;		// 코인 가격
	float _angle;
	float _gravity;
	float _time;
	float _speed;
	POINTF _startPos;

	float _vecX;
	float _vecY;

public:
	// pivot x, y : 중심x, bottom y, 이미지 크기에 맞춰서 생성
	HRESULT init(float x, float y, unsigned int uid, const char* imgName);
	void update();
	void move();

	int getPrice() {return _value;}
	void intersectWithObject(gameObject* obj);
};

class objectNPC: public gameObject
{
	enum eNPCSTATE
	{
		eIDLE,
		eLOOK,

		eNONE,
		eCOUNT = eNONE,
	};

private:
	int _lookCnt;

public:
	HRESULT init(float x, float y, unsigned int uid, const char* imgName);
	void update();
	void hitObject();
};