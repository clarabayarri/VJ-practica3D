#include "cTimeGauge.h"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

cTimeGauge::cTimeGauge(void)
{
}


cTimeGauge::~cTimeGauge(void)
{
}

void cTimeGauge::Init()
{
	StartTime = time(&StartTime);
}

void cTimeGauge::Draw(cData *Data)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 2.0, 1.0, 0.0);

	CurrentTime = time(&CurrentTime);
	double Difference = difftime(CurrentTime, StartTime);
	string text = FormatTime(Difference);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0.2f,0.2f,0.2f);
	glTranslatef(0.0f,0.0f,-0.1f);
	glRasterPos2i(0, 0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *) text.c_str());
}

string cTimeGauge::FormatTime(double Difference)
{
	int TimeSeconds = ((int) Difference) % 60;
	int TimeMinutes = ((int) Difference) / 60;

	std::stringstream ss;
    if (TimeMinutes < 10) {
		ss << "0";
	}
    ss << TimeMinutes << ":";
	if (TimeSeconds < 10) {
		ss << "0";
	}
	ss << TimeSeconds;
    std::string s(ss.str());
	return s;
}