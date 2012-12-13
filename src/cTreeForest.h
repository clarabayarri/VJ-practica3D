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
	void RenderPhysical();

	bool Collides(vector<float> PlayerPosition, float PlayerRadius);

	vector<vector<float> > GetTrees();
private:
	int dlId;
	int dlIdPhysical;
	int texId;

	vector<vector<float> > trees;
};

