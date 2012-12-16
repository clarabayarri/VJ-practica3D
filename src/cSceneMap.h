#pragma once

#include "cData.h"
#include "Constants.h"
using namespace std;

class cSceneMap
{
public:
	cSceneMap(void);
	~cSceneMap(void);

	void Init(const vector<vector<float> >& trees);

	void Draw(cData *Data, const std::vector<float>& player, const std::vector<std::vector<float> >& enemies);

private:
	int dlId;
};

