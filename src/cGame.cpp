#include "cGame.h"
#include "Globals.h"

#define STEP_SIZE 1
#define ANGLE_STEP_SIZE 5

cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::Init()
{
	glewInit();
	bool res=true;
	
	//Positions initialization
	mouseX = -1;
	mouseY = -1;
	ballX = 0;
	ballZ = 0;
	ballAngle = 0;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	// Shader initialization
	shaderManager.initShaders();

	//Scene initialization
	res = Data.Init();
	if (!res) return false;
	Scene.Init();
	res = Scene.LoadLevel(1);
	if(!res) return false;

	return res;
}

bool cGame::Loop()
{
	bool res=true;

	res = Process();
	if(res) Render();

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
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

	//Ball movement
	if(keys['e']) {
		ballX += STEP_SIZE * sin((90-ballAngle)*0.0174532925);
		ballZ -= STEP_SIZE * sin(ballAngle*0.0174532925);
	}
	if(keys['w']) {
		ballX += STEP_SIZE * cos((90-ballAngle)*0.0174532925);
		ballZ -= STEP_SIZE * cos(ballAngle*0.0174532925);
	}
	if(keys['q']) {
		ballX -= STEP_SIZE * sin((90-ballAngle)*0.0174532925);
		ballZ += STEP_SIZE * sin(ballAngle*0.0174532925);
	}
	if(keys['s']) {
		ballX -= STEP_SIZE * cos((90-ballAngle)*0.0174532925);
		ballZ += STEP_SIZE * cos(ballAngle*0.0174532925);
	}
	if(keys['a']) ballAngle -= ANGLE_STEP_SIZE;
	if(keys['d']) ballAngle += ANGLE_STEP_SIZE;

	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	// Dibuixar pilota
	// Personatge.Draw()
	glTranslatef(0,0,-CAMERA_DIST_TO_PLAYER);
	glRotatef(CAMERA_ANGLE_TO_PLAYER,1,0,0);
	GLUquadricObj *q = gluNewQuadric();
		gluSphere(q, 1,16,16);
		gluDeleteQuadric(q);

	// Dibuixar escena
	glLoadIdentity();
	glTranslatef(-ballX,0,-ballZ);
	glTranslatef(0,0,-CAMERA_DIST_TO_PLAYER);
	
	glRotatef(-ballAngle,0,1,0);
	glRotatef(CAMERA_ANGLE_TO_PLAYER,1,0,0);

	Scene.Draw(&Data, &shaderManager);

	glutSwapBuffers();
}
