#include "cScene.h"
#include "Globals.h"
#include "customshadermanager.h"

cScene::cScene(void):x(0),z(0) {}
cScene::~cScene(void){}

void cScene::Init() {
	forest.Init();
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
/**
void cScene::DrawGrass(cData *Data) {
	srand(time(NULL));
	if (!wind) {
		wind = (rand()%5 == 0);
		windangle = 180.0;
		amplitude = 1.0;
	} else {
		windangle+=1.5;
		if (windangle > 360 && (int)windangle%180) amplitude *= 0.95;
		if (windangle > 1080) wind = false;
	}
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_GRASS));
	for (int i = 0; i < GRASS_NUMBER; ++i) {
		glPushMatrix();
		glTranslatef(grassPosition[i].first,0,grassPosition[i].second);
		glRotatef(grassRotation[i],0.0f,1.0f,0.0f);
		if(grassRotation[i] > 90) glRotatef(-amplitude*45*sin(windangle*PI/180.0),1.0f,0.0f,0.0f);
		else glRotatef(amplitude*45*sin(windangle*PI/180.0),1.0f,0.0f,0.0f);

		glCallList(dl_grass);
		glPopMatrix();
	}

}**/

/**
void cScene::MakeCubeDL(float w,float h,float d,float tw,float th,float td) {
	dl_cube = glGenLists(1);
	glNewList(dl_cube,GL_COMPILE);
		glBegin(GL_QUADS);
			// Front Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0,  0);
			glTexCoord2f(  tw, 0.0f); glVertex3f(w, 0,  0);
			glTexCoord2f(  tw,   th); glVertex3f(w, h,  0);
			glTexCoord2f(0.0f,   th); glVertex3f(0, h,  0);
			// Back Face
			glTexCoord2f(  tw, 0.0f); glVertex3f(0, 0, -d);
			glTexCoord2f(  tw,   th); glVertex3f(0, h, -d);
			glTexCoord2f(0.0f,   th); glVertex3f(w, h, -d);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(w, 0, -d);
			// Right face
			glTexCoord2f(  td, 0.0f); glVertex3f(w, 0, -d);
			glTexCoord2f(  td,   th); glVertex3f(w, h, -d);
			glTexCoord2f(0.0f,   th); glVertex3f(w, h,  0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(w, 0,  0);
			// Left Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -d);
			glTexCoord2f(  td, 0.0f); glVertex3f(0, 0,  0);
			glTexCoord2f(  td,   th); glVertex3f(0, h,  0);
			glTexCoord2f(0.0f,   th); glVertex3f(0, h, -d);
			// Bottom Face
			/*glTexCoord2f(  tw,   td); glVertex3f(0, 0, -d);
			glTexCoord2f(0.0f,   td); glVertex3f(w, 0, -d);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(w, 0,  0);
			glTexCoord2f(  tw, 0.0f); glVertex3f(0, 0,  0);
			// Top Face
			glTexCoord2f(0.0f,   td); glVertex3f(0, h, -d);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, h,  0);
			glTexCoord2f(  tw, 0.0f); glVertex3f(w, h,  0);
			glTexCoord2f(  tw,   td); glVertex3f(w, h, -d);
		glEnd();
	glEndList();
}**/