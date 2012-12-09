#pragma once

#pragma comment(lib,"OpenGLUT")

#include "cData.h"
#include <ctime>
using namespace std;

class cTimeGauge
{
public:
	cTimeGauge(void);
	~cTimeGauge(void);

	void Init();

	void Draw(cData *Data);

private:
	time_t StartTime;
	time_t CurrentTime;

	string FormatTime(double Difference);
};

