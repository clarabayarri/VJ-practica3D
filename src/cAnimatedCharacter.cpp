#include "cAnimatedCharacter.h"

#define STEP_SIZE 0.1
#define ANGLE_STEP_SIZE 5

cAnimatedCharacter::cAnimatedCharacter(void):x(5),z(5){}

cAnimatedCharacter::~cAnimatedCharacter(void){}

void cAnimatedCharacter::MoveForward()
{
	x += STEP_SIZE * cos((90-orientationAngle)*0.0174532925);
	z -= STEP_SIZE * cos(orientationAngle*0.0174532925);
}

void cAnimatedCharacter::MoveBackward()
{
	x -= STEP_SIZE * cos((90-orientationAngle)*0.0174532925);
	z += STEP_SIZE * cos(orientationAngle*0.0174532925);
}

void cAnimatedCharacter::MoveLeft()
{
	x -= STEP_SIZE * sin((90-orientationAngle)*0.0174532925);
	z -= STEP_SIZE * sin(orientationAngle*0.0174532925);
}

void cAnimatedCharacter::MoveRight()
{
	x += STEP_SIZE * sin((90-orientationAngle)*0.0174532925);
	z += STEP_SIZE * sin(orientationAngle*0.0174532925);
}

void cAnimatedCharacter::RotateLeft()
{
	orientationAngle -= ANGLE_STEP_SIZE;
}

void cAnimatedCharacter::RotateRight()
{
	orientationAngle += ANGLE_STEP_SIZE;
}

void cAnimatedCharacter::Draw()
{
	GLUquadricObj *q = gluNewQuadric();
	gluSphere(q, 0.1,16,16);
	gluDeleteQuadric(q);
}
