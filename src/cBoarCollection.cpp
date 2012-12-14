#include "cBoarCollection.h"
#include "Constants.h"

#define BOAR_WIDTH 0.5f
#define BOAR_HEIGHT 0.5f
#define BLINK_TOTAL 20

cBoarCollection::cBoarCollection(void)
{
}


cBoarCollection::~cBoarCollection(void)
{
}

vector<vector<float> > cBoarCollection::GetBoars() {
	return boars;
}

void cBoarCollection::Init(const vector<vector<float> >& t, int tex) {
	boars = vector<vector<float> >(t); 
	disappearing = vector<int> (t.size(),BLINK_TOTAL);
	texId = tex;
}

void cBoarCollection::Render(cData * data, float OrientationAngle) {
	glEnable(GL_TEXTURE_2D);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D,data->GetID(texId));
	glBegin(GL_QUADS);
	for (unsigned int j = 0; j < boars.size(); ++j) {
		if (disappearing[j] % 4 == 0) {
			float x = boars[j][0];
			float y = boars[j][1];
			float z = boars[j][2];

			float displacement = BOAR_WIDTH/2.0f;
			float ax = displacement * (float) sin((90-OrientationAngle)*0.0174532925);
			float az = displacement * (float) sin(OrientationAngle*0.0174532925);

			glTexCoord2f(0.000f, 1.000f); glVertex3f((x-ax)*DILATATION, y,				(float) (z-az)*DILATATION	);
			glTexCoord2f(1.000f, 1.000f); glVertex3f((x+ax)*DILATATION, y,				(float) (z+az)*DILATATION	);
			glTexCoord2f(1.000f, 0.000f); glVertex3f((x+ax)*DILATATION, y+BOAR_HEIGHT,	(float) (z+az)*DILATATION	);
			glTexCoord2f(0.000f, 0.000f); glVertex3f((x-ax)*DILATATION, y+BOAR_HEIGHT,	(float) (z-az)*DILATATION	);
		}
		if (disappearing[j] < BLINK_TOTAL) {
			disappearing[j]--;
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);

	for (unsigned int j = 0; j < boars.size(); ++j) {
		if (disappearing[j] == 0) {
			boars.erase(boars.begin()+j);
			disappearing.erase(disappearing.begin()+j);
			break;
		}
	}
}

void cBoarCollection::RenderPhysical(float OrientationAngle)
{
	// Billboard
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	for (unsigned int j = 0; j < boars.size(); ++j) {
		float x = boars[j][0];
		float y = boars[j][1];
		float z = boars[j][2];
		
		float displacement = BOAR_WIDTH/2.0f;
		float ax = displacement * (float) sin((90-OrientationAngle)*0.0174532925);
		float az = displacement * (float) sin(OrientationAngle*0.0174532925);

		glVertex3f((x-ax)*DILATATION, y,				(float) (z-az)*DILATATION	);
		glVertex3f((x+ax)*DILATATION, y,				(float) (z+az)*DILATATION	);
		glVertex3f((x+ax)*DILATATION, y+BOAR_HEIGHT,	(float) (z+az)*DILATATION	);
		glVertex3f((x-ax)*DILATATION, y+BOAR_HEIGHT,	(float) (z-az)*DILATATION	);
	}
	glEnd();

	// Cylindre
	for (unsigned int j = 0; j < boars.size(); ++j) {
		float x = boars[j][0] * DILATATION;
		float y = boars[j][1];
		float z = boars[j][2] * DILATATION;

		float radius = BOAR_WIDTH/2.0f;
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
				glVertex3f(x + cos(degInRad)*radius, y + BOAR_HEIGHT, z + sin(degInRad)*radius);
			}
		glEnd();

		// Middle
		glBegin(GL_TRIANGLE_STRIP);
			for (int i=0; i < 360; i+=20)
			{
				float degInRad = i*DEG2RAD;
				glVertex3f(x + cos(degInRad)*radius, y, z + sin(degInRad)*radius);
				glVertex3f(x + cos(degInRad)*radius, y + BOAR_HEIGHT, z + sin(degInRad)*radius);
			}
		glEnd();
		}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool cBoarCollection::Collides(vector<float> PlayerPosition, float PlayerRadius)
{
	for (unsigned int j = 0; j < boars.size(); ++j) {
		float diffx = PlayerPosition[0] - boars[j][0]*DILATATION;
		float diffz = PlayerPosition[2] - boars[j][2]*DILATATION;
		float distance = sqrt(diffx*diffx + diffz*diffz);
		if (distance < PlayerRadius+BOAR_WIDTH/2 && disappearing[j] == BLINK_TOTAL) {
			disappearing[j]--;
			return true;
		}
	}
	return false;
}
