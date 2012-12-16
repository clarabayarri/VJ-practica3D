#pragma once
#include "cData.h"
#include <vector>


class cBoarCollection
{
public:
	cBoarCollection(void);
	~cBoarCollection(void);

	void Init(const std::vector<std::vector<float> >& t, int tex);
	void Render(cData * data, float OrientationAngle);
	void RenderPhysical(float OrientationAngle);

	bool Collides(std::vector<float> PlayerPosition);

	std::vector<std::vector<float> > GetBoars();
private:
	int texId;

	std::vector<std::vector<float> > boars;
	std::vector<int> disappearing;
};

