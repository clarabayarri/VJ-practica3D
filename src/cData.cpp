#include "cData.h"

cData::cData(void) {}
cData::~cData(void){}

int cData::GetID(int img)
{
	return texture[img].GetID();
}

void cData::GetSize(int img, int *w, int *h)
{
	texture[img].GetSize(w,h);
}

bool cData::LoadImage(int img, char *filename, int type)
{
	int res;

	res = texture[img].Load(filename,type);
	if(!res) return false;

	return true;
}

bool cData::Init() {
	if(LoadImage(IMG_WALL1,	"textures/wall1.png",GL_RGBA))
	if(LoadImage(IMG_WALL2,	"textures/wall2.png",GL_RGBA))
	if(LoadImage(IMG_WALL3,	"textures/wall3.png",GL_RGBA))
	if(LoadImage(IMG_FLOOR,	"textures/floor.png",GL_RGBA))
	if(LoadImage(IMG_ROOF,	"textures/roof.png",GL_RGBA))
	if(LoadImage(IMG_GRASS,	"textures/grass.png",GL_RGBA))
		return true;

	return false;
}