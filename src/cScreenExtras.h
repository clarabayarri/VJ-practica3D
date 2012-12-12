#pragma once

#include "cData.h"
#include "cTimeGauge.h"
#include "cMunitionCounter.h"
#include "cSceneMap.h"

#define SCREEN_MARGIN 30

class cScreenExtras
{
public:
	cScreenExtras(void);
	~cScreenExtras(void);

	void Init(const vector<vector<float> >& trees);
	void Draw(cData *Data, double RemainingTime, const vector<float>& player, int munitionCount);

private:
	cTimeGauge TimeGauge;
	cMunitionCounter MunitionCounter;
	cSceneMap SceneMap;

	void DrawTimeGauge(double RemainingTime);
	void DrawMunitionCounter(cData *Data, int count);
	void DrawMap(cData *Data, const vector<float>& player);
};

