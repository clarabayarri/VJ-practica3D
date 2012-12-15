#include "cScene.h"
#include "Globals.h"
#include "customshadermanager.h"

cScene::cScene(void):x(0),z(0) {}
cScene::~cScene(void){}

void cScene::Init() {
	forest.Init();
	IsInitialized = true;
}

vector<vector<float> > cScene::GetForest() {
	return forest.GetTrees();
}

void cScene::Draw(cData *Data, CustomShaderManager *shaderManager, float OrientationAngle) {
	shaderManager->selectShader(-1);
	forest.Render(Data, shaderManager, OrientationAngle);
	glDisable(GL_TEXTURE_2D);
}

void cScene::DrawPhysical(float OrientationAngle)
{
	forest.RenderPhysical(OrientationAngle);
}

float cScene::GetHeight(float x, float z) {
	return forest.GetHeight(x,z);
}

float cScene::GetMinY() {
	return forest.GetMinY();
}

bool cScene::CollidesPhysics(vector<float> PlayerPosition, float PlayerRadius)
{
	// Walls
	if (PlayerPosition[0] < PlayerRadius || PlayerPosition[2] < PlayerRadius ||
		PlayerPosition[0] + PlayerRadius > (TERRAIN_SIZE-1)*DILATATION ||
		PlayerPosition[2] + PlayerRadius > (TERRAIN_SIZE-1)*DILATATION) return true;

	// Forest
	return forest.CollidesPhysics(PlayerPosition, PlayerRadius);
}

bool cScene::CollidesBoars(vector<float> PlayerPosition, float PlayerRadius)
{
	return forest.CollidesBoars(PlayerPosition, PlayerRadius);
}