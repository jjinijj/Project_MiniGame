#pragma once
#include "gameNode.h"
#include "animation.h"
#include <list>
#include <map>

using namespace std;

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
	ePLAYER_STATE_DEAD,
	ePLAYER_STATE_FLYING,
	ePLAYER_STATE_FALLING,
	ePLAYER_STATE_LAND,

	ePLAYER_STATE_NONE,
	ePLAYER_STATE_COUNT = ePLAYER_STATE_NONE,
};

enum eDirection
{
	eDIRECTION_RIGHT,
	eDIRECTION_LEFT,

	eDIRECTION_UP,
	eDIRECTION_DOWN,
	  
	eDIRECTION_NONE,
	eDIRECTION_COUNT = eDIRECTION_NONE,
};


class player: public gameNode
{
private:
	map<ePLAYER_STATE, animation*> _animMap;
	
	ePLAYER_STATE _state;
	eDirection _dir_LR;
	eDirection _dir_UD;
	animation* _anim;
	ePLAYER_STATE _beforeState;
	ePLAYER_STATE _nextState;

	POINTF _position;
	
	int _jumpCount;

public:
	player();
	~player();

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void move();
	void changeState(ePLAYER_STATE state);
	bool isStateCheck_Attack() {	return ((ePLAYER_STATE_ATTACK_1 == _state) || (ePLAYER_STATE_ATTACK_2 == _state) || (ePLAYER_STATE_ATTACK_3 == _state) ||
											(ePLAYER_STATE_ATTACK_UP == _state) || (ePLAYER_STATE_ATTACK_DOWN == _state)); }
	

};