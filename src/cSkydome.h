#pragma once

#include "cVBO.h"
#include "cData.h"

#define SKY_SIZE 1.0f

class cSkydome : public cVBO {
public:
	cSkydome(void);
	~cSkydome(void);

	void Init();
	void Render(cData * data);
	void SetTexId(int id);
private:
	int texId;
};

