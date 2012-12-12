#pragma once

#include "Globals.h"
#include "Constants.h"
using namespace std;

class cAnimatedCharacter
{
public:
	float x;
	float z;
	float orientationAngle;

	cAnimatedCharacter(void);
	~cAnimatedCharacter(void);

	void SetXZ(float setx, float setz);
	void SetX(float setx);
	void SetZ(float setz);
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void RotateLeft();
	void RotateRight();

	void Draw();
	void DrawPhysical();

	vector<float> GetPosition();
};

