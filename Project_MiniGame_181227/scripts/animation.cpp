#include "stdafx.h"
#include "animation.h"

animation::animation()
{
}

animation::~animation()
{
}

void animation::init(image* img, bool isLoop, int startIdx, int endIdx, int frameCycle, int frameY, int loopStartIdx)
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

}

void animation::start()
{
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

