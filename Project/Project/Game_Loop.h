/************************************************************************
* Filename:  		Game_Loop.h
* Date:      		24/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Main Loop of the Game, System Initialization, System Procedure
*************************************************************************/
#pragma once

#include "Animation_Manager.h"
#include "Graphic_Setup.h"
#include "Render_Manager.h"
#include "Scene_Manager.h"
#include "VR.h"
#include "XTime.h"
#include "dopeSoundSystem.h"
#include "Particle.h"

class cGame_Loop
{
private:
	cAnimation_Manager c_Animation_Manager;
	cGraphics_Setup *c_Graphics_Setup;
	cRender_Manager c_Render_Manager;
	cScene_Manager c_Scene_Manager;
	cVR c_VR;
	tScene_Objects tObject_List;
	XTime c_XTime;
	dopeSoundSystem sound;

	int m_nScene_Id;
	bool bChange_Scene = false;
	bool bMove_Bullet = false;

	tFloat3 lhand;

	Particle p;

public:
	cGame_Loop();
	~cGame_Loop();

	void Initialize(cGraphics_Setup* _setup);
	void Setup();
	void Update();
	void Clean_Up();
};