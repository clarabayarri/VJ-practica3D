#pragma once

#include "cData.h"
using namespace std;

#define SCENE_WIDTH		8	//#tiles
#define SCENE_DEPTH		8

#define TILE_SIZE		4	//space units

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define GRASS_NUMBER	100
#define GRASS_PLANES	1


class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	void Init();
	bool LoadLevel(int level);
	void Draw(cData *Data);
	int *GetMap();
	void renderBillBoard();

private:
	void DrawGrass(cData *Data);
	void MakeCubeDL(float w,float h,float d,float tw,float th,float td);
	void MakeGrassDL();
	int dl_cube;

	int dl_grass;
	vector<pair<float,float> > grassPosition;
	vector<float> grassRotation;

	bool wind;
	float windangle;
	float amplitude;

	int map[SCENE_WIDTH * SCENE_DEPTH];		//scene

	float x;
	float z;
};
