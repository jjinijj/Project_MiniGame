#pragma once
#include "gameNode.h"

class animation: public gameNode
{
private:
	image* _image;	//�̹���

	bool _isLoop;		// ���� ��?
	bool _isPlaying;	// �ִϸ��̼� ���� ��?
	bool _isReverse;	// �����?
	
	int _startIdx;		// ������ ���� index
	int _loopStartIdx;	// ���� ������ ���� index
	int _endIdx;		// ������ ���� index

	int _frameCycle;	// ������ �ֱ�
	int _frameY;		// ��� �� ������ Y
	
	int _count;			// frameCount
	int _curFrameX;		// ���� ������� frameX

	int _eventFrameX;	// �̺�Ʈ�� �߻� �� frameX

public:
	animation();
	~animation();

	// �ʱ�ȭ : ����� �� ����� �̹���, ���� ����, ���� �ε���, ���� �ε���, ������ ����Ŭ �ֱ�, ����� ������ Y
	HRESULT init(image* img, bool isLoop, int startIdx, int endIdx, int frameCycle, int frameY, int loopStartIdx = -1);
	
	void release();
	void update();

	// ����
	void start();
	
	// ���� : ����� ��ġ left, top, alpha
	void render(float x, float y, float alpha = 1.f);
	
	//����
	void end();

	void SetPlayDirection(bool isReverse) {_isReverse = isReverse;}

	// ����� frameY ����
	void SetFrameY(int frameY) {_frameY = frameY;}

	// �̺�Ʈ ������ ����
	void SetEventFrameX(int frameX) {_eventFrameX = frameX;}

	// �÷��� ���� Ȯ��
	bool IsPlayingAnimation() {return _isPlaying;}

	// �̺�Ʈ ������?
	bool IsEventFrame() {return (_curFrameX == _eventFrameX);}

private:
	// �÷���
	void play();

	// ���÷���
	void playReverse();

};