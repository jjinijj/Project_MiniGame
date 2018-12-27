#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		CAMERA->init();
		D2DMANAGER->init();
		TXTDATA->init();
		IMGDATA->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		CAMERA->release();
		CAMERA->releaseSingleton();
		D2DMANAGER->release();
		D2DMANAGER->releaseSingleton();

		TXTDATA->releaseSingleton();
		IMGDATA->releaseSingleton();
	}
}

void gameNode::update()
{
	CAMERA->update();
}

void gameNode::render()
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;		//조사 한 번 해바밤바1
	HDC			hdc;	//조사 한 번 해바밤바2

	switch (iMessage)
	{
		case WM_CREATE:

		break;
		case WM_TIMER:
			this->update();
			this->render();
		break;
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam) + CAMERA->getPosX() );
			_ptMouse.y = static_cast<float>(HIWORD(lParam) + CAMERA->getPosY() );
		break;

		case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
