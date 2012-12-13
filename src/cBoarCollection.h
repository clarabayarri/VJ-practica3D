#pragma once
#include "cData.h"
#include <vector>
using namespace std;

class cBoarCollection
{
public:
	cBoarCollection(void);
	~cBoarCollection(void);

	void Init(const vector<vector<float> >& t, int tex);
	void Render(cData * data, float OrientationAngle);
	void RenderPhysical(float OrientationAngle);

	bool Collides(vector<float> PlayerPosition, float PlayerRadius);

	vector<vector<float> > GetBoars();
private:
	int texId;

	vector<vector<float> > boars;
};

