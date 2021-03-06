#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "Constants.h"

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA, bool minf = false);
	bool Init();

private:
	cTexture texture[NUM_IMG];
};
