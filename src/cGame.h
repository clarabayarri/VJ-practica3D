#pragma once

#include "cScene.h"
#include "cData.h"
#include "customshadermanager.h"
#include "cScreenExtras.h"
#include "Constants.h"

#define CAMERA_DIST_TO_PLAYER 10
#define CAMERA_ANGLE_TO_PLAYER 20

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
	cScreenExtras ScreenExtras;
	cData Data;
	
	float ballX;
	float ballZ;
	float ballAngle;

	int mouseX;
	int mouseY;

	CustomShaderManager shaderManager;
};
