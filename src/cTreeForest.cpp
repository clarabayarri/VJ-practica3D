#include "cTreeForest.h"
#include "cFloor.h"
#include "Globals.h"

#define TREE_PHYSICAL_WIDTH 0.5f

cTreeForest::cTreeForest() {}

cTreeForest::~cTreeForest() {}

std::vector<std::vector<float> > cTreeForest::GetTrees() {
	return trees;
}

void cTreeForest::Init(const std::vector<std::vector<float> >& t, int tex) {
	trees = std::vector<std::vector<float> >(t); 
	texId = tex;

	dlId = glGenLists(1);
	glNewList(dlId,GL_COMPILE);
		glBegin(GL_QUADS);
		for (unsigned int j = 0; j < trees.size(); ++j) {
			for (int i = 0; i < TREE_PLANES; ++i) {
				float x = trees[j][0];
				float y = trees[j][1];
				float z = trees[j][2];
				glTexCoord2f(0.000f, 1.000f); glVertex3f((float) -cos((180.0/TREE_PLANES*i)*PI/180.0)+x*DILATATION	, y,	(float) sin((180.0/TREE_PLANES*i)*PI/180.0)+z*DILATATION	);
				glTexCoord2f(1.000f, 1.000f); glVertex3f((float) cos((180.0/TREE_PLANES*i)*PI/180.0)+x*DILATATION	, y,	(float) -sin((180.0/TREE_PLANES*i)*PI/180.0)+z*DILATATION	);
				glTexCoord2f(1.000f, 0.000f); glVertex3f((float) cos((180.0/TREE_PLANES*i)*PI/180.0)+x*DILATATION	, y+2,	(float) -sin((180.0/TREE_PLANES*i)*PI/180.0)+z*DILATATION	);
				glTexCoord2f(0.000f, 0.000f); glVertex3f((float) -cos((180.0/TREE_PLANES*i)*PI/180.0)+x*DILATATION	, y+2,  (float)sin((180.0/TREE_PLANES*i)*PI/180.0)+z*DILATATION	);
			}
		}
		glEnd();
	glEndList();

	dlIdPhysical = glGenLists(1);
	glNewList(dlIdPhysical,GL_COMPILE);
	for (unsigned int j = 0; j < trees.size(); ++j) {
		float x = trees[j][0] * DILATATION;
		float y = trees[j][1];
		float z = trees[j][2] * DILATATION;

		float radius = TREE_PHYSICAL_WIDTH / 2.0f;
		float height = 2.0f;

		// Bottom face
		glBegin(GL_LINE_LOOP);
			for (int i=0; i < 360; i++)
			{
				float degInRad = i*DEG2RAD;
				glVertex3f(x + cos(degInRad)*radius, y, z + sin(degInRad)*radius);
			}
		glEnd();

		// Top face
		glBegin(GL_LINE_LOOP);
			for (int i=0; i < 360; i++)
			{
				float degInRad = i*DEG2RAD;
				glVertex3f(x + cos(degInRad)*radius, y + height, z + sin(degInRad)*radius);
			}
		glEnd();

		// Middle
		glBegin(GL_TRIANGLE_STRIP);
			for (int i=0; i < 360; i+=10)
			{
				float degInRad = i*DEG2RAD;
				glVertex3f(x + cos(degInRad)*radius, y, z + sin(degInRad)*radius);
				glVertex3f(x + cos(degInRad)*radius, y + height, z + sin(degInRad)*radius);
			}
		glEnd();

	}
	glEndList();
}

void cTreeForest::Render(cData * data) {
	glEnable(GL_TEXTURE_2D);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D,data->GetID(texId));
	glCallList(dlId);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}

void cTreeForest::RenderPhysical()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCallList(dlIdPhysical);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool cTreeForest::Collides(std::vector<float> PlayerPosition)
{
	for (unsigned int j = 0; j < trees.size(); ++j) {
		float diffx = PlayerPosition[0] - trees[j][0]*DILATATION;
		float diffz = PlayerPosition[2] - trees[j][2]*DILATATION;
		float distance = sqrt(diffx*diffx + diffz*diffz);
		if (distance < PlayerPosition[PLAYER_RADIUS] + TREE_PHYSICAL_WIDTH/2) {
			return true;
		}
	}
	return false;
}