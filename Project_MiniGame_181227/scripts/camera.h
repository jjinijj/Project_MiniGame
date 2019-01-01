#pragma once
#include "singletonBase.h"

#define CAMERA_SPEED 10.0f

class player;
class camera : public singletonBase<camera>
{
private:
	float posX;
	float posY;

	player* _player;

public:
	camera();
	~camera();

	HRESULT init();
	HRESULT init(float x, float y);
	void release();
	void update();
	void render();
	void move();

	float getPosX()			{ return posX; }
	float getPosY()			{ return posY; }
	float setPosX(float x)  { posX = x; }
	float setPosY(float y)  { posX = y; }

	void setLinkPlayer(player* target) {_player = target;}

};

