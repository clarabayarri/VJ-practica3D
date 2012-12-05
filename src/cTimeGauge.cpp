#include "cTimeGauge.h"


cTimeGauge::cTimeGauge(void)
{
}


cTimeGauge::~cTimeGauge(void)
{
}

void cTimeGauge::Draw(cData *Data)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-0.1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_FENCE));
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);	glVertex2i(1,	0);
		glTexCoord2f(0.0f, 0.0f);	glVertex2i(0,	0);
		glTexCoord2f(0.0f, 1.0f);	glVertex2i(0,	1);
		glTexCoord2f(1.0f, 1.0f);	glVertex2i(1,	1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}