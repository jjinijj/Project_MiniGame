#pragma once
#include "enemy.h"

class player;
class primalAspid : public enemy
{
private:

	enum 
	{
		// �÷��̾ �߰��� �� �ִ� �Ÿ�
		SIGHT_RANGE = 800,

		// �÷��̾�� �ִ� �����ϴ� �Ÿ�. �� �Ÿ� �ȿ��� ������ �ϰ� ����������
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