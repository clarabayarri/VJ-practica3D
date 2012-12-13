#include "cGame.h"
#include "Globals.h"
#include <ctime>

cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::Init()
{
	glewInit();
	bool res=true;
	
	//Positions initialization
	mouseX = -1;
	mouseY = -1;
	CameraDist = DEFAULT_CAMERA_DIST_TO_PLAYER;
	CameraAngle = DEFAULT_CAMERA_ANGLE_TO_PLAYER;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Shader initialization
	shaderManager.initShaders();

	//Scene initialization
	res = Data.Init();
	if (!res) return false;
	Scene.Init();
	ScreenExtras.Init(Scene.GetForest());
	LevelTimeLimit = 5*60;
	StartTime = time(0);
	if(!res) return false;

	skydome.Init();
	skydome.SetTexId(IMG_SKY1);
	clouds.Init();
	clouds.SetTexId(IMG_SKY2);

	InitialZoomAngle = INITIAL_ZOOM_TOTAL_ROTATION_ANGLE;
	InitialZoomDistance = INITIAL_ZOOM_TOTAL_DISTANCE;

	Player.SetXZ((float) TERRAIN_SIZE,(float) TERRAIN_SIZE);

	WireframeRendering = false;
	MunitionCount = 0;

	return res;
}

bool cGame::Loop()
{
	bool res=true;

	res = Process();
	if(res) Render();

	return res;
}

void cGame::Finalize() {}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	keys[key] = press;
}

void cGame::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press) {
	skeys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
	if (mouseX == -1) {
		mouseX = x;
		mouseY = y;
	} else {
		//ballAngle += (mouseX - x)*360 / SCREEN_WIDTH;
		//SetCursorPos(x,mouseY);
		mouseX = x;
	}
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	// Process Input
	if(keys[27])	res=false;	

	// Game over?
	if(!Gameover && GetTimeRemainingForLevel() <= 0.0) {
		Gameover = true;
	}

	// Omit keys while zooming into the scene
	if(InitialZoomDistance > 0) return res;
	
	// Game Logic
	// Player movement
	if(keys['e']) {
		Player.MoveRight();
		if(Scene.CollidesBoars(Player.GetPosition(),Player.radius)) ++MunitionCount;
		if(Scene.CollidesPhysics(Player.GetPosition(),Player.radius)) Player.MoveLeft();
	}
	if(keys['w']) {
		Player.MoveForward();
		if(Scene.CollidesBoars(Player.GetPosition(),Player.radius)) ++MunitionCount;
		if(Scene.CollidesPhysics(Player.GetPosition(),Player.radius)) Player.MoveBackward();
	}
	if(keys['q']) {
		Player.MoveLeft();
		if(Scene.CollidesBoars(Player.GetPosition(),Player.radius)) ++MunitionCount;
		if(Scene.CollidesPhysics(Player.GetPosition(),Player.radius)) Player.MoveRight();
	}
	if(keys['s']) {
		Player.MoveBackward();
		if(Scene.CollidesBoars(Player.GetPosition(),Player.radius)) ++MunitionCount;
		if(Scene.CollidesPhysics(Player.GetPosition(),Player.radius)) Player.MoveForward();
	}
	if(keys['a']) Player.RotateLeft();
	if(keys['d']) Player.RotateRight();

	if(keys['p']) {
		WireframeRendering = !WireframeRendering;
		keys['p'] = false;
		if(!WireframeRendering) {
			CameraDist = DEFAULT_CAMERA_DIST_TO_PLAYER;
			CameraAngle = DEFAULT_CAMERA_ANGLE_TO_PLAYER;
		}
	}

	// Camera angle and distance to player
	if(WireframeRendering) {
		if(keys['8']) {
			CameraDist--;
			if (CameraDist < DEFAULT_CAMERA_DIST_TO_PLAYER) CameraDist = DEFAULT_CAMERA_DIST_TO_PLAYER;
		}
		if(keys['2']) {
			CameraDist++;
			if (CameraDist > DEFAULT_CAMERA_DIST_TO_PLAYER*8) CameraDist = DEFAULT_CAMERA_DIST_TO_PLAYER*8;
		}
		if(keys['4']) {
			CameraAngle--;
			if (CameraAngle < 0) CameraAngle = 0;
		}
		if(keys['6']) {
			CameraAngle++;
			if (CameraAngle > 90) CameraAngle = 90;
		}
	}
	
	//if(ballX < 0) ballX = 0;
	//if(ballZ < 0) ballZ = 0;
	//if(ballX > (TERRAIN_SIZE-1)*DILATATION) ballX = (TERRAIN_SIZE-1)*DILATATION;
	//if(ballZ > (TERRAIN_SIZE-1)*DILATATION) ballZ = (TERRAIN_SIZE-1)*DILATATION;
	return res;
}

//Output
void cGame::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.01,100);
	
	glMatrixMode(GL_MODELVIEW);
	
	// Dibuixar Skydome
	glLoadIdentity();
	glTranslatef(0.0f,-(float) SKY_SIZE/2+0.1f,0.0f);
	glRotatef(Player.orientationAngle,0,1,0);
	skydome.Render(&Data);
	glRotatef((float) (glutGet(GLUT_ELAPSED_TIME)%360000)/1000,0,1,0);
	clouds.Render(&Data);

	float TotalDistanceToPlayer = CameraDist + InitialZoomDistance;
	float TotalRotationAngle = Player.orientationAngle + InitialZoomAngle;

	// Dibuixar personatge
	glLoadIdentity();
	glRotatef(-DEFAULT_CAMERA_ANGLE_TO_PLAYER, 1, 0, 0);
	glTranslatef(0, 0, -TotalDistanceToPlayer);
	Player.Draw();

	// Dibuixar escena
	glLoadIdentity();
	glTranslatef(0.0f, (float) sin(-DEFAULT_CAMERA_ANGLE_TO_PLAYER*0.0174532925)*TotalDistanceToPlayer-Scene.GetHeight(Player.x/DILATATION,Player.z/DILATATION), -TotalDistanceToPlayer);
	glRotatef(CameraAngle - DEFAULT_CAMERA_ANGLE_TO_PLAYER,1.0f,0.0f,0.0f);
	glRotatef(TotalRotationAngle, 0, 1, 0);
	glTranslatef(-Player.x, 0, -Player.z);	
	Scene.Draw(&Data, &shaderManager, TotalRotationAngle);

	if (WireframeRendering) {
		// Dibuixar personatge
		glLoadIdentity();
		glRotatef(-DEFAULT_CAMERA_ANGLE_TO_PLAYER, 1, 0, 0);
		glTranslatef(0, 0, -TotalDistanceToPlayer);
		Player.DrawPhysical();

		// Dibuixar escena
		glLoadIdentity();
		glTranslatef(0.0f, (float) sin(-DEFAULT_CAMERA_ANGLE_TO_PLAYER*0.0174532925)*TotalDistanceToPlayer-Scene.GetHeight(Player.x/DILATATION,Player.z/DILATATION), -TotalDistanceToPlayer);
		glRotatef(CameraAngle - DEFAULT_CAMERA_ANGLE_TO_PLAYER,1.0f,0.0f,0.0f);
		glRotatef(TotalRotationAngle, 0, 1, 0);
		glTranslatef(-Player.x, 0, -Player.z);	
		Scene.DrawPhysical(TotalRotationAngle);
	}

	if (Gameover) {
		DrawGameOver();
	}

	// Only draw extras once the player has control
	if (InitialZoomDistance == 0) {
		ScreenExtras.Draw(&Data, GetTimeRemainingForLevel(), Player.GetPosition(), MunitionCount);
	}
	
	glutSwapBuffers();

	if (InitialZoomAngle > 0) InitialZoomAngle -= INITIAL_ZOOM_ANGLE_DECREASE_STEP;
	else if (InitialZoomDistance > 0) {
		InitialZoomDistance -= INITIAL_ZOOM_DISTANCE_DECREASE_STEP;
		if (InitialZoomDistance == 0) StartTime = time(0);
	}
}

double cGame::GetTimeRemainingForLevel()
{
	time_t CurrentTime = time(0);
	return max(0.0, LevelTimeLimit - difftime(CurrentTime, StartTime));
}

void cGame::DrawGameOver()
{
	GLuint left = SCREEN_WIDTH/2 - 200;
	GLuint top = SCREEN_HEIGHT/2 - 200;
	GLuint right = SCREEN_WIDTH/2 + 200;
	GLuint bottom = SCREEN_HEIGHT/2 + 200;
	glViewport(left, SCREEN_HEIGHT - bottom, right - left, bottom - top);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-0.1f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_GAMEOVER));
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);	glVertex2i(1,	0);
		glTexCoord2f(0.0f, 0.0f);	glVertex2i(0,	0);
		glTexCoord2f(0.0f, 1.0f);	glVertex2i(0,	1);
		glTexCoord2f(1.0f, 1.0f);	glVertex2i(1,	1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
