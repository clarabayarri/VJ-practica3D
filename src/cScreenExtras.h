#pragma once

#include "cData.h"
#include "cTimeGauge.h"
#include "cMunitionCounter.h"
#include "cSceneMap.h"
#include "cTreeForest.h"

#define SCREEN_MARGIN 30

class cScreenExtras
{
public:
	cScreenExtras(void);
	~cScreenExtras(void);

	void init(cForest *Forest);
	void Draw(cData *Data);

private:
	cTimeGauge TimeGauge;
	cMunitionCounter MunitionCounter;
	cSceneMap SceneMap;

	void DrawTimeGauge(cData *Data);
	void DrawMunitionCounter(cData *Data);
	void DrawMap(cData *Data);
};

