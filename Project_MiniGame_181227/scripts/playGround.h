#pragma once
#include "gameNode.h"
#include "player.h"
#include "ObjectManager.h"
#include "enemyManager.h"
#include "bulletManager.h"
#include "UIManager.h"

class playGround : public gameNode
{
private:
	player*			_player;
	objectManager*	_objManager;
	enemyManager*	_enemyManager;
	bulletManager*	_bulletManager;
	uiManager*		_uiManager;

	bool _isDataLoaded;
	bool _isPlaying;

	image* _title;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

