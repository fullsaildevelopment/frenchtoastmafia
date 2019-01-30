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
	m_nScene_Id = 0;
}

void cGame_Loop::Setup()
{
	tPersonal_Object_List = c_Scene_Manager.Get_Personal_Scene();
	c_Render_Manager.Load_Data(2, tPersonal_Object_List);

	tWorld_Object_List = c_Scene_Manager.Get_World_Scene(m_nScene_Id);
	c_Render_Manager.Load_Data(m_nScene_Id, tWorld_Object_List);

	tSpell_Book = c_Scene_Manager.Get_Spell_Book();
	c_Render_Manager.Load_Data(9, tSpell_Book);

	tFireball_Nodes = c_Scene_Manager.Get_Spell_Node_Fireball();
	c_Render_Manager.Load_Data(9, tFireball_Nodes);

	tIcebolt_Nodes = c_Scene_Manager.Get_Spell_Node_Icebolt();
	c_Render_Manager.Load_Data(9, tIcebolt_Nodes);

	tShield_Nodes = c_Scene_Manager.Get_Spell_Node_Shield();
	c_Render_Manager.Load_Data(9, tShield_Nodes);

	UI_Object_List = c_Scene_Manager.Get_UI();
	c_Render_Manager.Load_Data(9, UI_Object_List);

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
		c_Dragon.setPosition4x4(tWorld_Object_List->fWorld_Matrix[2]);
		c_Dragon_Fireball.setPosition4x4(tWorld_Object_List->fWorld_Matrix[3]);
		c_AI.setIsHit(false);

		xmf_in = tFloat4x4_to_XMFLOAT4x4(c_Head_Mount.Get_CurrentLook(c_Offset_Matrix.GetPosition4x4()));
		xmm_in = XMLoadFloat4x4(&xmf_in);
		xmm_in = XMMatrixMultiply(XMMatrixTranslation(0.0f, 0.0f, -0.75f), xmm_in);
		XMStoreFloat4x4(&xmf_out, xmm_in);
		c_Spell_Book.setPosition4x4(XMFLOAT4x4_to_tFloat4x4(xmf_out));

		if (bMove_Spell_01)
		{
			if (personal_swap_Id.fZ == 1)
				xmf_in = tFloat4x4_to_XMFLOAT4x4(tPersonal_Object_List->fWorld_Matrix[8]);
			else if (personal_swap_Id.fZ == 2)
				xmf_in = tFloat4x4_to_XMFLOAT4x4(tPersonal_Object_List->fWorld_Matrix[9]);
			//else if (personal_swap_Id.fZ == 3)
			//	xmf_in = tFloat4x4_to_XMFLOAT4x4(tPersonal_Object_List->fWorld_Matrix[10]);

			xmm_in = XMLoadFloat4x4(&xmf_in);
			xmm_in = XMMatrixMultiply(XMMatrixTranslation(0.0f, 0.0f, -200.0f * c_XTime.Delta()), xmm_in);
			XMStoreFloat4x4(&xmf_out, xmm_in);
			c_Player_Spell_01.setPosition4x4(XMFLOAT4x4_to_tFloat4x4(xmf_out));

			if (personal_swap_Id.fZ == 1)
				tPersonal_Object_List->fWorld_Matrix[8] = c_Player_Spell_01.getPosition4x4();
			else if (personal_swap_Id.fZ == 2)
				tPersonal_Object_List->fWorld_Matrix[9] = c_Player_Spell_01.getPosition4x4();
			//else if (personal_swap_Id.fZ == 3)
			//	tPersonal_Object_List->fWorld_Matrix[10] = c_Player_Spell_01.getPosition4x4();
		}
		else
		{
			xmf_in = tFloat4x4_to_XMFLOAT4x4(c_Controllers.Get_Left_Hand());
			xmm_in = XMLoadFloat4x4(&xmf_in);
			if (personal_swap_Id.fW != 3)
				xmm_in = XMMatrixMultiply(XMMatrixTranslation(0.2f, 0.125f, -0.3f), xmm_in);
			XMStoreFloat4x4(&xmf_out, xmm_in);
			c_Player_Spell_01.setPosition4x4(XMFLOAT4x4_to_tFloat4x4(xmf_out));

			if (personal_swap_Id.fZ == 1)
				tPersonal_Object_List->fWorld_Matrix[8] = c_Player_Spell_01.getPosition4x4();
			else if (personal_swap_Id.fZ == 2)
				tPersonal_Object_List->fWorld_Matrix[9] = c_Player_Spell_01.getPosition4x4();
			else if (personal_swap_Id.fZ == 3)
				tPersonal_Object_List->fWorld_Matrix[10] = c_Player_Spell_01.getPosition4x4();
		}

		if (bMove_Spell_02)
		{
			if (personal_swap_Id.fW == 1)
				xmf_in = tFloat4x4_to_XMFLOAT4x4(tPersonal_Object_List->fWorld_Matrix[11]);
			else if (personal_swap_Id.fW == 2)
				xmf_in = tFloat4x4_to_XMFLOAT4x4(tPersonal_Object_List->fWorld_Matrix[12]);
			//else if (personal_swap_Id.fW == 3)
			//	xmf_in = tFloat4x4_to_XMFLOAT4x4(tPersonal_Object_List->fWorld_Matrix[13]);

			xmm_in = XMLoadFloat4x4(&xmf_in);
			xmm_in = XMMatrixMultiply(XMMatrixTranslation(0.0f, 0.0f, -200.0f * c_XTime.Delta()), xmm_in);
			XMStoreFloat4x4(&xmf_out, xmm_in);
			c_Player_Spell_02.setPosition4x4(XMFLOAT4x4_to_tFloat4x4(xmf_out));

			if (personal_swap_Id.fW == 1)
				tPersonal_Object_List->fWorld_Matrix[11] = c_Player_Spell_02.getPosition4x4();
			else if (personal_swap_Id.fW == 2)
				tPersonal_Object_List->fWorld_Matrix[12] = c_Player_Spell_02.getPosition4x4();
			//else if (personal_swap_Id.fW == 3)
			//	tPersonal_Object_List->fWorld_Matrix[13] = c_Player_Spell_02.getPosition4x4();
		}
		else
		{
			xmf_in = tFloat4x4_to_XMFLOAT4x4(c_Controllers.Get_Right_Hand());
			xmm_in = XMLoadFloat4x4(&xmf_in);
			//if (personal_swap_Id.fW == 3)
			//	xmm_in = XMMatrixMultiply(XMMatrixTranslation(-0.1f, -0.125f, -0.3f), xmm_in);
			//else
			if (personal_swap_Id.fW != 3)
				xmm_in = XMMatrixMultiply(XMMatrixTranslation(0.2f, 0.125f, -0.3f), xmm_in);
			XMStoreFloat4x4(&xmf_out, xmm_in);
			c_Player_Spell_02.setPosition4x4(XMFLOAT4x4_to_tFloat4x4(xmf_out));

			if (personal_swap_Id.fW == 1)
				tPersonal_Object_List->fWorld_Matrix[11] = c_Player_Spell_02.getPosition4x4();
			else if (personal_swap_Id.fW == 2)
				tPersonal_Object_List->fWorld_Matrix[12] = c_Player_Spell_02.getPosition4x4();
			else if (personal_swap_Id.fW == 3)
				tPersonal_Object_List->fWorld_Matrix[13] = c_Player_Spell_02.getPosition4x4();
		}

		// Physics
		XMFLOAT4X4 xmf_origin, xmf_offset, xmf_out;
		XMMATRIX xmm_origin, xmm_offset, xmm_out;
		tFloat4x4 tOut;

		// AABB
		{
			tAABB_Player.center = c_Player.getPosition4().fXYZ;
			tAABB_Player.center.fY -= 0.5f;
			tAABB_Player.extents = tFloat3{ 0.75f, 1.25f, 0.75f };


			tAABB_Player_Spell_01.center = c_Player_Spell_01.getPosition4().fXYZ;
			tAABB_Player_Spell_01.extents = tFloat3{ 0.2f, 0.13f, 0.2f };

			tAABB_Player_Spell_02.center = c_Player_Spell_02.getPosition4().fXYZ;
			tAABB_Player_Spell_02.extents = tFloat3{ 0.2f, 0.13f, 0.2f };

			tAABB_Player_Shield_01.center = tPersonal_Object_List->fWorld_Matrix[10].tW.fXYZ;
			tAABB_Player_Shield_01.extents = tFloat3{ 1.0f, 0.75f, 1.0f };
						  
			tAABB_Player_Shield_02.center = tPersonal_Object_List->fWorld_Matrix[13].tW.fXYZ;
			tAABB_Player_Shield_02.extents = tFloat3{ 1.0f, 0.75f, 1.0f };

			tAABB_Dragon.center = c_Dragon.getPosition4().fXYZ;
			tAABB_Dragon.extents = tFloat3{ 15.0f, 100.0f, 35.0f };

			tAABB_Dragon_Fireball[0].center = tWorld_Object_List->fFireball_Matrix[0].tW.fXYZ;
			tAABB_Dragon_Fireball[0].extents = tFloat3{ 0.2f, 0.13f, 0.2f };

			tAABB_Dragon_Fireball[1].center = tWorld_Object_List->fFireball_Matrix[1].tW.fXYZ;
			tAABB_Dragon_Fireball[1].extents = tFloat3{ 0.2f, 0.13f, 0.2f };

			tAABB_Dragon_Fireball[2].center = tWorld_Object_List->fFireball_Matrix[2].tW.fXYZ;
			tAABB_Dragon_Fireball[2].extents = tFloat3{ 0.2f, 0.13f, 0.2f };

			tAABB_Left_Hand.center = c_Controllers.Get_Left_Hand().tW.fXYZ;
			tAABB_Left_Hand.extents = tFloat3{ 0.0625f, 0.0625f, 0.15f };

			tAABB_Right_Hand.center = c_Controllers.Get_Right_Hand().tW.fXYZ;
			tAABB_Right_Hand.extents = tFloat3{ 0.0625f, 0.0625f, 0.15f };

			// Spell Book
			{
				// Fireball
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tSpell_Book->fWorld_Matrix[1]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Spell_1.center = tOut.tW.fXYZ;
					tAABB_Spell_1.extents = tFloat3{ 0.0625f, 0.0625f, 0.1f };
				}
				// Fireball

				// Icebolt
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tSpell_Book->fWorld_Matrix[2]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Spell_2.center = tOut.tW.fXYZ;
					tAABB_Spell_2.extents = tFloat3{ 0.0625f, 0.0625f, 0.1f };
				}
				// Icebolt

				// Shield
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tSpell_Book->fWorld_Matrix[3]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Spell_3.center = tOut.tW.fXYZ;
					tAABB_Spell_3.extents = tFloat3{ 0.0625f, 0.0625f, 0.1f };
				}
				// Shield

				// Cancel
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tSpell_Book->fWorld_Matrix[4]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Cancel.center = tOut.tW.fXYZ;
					tAABB_Cancel.extents = tFloat3{ 0.0625f, 0.0625f, 0.1f };
				}
				// Cancel
			}
			// Spell Book

			// Spell Nodes - Fireball
			{
				// Node 1
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tFireball_Nodes->fWorld_Matrix[1]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Fireball_1.center = tOut.tW.fXYZ;
					tAABB_Fireball_1.extents = tFloat3{ 0.03125f, 0.03125f, 0.1f };
				}
				// Node 1

				// Node 2
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tFireball_Nodes->fWorld_Matrix[2]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Fireball_2.center = tOut.tW.fXYZ;
					tAABB_Fireball_2.extents = tFloat3{ 0.03125f, 0.03125f, 0.1f };
				}
				// Node 2

				// Node 3
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tFireball_Nodes->fWorld_Matrix[3]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Fireball_3.center = tOut.tW.fXYZ;
					tAABB_Fireball_3.extents = tFloat3{ 0.03125f, 0.03125f, 0.1f };
				}
				// Node 3
			}
			// Spell Nodes - Fireball

			// Spell Nodes - Icebolt
			{
				// Node 1
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tIcebolt_Nodes->fWorld_Matrix[1]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Icebolt_1.center = tOut.tW.fXYZ;
					tAABB_Icebolt_1.extents = tFloat3{ 0.03125f, 0.03125f, 0.1f };
				}
				// Node 1

				// Node 2
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tIcebolt_Nodes->fWorld_Matrix[2]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Icebolt_2.center = tOut.tW.fXYZ;
					tAABB_Icebolt_2.extents = tFloat3{ 0.03125f, 0.03125f, 0.1f };
				}
				// Node 2

				// Node 3
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tIcebolt_Nodes->fWorld_Matrix[3]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Icebolt_3.center = tOut.tW.fXYZ;
					tAABB_Icebolt_3.extents = tFloat3{ 0.03125f, 0.03125f, 0.1f };
				}
				// Node 3
			}
			// Spell Nodes - Icebolt

			// Spell Nodes - Shield
			{
				// Node 1
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tShield_Nodes->fWorld_Matrix[1]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Shield_1.center = tOut.tW.fXYZ;
					tAABB_Shield_1.extents = tFloat3{ 0.03125f, 0.03125f, 0.1f };
				}
				// Node 1

				// Node 2
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tShield_Nodes->fWorld_Matrix[2]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Shield_2.center = tOut.tW.fXYZ;
					tAABB_Shield_2.extents = tFloat3{ 0.03125f, 0.03125f, 0.1f };
				}
				// Node 2

				// Node 3
				{
					xmf_origin = tFloat4x4_to_XMFLOAT4x4(c_Spell_Book.getPosition4x4());
					xmm_origin = XMLoadFloat4x4(&xmf_origin);
					xmf_offset = tFloat4x4_to_XMFLOAT4x4(tShield_Nodes->fWorld_Matrix[3]);
					xmm_offset = XMLoadFloat4x4(&xmf_offset);
					xmm_out = XMMatrixMultiply(xmm_offset, xmm_origin);
					XMStoreFloat4x4(&xmf_out, xmm_out);
					tOut = XMFLOAT4x4_to_tFloat4x4(xmf_out);
					tAABB_Shield_3.center = tOut.tW.fXYZ;
					tAABB_Shield_3.extents = tFloat3{ 0.03125f, 0.03125f, 0.1f };
				}
				// Node 3
			}
			// Spell Nodes - Shield
		}
		// AABB

		// Collisions
		{
			// Shield vs Dragon Fireball
			for (int i = 0; i < tWorld_Object_List->maxFireballs; i++)
			{
				if (tWorld_Object_List->fFireball_State[i] != true)
				{
					continue;
				}

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Player_Shield_01, tAABB_Dragon_Fireball[i]) || t_Collisions.Detect_AABB_To_AABB(tAABB_Player_Shield_02, tAABB_Dragon_Fireball[i]))
				{
					tWorld_Object_List->fFireball_State[i] = false;
					tWorld_Object_List->fFireballs_Alive -= 1;

					if (t_Collisions.Detect_AABB_To_AABB(tAABB_Player_Shield_01, tAABB_Dragon_Fireball[i]))
					{
						c_Spell_Shield_01.setHealth(-1);
						if (c_Spell_Shield_01.getHealth() <= 0)
						{
							personal_swap_Id.fX = 0;
							personal_swap_Id.fZ = 0;
							bSpell_Ready_01 = false;
							c_Spell_Shield_01.setIsActive(false);
							c_Spell_Shield_01.resetHealth();
						}
					}

					if (t_Collisions.Detect_AABB_To_AABB(tAABB_Player_Shield_02, tAABB_Dragon_Fireball[i]))
					{
						c_Spell_Shield_02.setHealth(-1);
						if (c_Spell_Shield_02.getHealth() <= 0)
						{
							personal_swap_Id.fY = 0;
							personal_swap_Id.fW = 0;
							bSpell_Ready_02 = false;
							c_Spell_Shield_02.setIsActive(false);
							c_Spell_Shield_02.resetHealth();
						}
					}

					//sound.playSoundEffect("Pain-SoundBible.com-1883168362.mp3", FMOD_DEFAULT, 0.7f);
				}
				else if (tWorld_Object_List->fFireball_Matrix[i].tW.fY < -5)
				{
					tWorld_Object_List->fFireball_State[i] = false;
					tWorld_Object_List->fFireballs_Alive -= 1;
				}
			}
			// Shield vs Dragon Fireball	

			// Player vs Dragon Fireball
			for (int i = 0; i < tWorld_Object_List->maxFireballs; i++)
			{
				if (tWorld_Object_List->fFireball_State[i] != true)
				{
					continue;
				}

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Player, tAABB_Dragon_Fireball[i]))
				{
					tWorld_Object_List->fFireball_State[i] = false;
					tWorld_Object_List->fFireballs_Alive -= 1;
					//c_Dragon_Fireball.setIsActive(false);
					c_Player.setHealth(-10);
					//tWorld_Object_List->fWorld_Matrix[3].tW.fY = 500;
					sound.playSoundEffect("Pain-SoundBible.com-1883168362.mp3", FMOD_DEFAULT, 0.7f);
					if (c_Player.getHealth() <= 0)
						c_Player.setIsAlive(false);
				}
				else if (tWorld_Object_List->fFireball_Matrix[i].tW.fY < -5)
				{
					tWorld_Object_List->fFireball_State[i] = false;
					tWorld_Object_List->fFireballs_Alive -= 1;
				}
			}
			// Player vs Dragon Fireball

			// Dragon vs Player Fireball
			if ((t_Collisions.Detect_AABB_To_AABB(tAABB_Dragon, tAABB_Player_Spell_01) && c_Player_Spell_01.getIsActive())
				|| (t_Collisions.Detect_AABB_To_AABB(tAABB_Dragon, tAABB_Player_Spell_02) && c_Player_Spell_02.getIsActive()))
			{
				tWorld_Object_List->currAnim[2] = 1;

				dragon_hit = true;
				//dragon_hit = c_AI.setIsHit(true);
				//dragon_hit = c_AI.getIsHit();
				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Dragon, tAABB_Player_Spell_01) && c_Player_Spell_01.getIsActive())
				{
					c_Player_Spell_01.setIsActive(false);
					bMove_Spell_01 = false;
				}

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Dragon, tAABB_Player_Spell_02) && c_Player_Spell_02.getIsActive())
				{
					c_Player_Spell_02.setIsActive(false);
					bMove_Spell_02 = false;
				}

				c_AI.setIsHit(true);
				c_Dragon.setHealth(-20);
				c_Render_Manager.set_particle_array(p.get_particles());
				p.create_particles(dragon_blast_color, c_XTime.Delta(), dragon_blast_acceleration, dragon_blast_kill, dragon_hit);

				if (c_Player.getHealth() <= 0)
					c_Player.setIsAlive(false);
			}
			// Dragon vs Player Fireball

			// Spell Book
			if (bDisplay_Spell_Book || bDisplay_Spell_Node)
			{
				if (personal_swap_Id.fX == 0)
					personal_swap_Id.fX = 1;

				if (personal_swap_Id.fY == 0)
					personal_swap_Id.fY = 1;
			}

			if (bDisplay_Spell_Book)
			{
				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Spell_1) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Spell_1))
				{
					if (!bDisplay_Spell_Node)
					{
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = true;
						bDisplay_Fireball = true;
						memset(bNode_Order, 0, sizeof(bNode_Order));
					}
				}

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Spell_2) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Spell_2))
				{
					if (!bDisplay_Spell_Node)
					{
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = true;
						bDisplay_Icebolt = true;
						memset(bNode_Order, 0, sizeof(bNode_Order));
					}
				}

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Spell_3) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Spell_3))
				{
					if (!bDisplay_Spell_Node)
					{
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = true;
						bDisplay_Shield = true;
						memset(bNode_Order, 0, sizeof(bNode_Order));
					}
				}

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Cancel) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Cancel))
				{
					bDisplay_Spell_Book = false;
					bDisplay_Spell_Node = false;
					bDisplay_Fireball = false;
					bDisplay_Icebolt = false;
					bDisplay_Shield = false;
					bSpell_Ready_01 = false;
					bSpell_Ready_02 = false;
					c_Spell_Shield_01.setIsActive(false);
					c_Spell_Shield_02.setIsActive(false);
					c_Spell_Shield_01.resetHealth();
					c_Spell_Shield_02.resetHealth();
					memset(bNode_Order, 0, sizeof(bNode_Order));
					personal_swap_Id = { 0.0f, 0.0f, 0.0f, 0.0f };
				}
			}
			// Spell Book

			// Fireball Nodes
			if (bDisplay_Fireball)
			{
				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Fireball_1) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Fireball_1))
					bNode_Order[0] = true;

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Fireball_2) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Fireball_2))
				{
					if (bNode_Order[0])
						bNode_Order[1] = true;
					else
					{
						memset(bNode_Order, 0, sizeof(bNode_Order));
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = false;
						bDisplay_Fireball = false;
						bSpell_Ready_01 = false;
						bSpell_Ready_02 = false;
						c_Spell_Shield_01.setIsActive(false);
						c_Spell_Shield_02.setIsActive(false);
						c_Spell_Shield_01.resetHealth();
						c_Spell_Shield_02.resetHealth();
						personal_swap_Id = { 0.0f, 0.0f, 0.0f, 0.0f };
					}
				}

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Fireball_3) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Fireball_3))
				{
					if (bNode_Order[1])
					{
						bNode_Order[2] = true;
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = false;
						bDisplay_Fireball = false;

						if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Fireball_3))
						{
							bSpell_Ready_01 = true;
							personal_swap_Id.fX = 2;
							personal_swap_Id.fZ = 1;

							if (personal_swap_Id.fY == 1)
								personal_swap_Id.fY = 0;
						}

						if (t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Fireball_3))
						{
							bSpell_Ready_02 = true;
							personal_swap_Id.fY = 2;
							personal_swap_Id.fW = 1;

							if (personal_swap_Id.fX == 1)
								personal_swap_Id.fX = 0;
						}
					}
					else
					{
						memset(bNode_Order, 0, sizeof(bNode_Order));
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = false;
						bDisplay_Fireball = false;
						bSpell_Ready_01 = false;
						bSpell_Ready_02 = false;
						c_Spell_Shield_01.setIsActive(false);
						c_Spell_Shield_02.setIsActive(false);
						c_Spell_Shield_01.resetHealth();
						c_Spell_Shield_02.resetHealth();
						personal_swap_Id = { 0.0f, 0.0f, 0.0f, 0.0f };
					}
				}
			}
			// Fireball Nodes

			// Icebolt Nodes
			if (bDisplay_Icebolt)
			{
				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Icebolt_1) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Icebolt_1))
					bNode_Order[0] = true;

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Icebolt_2) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Icebolt_2))
				{
					if (bNode_Order[0])
						bNode_Order[1] = true;
					else
					{
						memset(bNode_Order, 0, sizeof(bNode_Order));
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = false;
						bDisplay_Icebolt = false;
						bSpell_Ready_01 = false;
						bSpell_Ready_02 = false;
						c_Spell_Shield_01.setIsActive(false);
						c_Spell_Shield_02.setIsActive(false);
						c_Spell_Shield_01.resetHealth();
						c_Spell_Shield_02.resetHealth();
						personal_swap_Id = { 0.0f, 0.0f, 0.0f, 0.0f };
					}
				}

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Icebolt_3) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Icebolt_3))
				{
					if (bNode_Order[1])
					{
						bNode_Order[2] = true;
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = false;
						bDisplay_Icebolt = false;

						if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Icebolt_3))
						{
							bSpell_Ready_01 = true;
							personal_swap_Id.fX = 2;
							personal_swap_Id.fZ = 2;

							if (personal_swap_Id.fY == 1)
								personal_swap_Id.fY = 0;
						}

						if (t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Icebolt_3))
						{
							bSpell_Ready_02 = true;
							personal_swap_Id.fY = 2;
							personal_swap_Id.fW = 2;

							if (personal_swap_Id.fX == 1)
								personal_swap_Id.fX = 0;
						}
					}
					else
					{
						memset(bNode_Order, 0, sizeof(bNode_Order));
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = false;
						bDisplay_Icebolt = false;
						bSpell_Ready_01 = false;
						bSpell_Ready_02 = false;
						c_Spell_Shield_01.setIsActive(false);
						c_Spell_Shield_02.setIsActive(false);
						c_Spell_Shield_01.resetHealth();
						c_Spell_Shield_02.resetHealth();
						personal_swap_Id = { 0.0f, 0.0f, 0.0f, 0.0f };
					}
				}
			}
			// Icebolt Nodes

			// Shield Nodes
			if (bDisplay_Shield)
			{
				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Shield_1) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Shield_1))
					bNode_Order[0] = true;

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Shield_2) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Shield_2))
				{
					if (bNode_Order[0])
						bNode_Order[1] = true;
					else
					{
						memset(bNode_Order, 0, sizeof(bNode_Order));
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = false;
						bDisplay_Shield = false;
						bSpell_Ready_01 = false;
						bSpell_Ready_02 = false;
						c_Spell_Shield_01.setIsActive(false);
						c_Spell_Shield_02.setIsActive(false);
						c_Spell_Shield_01.resetHealth();
						c_Spell_Shield_02.resetHealth();
						personal_swap_Id = { 0.0f, 0.0f, 0.0f, 0.0f };
					}
				}

				if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Shield_3) || t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Shield_3))
				{
					if (bNode_Order[1])
					{
						bNode_Order[2] = true;
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = false;
						bDisplay_Shield = false;

						if (t_Collisions.Detect_AABB_To_AABB(tAABB_Left_Hand, tAABB_Shield_3))
						{
							bSpell_Ready_01 = true;
							personal_swap_Id.fX = 3;
							personal_swap_Id.fZ = 3;
							
							if (c_Spell_Shield_01.getIsActive())
								c_Spell_Shield_01.setHealth(2);
							else
								c_Spell_Shield_01.setIsActive(true);

							if (personal_swap_Id.fY == 1)
								personal_swap_Id.fY = 0;
						}

						if (t_Collisions.Detect_AABB_To_AABB(tAABB_Right_Hand, tAABB_Shield_3))
						{
							bSpell_Ready_02 = true;
							personal_swap_Id.fY = 3;
							personal_swap_Id.fW = 3;

							if (c_Spell_Shield_02.getIsActive())
								c_Spell_Shield_02.setHealth(2);
							else				
								c_Spell_Shield_02.setIsActive(true);


							if (personal_swap_Id.fX == 1)
								personal_swap_Id.fX = 0;
						}
					}
					else
					{
						memset(bNode_Order, 0, sizeof(bNode_Order));
						bDisplay_Spell_Book = false;
						bDisplay_Spell_Node = false;
						bDisplay_Shield = false;
						bSpell_Ready_01 = false;
						bSpell_Ready_02 = false;
						c_Spell_Shield_01.setIsActive(false);
						c_Spell_Shield_02.setIsActive(false);
						c_Spell_Shield_01.resetHealth();
						c_Spell_Shield_02.resetHealth();
						personal_swap_Id = { 0.0f, 0.0f, 0.0f, 0.0f };
					}
				}
			}
			// Shield Nodes
		}
		// Collisions

		if (dragon_hit == true)
			timeCheck += 1;

		if (timeCheck > 75)
		{
			dragon_hit = false;
			timeCheck = 0;
		}

		if ((!c_Player.getIsAlive() || !c_Dragon.getIsAlive()) && m_nScene_Id == 2)
			bChange_Scene = true;

		// Player Fireball
		if (c_Player_Spell_01.getPosition4().fX < -500 || c_Player_Spell_01.getPosition4().fX > 500 || c_Player_Spell_01.getPosition4().fY < -50 || c_Player_Spell_01.getPosition4().fY > 400 || c_Player_Spell_01.getPosition4().fZ < -500 || c_Player_Spell_01.getPosition4().fZ > 500)
			bMove_Spell_01 = false;

		if (c_Player_Spell_02.getPosition4().fX < -500 || c_Player_Spell_02.getPosition4().fX > 500 || c_Player_Spell_02.getPosition4().fY < -50 || c_Player_Spell_02.getPosition4().fY > 400 || c_Player_Spell_02.getPosition4().fZ < -500 || c_Player_Spell_02.getPosition4().fZ > 500)
			bMove_Spell_02 = false;

		if (bMove_Spell_01)
		{
			if (!c_Player_Spell_01.getIsActive())
				sound.playSoundEffect("Large Fireball-SoundBible.com-301502490.mp3", FMOD_DEFAULT, 0.6f);

			c_Player_Spell_01.setIsActive(true);
		}
		else
			c_Player_Spell_01.setIsActive(false);

		if (bMove_Spell_02)
		{
			if (!c_Player_Spell_02.getIsActive())
				sound.playSoundEffect("Large Fireball-SoundBible.com-301502490.mp3", FMOD_DEFAULT, 0.6f);

			c_Player_Spell_02.setIsActive(true);
		}
		else
			c_Player_Spell_02.setIsActive(false);
	}

	// Trackpad movement
	if (movement.fX > 0.0f || movement.fY > 0.0f || movement.fZ > 0.0f || movement.fW > 0.0f)
	{
		c_Offset_Matrix.Update_Offset(c_XTime.Delta(), c_Head_Mount.Get_mat4HMDPose(), movement);
		bCharacter_Moving = true;
	}

	if (movement.fX == 0.0f && movement.fY == 0.0f && movement.fZ == 0.0f && movement.fW == 0.0f)
		bCharacter_Moving = false;

	// Controller Inputs
	c_Controllers.Update_Controller(m_nScene_Id, &bChange_Scene, &bDisplay_Spell_Book, bDisplay_Spell_Node, &bReset_Offset, &bMove_Spell_01, &bMove_Spell_02, &bSpell_Ready_01, &bSpell_Ready_02, &movement, c_Offset_Matrix.GetPosition4x4());


	// Special (Reset Position)
	if (bReset_Offset && m_nScene_Id != 2)
	{
		c_Offset_Matrix.ResetPosition();
		bReset_Offset = false;
	}


	// Scene Transitions
	if (bChange_Scene)
	{
		if (m_nScene_Id == 2)
		{
			personal_swap_Id = { 0.0f, 0.0f, 0.0f, 0.0f };
			memset(bNode_Order, 0, sizeof(bNode_Order));
			bDisplay_Spell_Book = false;
			bDisplay_Spell_Node = false;
			bDisplay_Fireball = false;
			bDisplay_Icebolt = false;
			bDisplay_Shield = false;
			bMove_Spell_01 = false;
			bMove_Spell_02 = false;
			bSpell_Ready_01 = false;
			bSpell_Ready_02 = false;
			c_Spell_Shield_01.setIsActive(false);
			c_Spell_Shield_02.setIsActive(false);
			c_Spell_Shield_01.resetHealth();
			c_Spell_Shield_02.resetHealth();
		}

		c_Render_Manager.Unload(tWorld_Object_List);
		m_nScene_Id++;
		if (m_nScene_Id > 3)
		{
			m_nScene_Id = 2;
			c_Player.setIsAlive(true);
			c_Player.resetHealth();
			c_Dragon.setIsAlive(true);
			c_Dragon.resetHealth();
		}
		tWorld_Object_List = c_Scene_Manager.Get_World_Scene(m_nScene_Id);
		c_Render_Manager.Load_Data(m_nScene_Id, tWorld_Object_List);

		c_Offset_Matrix.ResetPosition();
		c_AI.resetHP();
		bChange_Scene = false;
	}

	if (m_nScene_Id == 0)
	{
		if (c_XTime.TotalTime() > 4.0f)
			bChange_Scene = true;
	}

	switch (c_Spell_Shield_01.getHealth())
	{
	case 1:
		fname = "Shield_Red.dds";
		c_Render_Manager.Texture_Swap(fname, &tPersonal_Object_List->d3d_SRV[10]);
		break;
	case 2:
		fname = "Shield_Yellow.dds";
		c_Render_Manager.Texture_Swap(fname, &tPersonal_Object_List->d3d_SRV[10]);
		break;
	case 3:
		fname = "Shield_Green.dds";
		c_Render_Manager.Texture_Swap(fname, &tPersonal_Object_List->d3d_SRV[10]);
		break;
	default:
		fname = "Shield_Blue.dds";
		c_Render_Manager.Texture_Swap(fname, &tPersonal_Object_List->d3d_SRV[10]);
		break;
	}


	switch (c_Spell_Shield_02.getHealth())
	{
	case 1:
		fname = "Shield_Red.dds";
		c_Render_Manager.Texture_Swap(fname, &tPersonal_Object_List->d3d_SRV[13]);
		break;
	case 2:
		fname = "Shield_Yellow.dds";
		c_Render_Manager.Texture_Swap(fname, &tPersonal_Object_List->d3d_SRV[13]);
		break;
	case 3:
		fname = "Shield_Green.dds";
		c_Render_Manager.Texture_Swap(fname, &tPersonal_Object_List->d3d_SRV[13]);
		break;
	 default:
		fname = "Shield_Blue.dds";
		c_Render_Manager.Texture_Swap(fname, &tPersonal_Object_List->d3d_SRV[13]);
		break;
	}


	// Renders
	if (m_nScene_Id == 2)
	{
		//c_AI.resolveDragonState(&tWorld_Object_List, c_Offset_Matrix.GetPosition4x4(), c_XTime.Delta());
		c_AI.resolveDragonState(tWorld_Object_List, c_Player.getPosition4x4(), c_XTime.Delta(), &c_Dragon_Fireball);
	}
	c_Animation_Manager.Animate(c_XTime.Delta(), c_XTime.TotalTimeExact(), tWorld_Object_List);
	c_Render_Manager.set_particle_array(p.get_particles());   // JUST ADDED THIS
	p.create_particles(fireball_color, c_XTime.Delta(), fireball_acceleration, fireball_kill, dragon_hit);
	c_Render_Manager.Draw_World(m_nScene_Id, tWorld_Object_List, &bChange_Scene, c_Head_Mount, c_Offset_Matrix.GetPosition4x4(), c_XTime.TotalTime(), &c_AI, dragon_hit, c_XTime.Delta(), c_Player.getPosition4x4());
	c_Render_Manager.Draw_UI(UI_Object_List, c_Head_Mount, c_Offset_Matrix.GetPosition4x4(), tWorld_Object_List->fWorld_Matrix[2], c_Dragon, c_Player);
	c_Render_Manager.Draw_Spell(tSpell_Book, c_Head_Mount, c_Offset_Matrix.GetPosition4x4(), bDisplay_Spell_Book, false, bNode_Order);
	c_Render_Manager.Draw_Spell(tFireball_Nodes, c_Head_Mount, c_Offset_Matrix.GetPosition4x4(), bDisplay_Fireball, true, bNode_Order);
	c_Render_Manager.Draw_Spell(tIcebolt_Nodes, c_Head_Mount, c_Offset_Matrix.GetPosition4x4(), bDisplay_Icebolt, true, bNode_Order);
	c_Render_Manager.Draw_Spell(tShield_Nodes, c_Head_Mount, c_Offset_Matrix.GetPosition4x4(), bDisplay_Shield, true, bNode_Order);
	c_Render_Manager.Draw_Personal(tPersonal_Object_List, c_Head_Mount, c_Controllers, c_Offset_Matrix.GetPosition4x4(), &bMove_Spell_01, &bMove_Spell_02, &bSpell_Ready_01, &bSpell_Ready_02, c_Player, personal_swap_Id);


	//c_Render_Manager.Debugging_AABB(tAABB_Player, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
	//c_Render_Manager.Debugging_AABB(tAABB_Player_Shield_01, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
	//c_Render_Manager.Debugging_AABB(tAABB_Player_Shield_02, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());

	
	// AABB Visual Debugging
	/*
	if (m_nScene_Id == 2)
	{
		c_Render_Manager.Debugging_AABB(tAABB_Left_Hand, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
		c_Render_Manager.Debugging_AABB(tAABB_Right_Hand, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());

		if (bDisplay_Spell_Book)
		{
			c_Render_Manager.Debugging_AABB(tAABB_Spell_1, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
			c_Render_Manager.Debugging_AABB(tAABB_Spell_2, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
			c_Render_Manager.Debugging_AABB(tAABB_Spell_3, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
			c_Render_Manager.Debugging_AABB(tAABB_Cancel, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
		}

		if (bDisplay_Fireball)
		{
			c_Render_Manager.Debugging_AABB(tAABB_Fireball_1, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
			c_Render_Manager.Debugging_AABB(tAABB_Fireball_2, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
			c_Render_Manager.Debugging_AABB(tAABB_Fireball_3, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
		}

		if (bDisplay_Icebolt)
		{
			c_Render_Manager.Debugging_AABB(tAABB_Icebolt_1, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
			c_Render_Manager.Debugging_AABB(tAABB_Icebolt_2, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
			c_Render_Manager.Debugging_AABB(tAABB_Icebolt_3, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
		}

		if (bDisplay_Shield)
		{
			c_Render_Manager.Debugging_AABB(tAABB_Shield_1, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
			c_Render_Manager.Debugging_AABB(tAABB_Shield_2, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
			c_Render_Manager.Debugging_AABB(tAABB_Shield_3, c_Head_Mount, c_Offset_Matrix.GetPosition4x4());
		}
	}
	*/

	c_Head_Mount.VR_Render();

	// Other updates
	sound.updateSoundSystem();
}

void cGame_Loop::Clean_Up()
{
	//delete[] tSpell_Book;
	//delete[] tPersonal_Object_List;
	//delete[] tWorld_Object_List;

}
