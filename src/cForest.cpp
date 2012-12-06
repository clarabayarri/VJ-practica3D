#include "cForest.h"

cForest::cForest(void){}

cForest::~cForest(void){}

vector<cTreeForest> cForest::GetTrees()
{
	return trees;
}

void cForest::Init() {
	floor.Init();
	wall.Init(&floor);
	trees = vector<cTreeForest>(NUM_TREE_TYPES);

	vector<int> counter(5,0);
	for (int i = 0; i < NUM_TREES; ++i) counter[rand()%5]++;
	for (int i = 0; i < NUM_TREE_TYPES; ++i) {
		vector<vector<float> > coords(counter[i],vector<float>(3));
		int size = (floor.GetSize()-2);
		for (int j = 0; j < counter[i]; ++j) {
			coords[j][0] = ((rand()%size+1));
			coords[j][2] = ((rand()%size+1));
			coords[j][1] = floor.GetY(coords[j][0],coords[j][2]);
		}
		trees[i].Init(coords,IMG_TREE1+i);
	}
}

void cForest::Render(cData * data, CustomShaderManager * shader) {
	floor.Render(data,shader);
	wall.Render(data);
	for (int i = 0; i < NUM_TREE_TYPES; ++i) trees[i].Render(data);
}

float cForest::GetHeight(float x, float z) {
	float x0 = std::floor(x);
	float z0 = std::floor(z);
	int tSize = floor.GetSize();

	float height = 0;
	if (x0+1 < tSize && z0+1 < tSize) {
		height = (z-z0)*((x-x0)* floor.GetY(x0,z0)+ (1-x+x0)*floor.GetY(x0+1,z0))+(1-z+z0)*((x-x0)*floor.GetY(x0,z0+1) + (1-x+x0)*floor.GetY(x0+1,z0+1));
	} else if (x0+1 < tSize) {
		height = ((x-x0)* floor.GetY(x0,z0)+ (1-x+x0)*floor.GetY(x0+1,z0));
	} else if (z0+1 < tSize) {
		height = (z-z0)*(floor.GetY(x0,z0))+(1-z+z0)*(floor.GetY(x0,z0+1));
	} else {
		height = floor.GetY(x0,z0);
	}

	return height;
}