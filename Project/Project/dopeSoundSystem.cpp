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
	                                                                // FMOD_LOOP_NORMAL
		//System->createSound("fionnulas-tale-celtic-flute-music.mp3", FMOD_DEFAULT, NULL, &song);
		////System->createSound("celtic-harp-and-flute-music-call-of-the-ancients.mp3", FMOD_LOOP_NORMAL, NULL, &song2);
		//FMOD::Sound *songStreaming;
		//System->createStream("fionnulas-tale-celtic-flute-music.mp3", FMOD_DEFAULT, 0, &songStreaming);

		//// system->playSound(FMOD_CHANNEL_FREE, audio, false, 0);  // to play a sound with no looping needed
		//FMOD::Channel *soundChannel;
		//System->playSound(song, NULL, false, &soundChannel);
		////resulty = FMOD::System::createStream()

		/*soundChannel->setMode(FMOD_LOOP_NORMAL);
		soundChannel->setLoopCount(-1);*/

		//bool pauseSound;
		//pauseSound = false;

		//soundChannel->getPaused(&pauseSound);
		//soundChannel->setPaused(!pauseSound);
		
		//System->update(); // will want to call in the games main loop
		//System->release(); // will want to call when closing the game
}


dopeSoundSystem::~dopeSoundSystem()
{
	System->release();
}

void dopeSoundSystem::playSong(const char* soundName)
{
	System->createSound(soundName, FMOD_DEFAULT, NULL, &song);
	//System->createSound("celtic-harp-and-flute-music-call-of-the-ancients.mp3", FMOD_LOOP_NORMAL, NULL, &song2);
	//FMOD::Sound *songStreaming;
	System->createStream(soundName, FMOD_DEFAULT, 0, &songStreaming);

	// system->playSound(FMOD_CHANNEL_FREE, audio, false, 0);  // to play a sound with no looping needed
	//FMOD::Channel *soundChannel;
	System->playSound(song, NULL, false, &soundChannel);
	//resulty = FMOD::System::createStream()
	soundChannel->setMode(FMOD_LOOP_NORMAL);  // if i want sounds to cue them call default and play another song
	soundChannel->setLoopCount(-1);
}
void dopeSoundSystem::play3DSound(const char* soundName)
{
	System->createSound(soundName, FMOD_3D, NULL, &soundEffect);

	System->createStream(soundName, FMOD_DEFAULT, 0, &soundEffectStreaming);

	System->playSound(soundEffect, NULL, false, &threeDSoundChannel);

	threeDSoundChannel->setMode(FMOD_3D_HEADRELATIVE);
	//FMOD_3D_INVERSEROLLOFF  // All sounds naturally attenuate (fade out) in the real world using a inverse distance attenuation
	//FMOD_3D_LINEARROLLOFF
	// set3DSettings you can use to change the mindistance/ distance factor, doppler effect, rolloff scale
}
void dopeSoundSystem::pauseNUnPause()
{
	soundChannel->getPaused(&pauseSound);
	soundChannel->setPaused(!pauseSound);
}
void dopeSoundSystem::stopSong()
{
	soundChannel->stop();
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

