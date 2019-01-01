#pragma once
#include "enemy.h"

class player;
class bulletManager;
class primalAspid : public enemy
{
private:

	enum 
	{
		// �÷��̾ �߰��� �� �ִ� �Ÿ�
		SIGHT_RANGE = 800,

		// �÷��̾�� �ִ� �����ϴ� �Ÿ�. �� �Ÿ� �ȿ��� ������ �ϰ� ����������
		CLOSEST_RANGE = 200,

		BULLET_SIZE = 50,
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
	bulletManager* _bulletM;
	float _angle;

	const char* _bulletImgName;
	const char* _bulletPangImgName;

public:
	HRESULT init(POINTF position, unsigned int uid);
	void update();
	void move();
	void dead();
	bool isFire();
	void bulletFire();
	POINTF getBulletFirePoint();

	void setBulletImgNames(const char* fireImgName, const char* pangImgName) {_bulletImgName = fireImgName; _bulletPangImgName = pangImgName;}
	void setPlayerLink(player* target) {_target = target;}
	void setBulletMLink(bulletManager* bulletM) {_bulletM = bulletM;}
};