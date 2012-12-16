#include "cBauul.h"

#define DISAPPEAR_BLINK 40

cBauul::cBauul():nextState(true),actionstate(0) {}

cBauul::~cBauul() {}

void cBauul::Init() {
	SetModel("bauul");
	radius = 1.5f;
}

void cBauul::Draw() {
	animation_frame += 0.4f;
	if (disappearing % 5 == disappearing % 10) {
		int start_frame = animlist[state][0];
		int modulo = animlist[state][1] - animlist[state][0] +1;
		if ((int)animation_frame/20 > 1) nextState = true;
		model.Render(0,0,0,90+orientationAngle,0, start_frame + (int)animation_frame%modulo,1,  1,1,  0,0,0);
	}
	if (disappearing > 0) {
		disappearing++;
		if (disappearing == DISAPPEAR_BLINK) dead = true;
	}
}

void cBauul::Logic(float min, float max) {
	if (nextState) {
		Stop();
		animation_frame = 0;
		nextState = false;
		int random = rand()%5;
		if (random == 0) 
			actionstate = STATE_MOVE_FORWARD;
		else if (random == 1)
			actionstate = STATE_ROTATE_LEFT;
		else if (random == 2)
			actionstate = STATE_ROTATE_RIGHT;
		else 
			actionstate = STATE_STANDBY;
	}
	switch(actionstate) {
		case STATE_STANDBY: Stop(); break;
		case STATE_MOVE_FORWARD: MoveForward(min,max); break;
		case STATE_ROTATE_LEFT: RotateLeft(); break;
		case STATE_ROTATE_RIGHT: RotateRight(); break;
	}
}

void cBauul::MoveForward(float min, float max) {
	cAnimatedCharacter::MoveForward();
	if (x < min) x = min;
	if (x > max) x = max;
	if (z < min) z = min;
	if (z > max) z = max;
}

void cBauul::DrawPhysical() {
	model.RenderBoundingBox();
}

void cBauul::Attack() {
	nextState = false;
	actionstate = STATE_ATTACK;
	SetState(ANIM_ATTACK);
}

void cBauul::DecreaseLife() {
	life -= 50;
}