#pragma once
#include "enemy.h"

class gruzzer : public enemy
{
private:
	enum eSTATE
	{
		eMOVE,
		eDEAD,

		eSTATE_NONE,
		eSTATE_COUNT = eSTATE_NONE,
	};

private:

public:

	HRESULT init(POINTF position, unsigned int uid);
	void update();
	void move();
	void dead();

};

