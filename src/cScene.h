#pragma once

#include "cData.h"
#include "cForest.h"
#include "customshadermanager.h"
using namespace std;

#define SCENE_WIDTH		8	//#tiles
#define SCENE_DEPTH		8

#define TILE_SIZE		4	//space units

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define GRASS_NUMBER	100
#define GRASS_PLANES	1


class cScene {
public:
	cScene(void);
	virtual ~cScene(void);

	bool IsInitialized;

	void Init();
	void Draw(cData *Data, CustomShaderManager *shaderManager, float OrientationAngle);
	void DrawPhysical(float OrientationAngle);
	int *GetMap();
	void renderBillBoard();
	float GetHeight(float x, float z);
	float GetMinY();

	bool CollidesPhysics(vector<float> PlayerPosition, float PlayerRadius);
	bool CollidesBoars(vector<float> PlayerPosition, float PlayerRadius);

	vector<vector<float> > GetForest();

private:
	cForest forest;	

	int map[SCENE_WIDTH * SCENE_DEPTH];		//scene

	float x;
	float z;
};
