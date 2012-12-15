#pragma once

#include "rendermd2.h"
#include "cTexture.h"

enum {
    ANIM_STAND,
    ANIM_RUN,
    ANIM_ATTACK,
    ANIM_PAIN_A,
    ANIM_PAIN_B,
    ANIM_PAIN_C,
    ANIM_JUMP,
    ANIM_FLIP,
    ANIM_SALUTE,
    ANIM_FALLBACK,
    ANIM_WAVE,
    ANIM_POINT,
    ANIM_CROUCH_STAND,
    ANIM_CROUCH_WALK,
    ANIM_CROUCH_ATTACK,
    ANIM_CROUCH_PAIN,
    ANIM_CROUCH_DEATH, 
    ANIM_DEATH_FALLBACK,
    ANIM_DEATH_FALLFORWARD,
    ANIM_DEATH_FALLBACKSLOW,
    ANIM_BOOM
};

class cMD2Model
{
public:
	cMD2Model();
	~cMD2Model();

	bool Load(char *filename);
	void SetAnimation(int anim_state);
	void SetColor(float r,float g,float b);
	void Render(float x,float y,float z);
	void Render(float x,float y,float z,float yaw,float pitch);
	void Render(float x,float y,float z,float yaw,float pitch,float frame,float range,float scale,float speed,float snap,float time_last,float time_base);
	void RenderBoundingBox();
	void RenderBoundingBox(float x,float y,float z,float yaw,float pitch);

	float GetMaxX();
	float GetMaxY();
	float GetMaxZ();

	float GetMinX();
	float GetMinY();
	float GetMinZ();

private:
	md2 *model;
	vec color;
	int anim, frame;
	cTexture tex;
};

