#include "cWall.h"

cWall::cWall(void) {}

cWall::~cWall(void) {}

void cWall::Init(cFloor * floor) {
	unsigned int f = 0;
	unsigned int tSize = (unsigned int) floor->GetSize();
	float tDilatation = floor->GetDilatation();

	vertices = vector<vertex>((tSize)*8);
	faces = vector<face>((tSize-1)*8);
	textures = vector<pair<float,float> >((tSize)*8);	

	for (unsigned int i = 0; i < tSize; ++i) {
		//Front
		vertices[2*i]			= vertex(i*tDilatation,floor->GetY(i,0),0,0,0,1);
		vertices[2*i+1]			= vertex(i*tDilatation,floor->GetY(i,0)+WALL_HEIGHT,0,0,0,1);
		//Back
		vertices[tSize*2+2*i]	= vertex(i*tDilatation,floor->GetY(i,tSize-1),(tSize-1)*tDilatation,0,0,-1);
		vertices[tSize*2+2*i+1]	= vertex(i*tDilatation,floor->GetY(i,tSize-1)+WALL_HEIGHT,(tSize-1)*tDilatation,0,0,-1);
		//Left
		vertices[tSize*4+2*i]	= vertex(0,floor->GetY(0,i),i*tDilatation,1,0,0);
		vertices[tSize*4+2*i+1]	= vertex(0,floor->GetY(0,i)+WALL_HEIGHT,i*tDilatation,1,0,0);
		//Right  
		vertices[tSize*6+2*i]	= vertex((tSize-1)*tDilatation,floor->GetY(tSize-1,i),i*tDilatation,-1,0,0);
		vertices[tSize*6+2*i+1]	= vertex((tSize-1)*tDilatation,floor->GetY(tSize-1,i)+WALL_HEIGHT,i*tDilatation,-1,0,0);
	}

	for (unsigned int i = 0; i < (tSize-1); ++i) {
		int index = 2*i;
		for (unsigned int j = 0; j < 4; ++j) {
			faces[f++] = face(index,index+3,index+1,0,0,1);
			faces[f++] = face(index,index+2,index+3,0,0,1);
			index += tSize*2;
		}
    }

	GenerateArrays();
	
	for (unsigned int i = 0; i < (tSize)*2; ++i) {
		textures[i*4]	= pair<float,float>(0.000f,1.000f);
		textures[i*4+1] = pair<float,float>(0.000f,0.250f);
		textures[i*4+2] = pair<float,float>(1.000f,1.000f);
		textures[i*4+3] = pair<float,float>(1.000f,0.250f);
    }

	GenerateTextureArray();
}

void cWall::Render(cData * data) {
	glEnable(GL_TEXTURE_2D);
	glAlphaFunc(GL_GREATER, 0.2f);
	glEnable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D,data->GetID(IMG_FENCE));
	cVBO::Render();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}

void cWall::RenderPhysical()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	cVBO::Render();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}