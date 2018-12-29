#pragma once
#include "singletonBase.h"
#include "enemy.h"
#include <list>


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

public:
	
	HRESULT init();
	void update();
	void render();
	void release();

	void setManagerLink(objectManager* objM) {_objM = objM;}

	void setEnemys();

	void removeEnemy(int uid);
	void hitEnemy(int uid);
	const lEnemy& getEnemyList() {return _enemyList;}

private:
	enemy* findEnemy(int uid);
};