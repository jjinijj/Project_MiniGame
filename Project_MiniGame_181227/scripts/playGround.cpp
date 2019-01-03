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

	// enemy tiktik
	IMAGEMANAGER->addFrameImage("tiktik_move", L"image/tiktik_move.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_move_under", L"image/tiktik_move_under.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_move_sideup", L"image/tiktik_move_sideup.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_move_sidedown", L"image/tiktik_move_sidedown.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_climbup_uts", L"image/tiktik_climbup_uts.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_climbup_stu", L"image/tiktik_climbup_stu.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_climbdown_stu", L"image/tiktik_climbdown_stu.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_climbdown_ots", L"image/tiktik_climbdown_ots.png", 416, 190, 4, 2);
	IMAGEMANAGER->addFrameImage("tiktik_dead", L"image/tiktik_dead.png", 208, 190, 2, 2);

	// enemy gruzze
	IMAGEMANAGER->addFrameImage("gruzzer_move", L"image/gruzzer_move.png", 524, 218, 4, 2);
	IMAGEMANAGER->addFrameImage("gruzzer_dead", L"image/gruzzer_dead.png", 655, 218, 5, 2);

	// enemy pribalAspid
	IMAGEMANAGER->addFrameImage("primalAspid_move", L"image/primalAspid_move.png", 684, 272, 4, 2);
	IMAGEMANAGER->addFrameImage("primalAspid_attack", L"image/primalAspid_attack.png", 684, 272, 4, 2);
	IMAGEMANAGER->addFrameImage("primalAspid_dead", L"image/primalAspid_dead.png", 171, 272, 1, 2);
	
	// enemy bullet
	IMAGEMANAGER->addFrameImage("bullet_fire", L"image/bullet_fire.png", 270, 30, 7, 1);
	IMAGEMANAGER->addFrameImage("bullet_pang", L"image/bullet_pang.png", 203, 30, 3, 1);
	
	// enemy boos mawlek
	IMAGEMANAGER->addFrameImage("mawlek_body", L"image/mawlek_body.png", 3476, 1884, 11, 6);
	IMAGEMANAGER->addFrameImage("mawlek_head", L"image/mawlek_head.png", 417, 428, 3, 4);
	IMAGEMANAGER->addFrameImage("mawlek_arms", L"image/mawlek_arms.png", 872, 1683, 4, 6);

	// floor
	IMAGEMANAGER->addImage("floor", L"image/floor.png", 326, 34);
	IMAGEMANAGER->addImage("floor_stone", L"image/floor_stone.png", 296, 21);
	
	// wall
	IMAGEMANAGER->addImage("wall_L", L"image/wall_L.png", 105, 169);
	IMAGEMANAGER->addImage("wall_R", L"image/wall_R.png", 105, 169);

	// block
	IMAGEMANAGER->addImage("block", L"image/block.png", 390, 73);

	// block big
	IMAGEMANAGER->addImage("block_big", L"image/block_big.png", 677, 209);
	
	// chair
	IMAGEMANAGER->addImage("chair", L"image/chair.png", 185, 92);

	// gold Rock
	IMAGEMANAGER->addFrameImage("goldRock", L"image/goldRock.png", 749, 109, 7, 1);

	// coin
	IMAGEMANAGER->addFrameImage("coin", L"image/coin.png", 104, 28, 4, 1);
	
	// ui hp
	IMAGEMANAGER->addFrameImage("hp", L"image/hp.png", 560, 292, 7, 2);
	
	// ui coin
	IMAGEMANAGER->addImage("coin_ui", L"image/coin_ui.png", 59, 54);

	// ui skill gauage
	IMAGEMANAGER->addFrameImage("skillGauge_in", L"image/skillGauge_in.png", 480, 156, 2, 1);
	IMAGEMANAGER->addImage("skillGauge_out", L"image/skillGauge_out.png", 480, 156);

	// ui charmSlot
	IMAGEMANAGER->addImage("charmSlot", L"image/charmSlot.png", 30, 30);

	// player bullet
	IMAGEMANAGER->addFrameImage("player_bullet_fire_L", L"image/player_bullet_fire_L.png", 540, 202, 2, 1);
	IMAGEMANAGER->addFrameImage("player_bullet_pang_L", L"image/player_bullet_pang_L.png", 1080, 202, 4, 1);
	IMAGEMANAGER->addFrameImage("player_bullet_fire_R", L"image/player_bullet_fire_R.png", 540, 202, 2, 1);
	IMAGEMANAGER->addFrameImage("player_bullet_pang_R", L"image/player_bullet_pang_R.png", 1080, 202, 4, 1);
	
	// ui number
	IMAGEMANAGER->addFrameImage("number", L"image/number.png", 320, 49, 10, 1);
	
	//
	IMAGEMANAGER->addImage("cliff_L", L"image/cliff_L.png", 513, 372);
	IMAGEMANAGER->addImage("cliff_R", L"image/cliff_R.png", 513, 372);

	// npc
	IMAGEMANAGER->addFrameImage("npc", L"image/npc.png", 2219, 376, 7, 2);
	
	// item
	IMAGEMANAGER->addImage("charm1", L"image/charm1_.png", 50, 50);
	IMAGEMANAGER->addImage("charm2", L"image/charm2_.png", 50, 50);

	_player = new player;
	_player->init();

	_objManager = new objectManager;
	_objManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_bulletManager = new bulletManager;
	_bulletManager->init();

	_uiManager = new uiManager;
	_uiManager->init();

	_objManager->setMap();

	_player->setManagerLink(_objManager, _bulletManager, _enemyManager, _uiManager);
	
	_objManager->setLinkPlayer(_player);
	
	_enemyManager->setManagerLink(_objManager, _bulletManager);
	_enemyManager->setPlayerLink(_player);
	
	_bulletManager->setLink(_player, _enemyManager, _objManager);

	CAMERA->setLinkPlayer(_player);

	_player->loadData();
	_enemyManager->loadData();
	_objManager->loadData();
	
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

	_uiManager->release();
	_uiManager->releaseSingleton();
}

void playGround::update()
{
	if ( KEYMANAGER->isOnceKeyDown(VK_F1) )
	{
		_isDebugMode = !_isDebugMode;

		if (_isDebugMode)
		{
			if (KEYMANAGER->isOnceKeyDown('R'))
			{
				release();

				init();
				return;
			}
		}
	}

	gameNode::update();

	_player->update();
	_objManager->update();
	_enemyManager->update();
	_bulletManager->update();
	_uiManager->update();
}

void playGround::render()
{
	// Draw 시작 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->beginDraw();

	//===========================================================================
	//				##		여기에 코드 작성(Start)		##

	_objManager->render();
	_enemyManager->render();
	_bulletManager->render();
	_player->render();
	_uiManager->render();

	//D2DMANAGER->_renderTarget->CreateLayer()
	//				##		여기에 코드 작성(End)		##
	//===========================================================================
	//카메라 정보 출력
	
	if ( _isDebugMode )
	{
		WCHAR str[128];
		swprintf_s(str, L"cameraX : %.1f / %.1f", CAMERA->getPosX(), ( float )( MAPSIZEX - WINSIZEX ));
		D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"나눔고딕", 15.0f
								, str
								, CAMERA->getPosX() + WINSIZEX - 200
								, CAMERA->getPosY() + 20
								, CAMERA->getPosX() + WINSIZEX - 200 + 300
								, CAMERA->getPosY() + 100);

		swprintf_s(str, L"cameraY : %.1f / %.1f", CAMERA->getPosY(), ( float )( MAPSIZEY - WINSIZEY ));
		D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"나눔고딕"
								, 15.0f
								, str
								, CAMERA->getPosX() + WINSIZEX - 200
								, CAMERA->getPosY() + 40
								, CAMERA->getPosX() + WINSIZEX
								, CAMERA->getPosY() + 120);

		//마우스 위치 출력
		swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
		D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush
								, L"맑은고딕"
								, 15.0f
								, str
								, CAMERA->getPosX() + WINSIZEX - 200
								, CAMERA->getPosY() + 60
								, CAMERA->getPosX() + WINSIZEX
								, CAMERA->getPosY() + 60);
		swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);
		D2DMANAGER->drawTextD2D(D2DMANAGER->_defaultBrush, L"맑은고딕"
								, 15.0f
								, str
								, CAMERA->getPosX() + WINSIZEX - 200
								, CAMERA->getPosY() + 80
								, CAMERA->getPosX() + WINSIZEX
								, CAMERA->getPosY() + 80);
	}
	// Draw 끝 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->endDraw();
}