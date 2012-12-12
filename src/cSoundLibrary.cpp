#include "cSoundLibrary.h"


cSoundLibrary::cSoundLibrary() {
	FMOD_RESULT result;
	result = FMOD::System_Create(&fmodSystem);
	result = fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
}

cSoundLibrary::~cSoundLibrary() {}

void cSoundLibrary::Init() {
	FMOD_RESULT result;
	result = fmodSystem->createStream("music/test.mp3", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &ambientSound[AMBIENT_HALLELLUJAH]);
	//result = fmodSystem->createStream("music/test.mp3", FMOD_SOFTWARE, 0, &actionSound[AMBIENT_HALLELLUJAH]);
}

void cSoundLibrary::PlayAmbient(int soundId) {
	FMOD_RESULT result;
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, ambientSound[soundId], false, &ambientChannel);
}

void cSoundLibrary::PlayAction(int soundId) {
	FMOD_RESULT result;
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, actionSound[soundId], false, &actionChannel);
}

void cSoundLibrary::Update() {
	fmodSystem->update();
}

void cSoundLibrary::SetAmbientVolume(float volume) {
	ambientChannel->setVolume(volume);
}

void cSoundLibrary::SetActionVolume(float volume) {
	actionChannel->setVolume(volume);
}