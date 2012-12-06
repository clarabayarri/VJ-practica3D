#pragma once
#include "cData.h"
#include <vector>
using namespace std;

class cTreeForest {
public:
	cTreeForest();
	~cTreeForest();

	void Init(const vector<vector<float> >& t, int tex);
	void Render(cData * data);

	vector<vector<float> > GetTrees();
private:
	int dlId;
	int texId;

	vector<vector<float> > trees;
};

