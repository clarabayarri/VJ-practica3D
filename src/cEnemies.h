#pragma once

#include "cScene.h"
#include "cBauul.h"

class cEnemies
{
public:
	cEnemies(void);
	~cEnemies(void);

	void Init();

	void Draw(cScene *Scene);
	void DrawPhysical(cScene *Scene);

	void Logic();

	bool Collides(std::vector<float> PlayerPosition);

private:
	std::vector<cBauul> bauuls;
};

