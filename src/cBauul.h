#pragma once
#include "canimatedcharacter.h"

#define STATE_STANDBY		0
#define STATE_MOVE_FORWARD	1
#define STATE_ROTATE_LEFT	2
#define STATE_ROTATE_RIGHT	3
#define STATE_ATTACK		4

class cBauul :
	public cAnimatedCharacter
{
public:
	cBauul();
	~cBauul();

	void Init();
	void Draw();
	void Logic(float min, float max);
	void MoveForward(float min, float max);
	void Attack();
	
protected:
	void DecreaseLife();

private:
	bool nextState;
	int actionstate;
};

