#pragma once
#include "gameNode.h"
#include "player.h"

#define ENEMY_MAX 18

class playGround : public gameNode
{
private:
	player _player;


	bool _isDataLoaded;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	playGround();
	~playGround();
};