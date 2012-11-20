#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		6

//Image identifiers
#define IMG_WALL1	0
#define IMG_WALL2	1
#define IMG_WALL3	2
#define IMG_FLOOR	3
#define IMG_ROOF	4
#define IMG_GRASS	5

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);
	bool Init();

private:
	cTexture texture[NUM_IMG];
};
