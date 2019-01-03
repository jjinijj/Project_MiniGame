#pragma once
#include "singletonBase.h"
#include"bullet.h"
#include <queue>
#include <list>


class player;
class enemyManager;
class objectManager;
class bulletManager : public singletonBase<bulletManager>
{
private:
	enum 
	{
		BULLET_COUNT = 50,
	};

	queue<arcBullet*>	 _arcBulletQ;		// ������ �׸��� bullet pool
	queue<linearBullet*> _linearbulletQ;	// ���� bullet pool
	
	list<bullet*> _bulletList;				// ���� ������� bullets
	list<bullet*>::iterator _iter;			// iterator

	bullet* _playerBullet;					// �÷��̾� bullet;

	player* _player;
	enemyManager* _enemyM;
	objectManager* _objM;

public:
	void init();
	void update();
	void render();
	void release();

	// bullet ���� : q���� bullet�� ����
	bullet* createBullet(eBULLET_TYPE type);
	void firePlayerBullet(POINTF pos, float angle);
	bool checkPlayerBullet();
	void setLink(player* p, enemyManager* emM, objectManager* objM) {_player = p, _enemyM = emM; _objM = objM;}


private:
	// bullet �浹 Ȯ��
	bool checkHitSomething(bullet* bt);
	
	// bullet �浹 Ȯ��
	bool checkPlayerBulletHitSomething();

	// �� �ȿ� �ֳ�?
	bool checkBulletIntheField(bullet* bt);

	// q�� ������
	list<bullet*>::iterator returnBulletQ(list<bullet*>::iterator it);
};