#include "cPlayer.h"


cPlayer::cPlayer(void) {}

cPlayer::~cPlayer(void){}

void cPlayer::Init() {
	SetModel("knight");
	SetState(ANIM_STAND);
	dying = false;
	radius = 0.3f;
	scale = 0.25f;
}

void cPlayer::Draw() {
	glPushMatrix();
	glScalef(scale,scale,scale);

	cAnimatedCharacter::Draw();
	glPopMatrix();
}

void cPlayer::DrawPhysical(cScene *Scene) {
	glPushMatrix();
	glTranslatef(x,Scene->GetHeight(x/DILATATION,z/DILATATION),z);
	glColor3f(0.13f, 0.267f, 0.722);
	cAnimatedCharacter::DrawPhysical();
	glColor3f(1.0f,1.0f,1.0f);
	glPopMatrix();
}

float cPlayer::GetMinY() {
	return model.GetMinY()/4;
}

float cPlayer::GetCurrentMinX() {
	return model.GetMinX()/4+x;
}

float cPlayer::GetCurrentMinZ() {
	return model.GetMinZ()/4+z;
}

float cPlayer::GetCurrentMaxX() {
	return model.GetMaxX()/4+x;
}

float cPlayer::GetCurrentMaxZ() {
	return model.GetMaxZ()/4+z;
}

void cPlayer::DecreaseLife() {
	life -= 20;
}