#include "cSceneMap.h"

#define MAP_MARGIN 3

cSceneMap::cSceneMap(void)
{
}


cSceneMap::~cSceneMap(void)
{
}

void cSceneMap::Init(cForest *forest)
{
	dlId = glGenLists(1);
	glNewList(dlId,GL_COMPILE);
		// Draw background
		glColor3f(0.969,0.839,0.612);
		glBegin(GL_QUADS);
			glVertex3f(1.0,1.0,-0.1);
			glVertex3f(99.0,1.0,-0.1);
			glVertex3f(99.0,99.0,-0.1);
			glVertex3f(1.0,99.0,-0.1);
		glEnd();
	
		// Draw border
		glColor3f(0.275,0.212,0.086);
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
			glVertex2i(1,1);
			glVertex2i(99,1);
			glVertex2i(99,99);
			glVertex2i(1,99);
		glEnd();

		//Draw trees
		vector<cTreeForest> treeForests = forest->GetTrees();
		glEnable(GL_POINT_SMOOTH);
		glPointSize(2.0f);
		glColor3f(0.106,0.369,0.125);
		glBegin(GL_POINTS);
			for (int k = 0; k < NUM_TREE_TYPES; ++k) {
				cTreeForest treeForest = treeForests[k];
				vector<vector<float> > trees = treeForest.GetTrees();
				for (unsigned int j = 0; j < trees.size(); ++j) {
					for (int i = 0; i < TREE_PLANES; ++i) {
						float x = trees[j][0];
						float z = trees[j][2];
						glVertex2f(3*x + MAP_MARGIN,3*z + MAP_MARGIN);
					}
				}
			}
		glEnd();
	glEndList();
}

void cSceneMap::Draw(cData *Data, cAnimatedCharacter *player)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 101, 101, -1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-0.2);

	// Draw border and trees
	glCallList(dlId);

	// Draw player
	glEnable(GL_POINT_SMOOTH);
	glPointSize(3.0f);
	glColor3f(0.874,0.106,0.416);
	glBegin(GL_POINTS);
		glVertex3f(3*player->x + MAP_MARGIN,3*player->z + MAP_MARGIN, 0.1);
	glEnd();

	// Clear colors
	glColor3f(1.0f,1.0f,1.0f);
	

}