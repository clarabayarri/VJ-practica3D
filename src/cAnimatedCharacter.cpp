#include "cAnimatedCharacter.h"
#include "Constants.h"

#define STEP_SIZE 0.1f
#define ANGLE_STEP_SIZE 5.0f

cAnimatedCharacter::cAnimatedCharacter(void):x(1.0f),z(1.0f),radius(0.1f),life(100),dead(false),animation_frame(0.0f),dying(false){
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

void cAnimatedCharacter::MoveForward() {
	if (!dying) {
		x += STEP_SIZE * (float) cos((90-orientationAngle)*0.0174532925);
		z -= STEP_SIZE * (float) cos(orientationAngle*0.0174532925);
		SetState(ANIM_RUN);
	}
}

void cAnimatedCharacter::MoveBackward() {
	if (!dying) {
		x -= STEP_SIZE * (float) cos((90-orientationAngle)*0.0174532925);
		z += STEP_SIZE * (float) cos(orientationAngle*0.0174532925);
		SetState(ANIM_RUN);
	}
}

void cAnimatedCharacter::MoveLeft() {
	if (!dying) {
		x -= STEP_SIZE * (float) sin((90-orientationAngle)*0.0174532925);
		z -= STEP_SIZE * (float) sin(orientationAngle*0.0174532925);
		SetState(ANIM_RUN);
	}
}

void cAnimatedCharacter::MoveRight() {
	if (!dying) {
		x += STEP_SIZE * (float) sin((90-orientationAngle)*0.0174532925);
		z += STEP_SIZE * (float) sin(orientationAngle*0.0174532925);
		SetState(ANIM_RUN);
	}
}

void cAnimatedCharacter::RotateLeft() {
	if (!dying)
		orientationAngle -= ANGLE_STEP_SIZE;
}

void cAnimatedCharacter::RotateRight() {
	if (!dying)
		orientationAngle += ANGLE_STEP_SIZE;
}

void cAnimatedCharacter::Draw() {
	animation_frame += 0.4f;
	int start_frame = animlist[state][0];
	int modulo = animlist[state][1] - animlist[state][0] +1;
	if (dying && animation_frame/modulo > 1) animation_frame = modulo-1;
	if (!dead) model.Render(0,0,0,90,0, start_frame + (int)animation_frame%modulo,1,  1,1,  0,0,0);
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
	if (!dying)
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

void cAnimatedCharacter::Kill() {
	if(!dying) animation_frame = 0;
	dying = true;
	SetState(STATE_DYING);
}

bool cAnimatedCharacter::CollidesBullet(std::vector<float> Position) {
	if (life > 0 && Position[1] < model.GetMaxY() && sqrt((x-Position[0])*(x-Position[0])+(z-Position[2])*(z-Position[2])) < radius) {
		DecreaseLife();
		if (life <= 0) StartDisappearing();
		return true;
	}
	return false;
}

void cAnimatedCharacter::DecreaseLife() {

}

void cAnimatedCharacter::StartDisappearing() {
	disappearing = 1;
	Kill();
}

bool cAnimatedCharacter::IsDead() {
	return (dead || dying);
}