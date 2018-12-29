#include "stdafx.h"
#include "animation.h"

animation::animation()
{
}

animation::~animation()
{
}

HRESULT animation::init(image* img, bool isLoop, int startIdx, int endIdx, int frameCycle, int frameY, int loopStartIdx)
{
	_image = img;

	_isLoop = isLoop;
	_isPlaying = false;

	_startIdx = startIdx;
	_endIdx = endIdx;
	if(-1 != loopStartIdx)
		_loopStartIdx = loopStartIdx;
	else
		_loopStartIdx = _startIdx;
	
	_frameCycle = frameCycle;
	_frameY = frameY;
	
	_count = 0;
	_curFrameX = _startIdx;

	_eventFrameX = -1; // 이벤트 프레임 없음으로 초기화
	_isReverse = false;	// 정방향 재생

	return S_OK;
}

void animation::release()
{
}

void animation::update()
{
	if(_isReverse)
		playReverse();
	else
		play();
}

void animation::start()
{
	if(_isReverse)
		_curFrameX = _endIdx;
	else
		_curFrameX = _startIdx;

	_isPlaying = true;

}

void animation::play()
{
	if(!_isPlaying)
		return;

	++_count;
	if (_frameCycle < _count)
	{
		_count = 0;
		_doEvent = false;
		++_curFrameX;
		if (_endIdx < _curFrameX)
		{
			if(_isLoop) 
				_curFrameX = _loopStartIdx;
			else
			{
				_curFrameX = _endIdx;
				end(); 
				return;
			}
		}
	}
}

void animation::playReverse()
{
	if (!_isPlaying)
		return;

	--_count;
	if (_count < 0)
	{
		_count = _frameCycle;
		_doEvent = false;
		--_curFrameX;
		if (_curFrameX < _startIdx)
		{
			if (_isLoop)
				_curFrameX = _endIdx;
			else
			{
				_curFrameX = _startIdx;
				end();
				return;
			}
		}
	}
}

void animation::render(float x, float y, float alpha)
{
	_image->frameRender(x, y, _curFrameX, _frameY, alpha);
}

void animation::end()
{
	_isPlaying = false;
}

