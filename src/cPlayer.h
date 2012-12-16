#pragma once
#include "canimatedcharacter.h"
class cPlayer :
	public cAnimatedCharacter
{
public:
	cPlayer(void);
	~cPlayer(void);

	void Init();
	void Draw();
	float GetMinY();

	float GetCurrentMinX();
	float GetCurrentMinZ();
	float GetCurrentMaxX();
	float GetCurrentMaxZ();
};

