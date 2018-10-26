#include "Game_Loop.h"



cGame_Loop::cGame_Loop()
{
}


cGame_Loop::~cGame_Loop()
{
}

void cGame_Loop::Initialize(cGraphics_Setup _setup)
{
	c_Graphics_Setup = &_setup;
}

void cGame_Loop::Setup()
{
	c_Render_Manager.Initialize(c_Graphics_Setup);
	//sound.playSong("fionnulas-tale-celtic-flute-music.mp3", FMOD_LOOP_NORMAL);
}


void cGame_Loop::Update()
{
	//sound.updateSoundSystem();
}

void cGame_Loop::Clean_Up()
{
}
