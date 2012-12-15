#include "cAnimatedCharacter.h"

#define STEP_SIZE 0.1f
#define ANGLE_STEP_SIZE 5.0f

cAnimatedCharacter::cAnimatedCharacter(void):x(1.0f),z(1.0f),radius(0.1f){}

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

void cAnimatedCharacter::SetModel(char * m) {
	model.Load(m);
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

void cAnimatedCharacter::Draw() {
	glTranslatef(0.0f,-model.GetMinY()/4,0.0f);
	glScalef(0.25f,0.25f,0.25f);
	model.Render(0,0,0,90,0);
}

void cAnimatedCharacter::DrawPhysical() {

}

std::vector<float> cAnimatedCharacter::GetPosition() {
	std::vector<float> position(4);
	position[0] = x;
	position[1] = 0;
	position[2] = z;
	position[3] = orientationAngle;
	return position;
}
