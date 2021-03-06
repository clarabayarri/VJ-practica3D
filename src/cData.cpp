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

bool cData::LoadImage(int img, char *filename, int type, bool minf) {
	int res;
	
	if (minf) res = texture[img].Load(filename,type,GL_REPEAT,GL_REPEAT,GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR); 
	else res = texture[img].Load(filename,type);
	if(!res) return false;

	return true;
}

bool cData::Init() {
	if(LoadImage(IMG_GRASS,	"textures/grass.png",GL_RGBA))
	if(LoadImage(IMG_FENCE,	"textures/fencefeather.png",GL_RGBA,true))
	if(LoadImage(IMG_TREE1,	"textures/tree1.png",GL_RGBA))
	if(LoadImage(IMG_TREE2,	"textures/tree2.png",GL_RGBA))
	if(LoadImage(IMG_TREE3,	"textures/tree3.png",GL_RGBA))
	if(LoadImage(IMG_TREE4,	"textures/tree4.png",GL_RGBA))
	if(LoadImage(IMG_TREE5,	"textures/tree5.png",GL_RGBA))
	if(LoadImage(IMG_FLOOR1,"textures/grass-brown.png",GL_RGBA,true))
	if(LoadImage(IMG_FLOOR2,"textures/grass-green.png",GL_RGBA,true))
	if(LoadImage(IMG_SKY1,"textures/skydome6.png",GL_RGBA,true))
	if(LoadImage(IMG_SKY2,"textures/skydome2clouds.png",GL_RGBA,true))
	if(LoadImage(IMG_SENGLAR,"textures/senglar.png",GL_RGBA,true))
	if(LoadImage(IMG_GAMEOVER,"textures/gameover.png",GL_RGBA,true))
	if(LoadImage(IMG_BOAR1,"textures/boar1.png",GL_RGBA,true))
	if(LoadImage(IMG_BOAR2,"textures/boar2.png",GL_RGBA,true))
	if(LoadImage(IMG_BOAR3,"textures/boar3.png",GL_RGBA,true))
	if(LoadImage(IMG_BOAR4,"textures/boar4.png",GL_RGBA,true))
	if(LoadImage(IMG_START_SCREEN,"textures/boarquest.png",GL_RGBA,true))
	if(LoadImage(IMG_LEVEL_UP,"textures/levelup.png",GL_RGBA,true))
		return true;

	return false;
}