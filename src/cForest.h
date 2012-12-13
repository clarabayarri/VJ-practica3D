#pragma once

#include "cFloor.h"
#include "cWall.h"
#include "cTreeForest.h"
#include "cBoarCollection.h"
#include "customshadermanager.h"

class cForest {
public:
	cForest(void);
	~cForest(void);

	void Init();
	void Render(cData * data, CustomShaderManager * shader, float OrientationAngle);
	void RenderPhysical(float OrientationAngle);
	float GetHeight(float x, float z);
	float GetMinY();

	bool CollidesPhysics(vector<float> PlayerPosition, float PlayerRadius);
	bool CollidesBoars(vector<float> PlayerPosition, float PlayerRadius);

	vector<vector<float> > GetTrees();
	vector<vector<float> > GetBoars();

private:
	cFloor floor;
	cWall wall;
	vector<cTreeForest> trees;
	vector<cBoarCollection> boars;
};

