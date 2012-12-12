#pragma once

#pragma comment(lib,"OpenGLUT")

#include "cData.h"
#include "Globals.h"
using namespace std;

class cTimeGauge
{
public:
	cTimeGauge(void);
	~cTimeGauge(void);

	void Draw(double RemainingTime);

private:
	bool ChangingColor;
	int ColorCount;

	string FormatTime(double Difference);
};

