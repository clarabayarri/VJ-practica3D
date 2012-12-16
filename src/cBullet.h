#pragma once

#include "cData.h"
#include "Globals.h"

class cBullet
{
public:
	cBullet(void);
	~cBullet(void);

	bool IsFinished;

	void SetPosition(std::vector<float> Position);

	void Move();
	void Draw(cData *Data);
	void DrawPhysical();

	std::vector<float> GetPosition();

private:
	float x, y, z;

	int FrameCount;
	float orientationAngle;
};

