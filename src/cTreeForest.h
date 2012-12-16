#pragma once
#include "cData.h"
#include <vector>


class cTreeForest {
public:
	cTreeForest();
	~cTreeForest();

	void Init(const std::vector<std::vector<float> >& t, int tex);
	void Render(cData * data);
	void RenderPhysical();

	bool Collides(std::vector<float> PlayerPosition);

	std::vector<std::vector<float> > GetTrees();
private:
	int dlId;
	int dlIdPhysical;
	int texId;

	std::vector<std::vector<float> > trees;
};

