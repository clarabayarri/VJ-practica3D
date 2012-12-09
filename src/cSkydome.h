#pragma once

#include "cVBO.h"
#include "cData.h"
#include "Constants.h"

class cSkydome : public cVBO {
public:
	cSkydome(void);
	~cSkydome(void);

	void Init();
	void Render(cData * data);
};

