#include "cTreeForest.h"
#include "cFloor.h"

cTreeForest::cTreeForest() {}

cTreeForest::~cTreeForest() {}

vector<vector<float> > cTreeForest::GetTrees() {
	return trees;
}

void cTreeForest::Init(const vector<vector<float> >& t, int tex) {
	trees = vector<vector<float> >(t); 
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