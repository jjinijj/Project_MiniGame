#pragma once
#include "singletonBase.h"
#include "enemy.h"
#include <list>


enum
{
	// 스테이지에 존재하는 적의 최대 수
	ENEMY_COUNT_IN_STAGE = 5,

	// 보스 등장하기 위한 적의 수
	ENEMY_COUNT_NEED_EXIST_BOSS = 50,

};


typedef std::list<enemy*>					lEnemy;
typedef std::list<enemy*>::iterator			ilEnemy;
typedef std::list<enemy*>::const_iterator	cilEnemy;

class objectManager;
class enemyManager : singletonBase<enemyManager>
{
private:

	lEnemy	_enemyList;
	lEnemy	_deadEnemyList;
	ilEnemy	_iter;

	objectManager* _objM;

	int _enemyCnt;
	bool _isExistBoss;

public:
	
	HRESULT init();
	void update();
	void render();
	void release();

	void setManagerLink(objectManager* objM) {_objM = objM;}

	void setEnemys();


	void createEnemy(eENEMY_TYPE type);

	void removeEnemy(int uid);
	void hitEnemy(int uid);
	const lEnemy& getEnemyList() {return _enemyList;}

private:
	enemy* findEnemy(int uid);
};