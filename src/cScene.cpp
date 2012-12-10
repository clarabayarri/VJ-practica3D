#include "cScene.h"
#include "Globals.h"
#include "customshadermanager.h"

cScene::cScene(void):x(0),z(0) {}
cScene::~cScene(void){}

void cScene::Init() {
	forest.Init();
}

vector<vector<float> > cScene::GetForest() {
	return forest.GetTrees();
}

bool cScene::LoadLevel(int level)
{
	FILE *fd;
	char file[16],tile;
	int i,j;

	if(level<10) sprintf(file,"%s0%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);
	else		 sprintf(file,"%s%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	for(i=SCENE_DEPTH-1;i>=0;i--)
	{
		for(j=0;j<SCENE_WIDTH;j++)
		{
			fscanf(fd,"%c",&tile);
			if(tile==' ')
			{
				//GRASS_PLANES must be != 0 !!!
				map[(i*SCENE_WIDTH)+j]=0;
			}
			else
			{
				//GRASS_PLANES = 1,2,3,...
				map[(i*SCENE_WIDTH)+j] = tile-48;
			}
		}
		fscanf(fd,"%c",&tile); //pass enter
	}

	fclose(fd);

	return true;
}

void cScene::Draw(cData *Data, CustomShaderManager *shaderManager) {
	shaderManager->selectShader(-1);
	forest.Render(Data,shaderManager);
	glDisable(GL_TEXTURE_2D);
}

float cScene::GetHeight(float x, float z) {
	return forest.GetHeight(x,z);
}

float cScene::GetMinY() {
	return forest.GetMinY();
}