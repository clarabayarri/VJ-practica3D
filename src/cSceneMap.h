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

	void Draw(cData *Data, const vector<float>& player);

private:
	int dlId;
};

