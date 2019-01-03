#pragma once
#include "singletonBase.h"
#include "uiNode.h"

class uiManager : public singletonBase<uiManager>
{
	enum eHPICONSTATE
	{
		eFILL,
		eCRASH,
		eEMPTY,

		eHPICONSTATE_NONE,
		eHPCOUNTSTATE_COUNT = eHPICONSTATE_NONE,
	};

private:
	uiProgressbar* _skillGauge;
	vector<uiSprite*> _hp;
	vector<uiSprite*>::iterator _iter_hp;
	uiImage* _coinUi;

	vector<uiNumText*> _coinText;
	vector<uiNumText*>::iterator _iter_coin;

	int _hpCnt;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setHpMaxCount(int value);
	void setHpCurCount(int value);
	void loseHp();

	void setCoinCnt();
	
	void setSkillGauge(int cur, int max);

	void setCoin(int value);
};