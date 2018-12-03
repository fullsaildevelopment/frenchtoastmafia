/************************************************************************
* Filename:  		Game_Loop.h
* Date:      		24/10/2018
* Mod. Date: 		03/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Main Loop of the Game, System Initialization, System Procedure
*************************************************************************/
#pragma once

#include "Animation_Manager.h"
#include "Camera.h"
#include "Controllers.h"
#include "Head_Mount.h"
#include "Graphic_Setup.h"
#include "Render_Manager.h"
#include "Scene_Manager.h"
#include "VR_Setup.h"
#include "XTime.h"
#include "dopeSoundSystem.h"

class cGame_Loop
{
private:
	cAnimation_Manager c_Animation_Manager;
	cCamera c_Camera;
	cControllers c_Controllers;
	cGraphics_Setup *c_Graphics_Setup;
	cHead_Mount c_Head_Mount;
	cRender_Manager c_Render_Manager;
	cScene_Manager c_Scene_Manager;
	cVR_Setup *c_VR_Setup;
	tScene_Objects tObject_List;
	XTime c_XTime;
	dopeSoundSystem sound;

	int m_nScene_Id;
	bool bChange_Scene = false;
	bool bMove_Bullet = false;

	tFloat3 lhand;
	tFloat4 movement = { 0.0f, 0.0f, 0.0f, 0.0f };

public:
	cGame_Loop();
	~cGame_Loop();

	void Initialize(cGraphics_Setup* _gsetup, cVR_Setup* _vsetup);
	void Setup();
	void Update();
	void Clean_Up();
};