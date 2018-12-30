#pragma once
#include "gameNode.h"
#include "player.h"
#include "ObjectManager.h"
#include "enemyManager.h"
#include "bulletManager.h"

class playGround : public gameNode
{
private:
	player*			_player;
	objectManager*	_objManager;
	enemyManager*	_enemyManager;
	bulletManager*	_bulletManager;

	bool _isDataLoaded;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};