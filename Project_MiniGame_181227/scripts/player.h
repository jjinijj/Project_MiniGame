#pragma once
#include "gameNode.h"
#include "animation.h"
#include <list>
#include <map>

using namespace std;
//using namespace JJINS_UTIL;

enum
{
	// 속도
	PLAYER_IDLE_SPEED = 10,
	PLAYER_ATTACK_SPEED = 3,
	PLAYER_MOVE_SPEED = 3,

	// 플레이어 한 프레임 이미지 크기
	PLAYER_SIZE_WIDE = 142,
	PLAYER_SIZE_HEIGHT = 133,
	PLAYER_SIZE_WIDE_HALF = PLAYER_SIZE_WIDE / 2,

	// 플레이어 collision 크기
	PLAYER_COL_SIZE_WIDE = 50,
	PLAYER_COL_SIZE_HEIGHT = 125,
	PLAYER_COL_SIZE_WIDE_HALF = PLAYER_COL_SIZE_WIDE / 2,
	PLAYER_COL_SIZE_HEIGHT_HALF = PLAYER_COL_SIZE_HEIGHT / 2,

	// 플레이어 무적 시간
	PLAYER_INVINCIBILITY_TIME = 50,
	PLAYER_PUSHED_TIME = 10,

	// 플레이어 점프 파워
	PLAYER_JUMP_POWER = 8,
	PLAYER_GRAVITY = 2,
	
	// 밀리는 힘의 크기
	PLAYER_PUSHED_POW = 2,

	// 캐릭터 초기  스텟
	PLAYER_MAX_HP = 5,
	PLAYER_ATTACK_RANGE_X = 100,
	PLAYER_ATTACK_RANGE_Y = 25,

};

enum ePLAYER_STATE
{
	ePLAYER_STATE_IDLE,
	ePLAYER_STATE_WALK,
	ePLAYER_STATE_LOOK_UP,
	ePLAYER_STATE_LOOK_DOWN,
	ePLAYER_STATE_JUMP,
	ePLAYER_STATE_ATTACK_1,
	ePLAYER_STATE_ATTACK_2,
	ePLAYER_STATE_ATTACK_3,
	ePLAYER_STATE_ATTACK_UP,
	ePLAYER_STATE_ATTACK_DOWN,
	ePLAYER_STATE_SIT,
	ePLAYER_STATE_DROWSE,
	ePLAYER_STATE_WAKEUP,
	ePLAYER_STATE_DEAD,
	ePLAYER_STATE_FLYING,
	ePLAYER_STATE_FALLING,
	ePLAYER_STATE_LAND,

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
class uiManager;
class gameObject;
class player: public gameNode
{
private:
	map<ePLAYER_STATE, animation*> _animMap;
	map<ePLAYER_STATE, animation*> _animMap_effect;
	map<ePLAYER_STATE, animation*>::iterator _ianiMap;
	ePLAYER_STATE _state;
	eDIRECTION _dir_LR;
	eDIRECTION _dir_UD;
	eDIRECTION _dir_pushed;
	
	animation* _anim;
	animation* _anim_effect;

	POINTF _position;	// middle, bottom
	POINTF _genPosition;	// regen position
	POINT _size;
	POINT _atkRange;

	RECT _collision;	// 플레이어 충돌체
	RECT _collisionAtk; // 공격 충돌체
	
	float _jumpPower;
	float _gravity;

	float _jumpHeight;
	bool _isFloating;
	bool _isAttack2Ready;
	bool _isAlive;
	bool _isJumpKeyUp;

	int _skillGauge;
	int _skillGaugeMax;
	int _hpCnt;
	int _maxHp;
	int _coin;
	int _ability;	// 추가 능력치 : 아이템효과

	int _drowsingCntDown;
	int _invinCntDown;		// 무적상태 : 피격당했을 때
	int _pushedCntDown;		// 밀릴때

	objectManager*	_objM;
	bulletManager*	_bulletM;
	enemyManager*	_enemyM;
	uiManager*		_uiM;
	
	
	// 테스트용
	RECTF _collisionChair; // 의자 테스트용

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
	void changeCoin(int value);

	void changeCharm(int charmType);

	void attackUseSword();
	void attackUseBullet();

	void setManagerLink(objectManager* objM, bulletManager* bulletM, enemyManager* enemyM, uiManager* uiM) {_objM = objM; _bulletM = bulletM; _enemyM = enemyM; _uiM = uiM;}
	float getPositionX() {return _position.x;}
	float getPositionY() {return _position.y;}
	RECT getCollisionRECT() {return _collision;}
	int getCoin() {return _coin; }
	
	bool checkInteractionObject(int type);
	gameObject* findInteractionObject(int type);
	bool checkIntersectEnemy();
	bool checkFloating();

	bool isStateCheck_Attack()  { return ((ePLAYER_STATE_ATTACK_1 == _state) || (ePLAYER_STATE_ATTACK_2 == _state) || (ePLAYER_STATE_ATTACK_3 == _state) ||
										(ePLAYER_STATE_ATTACK_UP == _state) || (ePLAYER_STATE_ATTACK_DOWN == _state)); }
	bool isMoveable()			{ return (ePLAYER_STATE_SIT != _state) && (ePLAYER_STATE_DROWSE != _state);}
	bool isStateFloating()		{ return  _isFloating; }



	// 플레이어 데이터 저장, 로드
	void saveData();
	void loadData();
};