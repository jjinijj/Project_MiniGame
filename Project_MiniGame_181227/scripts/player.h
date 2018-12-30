#pragma once
#include "gameNode.h"
#include "animation.h"
#include <list>
#include <map>

using namespace std;
//using namespace JJINS_UTIL;

enum
{
	// �ӵ�
	PLAYER_IDLE_SPEED = 10,
	PLAYER_ATTACK_SPEED = 3,
	PLAYER_MOVE_SPEED = 3,

	// �÷��̾� �� ������ �̹��� ũ��
	PLAYER_SIZE_WIDE = 142,
	PLAYER_SIZE_HEIGHT = 133,
	PLAYER_SIZE_WIDE_HALF = PLAYER_SIZE_WIDE / 2,

	// �÷��̾� collision ũ��
	PLAYER_COL_SIZE_WIDE = 50,
	PLAYER_COL_SIZE_HEIGHT = 125,
	PLAYER_COL_SIZE_WIDE_HALF = PLAYER_COL_SIZE_WIDE / 2,
	PLAYER_COL_SIZE_HEIGHT_HALF = PLAYER_COL_SIZE_HEIGHT / 2,

	// �÷��̾� ���� �ð�
	PLAYER_INVINCIBILITY_TIME = 50,
	PLAYER_PUSHED_TIME = 10,

	// �÷��̾� ���� �Ŀ�
	PLAYER_JUMP_POWER = 8,
	PLAYER_GRAVITY = 2,
	
	// �и��� ���� ũ��
	PLAYER_PUSHED_POW = 2,

};

enum ePLAYER_STATE
{
	ePLAYER_STATE_IDLE,
	ePLAYER_STATE_WALK,
	ePLAYER_STATE_LOOK_UP,
	ePLAYER_STATE_LOOK_DOWN,
	ePLAYER_STATE_JUMP,
	ePLAYER_STATE_ATTACK_1, // 5
	ePLAYER_STATE_ATTACK_2, // 6
	ePLAYER_STATE_ATTACK_3, // 7
	ePLAYER_STATE_ATTACK_UP, // 8
	ePLAYER_STATE_ATTACK_DOWN, // 9
	ePLAYER_STATE_SIT,
	ePLAYER_STATE_DROWSE,
	ePLAYER_STATE_WAKEUP,
	ePLAYER_STATE_DEAD,
	ePLAYER_STATE_FLYING,
	ePLAYER_STATE_FALLING,
	ePLAYER_STATE_LAND,
	//ePLAYER_STATE_HIT,

	ePLAYER_STATE_NONE,
	ePLAYER_STATE_COUNT = ePLAYER_STATE_NONE,
};

enum eDIRECTION
{
	eDIRECTION_RIGHT,
	eDIRECTION_LEFT,

	eDIRECTION_UP,
	eDIRECTION_DOWN,
	  
	eDIRECTION_NONE,
	eDIRECTION_COUNT = eDIRECTION_NONE,
};


class objectManager;
class bulletManager;
class enemyManager;
class player: public gameNode
{
private:
	map<ePLAYER_STATE, animation*> _animMap;
	map<ePLAYER_STATE, animation*>::iterator _ianiMap;
	ePLAYER_STATE _state;
	eDIRECTION _dir_LR;
	eDIRECTION _dir_UD;
	eDIRECTION _dir_pushed;
	animation* _anim;

	POINT _position;	// middle, bottom
	POINT _size;
	POINT _atkRange;

	RECT _collision;	// �÷��̾� �浹ü
	RECT _collisionAtk; // ���� �浹ü
	
	float _jumpPower;
	float _gravity;

	float _jumpHeight;
	bool _isFloating;
	bool _isAttack2Ready;
	bool _isAlive;
	bool _isJumpKeyUp;

	int _skillGauge;
	int _hpCnt;

	int _drowsingCntDown;
	int _invinCntDown;		// �������� : �ǰݴ����� ��
	int _pushedCntDown;		// �и���

	bool _showRect;
	
	objectManager*	_objM;
	bulletManager*	_bulletM;
	enemyManager*	_enemyM;

	
	
	
	// �׽�Ʈ��
	RECTF _collisionChair; // ���� �׽�Ʈ��

public:
	player();
	~player();

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void resetPlayer();
	void move();
	void updateCollision();
	void changeState(ePLAYER_STATE state);
	void evaluateEvent();

	void takeDamage();

	void attackUseSword();
	void attackUseBullet();

	void setManagerLink(objectManager* objM, bulletManager* bulletM, enemyManager* enemyM) {_objM = objM; _bulletM = bulletM; _enemyM = enemyM;}
	float getPositionX() {return _position.x;}
	float getPositionY() {return _position.y;}
	RECT getCollisionRECT() {return _collision;}
	
	bool checkInteractionObject();
	bool checkIntersectEnemy();
	bool checkFloating();

	bool isStateCheck_Attack() { return ((ePLAYER_STATE_ATTACK_1 == _state) || (ePLAYER_STATE_ATTACK_2 == _state) || (ePLAYER_STATE_ATTACK_3 == _state) ||
										(ePLAYER_STATE_ATTACK_UP == _state) || (ePLAYER_STATE_ATTACK_DOWN == _state)); }
	bool isMoveable()			{ return (ePLAYER_STATE_SIT != _state) && (ePLAYER_STATE_DROWSE != _state);}
	bool isStateFloating()		{return  _isFloating; }



};