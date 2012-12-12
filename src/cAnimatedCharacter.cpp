#include "cAnimatedCharacter.h"

#define STEP_SIZE 0.1f
#define ANGLE_STEP_SIZE 5.0f

cAnimatedCharacter::cAnimatedCharacter(void):x(TERRAIN_SIZE),z(TERRAIN_SIZE){}

cAnimatedCharacter::~cAnimatedCharacter(void){}

void cAnimatedCharacter::SetXZ(float setx, float setz) {
	SetX(setx);
	SetZ(setz);
}

void cAnimatedCharacter::SetX(float setx) {
	x = setx;
}

void cAnimatedCharacter::SetZ(float setz) {
	z = setz;
}

void cAnimatedCharacter::MoveForward()
{
	x += STEP_SIZE * (float) cos((90-orientationAngle)*0.0174532925);
	z -= STEP_SIZE * (float) cos(orientationAngle*0.0174532925);
}

void cAnimatedCharacter::MoveBackward()
{
	x -= STEP_SIZE * (float) cos((90-orientationAngle)*0.0174532925);
	z += STEP_SIZE * (float) cos(orientationAngle*0.0174532925);
}

void cAnimatedCharacter::MoveLeft()
{
	x -= STEP_SIZE * (float) sin((90-orientationAngle)*0.0174532925);
	z -= STEP_SIZE * (float) sin(orientationAngle*0.0174532925);
}

void cAnimatedCharacter::MoveRight()
{
	x += STEP_SIZE * (float) sin((90-orientationAngle)*0.0174532925);
	z += STEP_SIZE * (float) sin(orientationAngle*0.0174532925);
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

void cAnimatedCharacter::DrawPhysical()
{

}

vector<float> cAnimatedCharacter::GetPosition()
{
	vector<float> position(3);
	position[0] = x;
	position[1] = 0;
	position[2] = z;
	return position;
}
