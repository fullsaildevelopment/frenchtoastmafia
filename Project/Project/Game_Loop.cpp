#include "Game_Loop.h"



cGame_Loop::cGame_Loop(HWND _hWnd)
{
	hWnd = _hWnd;
}


cGame_Loop::~cGame_Loop()
{
}

void cGame_Loop::Setup()
{
	c_VR.Initialize(hWnd);
	cRender.Initialize();
	sound.playSong("fionnulas-tale-celtic-flute-music.mp3", FMOD_LOOP_NORMAL);
}

void cGame_Loop::Update()
{
	sound.updateSoundSystem();
}

void cGame_Loop::Clean_Up()
{
}
