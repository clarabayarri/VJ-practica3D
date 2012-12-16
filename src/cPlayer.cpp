#include "cPlayer.h"


cPlayer::cPlayer(void) {}

cPlayer::~cPlayer(void){}

void cPlayer::Init() {
	SetModel("knight");
}

void cPlayer::Draw() {
	glScalef(0.25f,0.25f,0.25f);

	cAnimatedCharacter::Draw();
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
