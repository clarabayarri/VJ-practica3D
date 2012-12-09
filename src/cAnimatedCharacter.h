#pragma once

#include "Globals.h"
using namespace std;

class cAnimatedCharacter
{
public:
	float x;
	float z;
	float orientationAngle;

	cAnimatedCharacter(void);
	~cAnimatedCharacter(void);

	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void RotateLeft();
	void RotateRight();

	void Draw();

	vector<float> GetPosition();
};

