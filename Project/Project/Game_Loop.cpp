#include "Game_Loop.h"



cGame_Loop::cGame_Loop()
{
}


cGame_Loop::~cGame_Loop()
{
}

void cGame_Loop::Initialize(cGraphics_Setup* _setup)
{
	c_Render_Manager.Initialize(_setup);
	c_VR.Initialize(_setup);
	nScene_Id = 2;
}

void cGame_Loop::Setup()
{
	t_Object_List = c_Scene_Manager.GetScene(nScene_Id);
	c_Render_Manager.Load(nScene_Id, &t_Object_List);
	//sound.playSong("fionnulas-tale-celtic-flute-music.mp3", FMOD_LOOP_NORMAL);
}


void cGame_Loop::Update(cGraphics_Setup* _setup)
{
	c_Render_Manager.Draw(nScene_Id, t_Object_List);
	c_VR.VR_Render();
	_setup->update_controller();
	//c_VR.update_controller();
	//sound.updateSoundSystem();
}

void cGame_Loop::Clean_Up()
{
}
