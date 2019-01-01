#pragma once
#include "gameNode.h"
#include "animation.h"

enum eENEMY_TYPE
{
	eENEMY_TIKTIK,
	eENEMY_GRUZZER,
	eENEMY_PRIMALASPID,
	eENEMY_MAWLEK,

	eENEMY_NONE,
	eENEMY_COUNT = eENEMY_NONE,
};

class objectManager;
class gameObject;
class enemy : public gameNode
{
protected:
	enum eDIRECTION
	{
		eRIGHT,
		eLEFT,
		eUP,
		eDOWN,

		eDIRECTION_NONE,
		eDIRECTION_COUNT = eDIRECTION_NONE,
	};


	map<int, animation*>			_animMap;
	map<int, animation*>::iterator	_ianiMap;

	animation* _anim;


	unsigned int _uid;
	bool _isAlive;
	bool _isDead;
	bool _isAppear;
	int _hp;
	int _speed;

	eDIRECTION _dir;
	eDIRECTION _dirUD;
	int _state;
	int _deadCnt;
	int _alphaCntDown;

	POINT _position;
	POINT _imgSize;
	POINT _imgSizeHalf;
	POINT _colSize;
	RECT _collision;

	eENEMY_TYPE _type;
	
	objectManager* _objM;

public:

	virtual HRESULT init(POINTF position, unsigned int uid);
	void update();
	void release();
	void render();
	virtual void dead();
	virtual bool isFire();
	virtual void bulletFire();
	virtual POINTF getBulletFirePoint();

	void move();
	void attack();
	void changeState(int state);

	void takeDamage();

	unsigned int getUid() {return _uid;}
	bool isAlive() {return _isAlive;}
	bool isAppear() {return _isAppear;}
	const RECT& getCollision() {return _collision;}
	POINTF getPosition() {return MakePointF((float)_position.x, (float)_position.y);}

	void setManagerLink(objectManager* objM) {_objM = objM;}
	eENEMY_TYPE getEnemyType() {return _type;}
};

