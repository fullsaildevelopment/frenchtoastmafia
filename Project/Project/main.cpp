//#include <stdio.h>
#include <iostream>
#include "dopeSoundSystem.h"
#include <Windows.h>

dopeSoundSystem sound;

int main()
{
	//sound.playSong("fionnulas-tale-celtic-flute-music.mp3");
	while (true)
	{
		//FMOD::System::update();

		if (GetAsyncKeyState('Z'))
		{
			sound.playSong("fionnulas-tale-celtic-flute-music.mp3");
		}

		if (GetAsyncKeyState('X'))
		{
			sound.pauseNUnPause();
		}

		if (GetAsyncKeyState('C'))
		{
			sound.stopSong();
		}
		
	}

	return 0;
}
