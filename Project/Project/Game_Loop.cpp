/************************************************************************
* Filename:  		Game_Loop.cpp
* Date:      		24/10/2018
* Mod. Date: 		03/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Main Loop of the Game, System Initialization, System Procedure
*************************************************************************/

#include "Game_Loop.h"


cGame_Loop::cGame_Loop()
{
}

cGame_Loop::~cGame_Loop()
{
}

void cGame_Loop::Initialize(cGraphics_Setup* _gsetup, cVR_Setup* _vsetup)
{
	c_Graphics_Setup = _gsetup;
	c_VR_Setup = _vsetup;
	c_Head_Mount.Initialize(_gsetup, _vsetup);
	c_Controllers.Initialize(_vsetup);
	c_Render_Manager.Initialize(_gsetup);
	c_Camera.Initialize();
	c_Head_Mount.SetupCameras();
	c_Head_Mount.UpdateHMDMatrixPose(c_Camera.GetPosition());
	c_XTime.Restart();
	m_nScene_Id = 0;
}

void cGame_Loop::Setup()
{
	tPersonal_Object_List = c_Scene_Manager.Get_Personal_Scene();
	tWorld_Object_List = c_Scene_Manager.Get_World_Scene(m_nScene_Id);
	c_Render_Manager.Load_Data(2, &tPersonal_Object_List);
	c_Render_Manager.Load_Data(m_nScene_Id, &tWorld_Object_List);
	sound.playSong("fionnulas-tale-celtic-flute-music.mp3", FMOD_LOOP_NORMAL, 0.1f);
}


void cGame_Loop::Update()
{
	c_XTime.Signal();
	
	c_Controllers.Update_Controller(m_nScene_Id, &bChange_Scene, &bMove_Bullet, &movement, c_Camera.GetPosition());

	if (movement.fX == 1.0f)
		c_Camera.Translation(tFloat4{ 0.0f, 0.0f, -5.0f * (float)c_XTime.Delta(), 0.0f });

	if (movement.fY == 1.0f)
		c_Camera.Translation(tFloat4{ 5.0f * (float)c_XTime.Delta(), 0.0f, 0.0f, 1.0f });

	if (movement.fZ == 1.0f)
		c_Camera.Translation(tFloat4{ 0.0f, 0.0f, 5.0f * (float)c_XTime.Delta(), 0.0f });

	if (movement.fW == 1.0f)
		c_Camera.Translation(tFloat4{ -5.0f * (float)c_XTime.Delta(), 0.0f, 0.0f, 1.0f });

	if (bChange_Scene) 
	{
		c_Render_Manager.Unload(&tWorld_Object_List);
		m_nScene_Id++;
		if (m_nScene_Id > 3)
			m_nScene_Id = 2;
		tWorld_Object_List = c_Scene_Manager.Get_World_Scene(m_nScene_Id);
		c_Render_Manager.Load_Data(m_nScene_Id, &tWorld_Object_List);
	
		bChange_Scene = false;
	}

	c_Animation_Manager.Animate(c_XTime.Delta(), c_XTime.TotalTimeExact(), &tWorld_Object_List);
	c_Render_Manager.Draw_World(m_nScene_Id, &tWorld_Object_List, &bChange_Scene, &bMove_Bullet, c_Head_Mount);
	c_Render_Manager.Draw_Personal(&tPersonal_Object_List, c_Head_Mount, c_Controllers);
	c_Head_Mount.VR_Render(c_Camera.GetPosition());
	sound.updateSoundSystem();
}

void cGame_Loop::Clean_Up()
{
}
