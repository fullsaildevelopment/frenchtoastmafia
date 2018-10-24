#pragma once

#include "dopeSoundSystem.h"
#include "Render_Manager.h"
#include "VR.h"

class cGame_Loop
{
private:
	HWND hWnd;
	dopeSoundSystem sound;
	cRender_Manager cRender;
	cVR c_VR;

public:
	cGame_Loop(HWND _hWnd);
	~cGame_Loop();

	void Setup();
	void Update();
	void Clean_Up();
};