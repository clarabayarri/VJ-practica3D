#pragma once

#include "cData.h"
#include "cForest.h"
#include "cTreeForest.h"
#include "cAnimatedCharacter.h"
#include "Constants.h"

class cSceneMap
{
public:
	cSceneMap(void);
	~cSceneMap(void);

	void Init(cForest *forest);

	void Draw(cData *Data, cAnimatedCharacter *player);

private:
	int dlId;
};

