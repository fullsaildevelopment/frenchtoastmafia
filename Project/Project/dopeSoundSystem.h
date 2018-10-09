#pragma once
#include <stdio.h>
#include <iostream>
#include <fmod.hpp>
#include <fmod_errors.h>

class dopeSoundSystem
{
private:
	FMOD::System* System;
	FMOD::Channel* soundChannel;
	FMOD::Channel* threeDSoundChannel;
	FMOD::Sound* songStreaming;
	bool pauseSound = false;
	FMOD::Sound* song;
	FMOD::Sound* soundEffect;
	FMOD::Sound* soundEffectStreaming
public:
	dopeSoundSystem();
	~dopeSoundSystem();
	void playSong(const char* soundName);
	void play3DSound(const char* soundName);
	void pauseNUnPause();
	void stopSong();
};

