#pragma once
#include "enemy.h"

class player;
class mawlek : public enemy
{
	enum 
	{
		ATTACK_RANGE = 300, // �ٰŸ� ���� ����
		ATTACK_RANGE_FAR = 100,// ���Ÿ� ���� ����

		IDLE_TIME = 10,
	};


	enum eSTATE
	{
		eIDLE,
		eMOVE,
		eATTACK1,		// ����
		eATTACK2,		// �ܹ� �߻�
		eATTACK3,		// ������� �߻�
		eDEAD,

		eNONE,
		eSTATE_COUNT = eNONE,
	};

	enum eBODYSTATE
	{
		eBODY_IDLE,
		eBODY_MOVE,
		eBODY_ATTACK,
	};

	enum eARMSTATE
	{
		eARM_IDLE,
		eARM_MOVE,
		eARM_ATTACK,
	};

	enum eHEADSTATE
	{
		eHEAD_IDLE,
		eHEAD_ATTAK,
	};

private:
	map<int, animation*>			_animMap_armL;
	map<int, animation*>			_animMap_armR;
	map<int, animation*>			_animMap_head;

	animation* _anim_armL;
	animation* _anim_armR;
	animation* _anim_head;

	eSTATE _mawlekState;

	eARMSTATE _armState;
	eHEADSTATE _headState;

	RECT _collisionAtk;

	player* _target;

	int _idleTime;

public:
	HRESULT init(POINTF position, unsigned int uid);
	void update();
	void release();
	void render();
	
	void dead();
	void move();

	void setPlayerLink(player* target) {_target = target;}

private:
	void changeArmState(eARMSTATE state);
	void changeHeadState(eHEADSTATE state);

	void attackSide(eDIRECTION dir);
};