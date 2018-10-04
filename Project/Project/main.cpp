#include <stdio.h>
#include <iostream>
#include <fmod.hpp>

FMOD_RESULT Studio::System::initialize
(
	int maxchannels,
	FMOD_STUDIO_INITFLAGS studioflags,
	FMOD_INITFLAGS flags,
	void *extradriverdata
);

int main()
{
	FMOD_RESULT resulty;

	FMOD::System* System = nullptr;   // creates system pointer

	resulty = FMOD::System_Create(&System);     // creates system object

	if (resulty != FMOD_OK)
	{
		printf("FMOD ERROR!, YOU SHALL PLAY IN SILENCE (&d) &s\n", resulty, FMOD_ERRORCALLBACK_INFO(resulty));
		exit(-1);
	}

	resulty = System->init(512, FMOD_INIT_NORMAL, 0);  // initilizes FMOD

	if (resulty != FMOD_OK)
	{
		printf("FMOD ERROR!, YOU SHALL PLAY IN SILENCE (&d) &s\n", resulty, FMOD_ERRORCALLBACK_INFO(resulty));
		exit(-1);
	}
	//resulty = FMOD::System::createStream()

	return 0;
}
