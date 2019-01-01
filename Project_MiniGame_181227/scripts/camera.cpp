#include "stdafx.h"
#include "camera.h"
#include "player.h"


camera::camera()
{
}


camera::~camera()
{
}

HRESULT camera::init()
{
	posX = posY = 0;
	return S_OK;
}

HRESULT camera::init(float x, float y)
{
	posX = x;
	posY = y;
	return S_OK;
}

void camera::release()
{
}

void camera::update()
{
	if (_player)
	{
		posX = _player->getPositionX() - WINSIZEX / 2;
		posY = _player->getPositionY() - WINSIZEX / 2;

		if(posX < 0)
			posX = 0;
		if(posY < 0)
			posY = 0;

		if( MAPSIZEX < posX + WINSIZEX )
			posX = MAPSIZEX - WINSIZEX;
		if (MAPSIZEY < posY + WINSIZEY )
			posY = MAPSIZEY - WINSIZEY;
	}

	move();
}

void camera::render()
{
}

void camera::move()
{
	/*
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && posX + WINSIZEX < MAPSIZEX)
	{
		posX += (CAMERA_SPEED);
		if (posX + WINSIZEX > MAPSIZEX)
			posX = MAPSIZEX - WINSIZEX;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && posX > 0)
	{
		posX -= CAMERA_SPEED;
		if (posX < 0)
			posX = 0;
	}


	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && posY + WINSIZEY < MAPSIZEY)
	{
		posY += CAMERA_SPEED;
		if (posY + WINSIZEY > MAPSIZEY)
			posY = MAPSIZEY - WINSIZEY;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && posY > 0)
	{
		posY -= CAMERA_SPEED;
		if (posY < 0)
			posY = 0;
	}
	*/
}
