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

	// 플레이어
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

	IMAGEMANAGER->addFrameImage("tiktik_move", L"image/tiktik_move.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_move_under", L"image/tiktik_move_under.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_move_sideup", L"image/tiktik_move_sideup.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_move_sidedown", L"image/tiktik_move_sidedown.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_climbup_uts", L"image/tiktik_climbup_uts.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_climbup_stu", L"image/tiktik_climbup_stu.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_climbdown_stu", L"image/tiktik_climbdown_stu.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_climbdown_ots", L"image/tiktik_climbdown_ots.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_dead", L"image/tiktik_dead.png", 208, 190, 2, 2);

	IMAGEMANAGER->addFrameImage("gruzzer_move", L"image/gruzzer_move.png", 524, 218, 4, 2);
	IMAGEMANAGER->addFrameImage("gruzzer_dead", L"image/gruzzer_dead.png", 655, 218, 5, 2);

	IMAGEMANAGER->addFrameImage("primalAspid_move", L"image/primalAspid_move.png", 684, 272, 4, 2);
	IMAGEMANAGER->addFrameImage("primalAspid_attack", L"image/primalAspid_attack.png", 684, 272, 4, 2);
	IMAGEMANAGER->addFrameImage("primalAspid_dead", L"image/primalAspid_dead.png", 171, 272, 1, 2);
	
	IMAGEMANAGER->addFrameImage("bullet_fire", L"image/bullet_fire.png", 270, 30, 7, 1);
	IMAGEMANAGER->addFrameImage("bullet_pang", L"image/bullet_pang.png", 203, 30, 3, 1);


	_player = new player;
	_player->init();

	_objManager = new objectManager;
	_objManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_bulletManager = new bulletManager;
	_bulletManager->init();

	_player->setManagerLink(_objManager, _bulletManager, _enemyManager);
	_enemyManager->setManagerLink(_objManager, _bulletManager);
	_enemyManager->setPlayerLink(_player);
	
	_bulletManager->setLink(_player, _enemyManager, _objManager);
	
	_enemyManager->setEnemys();

	return S_OK;
}

void playGround::release()
{
	gameNode::release();

	SAFE_RELEASE(_player);
	SAFE_DELETE(_player);

	_objManager->release();
	_objManager->releaseSingleton();

	_enemyManager->release();
	_enemyManager->releaseSingleton();
}

void playGround::update()
{
	if ( KEYMANAGER->isOnceKeyDown('R') )
	{
		release();

		init();
		return;
	}
	gameNode::update();

	_player->update();
	_objManager->update();
	_enemyManager->update();
	_bulletManager->update();
}

void playGround::render()
{
	// Draw 시작 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->beginDraw();

	//===========================================================================
	//				##		여기에 코드 작성(Start)		##

	_objManager->render();
	_bulletManager->render();
	_enemyManager->render();
	_player->render();

	//D2DMANAGER->_renderTarget->CreateLayer()
	//				##		여기에 코드 작성(End)		##
	//===========================================================================
	//카메라 정보 출력
	WCHAR str[128];

	swprintf_s(str, L"cameraX : %.1f / %.1f", CAMERA->getPosX(), (float)(MAPSIZEX - WINSIZEX));
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"나눔고딕", 15.0f
							, str
							, CAMERA->getPosX()
							, CAMERA->getPosY()
							, CAMERA->getPosX() + 300
							, CAMERA->getPosY() + 100);
	
	swprintf_s(str, L"cameraY : %.1f / %.1f", CAMERA->getPosY(), (float)(MAPSIZEY - WINSIZEY));
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"나눔고딕"
							, 15.0f
							, str
							, CAMERA->getPosX()
							, CAMERA->getPosY() + 20
							, CAMERA->getPosX() + 300
							, CAMERA->getPosY() + 120);

	//마우스 위치 출력
	swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush
							, L"맑은고딕"
							, 15.0f
							, str
							, CAMERA->getPosX() + WINSIZEX - 200
							, CAMERA->getPosY()
							, CAMERA->getPosX() + WINSIZEX
							, CAMERA->getPosY() + 60);
	swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);
	D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"맑은고딕"
							, 15.0f
							, str
							, CAMERA->getPosX() + WINSIZEX - 200
							, CAMERA->getPosY() + 20
							, CAMERA->getPosX() + WINSIZEX
							, CAMERA->getPosY() + 80);

	// Draw 끝 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->endDraw();
}