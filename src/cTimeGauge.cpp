#include "cTimeGauge.h"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

#define DANGER_TIME 30.0
#define COLOR_FRAMES 5

cTimeGauge::cTimeGauge(void)
{
}


cTimeGauge::~cTimeGauge(void)
{
}

void cTimeGauge::Draw(double RemainingTime)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 1.0, 0.0);

	string text = FormatTime(RemainingTime);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (RemainingTime > DANGER_TIME) {
		glColor3f(0.2f, 0.2f, 0.2f);
	} else {
		if (ChangingColor) {
			glColor3f(0.9f, 0.1f, 0.1f);
		} else {
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		
		ColorCount++;
		if (ColorCount > COLOR_FRAMES) {
			ColorCount = 0;
			ChangingColor = !ChangingColor;
		}
	}

	glTranslatef(0.0f, 0.0f, -0.1f);
	glRasterPos2f(0.0f, 0.6f);
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