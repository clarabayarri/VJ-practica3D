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

	bool CollidesPhysics(std::vector<float> PlayerPosition);
	bool CollidesBoars(std::vector<float> PlayerPosition);

	std::vector<std::vector<float> > GetTrees();
	std::vector<std::vector<float> > GetBoars();

private:
	cFloor floor;
	cWall wall;
	std::vector<cTreeForest> trees;
	std::vector<cBoarCollection> boars;
};

