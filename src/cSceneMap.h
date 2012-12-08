#pragma once

#include "cData.h"
#include "cAnimatedCharacter.h"
#include "Constants.h"
using namespace std;

class cSceneMap
{
public:
	cSceneMap(void);
	~cSceneMap(void);

	void Init(const vector<vector<float> >& trees);

	void Draw(cData *Data, cAnimatedCharacter *player);

private:
	int dlId;
};

