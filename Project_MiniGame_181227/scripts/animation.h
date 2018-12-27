#pragma once
#include "gameNode.h"

class animation: public gameNode
{
private:
	image* _image;	//이미지

	bool _isLoop;	// 루프 할?
	bool _isPlaying;// 애니메이션 실행 중?
	
	int _startIdx;		// 프레임 시작 index
	int _loopStartIdx;	// 루프 프레임 시작 index
	int _endIdx;		// 프레임 종료 index

	int _frameCycle; // 프레임 주기
	int _frameY;	 // 출력 할 프레임 Y
	
	int _count;		// frameCount
	int _curFrameX; // 현재 출력중인 frameX

public:
	animation();
	~animation();

	// 초기화 : 출력할 떄 사용할 이미지, 루프 여부, 시작 인덱스, 종료 인덱스, 프레임 사이클 주기, 출력할 프레임 Y
	void init(image* img, bool isLoop, int startIdx, int endIdx, int frameCycle, int frameY, int loopStartIdx = -1);
	
	// 시작
	void start();
	
	// 플레이
	void play();

	// 역플레이
	void playReverse();

	// 렌더 : 출력할 위치 left, top, alpha
	void render(float x, float y, float alpha = 1.f);
	
	//종료
	void end();

	// 출력할 frameY 변경
	void SetFrameY(int frameY) {_frameY = frameY;}

	// 플레이 여부 확인
	bool IsPlayingAnimation() {return _isPlaying;}

};