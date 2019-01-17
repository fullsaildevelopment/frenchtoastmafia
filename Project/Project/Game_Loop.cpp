/************************************************************************
* Filename:  		Game_Loop.cpp
* Date:      		24/10/2018
* Mod. Date: 		12/12/2018
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
		c_Player.setPosition4x4(c_Head_Mount.Get_CurrentLook(c_Offset_Matrix.GetPosition4x4()));
		c_Player.setHeading(c_Head_Mount.Get_CurrentLook(c_Offset_Matrix.GetPosition4x4()).tZ);
		c_Dragon.setPosition4x4(tWorld_Object_List.fWorld_Matrix[2]);
		c_Dragon_Fireball.setPosition4x4(tWorld_Object_List.fWorld_Matrix[3]);
		c_AI.setIsHit(false);
		if (bMove_Bullet)
		{
			xmf_in = tFloat4x4_to_XMFLOAT4x4(tWorld_Object_List.fWorld_Matrix[4]);
			xmm_in = XMLoadFloat4x4(&xmf_in);
			xmm_in = XMMatrixMultiply(XMMatrixTranslation(0.0f, 0.0f, -5.0f), xmm_in);
			XMStoreFloat4x4(&xmf_out, xmm_in);
			c_Player_Fireball.setPosition4x4(XMFLOAT4x4_to_tFloat4x4(xmf_out));
			tWorld_Object_List.fWorld_Matrix[4] = c_Player_Fireball.getPosition4x4();
		}
		else
		{
			xmf_in = tFloat4x4_to_XMFLOAT4x4(c_Head_Mount.Get_CurrentLook(c_Offset_Matrix.GetPosition4x4()));
			xmm_in = XMLoadFloat4x4(&xmf_in);
			xmm_in = XMMatrixMultiply(XMMatrixTranslation(0.0f, 0.0f, -1.0f), xmm_in);
			XMStoreFloat4x4(&xmf_out, xmm_in);
			c_Player_Fireball.setPosition4x4(XMFLOAT4x4_to_tFloat4x4(xmf_out));
			tWorld_Object_List.fWorld_Matrix[4] = c_Player_Fireball.getPosition4x4();
		}

		// Physics
		tAABB_Player.center = c_Player.getPosition4().fXYZ;
		tAABB_Player.extents = tFloat3{ 3.0f, 3.0f, 3.0f };

		tAABB_Player_Fireball.center = c_Player_Fireball.getPosition4().fXYZ;
		tAABB_Player_Fireball.extents = tFloat3{ 0.2f, 0.13f, 0.2f };

		tAABB_Dragon.center = c_Dragon.getPosition4().fXYZ;
		tAABB_Dragon.extents = tFloat3{ 250.0f, 400.0f, 250.0f };

		tAABB_Dragon_Fireball.center = tWorld_Object_List.fWorld_Matrix[3].tW.fXYZ;
		tAABB_Dragon_Fireball.extents = tFloat3{ 0.2f, 0.13f, 0.2f };

		// Collisions
		if (t_Collisions.Detect_AABB_To_AABB(tAABB_Player, tAABB_Dragon_Fireball) && c_Dragon_Fireball.getIsActive())
		{
			c_Dragon_Fireball.setIsActive(false);
			c_Player.setHealth(-10);
			tWorld_Object_List.fWorld_Matrix[3].tW.fY = 500;
			sound.playSoundEffect("Pain-SoundBible.com-1883168362.mp3", FMOD_DEFAULT, 0.7f);
			if (c_Player.getHealth() <= 0)
				c_Player.setIsAlive(false);
		}

		if (t_Collisions.Detect_AABB_To_AABB(tAABB_Dragon, tAABB_Player_Fireball) && c_Player_Fireball.getIsActive())
		{
			tWorld_Object_List.currAnim[2] = 1;
			//c_Animation_Manager.resetTime();
			dragon_hit = true;
			//dragon_hit = c_AI.setIsHit(true);
			//dragon_hit = c_AI.getIsHit();
			c_Player_Fireball.setIsActive(false);
			c_AI.setIsHit(true);
			c_Dragon.setHealth(-10);
			c_Render_Manager.set_particle_array(p.get_particles());
			p.create_particles(dragon_blast_color, c_XTime.Delta(), dragon_blast_acceleration, dragon_blast_kill, dragon_hit);
			c_Player_Fireball.setIsActive(false);

			if (c_Player.getHealth() <= 0)
				c_Player.setIsAlive(false);

			bMove_Bullet = false;
		}
		if (dragon_hit == true)
			timeCheck += 1;
		if (timeCheck > 75)
		{
			dragon_hit = false;
			timeCheck = 0;
		}
		if ((!c_Player.getIsAlive() || !c_Dragon.getIsAlive()) && m_nScene_Id == 2)
			bChange_Scene = true;
	}

	// Trackpad movement
	if (movement.fX > 0.0f || movement.fY > 0.0f || movement.fZ > 0.0f || movement.fW > 0.0f)
		c_Offset_Matrix.Update_Offset(c_XTime.Delta(), c_Head_Mount.Get_mat4HMDPose(), movement);

	// Controller Inputs
	c_Controllers.Update_Controller(m_nScene_Id, &bChange_Scene, &bMove_Bullet, &bReset_Offset, &movement, c_Offset_Matrix.GetPosition4x4());

	// Player Fireball
	if (c_Player_Fireball.getPosition4().fX < -600 || c_Player_Fireball.getPosition4().fX > 600 || c_Player_Fireball.getPosition4().fY < -50 || c_Player_Fireball.getPosition4().fY > 500 || c_Player_Fireball.getPosition4().fZ < -600 || c_Player_Fireball.getPosition4().fZ > 600)
		bMove_Bullet = false;

	if (bMove_Bullet)
	{
		if (!c_Player_Fireball.getIsActive())
			sound.playSoundEffect("Large Fireball-SoundBible.com-301502490.mp3", FMOD_DEFAULT, 0.6f);

		c_Player_Fireball.setIsActive(true);
	}
	else
		c_Player_Fireball.setIsActive(false);

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
		{
			m_nScene_Id = 2;
			c_Player.setIsAlive(true);
			c_Player.setHealth(100);
			c_Dragon.setIsAlive(true);
			c_Dragon.setHealth(100);
		}
		tWorld_Object_List = c_Scene_Manager.Get_World_Scene(m_nScene_Id);
		c_Render_Manager.Load_Data(m_nScene_Id, &tWorld_Object_List);

		c_Offset_Matrix.ResetPosition();
		c_AI.resetHP();
		bMove_Bullet = false;
		bChange_Scene = false;
	}

	// Renders
	if (m_nScene_Id == 2)
	{
		//c_AI.resolveDragonState(&tWorld_Object_List, c_Offset_Matrix.GetPosition4x4(), c_XTime.Delta());
		c_AI.resolveDragonState(&tWorld_Object_List, c_Player.getPosition4x4(), c_XTime.Delta(), &c_Dragon_Fireball);
	}
	c_Animation_Manager.Animate(c_XTime.Delta(), c_XTime.TotalTimeExact(), &tWorld_Object_List);
	c_Render_Manager.set_particle_array(p.get_particles());   // JUST ADDED THIS
	p.create_particles(fireball_color, c_XTime.Delta(), fireball_acceleration, fireball_kill, dragon_hit);
	c_Render_Manager.Draw_World(m_nScene_Id, &tWorld_Object_List, &bChange_Scene, &bMove_Bullet, c_Head_Mount, c_Offset_Matrix.GetPosition4x4(), c_XTime.TotalTime(), c_Player_Fireball, &c_AI, dragon_hit, c_XTime.Delta());
	c_Render_Manager.Draw_Personal(&tPersonal_Object_List, c_Head_Mount, c_Controllers, c_Offset_Matrix.GetPosition4x4(), c_Player_Fireball);
	c_Head_Mount.VR_Render();

	// Other updates
	sound.updateSoundSystem();
}

void cGame_Loop::Clean_Up()
{
}
