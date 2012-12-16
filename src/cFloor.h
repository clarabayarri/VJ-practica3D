#pragma once

#include <iostream>
#include "cVBO.h"
#include "cData.h"
#include "customshadermanager.h"
#include "Constants.h"


class cFloor : public cVBO {
public:
    cFloor();
    ~cFloor();

	void Init();
	float GetSize();
	float GetDilatation();
	float GetMinY();
	float GetMaxY();
	float GetY(int x, int z);

	void Render(cData * data, CustomShaderManager * shader);
	void RenderPhysical();

protected:
    void UpdateSmoothedNormals();
	void UpdateNormal(int f);

	std::vector<std::vector<float> > heights;

	float miny;
	float maxy;

    bool ready;
};