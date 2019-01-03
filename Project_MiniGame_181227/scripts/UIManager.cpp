#include "stdafx.h"
#include "UIManager.h"

HRESULT uiManager::init()
{
	_hpCnt = 5;

	_skillGauge = new uiProgressbar;
	_skillGauge->init("skillGauge_in","skillGauge_out", 30, 0);

	image* hpImg = IMAGEMANAGER->findImage("hp");
	for (int ii = 0; ii < _hpCnt; ++ii)
	{
		uiSprite* hp = new uiSprite;
		hp->init(ii * 80 + 160, 10);
		
		{
			animation* anim = new animation;
			anim->init(hpImg, true, 0, 4, 5, 0);
			hp->pushBackAnim(eFILL, anim);
		}

		{
			animation* anim = new animation;
			anim->init(hpImg, false, 0, 6, 5, 1);
			hp->pushBackAnim(eCRASH, anim);
		}

		hp->setSpriteAnim(eFILL);
		_hp.push_back(hp);
	}

	_coinUi = new uiImage;
	_coinUi->init("coin_ui", 170, 110);

	_skillGauge->setProgressbarY(0, 10);

	uiNumText* ui = new uiNumText;
	ui->init(250, 110);
	ui->setIsRender(true);

	ui->setText(0);

	_coinText.push_back(ui);

	return S_OK;
}

void uiManager::release()
{
	_skillGauge->release();

	for (_iter_hp = _hp.begin(); _hp.end() != _iter_hp; ++_iter_hp)
		(*_iter_hp)->release();
	for (_iter_coin = _coinText.begin(); _coinText.end() != _iter_coin; ++_iter_coin)
		(*_iter_coin)->release();

	_coinUi->release();

	_hp.clear();
}

void uiManager::update()
{
	_skillGauge->update();

	for(_iter_hp = _hp.begin(); _hp.end() != _iter_hp; ++_iter_hp)
		(*_iter_hp)->update();
	
	_coinUi->update();

	for (_iter_coin = _coinText.begin(); _coinText.end() != _iter_coin; ++_iter_coin)
		(*_iter_coin)->update();
}

void uiManager::render()
{
	_skillGauge->render();

	for (_iter_hp = _hp.begin(); _hp.end() != _iter_hp; ++_iter_hp)
		(*_iter_hp)->render();

	_coinUi->render();

	for (_iter_coin = _coinText.begin(); _coinText.end() != _iter_coin; ++_iter_coin)
	{
		uiNumText* num = (*_iter_coin);
		if(num->isRender())
			(*_iter_coin)->render();
	}
}

void uiManager::setHpMaxCount(int value)
{
	_hpCnt = _hp.size();
	if (_hpCnt < value)
	{
		image* hpImg = IMAGEMANAGER->findImage("hp");
		int plus = _hpCnt - value;
		for (int ii = 0; ii < plus; ++ii)
		{
			uiSprite* hp = new uiSprite;
			hp->init(ii * 80 + 160, 10);

			{
				animation* anim = new animation;
				anim->init(hpImg, true, 0, 4, 5, 0);
				hp->pushBackAnim(eFILL, anim);
			}

			{
				animation* anim = new animation;
				anim->init(hpImg, false, 0, 6, 5, 1);
				hp->pushBackAnim(eCRASH, anim);
			}

			hp->setSpriteAnim(eFILL);
			_hp.push_back(hp);
		}
	}

	for (int ii = 0; ii < _hpCnt; ++ii)
	{
		_hp[ii]->setSpriteAnim(eFILL);
	}
}

void uiManager::setHpCurCount(int value)
{

}

void uiManager::loseHp()
{
	if(_hpCnt <= 0)
		return;

	_hp[_hpCnt - 1]->setSpriteAnim(eCRASH);
	--_hpCnt;
}

void uiManager::setCoinCnt()
{
}

void uiManager::setSkillGauge(int cur, int max)
{
	_skillGauge->setProgressbarY(cur, max);
}

void uiManager::setCoin(int value)
{
	int temp = 0;
	POINTF pos = {};
	for (vector<uiNumText*>::iterator iter = _coinText.begin(); _coinText.end() != iter; ++iter)
	{
		uiNumText* ui = (*iter);
		if (0 == value)
		{
			ui->setIsRender(false);
			continue;
		}
		
		if(!ui->isRender())
			ui->setIsRender(true);

		temp = value % 10;
		value /= 10;

		ui->setText(temp);
		pos = ui->getPosition();
	}

	if (0 != value)
	{
		while (0 != value)
		{
			uiNumText* ui = new uiNumText;
			ui->init(pos.x + 33, pos.y);
			ui->setIsRender(true);

			temp = value % 10;
			value /= 10;

			ui->setText(temp);
			_coinText.push_back(ui);

			pos = ui->getPosition();
		}
		
	}

	int idx = _coinText.size() - 1;
	int size = _coinText.size() / 2;
	for (int ii = 0 ; ii < size ; ++ii)
	{
		int dest = _coinText[ii]->getText();
		int sour = _coinText[idx - ii]->getText();

		_coinText[idx - ii ]->setText(dest);
		_coinText[ii]->setText(sour);
	}
}
