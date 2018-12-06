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
#include "Offset_Matrix.h"
#include "Controllers.h"
#include "Head_Mount.h"
#include "Graphic_Setup.h"
#include "Render_Manager.h"
#include "Scene_Manager.h"
#include "VR_Setup.h"
#include "XTime.h"
#include "dopeSoundSystem.h"
#include "AI.h"

class cGame_Loop
{
private:
	cAnimation_Manager c_Animation_Manager;
	cControllers c_Controllers;
	cGraphics_Setup *c_Graphics_Setup;
	cHead_Mount c_Head_Mount;
	cOffset_Matrix c_Offset_Matrix;
	cRender_Manager c_Render_Manager;
	cScene_Manager c_Scene_Manager;
	cVR_Setup *c_VR_Setup;
	XTime c_XTime;
	dopeSoundSystem sound;
	AI c_AI;

	int m_nScene_Id;
	bool bChange_Scene = false;
	bool bMove_Bullet = false;
	bool bReset_Offset = false;

	tScene_Objects tPersonal_Object_List, tWorld_Object_List;
	tFloat4 movement = { 0.0f, 0.0f, 0.0f, 0.0f };

public:
	cGame_Loop();
	~cGame_Loop();

	void Initialize(cGraphics_Setup* _gsetup, cVR_Setup* _vsetup);
	void Setup();
	void Update();
	void Clean_Up();
};