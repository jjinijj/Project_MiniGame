#pragma once
#include "gameNode.h"

class animation: public gameNode
{
private:
	image* _image;	//�̹���

	bool _isLoop;	// ���� ��?
	bool _isPlaying;// �ִϸ��̼� ���� ��?
	
	int _startIdx;		// ������ ���� index
	int _loopStartIdx;	// ���� ������ ���� index
	int _endIdx;		// ������ ���� index

	int _frameCycle; // ������ �ֱ�
	int _frameY;	 // ��� �� ������ Y
	
	int _count;		// frameCount
	int _curFrameX; // ���� ������� frameX

public:
	animation();
	~animation();

	// �ʱ�ȭ : ����� �� ����� �̹���, ���� ����, ���� �ε���, ���� �ε���, ������ ����Ŭ �ֱ�, ����� ������ Y
	void init(image* img, bool isLoop, int startIdx, int endIdx, int frameCycle, int frameY, int loopStartIdx = -1);
	
	// ����
	void start();
	
	// �÷���
	void play();

	// ���÷���
	void playReverse();

	// ���� : ����� ��ġ left, top, alpha
	void render(float x, float y, float alpha = 1.f);
	
	//����
	void end();

	// ����� frameY ����
	void SetFrameY(int frameY) {_frameY = frameY;}

	// �÷��� ���� Ȯ��
	bool IsPlayingAnimation() {return _isPlaying;}

};