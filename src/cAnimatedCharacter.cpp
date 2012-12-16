#include "cAnimatedCharacter.h"
#include "Constants.h"

#define STEP_SIZE 0.1f
#define ANGLE_STEP_SIZE 5.0f

cAnimatedCharacter::cAnimatedCharacter(void):x(1.0f),z(1.0f),radius(0.1f),animation_frame(0.0f),life(100){
	state = -1;
	SetState(ANIM_STAND);
}

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
	SetState(ANIM_RUN);
}

void cAnimatedCharacter::MoveBackward()
{
	x -= STEP_SIZE * (float) cos((90-orientationAngle)*0.0174532925);
	z += STEP_SIZE * (float) cos(orientationAngle*0.0174532925);
	SetState(ANIM_RUN);
}

void cAnimatedCharacter::MoveLeft()
{
	x -= STEP_SIZE * (float) sin((90-orientationAngle)*0.0174532925);
	z -= STEP_SIZE * (float) sin(orientationAngle*0.0174532925);
	SetState(ANIM_RUN);
}

void cAnimatedCharacter::MoveRight() {
	x += STEP_SIZE * (float) sin((90-orientationAngle)*0.0174532925);
	z += STEP_SIZE * (float) sin(orientationAngle*0.0174532925);
	SetState(ANIM_RUN);
}

void cAnimatedCharacter::RotateLeft() {
	orientationAngle -= ANGLE_STEP_SIZE;
}

void cAnimatedCharacter::RotateRight() {
	orientationAngle += ANGLE_STEP_SIZE;
}

void cAnimatedCharacter::Draw() {
	animation_frame += 0.4f;
	int start_frame = animlist[state][0];
	int modulo = animlist[state][1] - animlist[state][0] +1;
	model.Render(0,0,0,90,0, start_frame + (int)animation_frame%modulo,1,  1,1,  0,0,0);
}

void cAnimatedCharacter::DrawPhysical() {

}

std::vector<float> cAnimatedCharacter::GetPosition() {
	std::vector<float> position(5);
	position[PLAYER_X] = x;
	position[PLAYER_Y] = 0;
	position[PLAYER_Z] = z;
	position[PLAYER_ANGLE] = orientationAngle;
	position[PLAYER_RADIUS] = radius;
	return position;
}

void cAnimatedCharacter::SetState(int st) {
	if (st != state) { 
		model.SetAnimation(st);
		state = st;
	}
}

void cAnimatedCharacter::Stop() {
	SetState(ANIM_STAND);
}

float cAnimatedCharacter::GetCurrentMinX() {
	return model.GetMinX()+x;
}

float cAnimatedCharacter::GetMinY() {
	return model.GetMinY();
}

float cAnimatedCharacter::GetCurrentMinZ() {
	return model.GetMinZ()+z;
}

float cAnimatedCharacter::GetCurrentMaxX() {
	return model.GetMaxX()+x;
}

float cAnimatedCharacter::GetMaxY() {
	return model.GetMaxY();
}

float cAnimatedCharacter::GetCurrentMaxZ() {
	return model.GetMaxZ()+z;
}

void cAnimatedCharacter::SetOrientation(float pitch) {
	orientationAngle = pitch;
}

bool cAnimatedCharacter::CollidesCharacter(float x0, float z0, float radius0) {
	//if ((GetCurrentMaxX() > minx && GetCurrentMaxX() < maxx) || (GetCurrentMinX() > minx && GetCurrentMinX() < maxx) && 
		//(GetCurrentMaxZ() > minz && GetCurrentMaxZ() < maxz) || (GetCurrentMinZ() > minz && GetCurrentMinZ() < maxz)) 
	if (sqrt((x-x0)*(x-x0)+(z-z0)*(z-z0)) < (radius+radius0)) return true;
	return false;
}

bool cAnimatedCharacter::CollidesBullet(std::vector<float> Position) {
	if (Position[1] < model.GetMaxY() && sqrt((x-Position[0])*(x-Position[0])+(z-Position[2])*(z-Position[2])) < radius) {
		DecreaseLife();
		return true;
	}
	return false;
}

void cAnimatedCharacter::DecreaseLife() {

}
