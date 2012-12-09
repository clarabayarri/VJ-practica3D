#include "cScreenExtras.h"


cScreenExtras::cScreenExtras(void)
{
}

cScreenExtras::~cScreenExtras(void)
{
}

void cScreenExtras::Init(const vector<vector<float> >& trees) {
	SceneMap.Init(trees);
	TimeGauge.Init();
}

void cScreenExtras::Draw(cData *Data, const vector<float>& player, int munitionCount)
{
	DrawTimeGauge(Data);
	DrawMunitionCounter(Data, munitionCount);
	DrawMap(Data, player);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void cScreenExtras::DrawTimeGauge(cData *Data)
{
	GLuint left = SCREEN_MARGIN;
	GLuint top = SCREEN_MARGIN;
	GLuint right = SCREEN_WIDTH*0.2 + SCREEN_MARGIN;
	GLuint bottom = SCREEN_HEIGHT * 0.15 + SCREEN_MARGIN;
	glViewport(left, SCREEN_HEIGHT - bottom, right - left, bottom - top);

	TimeGauge.Draw(Data);
}

void cScreenExtras::DrawMunitionCounter(cData *Data, int count)
{
	GLuint left = SCREEN_WIDTH - (100 + SCREEN_MARGIN);
	GLuint top = SCREEN_MARGIN;
	GLuint right = SCREEN_WIDTH - SCREEN_MARGIN;
	GLuint bottom = 50 + SCREEN_MARGIN;
	glViewport(left, SCREEN_HEIGHT - bottom, right - left, bottom - top);

	MunitionCounter.Draw(Data, count);
}

void cScreenExtras::DrawMap(cData *Data, const vector<float>& player)
{
	GLuint left = SCREEN_WIDTH - (100 + SCREEN_MARGIN);
	GLuint top = SCREEN_HEIGHT - (100 + SCREEN_MARGIN);
	GLuint right = SCREEN_WIDTH - SCREEN_MARGIN;
	GLuint bottom = SCREEN_HEIGHT - SCREEN_MARGIN;
	glViewport(left, SCREEN_HEIGHT - bottom, right - left, bottom - top);
	
	SceneMap.Draw(Data, player);
}
