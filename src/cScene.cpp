#include "cScene.h"
#include "Globals.h"
#include "customshadermanager.h"

cScene::cScene(void):x(0),z(0) {}
cScene::~cScene(void){}

void cScene::Init() {
	forest.Init();
}

vector<vector<float> > cScene::GetForest() {
	return forest.GetTrees();
}

void cScene::Draw(cData *Data, CustomShaderManager *shaderManager) {
	shaderManager->selectShader(-1);
	forest.Render(Data,shaderManager);
	glDisable(GL_TEXTURE_2D);
}

void cScene::DrawPhysical()
{
	forest.RenderPhysical();
}

float cScene::GetHeight(float x, float z) {
	return forest.GetHeight(x,z);
}

float cScene::GetMinY() {
	return forest.GetMinY();
}