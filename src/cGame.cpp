#include "cGame.h"
#include "Globals.h"
#include <ctime>

#define SECONDS_TO_MINUTE 60
#define BLINK_FRAMES 10

cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::Init() {
	glewInit();
	bool res=true;
	
	srand((unsigned int) time(NULL));

	//Positions initialization
	mouseX = -1;
	mouseY = -1;
	WireframeRendering = false;

	//Sounds initialization
	sounds.Init();
	playingAmbient = false; 
	playingEnemy = false; 

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

	InitStartScreen();
	return res;
}

void cGame::InitStartScreen()
{
	// Set options to false in case we return from game
	Gameover = false;
	WireframeRendering = false;
	Scene.IsInitialized = false;

	skydome.Init();
	skydome.SetTexId(IMG_SKY1);
	clouds.Init();
	clouds.SetTexId(IMG_SKY2);
}

void cGame::InitGame()
{
	CameraDist = DEFAULT_CAMERA_DIST_TO_PLAYER;
	CameraAngle = DEFAULT_CAMERA_ANGLE_TO_PLAYER;
	Scene.Init();
	ScreenExtras.Init(Scene.GetForest());
	LevelTimeLimit = 5*SECONDS_TO_MINUTE;
	StartTime = time(0);
	
	skydome.Init();
	skydome.SetTexId(IMG_SKY1);
	clouds.Init();
	clouds.SetTexId(IMG_SKY2);

	InitialZoomAngle = INITIAL_ZOOM_TOTAL_ROTATION_ANGLE;
	InitialZoomDistance = INITIAL_ZOOM_TOTAL_DISTANCE;

	Player.SetXZ((float) TERRAIN_SIZE,(float) TERRAIN_SIZE);
	Player.Init();

	Enemies.Init();

	MunitionCount = 5;
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
		mouseX = x;
	}
}

//Process
bool cGame::Process() {
	bool res=true;
	
	// Process Input
	if(keys[27])	res=false;	
	
	if (!playingAmbient) {
		sounds.PlayAmbient(SOUND_AMBIENT1);
		playingAmbient = true;
	}

	if(!Scene.IsInitialized) {
		ProcessStartScreenKeys();
	} else if (InitialZoomDistance == 0 && !Gameover) {
		ProcessGameKeys();
		ProcessBullets();
		CollidesEnemies();
	}

	if(WireframeRendering) ProcessWireframeModeKeys();

	return res;
}

void cGame::ProcessStartScreenKeys()
{
	if(keys[' ']) {
		InitGame();
	}
}

void cGame::ProcessBullets()
{
	for(int i = 0; i < Bullets.size(); ++i) {
		Bullets[i].Move();
	}
	for(int i = 0; i < Bullets.size(); ++i) {
		if (Bullets[i].IsFinished) {
			Bullets.erase(Bullets.begin() + i);
		}
	}
}

void cGame::CollidesBoars() {
	if(Scene.CollidesBoars(Player.GetPosition())) {
		++MunitionCount;
		sounds.PlayAction(SOUND_BOAR);
	}
}

void cGame::CollidesEnemies() {
	Enemies.Logic();
	for(int i = 0; i < Bullets.size(); ++i) {
		if(Enemies.CollidesBullet(Bullets[i].GetPosition())) {
			// TODO: Play sound
			Bullets.erase(Bullets.begin() + i);
			break;
		}
	}
	if (Enemies.Collides(Player.GetPosition())) {
		if(!playingEnemy) {
			sounds.PlayAction(SOUND_ENEMY);
			playingEnemy = true;
		}
		//Player.Die();
	}
}

void cGame::ProcessGameKeys()
{
	Player.Stop();
	// Player movement
	if(keys['e']) {
		Player.MoveRight();
		CollidesBoars();
		if(Scene.CollidesPhysics(Player.GetPosition())) Player.MoveLeft();
	}
	if(keys['w']) {
		Player.MoveForward();
		CollidesBoars();
		if(Scene.CollidesPhysics(Player.GetPosition())) Player.MoveBackward();
	}
	if(keys['q']) {
		Player.MoveLeft();
		CollidesBoars();
		if(Scene.CollidesPhysics(Player.GetPosition())) Player.MoveRight();
	}
	if(keys['s']) {
		Player.MoveBackward();
		CollidesBoars();
		if(Scene.CollidesPhysics(Player.GetPosition())) Player.MoveForward();
	}
	if(keys['a']) Player.RotateLeft();
	if(keys['d']) Player.RotateRight();
	if(keys[' ']) {
		keys[' '] = false;
		Shoot();
	}

	if(keys['p']) {
		WireframeRendering = !WireframeRendering;
		keys['p'] = false;
		if(!WireframeRendering) {
			CameraDist = DEFAULT_CAMERA_DIST_TO_PLAYER;
			CameraAngle = DEFAULT_CAMERA_ANGLE_TO_PLAYER;
		}
	}
}

void cGame::ProcessWireframeModeKeys()
{
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

void cGame::Shoot() {
	if (MunitionCount > 0) {
		cBullet Bullet;
		Bullet.SetPosition(Player.GetPosition());
		Bullet.Move();
		Bullets.push_back(Bullet);
		--MunitionCount;
	}
}

//Output
void cGame::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.01,100);
	
	glMatrixMode(GL_MODELVIEW);
	
	DrawSky();
	if(!Scene.IsInitialized) {
		DrawStartScreen();
	} else {
		DrawGame();
	}
	if (WireframeRendering)		DrawWireframeGame();
	if (Gameover)				DrawGameOver();
	
	glutSwapBuffers();

	UpdateFrameVariables();
}

void cGame::DrawStartScreen()
{
	GLuint left = SCREEN_WIDTH/2 - 200;
	GLuint top = SCREEN_HEIGHT/2 - 250;
	GLuint right = SCREEN_WIDTH/2 + 200;
	GLuint bottom = SCREEN_HEIGHT/2 + 300;
	glViewport(left, SCREEN_HEIGHT - bottom, right - left, bottom - top);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 1.25, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-0.1f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_START_SCREEN));
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);	glVertex2i(1,	0);
		glTexCoord2f(0.0f, 0.0f);	glVertex2i(0,	0);
		glTexCoord2f(0.0f, 1.0f);	glVertex2i(0,	1);
		glTexCoord2f(1.0f, 1.0f);	glVertex2i(1,	1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	if(FrameCounter % BLINK_FRAMES == FrameCounter % (BLINK_FRAMES*2)) {
		// Draw spacebar to start instructions
		glLoadIdentity();
		glTranslatef(0.0f,0.0f,-0.1f);
		glColor3f(0.2f,0.2f,0.2f);
		glRasterPos2f(0.2f, 1.1f);
		std::string text = "Press the spacebar to start!";
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *) text.c_str());
	
		glColor3f(1.0f,1.0f,1.0f);
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void cGame::DrawSky()
{
	// Dibuixar Skydome
	glLoadIdentity();
	glTranslatef(0.0f,-(float) SKY_SIZE/2,0.0f);
	glRotatef(Player.orientationAngle,0,1,0);
	skydome.Render(&Data);
	glRotatef((float) (glutGet(GLUT_ELAPSED_TIME)%360000)/1000,0,1,0);
	clouds.Render(&Data);
}

void cGame::DrawGame()
{
	float TotalDistanceToPlayer = CameraDist + InitialZoomDistance;
	float TotalRotationAngle = Player.orientationAngle + InitialZoomAngle;

	// Dibuixar personatge
	glLoadIdentity();
	glTranslatef(0.0f, (float) sin(-DEFAULT_CAMERA_ANGLE_TO_PLAYER*0.0174532925)*TotalDistanceToPlayer, -TotalDistanceToPlayer);
	glRotatef(CameraAngle - DEFAULT_CAMERA_ANGLE_TO_PLAYER,1.0f,0.0f,0.0f);
	glRotatef(InitialZoomAngle, 0, 1.0f, 0);
	Player.Draw();

	// Dibuixar escena
	glLoadIdentity();
	glTranslatef(0.0f, (float) sin(-DEFAULT_CAMERA_ANGLE_TO_PLAYER*0.0174532925)*TotalDistanceToPlayer-Scene.GetHeight(Player.x/DILATATION,Player.z/DILATATION)+Player.GetMinY(), -TotalDistanceToPlayer);
	glRotatef(CameraAngle - DEFAULT_CAMERA_ANGLE_TO_PLAYER,1.0f,0.0f,0.0f);
	glRotatef(TotalRotationAngle, 0, 1, 0);
	glTranslatef(-Player.x, 0, -Player.z);	
	Scene.Draw(&Data, &shaderManager, TotalRotationAngle);
	for (int i = 0; i < Bullets.size(); ++i) {
		Bullets[i].Draw(&Data);
	}
	Enemies.Draw(&Scene);
	

	// Only draw extras once the player has control
	if (InitialZoomDistance == 0) {
		ScreenExtras.Draw(&Data, GetTimeRemainingForLevel(), Player.GetPosition(), MunitionCount);
	}
}

void cGame::DrawWireframeGame() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.01,100);
	
	glMatrixMode(GL_MODELVIEW);

	float TotalDistanceToPlayer = CameraDist + InitialZoomDistance;
	float TotalRotationAngle = Player.orientationAngle + InitialZoomAngle;

	// Dibuixar personatge
	glLoadIdentity();
	glRotatef(-DEFAULT_CAMERA_ANGLE_TO_PLAYER, 1, 0, 0);
	glTranslatef(0, 0, -TotalDistanceToPlayer);
	Player.DrawPhysical();

	// Dibuixar escena
	glLoadIdentity();
	glTranslatef(0.0f,(float) sin(-DEFAULT_CAMERA_ANGLE_TO_PLAYER*0.0174532925)*TotalDistanceToPlayer-Scene.GetHeight(Player.x/DILATATION,Player.z/DILATATION)+Player.GetMinY(), -TotalDistanceToPlayer);
	glRotatef(CameraAngle - DEFAULT_CAMERA_ANGLE_TO_PLAYER,1.0f,0.0f,0.0f);
	glRotatef(TotalRotationAngle, 0, 1, 0);
	glTranslatef(-Player.x, 0, -Player.z);	
	for (int i = 0; i < Bullets.size(); ++i) {
		Bullets[i].DrawPhysical();
	}
	Scene.DrawPhysical(TotalRotationAngle);
	
	Enemies.DrawPhysical(&Scene);

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
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void cGame::UpdateFrameVariables()
{
	// Game over?
	if(Scene.IsInitialized && !Gameover && GetTimeRemainingForLevel() <= 0.0) {
		Gameover = true;
		FrameCounter = 0;
	}
	
	// Initial zoom
	if (InitialZoomAngle > 0) InitialZoomAngle -= INITIAL_ZOOM_ANGLE_DECREASE_STEP;
	else if (InitialZoomDistance > 0) {
		InitialZoomDistance -= INITIAL_ZOOM_DISTANCE_DECREASE_STEP;
		if (InitialZoomDistance == 0) StartTime = time(0);
	}

	// Frame counter
	++FrameCounter;
	if (Gameover && FrameCounter == BLINK_FRAMES*20) {
		InitStartScreen();
	}
	if (FrameCounter == BLINK_FRAMES*20) FrameCounter = 0;
}

double cGame::GetTimeRemainingForLevel()
{
	time_t CurrentTime = time(0);
	return max(0.0, LevelTimeLimit - difftime(CurrentTime, StartTime));
}
