#pragma once

#include "cScene.h"
#include "cData.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	cScene Scene;
	cData Data;
	
	int rendermode;
	float ballX;
	float ballZ;
	float ballAngle;

	int mouseX;
	int mouseY;
};
