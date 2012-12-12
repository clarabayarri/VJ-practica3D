
#pragma once

#pragma comment(lib,"fmodex_vc")

#include "fmod.hpp"
#include "fmod_errors.h"
#include "Constants.h"

class cSoundLibrary
{
public:
	cSoundLibrary();
	~cSoundLibrary();

	void Init();
	void Update();

	void PlayAmbient(int soundId);
	void PlayAction(int soundId);

	void SetAmbientVolume(float volume);
	void SetActionVolume(float volume);

private:
	FMOD::System* fmodSystem;

	FMOD::Sound	* ambientSound[NUM_AMBIENT_SOUNDS];
	FMOD::Sound	* actionSound[NUM_ACTION_SOUNDS];

	FMOD::Channel * ambientChannel;
	FMOD::Channel * actionChannel;
};

