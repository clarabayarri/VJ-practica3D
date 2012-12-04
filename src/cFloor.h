#pragma once

#include <iostream>
#include "cVBO.h"
#include "Constants.h"
using namespace std;

class cFloor : public cVBO {
public:
    cFloor();
    ~cFloor();

	void Init();
	float GetSize();
	float GetDilatation();
	float GetY(int x, int z);

protected:
    void UpdateSmoothedNormals();
	void UpdateNormal(int f);

	vector<vector<float> > heights;

    bool ready;
};