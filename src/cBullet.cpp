#include "cBullet.h"
#include "Globals.h"
#include "Constants.h"

#define BULLET_WIDTH 0.3f
#define BULLET_STEP_SIZE 0.3f
#define FLIGHT_TIME 30

cBullet::cBullet(void):IsFinished(false),FrameCount(0)
{
}


cBullet::~cBullet(void)
{
}

void cBullet::SetPosition(std::vector<float> Position)
{
	x = Position[0];
	y = Position[1]+0.5;
	z = Position[2];
	orientationAngle = Position[3];
}

std::vector<float> cBullet::GetPosition()
{
	std::vector<float> position(3);
	position[0] = x;
	position[1] = 0;
	position[2] = z;
	return position;
}

void cBullet::Move()
{
	x += BULLET_STEP_SIZE * (float) cos((90-orientationAngle)*0.0174532925);
	z -= BULLET_STEP_SIZE * (float) cos(orientationAngle*0.0174532925);
	if (FrameCount < FLIGHT_TIME/2) y += 0.1f;
	else y -= 0.1f;
	if (y < 0 || x < 0 || z < 0 ||
		x > (TERRAIN_SIZE-1)*DILATATION ||
		z > (TERRAIN_SIZE-1)*DILATATION) IsFinished = true;
}

void cBullet::Draw(cData *Data) 
{
	++FrameCount;
	
	float displacement = BULLET_WIDTH / 2.0f;
	float ax = displacement * (float) sin((90-orientationAngle)*0.0174532925);
	float az = displacement * (float) sin(orientationAngle*0.0174532925);

	glEnable(GL_TEXTURE_2D);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_BOAR1));
	glBegin(GL_QUADS);
		glTexCoord2f(0.000f, 1.000f); glVertex3f((x-ax), y,					(float) (z-az)	);
		glTexCoord2f(1.000f, 1.000f); glVertex3f((x+ax), y,					(float) (z+az)	);
		glTexCoord2f(1.000f, 0.000f); glVertex3f((x+ax), y+BULLET_WIDTH,	(float) (z+az)	);
		glTexCoord2f(0.000f, 0.000f); glVertex3f((x-ax), y+BULLET_WIDTH,	(float) (z-az)	);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}

void cBullet::DrawPhysical() 
{
	++FrameCount;
	
	float displacement = 0.5f;
	float ax = displacement * (float) sin((90-orientationAngle)*0.0174532925);
	float az = displacement * (float) sin(orientationAngle*0.0174532925);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
		glVertex3f((x-ax), y,				(float) (z-az)	);
		glVertex3f((x+ax), y,				(float) (z+az)	);
		glVertex3f((x+ax), y+BULLET_WIDTH,	(float) (z+az)	);
		glVertex3f((x-ax), y+BULLET_WIDTH,	(float) (z-az)	);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}