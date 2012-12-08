#pragma once

#include "cFloor.h"
#include "cWall.h"
#include "cTreeForest.h"
#include "customshadermanager.h"

class cForest {
public:
	cForest(void);
	~cForest(void);

	void Init();
	void Render(cData * data, CustomShaderManager * shader);
	float GetHeight(float x, float z);

	vector<vector<float> > GetTrees();

private:
	cFloor floor;
	cWall wall;
	vector<cTreeForest> trees;
};

