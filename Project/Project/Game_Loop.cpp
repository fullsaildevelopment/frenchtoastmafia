/************************************************************************
* Filename:  		Game_Loop.cpp
* Date:      		24/10/2018
* Mod. Date: 		11/12/2018
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
	c_Offset_Matrix.Initialize();
	c_Head_Mount.SetupCameras();
	c_Head_Mount.UpdateHMDMatrixPose();
	c_XTime.Restart();
	m_nScene_Id = 2;
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
	if (m_nScene_Id == 2)
	{
		// Gameplay
		c_Player.setPosition(c_Offset_Matrix.GetPosition4());
		c_Player.setHeading(c_Offset_Matrix.GetHeading());
		c_Player_Fireball.setPosition(c_Offset_Matrix.GetPosition4());
		c_Player_Fireball.setHeading(c_Offset_Matrix.GetHeading());

		// Physics
		tAABB_Player.center = c_Player.getPosition().fXYZ;
		tAABB_Player.center.fY -= 3;
		tAABB_Player.extents = tFloat3{ 1.0f, 3.0f, 1.0f };

		tAABB_Player_Fireball.center = c_Player_Fireball.getPosition().fXYZ;
		tAABB_Player_Fireball.extents = tFloat3{ 0.2f, 0.13f, 0.2f };

		tAABB_Dragon.center = tWorld_Object_List.fWorld_Matrix[2].tW.fXYZ;
		tAABB_Dragon.extents = tFloat3{ 175.0f, 90.0f, 170.0f };

		tAABB_Dragon_Fireball.center = tWorld_Object_List.fWorld_Matrix[3].tW.fXYZ;
		tAABB_Dragon_Fireball.extents = tFloat3{ 0.2f, 0.13f, 0.2f };

		// Collisions
		if (t_Collisions.Detect_AABB_To_AABB(tAABB_Player, tAABB_Dragon_Fireball))
			c_Player.TakeDamage(10);
		
		if (t_Collisions.Detect_AABB_To_AABB(tAABB_Dragon, tAABB_Player_Fireball))
			c_Dragon.TakeDamage(10);

		if ((c_Player.getHealth() <= 0 || c_Dragon.getHealth() <= 0) && m_nScene_Id == 2)
			m_nScene_Id++;
	}

	// Trackpad movement
	if (movement.fX > 0.0f || movement.fY > 0.0f || movement.fZ > 0.0f || movement.fW > 0.0f)
		c_Offset_Matrix.Update_Offset(c_XTime.Delta(), c_Head_Mount.Get_mat4HMDPose(), movement);

	// Controller Inputs
	c_Controllers.Update_Controller(m_nScene_Id, &bChange_Scene, &bMove_Bullet, &bReset_Offset, &movement, c_Offset_Matrix.GetPosition4x4());

	// Special (Reset Position)
	if (bReset_Offset && m_nScene_Id != 2)
	{
		c_Offset_Matrix.ResetPosition();
		bReset_Offset = false;
	}

	// Scene Transitions
	if (bChange_Scene) 
	{
		c_Render_Manager.Unload(&tWorld_Object_List);
		m_nScene_Id++;
		if (m_nScene_Id > 3)
			m_nScene_Id = 2;
		tWorld_Object_List = c_Scene_Manager.Get_World_Scene(m_nScene_Id);
		c_Render_Manager.Load_Data(m_nScene_Id, &tWorld_Object_List);

		c_Offset_Matrix.ResetPosition();
		bChange_Scene = false;
	}

	// Renders
	if (m_nScene_Id == 2)
	{
		c_AI.resolveDragonState(&tWorld_Object_List, c_Offset_Matrix.GetPosition4x4(), c_XTime.Delta());
	}
	c_Animation_Manager.Animate(c_XTime.Delta(), c_XTime.TotalTimeExact(), &tWorld_Object_List);
	p.create_particles(color, c_XTime.Delta(), acceleration);  // needs to be called when a fireball is thrown
	c_Render_Manager.set_particle_array(p.get_particles());   // JUST ADDED THIS
	c_Render_Manager.Draw_World(m_nScene_Id, &tWorld_Object_List, &bChange_Scene, &bMove_Bullet, c_Head_Mount, c_Offset_Matrix.GetPosition4x4(), c_XTime.TotalTime());
	c_Render_Manager.Draw_Personal(&tPersonal_Object_List, c_Head_Mount, c_Controllers, c_Offset_Matrix.GetPosition4x4(), c_Player_Fireball);
	c_Head_Mount.VR_Render();

	// Other updates
	sound.updateSoundSystem();
}

void cGame_Loop::Clean_Up()
{
}
