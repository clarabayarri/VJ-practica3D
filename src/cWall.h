#pragma once

#include "cVBO.h"
#include "cFloor.h"
#include "cData.h"

#define WALL_HEIGHT 0.8f

class cWall : public cVBO {
public:
	cWall(void);
	~cWall(void);

	void Init(cFloor * floor);
	void Render(cData * data);
	void RenderPhysical();
};

