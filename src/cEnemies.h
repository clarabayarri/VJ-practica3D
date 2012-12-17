#pragma once

#include "cScene.h"
#include "cBauul.h"

class cEnemies
{
public:
	cEnemies(void);
	~cEnemies(void);

	void Init(int count);

	std::vector<std::vector<float> > GetEnemies();
	int EnemyCount();

	void Draw(cScene *Scene);
	void DrawPhysical(cScene *Scene);

	void Logic(float min, float max);

	bool Collides(std::vector<float> PlayerPosition);
	bool CollidesBullet(std::vector<float> Position);

private:
	std::vector<cBauul> bauuls;
};

