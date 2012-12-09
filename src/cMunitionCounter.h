#pragma once

#include "cData.h"
#include "Globals.h"
using namespace std;

class cMunitionCounter
{
public:
	cMunitionCounter(void);
	~cMunitionCounter(void);

	void Draw(cData *Data, int count);

private:
	string FormatCount(int count);
};

