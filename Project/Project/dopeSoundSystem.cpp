#include "dopeSoundSystem.h"



dopeSoundSystem::dopeSoundSystem()
{
		//FMOD::System *System;  // this is in the header file
		FMOD_RESULT resulty;
		//FMOD::Sound* song;
		//FMOD::Sound* song2;
		//FMOD::ChannelGroup* channel;
		unsigned int soundVersion;
		FMOD_SPEAKERMODE speakerMODE;
		
	
		//FMOD::System* System = nullptr;   // creates system pointer
	
		resulty = FMOD::System_Create(&System);     // creates system object
	
		if (resulty != FMOD_OK)
		{
			printf("FMOD ERROR!, YOU SHALL PLAY IN SILENCE (&d) &s\n", resulty, FMOD_ErrorString(resulty));
			exit(-1);
			return;
		}
	
		int numDrivers;
		numDrivers = 0;
		System->getNumDrivers(&numDrivers);
	
		if (numDrivers == 0)
		{
			return;
		}
	                               // FMOD_INIT_3D_RIGHTHANDED    or LEFTHANDED
		resulty = System->init(512, FMOD_INIT_NORMAL, 0);  // initilizes FMOD
		//resulty = System->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);   // if i wanted to initialize FMOD studio and low level at the same time
	
		if (resulty != FMOD_OK)
		{
			printf("FMOD ERROR!, YOU SHALL PLAY IN SILENCE (&d) &s\n", resulty, FMOD_ErrorString(resulty));
			exit(-1);
			return;
		}                                                          
}


dopeSoundSystem::~dopeSoundSystem()
{
	System->release();
}

void dopeSoundSystem::playSong(const char* soundName, FMOD_MODE channel_mode)
{
	if (isPlaying == false)
	{
		System->createSound(soundName, FMOD_DEFAULT, NULL, &song);
		//System->createSound("celtic-harp-and-flute-music-call-of-the-ancients.mp3", FMOD_LOOP_NORMAL, NULL, &song2);
		//FMOD::Sound *songStreaming;
		System->createStream(soundName, FMOD_DEFAULT, 0, &songStreaming);

		// system->playSound(FMOD_CHANNEL_FREE, audio, false, 0);  // to play a sound with no looping needed
		//FMOD::Channel *soundChannel;
		System->playSound(song, NULL, false, &soundChannel);
		//resulty = FMOD::System::createStream()
		soundChannel->setMode(channel_mode);  // if i want sounds to cue them call default and play another song
		// FMOD_LOOP_NORMAL
		soundChannel->setLoopCount(-1);
		isPlaying = true;
	}
	else
	{
		return;
	}
}
void dopeSoundSystem::play3DSound(const char* soundName, FMOD_MODE channel_mode)
{
	System->createSound(soundName, FMOD_3D, NULL, &soundEffect);

	System->createStream(soundName, FMOD_DEFAULT, 0, &soundEffectStreaming);

	System->playSound(soundEffect, NULL, false, &threeDSoundChannel);

	threeDSoundChannel->setMode(channel_mode);   // if this doesn't work well makea whole new class for just 3D sounds initialize it with 3D_RIGHTHAND
	// FMOD_3D_HEADRELATIVE // plays sound relative to players head
	//FMOD_3D_INVERSEROLLOFF  // All sounds naturally attenuate (fade out) in the real world using a inverse distance attenuation
	//FMOD_3D_LINEARROLLOFF   // All sounds naturally attenuate (fade out) in the real world using a linear distance attenuation
	// set3DSettings you can use to change the mindistance/ distance factor, doppler effect, rolloff scale
}
void dopeSoundSystem::pauseNUnPause()
{
	if (isPlaying == true)
	{
		soundChannel->getPaused(&pauseSound);
		soundChannel->setPaused(!pauseSound);
	}
	else
	{
		return;
	}
}
void dopeSoundSystem::stopSong()
{
	if (isPlaying == true)
	{
		soundChannel->stop();

		isPlaying = false;
	}
	else
	{
		return;
	}
}

void dopeSoundSystem::setSoundVelocity(float posX, float prevX, float posY, float prevY, float posZ, float prevZ, double deltaTime)
{
	float velocityX;
	float velocityY;
	float velocityZ;

	velocityX = (posX - prevX) * 1000 / deltaTime;
	velocityY = (posY - prevY) * 1000 / deltaTime;
	velocityZ = (posZ - prevZ) * 1000 / deltaTime;
}
void dopeSoundSystem::set3DSoundSettings(float doppler_Scale, float distance_ScaleFac, float rolloff_Scale)
{
	System->set3DSettings(doppler_Scale, distance_ScaleFac, rolloff_Scale);
}
void dopeSoundSystem::updateSoundSystem()
{
	System->update();
}
void dopeSoundSystem::muteAudio()
{
	if (isPlaying == true)
	{
		soundChannel->getMute(&muteSound);
		soundChannel->setMute(!muteSound);
	}
	else
	{
		return;
	}
}
void dopeSoundSystem::playSoundEffect(const char* soundName, FMOD_MODE channel_mode)
{
	System->createSound(soundName, FMOD_DEFAULT, NULL, &soundEffect);
	//System->createSound("celtic-harp-and-flute-music-call-of-the-ancients.mp3", FMOD_LOOP_NORMAL, NULL, &song2);
	//FMOD::Sound *songStreaming;
	System->createStream(soundName, FMOD_DEFAULT, 0, &soundEffectStreaming);

	// system->playSound(FMOD_CHANNEL_FREE, audio, false, 0);  // to play a sound with no looping needed
	//FMOD::Channel *soundChannel;
	System->playSound(soundEffect, NULL, false, &soundEffectChannel);
	//resulty = FMOD::System::createStream()
	soundEffectChannel->setMode(channel_mode);  // if i want sounds to cue them call default and play another song
	// FMOD_LOOP_NORMAL
	soundEffectChannel->setLoopCount(-1);
}

