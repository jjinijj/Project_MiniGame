#pragma once
#include "enemy.h"

class player;
class primalAspid : public enemy
{
private:

	enum 
	{
		// 플레이어를 발견할 수 있는 거리
		SIGHT_RANGE = 800,

		// 플레이어와 최대 인접하는 거리. 이 거리 안에서 공격을 하고 도망갈거임
		CLOSEST_RANGE = 200,
	};

	enum eSTATE
	{
		eIDLE,
		eMOVE_APPROACH,
		eMOVE_FARWAY,
		eATTACK,
		eDEAD,

		eSTATE_NONE,
		eSTATE_COUNT = eSTATE_NONE,
	};

	player* _target;
	float _angle;

public:
	HRESULT init(POINTF position, unsigned int uid);
	void update();
	void move();
	void dead();

	void setPlayerLink(player* target) {_target = target;}
};