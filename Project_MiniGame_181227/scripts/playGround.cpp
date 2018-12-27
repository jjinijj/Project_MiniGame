#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	if ( !_isDataLoaded )
	{
		//IMGDATA->ImageLoad("imageData");

		_isDataLoaded = true;
	}

	IMAGEMANAGER->addFrameImage("knight_idle", L"image/knight_idle.png", 568, 266, 4, 2);
	IMAGEMANAGER->addFrameImage("knight_attack_down", L"image/knight_attack_down.png", 852, 266, 6, 2);
	IMAGEMANAGER->addFrameImage("knight_attack_up", L"image/knight_attack_up.png", 852, 266, 6, 2);
	IMAGEMANAGER->addFrameImage("knight_attack1", L"image/knight_attack1.png", 710, 266, 5, 2);
	IMAGEMANAGER->addFrameImage("knight_attack2", L"image/knight_attack2.png", 710, 266, 5, 2);
	IMAGEMANAGER->addFrameImage("knight_attack3", L"image/knight_attack3.png", 1278, 266, 9, 2);
	IMAGEMANAGER->addFrameImage("knight_dead", L"image/knight_dead.png", 1136, 266, 8, 2);
	IMAGEMANAGER->addFrameImage("knight_jump", L"image/knight_jump.png", 1562, 266, 11, 2);
	IMAGEMANAGER->addFrameImage("knight_lookup", L"image/knight_lookup.png", 994, 266, 7, 2);
	IMAGEMANAGER->addFrameImage("knight_lookdown", L"image/knight_lookdown.png", 426, 266, 3, 2);
	IMAGEMANAGER->addFrameImage("knight_sitAnddrowse", L"image/knight_sitAnddrowse.png", 568, 266, 4, 2);
	IMAGEMANAGER->addFrameImage("knight_walk", L"image/knight_walk.png", 852, 266, 6, 2);

	_player.init();

	return S_OK;
}

void playGround::release()
{
	gameNode::release();

	_player.release();
	
}

void playGround::update()
{
	gameNode::update();

	_player.update();
}

void playGround::render()
{
	// Draw ���� - �� �ڵ尡 ������ D2D ��� X
	D2DMANAGER->beginDraw();

	//===========================================================================
	//				##		���⿡ �ڵ� �ۼ�(Start)		##


	_player.render();

	for (int i = 0; i < 10; i++)
	for (int j = 0; j < 10; j++)
	{
		//IMAGEMANAGER->findImage("�׽�Ʈ")->frameRender(j * 200, i * 200, _index, 0, 1);
	}

	//IMAGEMANAGER->findImage("knight_idle")->frameRender(100, 100, _index, 0, 1);

	

	//D2DMANAGER->_renderTarget->CreateLayer()
	//				##		���⿡ �ڵ� �ۼ�(End)		##
	//===========================================================================
	//ī�޶� ���� ���
	WCHAR str[128];

	swprintf_s(str, L"cameraX : %.1f / %.1f", CAMERA->getPosX(), (float)(MAPSIZEX - WINSIZEX));
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"��������", 15.0f
							, str
							, CAMERA->getPosX()
							, CAMERA->getPosY()
							, CAMERA->getPosX() + 300
							, CAMERA->getPosY() + 100);
	
	swprintf_s(str, L"cameraY : %.1f / %.1f", CAMERA->getPosY(), (float)(MAPSIZEY - WINSIZEY));
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"��������"
							, 15.0f
							, str
							, CAMERA->getPosX()
							, CAMERA->getPosY() + 20
							, CAMERA->getPosX() + 300
							, CAMERA->getPosY() + 120);

	//���콺 ��ġ ���
	swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush
							, L"��������"
							, 15.0f
							, str
							, CAMERA->getPosX() + WINSIZEX - 200
							, CAMERA->getPosY()
							, CAMERA->getPosX() + WINSIZEX
							, CAMERA->getPosY() + 60);
	swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"��������"
							, 15.0f
							, str
							, CAMERA->getPosX() + WINSIZEX - 200
							, CAMERA->getPosY() + 20
							, CAMERA->getPosX() + WINSIZEX
							, CAMERA->getPosY() + 80);

	// Draw �� - �� �ڵ尡 ������ D2D ��� X
	D2DMANAGER->endDraw();
}