/************************************************************************
* Filename:  		Game_Loop.cpp
* Date:      		24/10/2018
* Mod. Date: 		08/11/2018
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
	tObject_List = c_Scene_Manager.GetScene(m_nScene_Id);
	c_Render_Manager.Load_Data(m_nScene_Id, &tObject_List);
	sound.playSong("fionnulas-tale-celtic-flute-music.mp3", FMOD_LOOP_NORMAL, 0.1f);
}


void cGame_Loop::Update()
{
	c_XTime.Signal();
	
	c_Controllers.Update_Controller(m_nScene_Id, &bChange_Scene, &bMove_Bullet, &lhand, &movement);

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
		c_Render_Manager.Unload(&tObject_List);
		m_nScene_Id++;
		if (m_nScene_Id > 3)
			m_nScene_Id = 2;
		tObject_List = c_Scene_Manager.GetScene(m_nScene_Id);
		c_Render_Manager.Load_Data(m_nScene_Id, &tObject_List);
	
		bChange_Scene = false;
	}

	c_Animation_Manager.Animate(c_XTime.Delta(), c_XTime.TotalTimeExact(), &tObject_List);
	c_Render_Manager.Draw(m_nScene_Id, &tObject_List, &bChange_Scene, &bMove_Bullet, lhand, c_Head_Mount);
	c_Head_Mount.VR_Render(c_Camera.GetPosition());
	sound.updateSoundSystem();
}

void cGame_Loop::Clean_Up()
{
}
