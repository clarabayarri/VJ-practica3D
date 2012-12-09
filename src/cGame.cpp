#include "cGame.h"
#include "Globals.h"

cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::Init()
{
	glewInit();
	bool res=true;
	
	//Positions initialization
	mouseX = -1;
	mouseY = -1;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
	glEnable(GL_ALPHA_TEST);

	// Shader initialization
	shaderManager.initShaders();

	//Scene initialization
	res = Data.Init();
	if (!res) return false;
	Scene.Init();
	ScreenExtras.Init(Scene.GetForest());
	res = Scene.LoadLevel(1);
	if(!res) return false;

	skydome.Init();

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
	
	//Process Input
	if(keys[27])	res=false;	
	
	//Game Logic
	//Player movement
	if(keys['e']) {
		Player.MoveRight();
	}
	if(keys['w']) {
		Player.MoveForward();
	}
	if(keys['q']) {
		Player.MoveLeft();
	}
	if(keys['s']) {
		Player.MoveBackward();
	}
	if(keys['a']) Player.RotateLeft();
	if(keys['d']) Player.RotateRight();

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
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	
	glMatrixMode(GL_MODELVIEW);
	
	// Dibuizar Skydome
	glLoadIdentity();
	glTranslatef(0,-2,0);
	glRotatef(Player.orientationAngle,0,1,0);
	skydome.Render(&Data);
	glRotatef((float) (glutGet(GLUT_ELAPSED_TIME)%360000)/1000,0,1,0);
	clouds.Render(&Data);

	// Dibuixar pilota
	// Personatge.Draw()
	glLoadIdentity();
	glRotatef(-CAMERA_ANGLE_TO_PLAYER,1,0,0);
	glTranslatef(0,0,-CAMERA_DIST_TO_PLAYER);
	GLUquadricObj *q = gluNewQuadric();
		gluSphere(q, 0.1,16,16);
		gluDeleteQuadric(q);

	// Dibuixar escena
	glLoadIdentity();
	glTranslatef(0,sin(-CAMERA_ANGLE_TO_PLAYER*0.0174532925)*CAMERA_DIST_TO_PLAYER-Scene.GetHeight(Player.x/DILATATION,Player.z/DILATATION),-CAMERA_DIST_TO_PLAYER);
	glRotatef(Player.orientationAngle,0,1,0);
	glTranslatef(-Player.x,0,-Player.z);
	
	Scene.Draw(&Data, &shaderManager);
	ScreenExtras.Draw(&Data, Player.GetPosition(), 0);
	glutSwapBuffers();
}
