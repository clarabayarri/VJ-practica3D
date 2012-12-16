#pragma once
#include "cScene.h"
#include "canimatedcharacter.h"

class cPlayer :
	public cAnimatedCharacter
{
public:
	cPlayer(void);
	~cPlayer(void);

	void Init();
	void Draw();
	void DrawPhysical(cScene *Scene);
	float GetMinY();

	float GetCurrentMinX();
	float GetCurrentMinZ();
	float GetCurrentMaxX();
	float GetCurrentMaxZ();

protected:
	void DecreaseLife();
};

