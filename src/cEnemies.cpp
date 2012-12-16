#include "cEnemies.h"
#include "Globals.h"
#include "Constants.h"

cEnemies::cEnemies(void)
{
}


cEnemies::~cEnemies(void)
{
}

void cEnemies::Init()
{
	bauuls = std::vector<cBauul>(NUM_BAUULS);
	for (int i = 0; i < NUM_BAUULS; ++i) {
		bauuls[i].Init();
		bauuls[i].SetXZ((rand()%(TERRAIN_SIZE-2)+1)*DILATATION,(rand()%(TERRAIN_SIZE-2)+1)*DILATATION);
		bauuls[i].SetOrientation(rand()%360);
	}
}

void cEnemies::Draw(cScene *Scene)
{
	for (int i = 0; i < NUM_BAUULS; ++i) {
		glPushMatrix();
		glTranslatef(bauuls[i].x,-bauuls[i].GetMinY()+Scene->GetHeight(bauuls[i].x/DILATATION,bauuls[i].z/DILATATION),bauuls[i].z);
		bauuls[i].Draw();
		glPopMatrix();
	}
}

void cEnemies::DrawPhysical(cScene *Scene)
{
	for (int i = 0; i < NUM_BAUULS; ++i) {
		glPushMatrix();
		glTranslatef(bauuls[i].x,-bauuls[i].GetMinY()+Scene->GetHeight(bauuls[i].x/DILATATION,bauuls[i].z/DILATATION),bauuls[i].z);
		bauuls[i].DrawPhysical();
		glPopMatrix();
	}
}

void cEnemies::Logic()
{
	for (int i = 0; i < NUM_BAUULS; ++i) {
		bauuls[i].Logic(DILATATION,(TERRAIN_SIZE-1)*DILATATION);
	}
}

bool cEnemies::Collides(std::vector<float> PlayerPosition)
{
	for (int i = 0; i < NUM_BAUULS; ++i) {
		bauuls[i].Logic(DILATATION,(TERRAIN_SIZE-1)*DILATATION);
		if (bauuls[i].CollidesCharacter(PlayerPosition[PLAYER_X],PlayerPosition[PLAYER_Z],PlayerPosition[PLAYER_RADIUS])) {
			bauuls[i].Attack();
			return true;
		}
	}
	return false;
}

