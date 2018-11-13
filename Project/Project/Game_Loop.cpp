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

void cGame_Loop::Initialize(cGraphics_Setup* _setup)
{
	//c_Graphics_Setup.Initialize();
	c_Graphics_Setup = _setup;
	c_Render_Manager.Initialize(_setup);
	c_VR.Initialize(_setup);
	c_XTime.Restart();
	m_nScene_Id = 2;
}

void cGame_Loop::Setup()
{
	tObject_List = c_Scene_Manager.GetScene(m_nScene_Id);
	c_Render_Manager.Load_Data(m_nScene_Id, &tObject_List);
	sound.playSong("fionnulas-tale-celtic-flute-music.mp3", FMOD_LOOP_NORMAL);
}


void cGame_Loop::Update()
{
	c_XTime.Signal();

	bool bEnd_Game;

	bEnd_Game = false;

	//while (!bEnd_Game)
	//{
	c_Graphics_Setup->handle_input(c_XTime.Delta());

	c_Animation_Manager.Animate(c_XTime.Delta(), c_XTime.TotalTimeExact(), &tObject_List);
	c_Render_Manager.Draw(m_nScene_Id, &tObject_List);
	c_VR.VR_Render();
	//}

	c_VR.update_controller();
	sound.updateSoundSystem();
}

void cGame_Loop::Clean_Up()
{
}
