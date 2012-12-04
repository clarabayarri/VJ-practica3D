#pragma once

#include "cFloor.h"
#include "cWall.h"
#include "cTreeForest.h"

class cForest
{
public:
	cForest(void);
	~cForest(void);

	void Init();
	void Render(cData * data);
private:
	cFloor floor;
	cWall wall;
	vector<cTreeForest> trees;
};

