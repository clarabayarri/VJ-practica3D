#include "cTreeForest.h"
#include "cFloor.h"

cTreeForest::cTreeForest() {}

cTreeForest::~cTreeForest() {}

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
				glTexCoord2f(0.000f, 1.000f); glVertex3f(-cos((180.0/TREE_PLANES*i)*PI/180.0)+x*DILATATION	, y,	sin((180.0/TREE_PLANES*i)*PI/180.0)+z*DILATATION	);
				glTexCoord2f(1.000f, 1.000f); glVertex3f(cos((180.0/TREE_PLANES*i)*PI/180.0)+x*DILATATION	, y,	-sin((180.0/TREE_PLANES*i)*PI/180.0)+z*DILATATION	);
				glTexCoord2f(1.000f, 0.000f); glVertex3f(cos((180.0/TREE_PLANES*i)*PI/180.0)+x*DILATATION	, y+2,	-sin((180.0/TREE_PLANES*i)*PI/180.0)+z*DILATATION	);
				glTexCoord2f(0.000f, 0.000f); glVertex3f(-cos((180.0/TREE_PLANES*i)*PI/180.0)+x*DILATATION	, y+2,  sin((180.0/TREE_PLANES*i)*PI/180.0)+z*DILATATION	);
			}
		}
		glEnd();
	glEndList();
}

void cTreeForest::Render(cData * data) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,data->GetID(texId));
	glCallList(dlId);
	glDisable(GL_TEXTURE_2D);
}