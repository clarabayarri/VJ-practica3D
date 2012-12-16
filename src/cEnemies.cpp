#include "cEnemies.h"
#include "Globals.h"
#include "Constants.h"

cEnemies::cEnemies(void) {}

cEnemies::~cEnemies(void) {}

void cEnemies::Init() {
	bauuls = std::vector<cBauul>(NUM_BAUULS);
	for (int i = 0; i < NUM_BAUULS; ++i) {
		bauuls[i].Init();
		bauuls[i].SetXZ((rand()%(TERRAIN_SIZE-2)+1)*DILATATION,(rand()%(TERRAIN_SIZE-2)+1)*DILATATION);
		bauuls[i].SetOrientation(rand()%360);
	}
}

std::vector<std::vector<float> > cEnemies::GetEnemies() {
	std::vector<std::vector<float> > result;
	for (unsigned int i = 0; i < bauuls.size(); ++i)
		if(!bauuls[i].IsDead()) result.push_back(bauuls[i].GetPosition());
	return result;
}

int cEnemies::EnemyCount() {
	int count = 0;
	for (unsigned int i = 0; i < bauuls.size(); ++i)
		if(!bauuls[i].IsDead()) ++count;
	return count;
}

void cEnemies::Draw(cScene *Scene) {
	for (unsigned int i = 0; i < bauuls.size(); ++i) {
		glPushMatrix();
		glTranslatef(bauuls[i].x,-bauuls[i].GetMinY()+Scene->GetHeight(bauuls[i].x/DILATATION,bauuls[i].z/DILATATION),bauuls[i].z);
		bauuls[i].Draw();
		glPopMatrix();
	}
}

void cEnemies::DrawPhysical(cScene *Scene) {
	glColor3f(0.722f, 0.13f, 0.13f);
	for (unsigned int i = 0; i < bauuls.size(); ++i) {
		glPushMatrix();
		glTranslatef(bauuls[i].x,Scene->GetHeight(bauuls[i].x/DILATATION,bauuls[i].z/DILATATION),bauuls[i].z);
		bauuls[i].DrawPhysical();
		glPopMatrix();
	}
	glColor3f(1.0f,1.0f,1.0f);
}

void cEnemies::Logic(float min, float max) {
	for (unsigned int i = 0; i < bauuls.size(); ++i)
		if (bauuls[i].dead) {
			//bauuls.erase(bauuls.begin()+i);
			break;
		}
	for (unsigned int i = 0; i < bauuls.size(); ++i)
		if (!bauuls[i].IsDead()) bauuls[i].Logic(min,max);
}

bool cEnemies::Collides(std::vector<float> PlayerPosition) {
	for (unsigned int i = 0; i < bauuls.size(); ++i)
		if (!bauuls[i].IsDead())
			if (bauuls[i].CollidesCharacter(PlayerPosition[PLAYER_X],PlayerPosition[PLAYER_Z],PlayerPosition[PLAYER_RADIUS])) {
				bauuls[i].Attack();
				return true;
			}
	return false;
}

bool cEnemies::CollidesBullet(std::vector<float> Position) {
	for (unsigned int i = 0; i < bauuls.size(); ++i)
		if (bauuls[i].CollidesBullet(Position)) {
			return true;
		}
	return false;
}

