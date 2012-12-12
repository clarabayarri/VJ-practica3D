#include "cMunitionCounter.h"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

cMunitionCounter::cMunitionCounter(void)
{
}


cMunitionCounter::~cMunitionCounter(void)
{
}

void cMunitionCounter::Draw(cData *Data, int count)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 2.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-0.1f);
	
	glColor3f(0.2f,0.2f,0.2f);
	glRasterPos2f(1.3f, 0.6f);
	string countText = FormatCount(count);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *) countText.c_str());
	
	glColor3f(1.0f,1.0f,1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_SENGLAR));
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);	glVertex2i(1,	0);
		glTexCoord2f(0.0f, 0.0f);	glVertex2i(0,	0);
		glTexCoord2f(0.0f, 1.0f);	glVertex2i(0,	1);
		glTexCoord2f(1.0f, 1.0f);	glVertex2i(1,	1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

string cMunitionCounter::FormatCount(int count)
{
	std::stringstream ss;
    ss << count;
    std::string s(ss.str());
	return s;
}
