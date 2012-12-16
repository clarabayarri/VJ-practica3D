#pragma once

#pragma comment(lib,"MD2Model")

#include "Globals.h"
#include "cMD2Model.h"
using namespace std;

/***** MD2 Models constants ****/
const int animlist[21][3] = 
{
    // first, last, fps
    {   0,  39,  9 },   // STAND
    {  40,  45, 10 },   // RUN
    {  46,  53, 10 },   // ATTACK
    {  54,  57,  7 },   // PAIN_A
    {  58,  61,  7 },   // PAIN_B
    {  62,  65,  7 },   // PAIN_C
    {  66,  71,  7 },   // JUMP
    {  72,  83,  7 },   // FLIP
    {  84,  94,  7 },   // SALUTE
    {  95, 111, 10 },   // FALLBACK
    { 112, 122,  7 },   // WAVE
    { 123, 134,  6 },   // POINT
    { 135, 153, 10 },   // CROUCH_STAND
    { 154, 159,  7 },   // CROUCH_WALK
    { 160, 168, 10 },   // CROUCH_ATTACK
    { 196, 172,  7 },   // CROUCH_PAIN
    { 173, 177,  5 },   // CROUCH_DEATH
    { 178, 183,  7 },   // DEATH_FALLBACK
    { 184, 189,  7 },   // DEATH_FALLFORWARD
    { 190, 197,  7 },   // DEATH_FALLBACKSLOW
    { 198, 198,  5 },   // BOOM
};

class cAnimatedCharacter
{
public:
	float x;
	float z;
	float orientationAngle;
	float radius;

	cAnimatedCharacter(void);
	~cAnimatedCharacter(void);

	void SetXZ(float setx, float setz);
	void SetX(float setx);
	void SetZ(float setz);
	void SetModel(char * m);
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void RotateLeft();
	void RotateRight();
	void SetOrientation(float pitch);

	virtual void Draw();
	virtual void DrawPhysical();

	void Stop();
	
	virtual float GetCurrentMinX();
	virtual float GetMinY();
	virtual float GetCurrentMinZ();
	virtual float GetCurrentMaxX();
	virtual float GetMaxY();
	virtual float GetCurrentMaxZ();
	bool CollidesCharacter(float x0, float z0, float radius0);

	std::vector<float> GetPosition();

protected:
	void SetState(int st);
	int state;
	cMD2Model model;
	float animation_frame;
};

