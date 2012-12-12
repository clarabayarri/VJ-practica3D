#include "cForest.h"

cForest::cForest(void){}

cForest::~cForest(void){}

vector<vector<float> > cForest::GetTrees() {
	vector<vector<float> > result(NUM_TREES);
	int counter = 0;
	for (unsigned int i = 0; i < NUM_TREE_TYPES; ++i) {
		vector<vector<float> > aux = trees[i].GetTrees();
		for (unsigned int j = 0; j < aux.size(); ++j) result[counter++] = aux[j];
	}
	return result;
}

void cForest::Init() {
	floor.Init();
	wall.Init(&floor);
	trees = vector<cTreeForest>(NUM_TREE_TYPES);

	vector<int> counter(5,0);
	for (int i = 0; i < NUM_TREES; ++i) counter[rand()%5]++;
	for (int i = 0; i < NUM_TREE_TYPES; ++i) {
		vector<vector<float> > coords(counter[i],vector<float>(3));
		int size = (int) (floor.GetSize()-3)*100+1;
		for (int j = 0; j < counter[i]; ++j) {
			coords[j][0] = (float) (rand()%size)/100+1;
			coords[j][2] = (float) (rand()%size)/100+1;
			coords[j][1] = GetHeight(coords[j][0], coords[j][2]);
		}
		trees[i].Init(coords,IMG_TREE1+i);
	}
}

void cForest::Render(cData * data, CustomShaderManager * shader) {
	floor.Render(data,shader);
	wall.Render(data);
	for (int i = 0; i < NUM_TREE_TYPES; ++i) trees[i].Render(data);
}

void cForest::RenderPhysical() {
	floor.RenderPhysical();
	wall.RenderPhysical();
	for (int i = 0; i < NUM_TREE_TYPES; ++i) trees[i].RenderPhysical();
}

float cForest::GetHeight(float x, float z) {
	int x0 = (int) std::floor(x);
	int z0 = (int) std::floor(z);
	int tSize = (int) floor.GetSize();

	float height = 0;
	if (x0+1 < tSize && z0+1 < tSize) {
		height = (1-z+z0)*((1-x+x0)*floor.GetY(x0,z0)+(x-x0)*floor.GetY(x0+1,z0))+(z-z0)*((1-x+x0)*floor.GetY(x0,z0+1) + (x-x0)*floor.GetY(x0+1,z0+1));
	} else if (x0+1 < tSize) {
		height = ((1-x+x0)*floor.GetY(x0,z0)+ (x-x0)*floor.GetY(x0+1,z0));
	} else if (z0+1 < tSize) {
		height = (1-z+z0)*(floor.GetY(x0,z0))+(z-z0)*(floor.GetY(x0,z0+1));
	} else {
		height = floor.GetY(x0,z0);
	}

	return height;
}

float cForest::GetMinY() {
	return floor.GetMinY();
}