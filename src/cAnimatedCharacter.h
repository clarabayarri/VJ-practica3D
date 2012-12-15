#pragma once

#pragma comment(lib,"MD2Model")

#include "Globals.h"
#include "cMD2Model.h"
using namespace std;

class cAnimatedCharacter
{
public:
	float x;
	float z;
	float orientationAngle;
	float radius;

	cAnimatedCharacter(void);
	~cAnimatedCharacter(void);

	void SetXZ(float setx, float setz);
	void SetX(float setx);
	void SetZ(float setz);
	void SetModel(char * m);
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void RotateLeft();
	void RotateRight();

	void Draw();
	void DrawPhysical();

	std::vector<float> GetPosition();

	cMD2Model model;
};

