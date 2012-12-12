#pragma once

#include "cScene.h"
#include "cData.h"
#include "customshadermanager.h"
#include "cScreenExtras.h"
#include "cAnimatedCharacter.h"
#include "cSkydome.h"
#include "Constants.h"
#include <ctime>

#define DEFAULT_CAMERA_DIST_TO_PLAYER 5.0f
#define DEFAULT_CAMERA_ANGLE_TO_PLAYER 15.0f

#define INITIAL_ZOOM_TOTAL_ROTATION_ANGLE 360
#define INITIAL_ZOOM_TOTAL_DISTANCE 40
#define INITIAL_ZOOM_ANGLE_DECREASE_STEP 5
#define INITIAL_ZOOM_DISTANCE_DECREASE_STEP 2

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
	void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	unsigned char skeys[256];

	cScene Scene;
	cScreenExtras ScreenExtras;
	cData Data;
	cSkydome skydome;
	cSkydome clouds;

	cAnimatedCharacter Player;

	int mouseX;
	int mouseY;

	int InitialZoomAngle;
	int InitialZoomDistance;

	bool WireframeRendering;
	bool Gameover;

	float CameraDist;
	float CameraAngle;

	time_t StartTime;
	double LevelTimeLimit;
	double GetTimeRemainingForLevel();

	CustomShaderManager shaderManager;

	void DrawGameOver();
};
