#include "cSceneMap.h"

#define MAP_MARGIN 1.0f

cSceneMap::cSceneMap(void) {}

cSceneMap::~cSceneMap(void) {}

void cSceneMap::Init(const vector<vector<float> >& trees) {
	dlId = glGenLists(1);
	glNewList(dlId,GL_COMPILE);
		// Draw background
		glColor3f(0.969f,0.839f,0.612f);
		glBegin(GL_QUADS);
			glVertex3f(0.0f,								0.0f,								-0.1f);
			glVertex3f(((float) TERRAIN_SIZE*DILATATION),	0.0f,								-0.1f);
			glVertex3f(((float) TERRAIN_SIZE*DILATATION),	((float) TERRAIN_SIZE*DILATATION),	-0.1f);
			glVertex3f(0.0f,								((float) TERRAIN_SIZE*DILATATION),	-0.1f);
		glEnd();
	
		// Draw border
		glColor3f(0.275f,0.212f,0.086f);
		glLineWidth(2.0f);
		glBegin(GL_LINE_LOOP);
			glVertex2i(0,								0);
			glVertex2i(((int) TERRAIN_SIZE*DILATATION),	0);
			glVertex2i(((int) TERRAIN_SIZE*DILATATION),	((int) TERRAIN_SIZE*DILATATION));
			glVertex2i(0,								((int) TERRAIN_SIZE*DILATATION));
		glEnd();

		//Draw trees
		glEnable(GL_POINT_SMOOTH);
		glPointSize(2.0f);
		glColor3f(0.106f,0.369f,0.125f);
		glBegin(GL_POINTS);
		for (unsigned int j = 0; j < trees.size(); ++j) {
			float x = trees[j][0];
			float z = trees[j][2];
			glVertex2f(DILATATION*x+MAP_MARGIN, DILATATION*z+MAP_MARGIN);
		}
		glEnd();
	glEndList();
}

void cSceneMap::Draw(cData *Data, const vector<float>& player)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-MAP_MARGIN, MAP_MARGIN + TERRAIN_SIZE*DILATATION, MAP_MARGIN + TERRAIN_SIZE*DILATATION, -MAP_MARGIN);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -0.2f);

	// Draw border and trees
	glCallList(dlId);

	// Draw player
	glEnable(GL_POINT_SMOOTH);
	glPointSize(3.0f);
	glColor3f(0.874f, 0.106f, 0.416f);
	glBegin(GL_POINTS);
		glVertex3f(player[0]+MAP_MARGIN, player[2]+MAP_MARGIN, 0.1f);
	glEnd();

	// Clear colors
	glColor3f(1.0f,1.0f,1.0f);
	

}