#include "cSkydome.h"
using namespace std;

cSkydome::cSkydome(void):texId(0) {}

cSkydome::~cSkydome(void) {}

void cSkydome::Init() {
	unsigned int f = 0;

	vertices = vector<vertex>(370);
	faces = vector<face>(648);
	textures = vector<pair<float,float> >(370);	

	for (unsigned int theta = 0; theta <= 9; ++theta)
		for (unsigned int phi = 0; phi <= 36; ++phi) {
			float t = ((float) theta*10)*PI/180;
			float p = ((float) phi*10)*PI/180;
			vertices[theta*37+phi] = vertex(cos(t)*cos(p)*SKY_SIZE,sin(t)*SKY_SIZE,cos(t)*sin(p)*SKY_SIZE,
											-cos(t)*cos(p),-sin(t),-cos(t)*sin(p));
			textures[theta*37+phi] = pair<float,float>((float) phi/36.0f,0.5f-(float) theta/18.0f);
		}

	for (unsigned int theta = 0; theta < 9; ++theta) {
		for (unsigned int phi = 0; phi < 36; ++phi) {
			int i1 = theta*37+phi; int i2 = i1+1;
			int i3 = (theta+1)*37+phi; int i4 = i3+1;
			faces[f++] = face(i1,i2,i3,0,0,1);
			faces[f++] = face(i2,i4,i3,0,0,1);
		}
	}
	GenerateArrays();
	GenerateTextureArray();
}

void cSkydome::Render(cData * data) {
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,data->GetID(texId));
	cVBO::Render();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

void cSkydome::SetTexId(int id) {
	texId = id;
}