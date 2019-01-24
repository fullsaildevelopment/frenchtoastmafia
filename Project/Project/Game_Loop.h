/************************************************************************
* Filename:  		Game_Loop.h
* Date:      		24/10/2018
* Mod. Date: 		12/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Main Loop of the Game, System Initialization, System Procedure
*************************************************************************/
#pragma once

#include "Animation_Manager.h"
#include "Base_Character.h"
#include "Base_Spell.h"
#include "Collisions.h"
#include "Offset_Matrix.h"
#include "Controllers.h"
#include "Head_Mount.h"
#include "Graphic_Setup.h"
#include "Render_Manager.h"
#include "Scene_Manager.h"
#include "Spell_Book.h"
#include "VR_Setup.h"
#include "XTime.h"
#include "dopeSoundSystem.h"
#include "Particle.h"
#include "AI.h"
class cGame_Loop
{
private:
	cAnimation_Manager c_Animation_Manager;
	cBase_Character c_Player, c_Dragon;
	cBase_Spell c_Player_Spell_01, c_Player_Spell_02, c_Player_Fireball, c_Dragon_Fireball;
	cControllers c_Controllers;
	cGraphics_Setup *c_Graphics_Setup;
	cHead_Mount c_Head_Mount;
	cOffset_Matrix c_Offset_Matrix;
	cRender_Manager c_Render_Manager;
	cScene_Manager c_Scene_Manager;
	cSpell_Book c_Spell_Book;
	tCollisions t_Collisions;

	cVR_Setup *c_VR_Setup;
	XTime c_XTime;
	dopeSoundSystem sound;

	AI c_AI;

	bool bChange_Scene = false;
	bool bReset_Offset = false;
	bool bCharacter_Moving = false;
	bool bDisplay_Spell_Book = false;
	bool bDisplay_Spell_Node = false;
	bool bDisplay_Fireball = false;
	bool bDisplay_Icebolt = false;
	bool bDisplay_Shield = false;
	bool bNode_Order[3] = { false };

	bool bMove_Bullet = false;
	bool bMove_Spell_01 = false;
	bool bMove_Spell_02 = false;

	bool bSpell_Ready = false;
	bool bSpell_Ready_01 = false;
	bool bSpell_Ready_02 = false;


	int m_nScene_Id;
	int nDisplay_Spell_Node = 0;

	tFloat4 personal_swap_Id = { 0.0f, 0.0f, 0.0f, 0.0f };
	tFloat4 movement = { 0.0f, 0.0f, 0.0f, 0.0f };
	tScene_Objects *tPersonal_Object_List, *tWorld_Object_List, *UI_Object_List;
	tScene_Objects *tSpell_Book, *tFireball_Nodes, *tIcebolt_Nodes, *tShield_Nodes;
	tAABB tAABB_Player, tAABB_Player_Fireball, tAABB_Dragon;
	tAABB tAABB_Left_Hand, tAABB_Right_Hand;
	tAABB tAABB_Spell_1, tAABB_Spell_2, tAABB_Spell_3, tAABB_Cancel;
	tAABB tAABB_Fireball_1, tAABB_Fireball_2, tAABB_Fireball_3;
	tAABB tAABB_Icebolt_1, tAABB_Icebolt_2, tAABB_Icebolt_3;
	tAABB tAABB_Shield_1, tAABB_Shield_2, tAABB_Shield_3;

	tNode *tNodeList;

	tAABB tAABB_Dragon_Fireball[3];


	// Particle Stuff

	Particle p;

	tFloat3 fireball_acceleration = { 0.0f, 0.0f, -9.81f };

	tFloat3 dragon_blast_acceleration = { 0.0f, -9.81f, 0.0f };

	tFloat4 fireball_color = { 0.2078f, 0.2078f, 0.2078f, 1.0f };   // 1.0f

	tFloat4 dragon_blast_color = { 1.0f, 0.0f, 0.0f, 1.0f };  // { 1.0f, 0.38039f, 0.0f, 1.0f };

	int test = 0;

	XMFLOAT4X4 xmf_in, xmf_out;
	XMMATRIX xmm_in;

	float fireball_kill = -2.0f;
	float dragon_blast_kill = 0;

	bool dragon_hit = false;
	float timeCheck = 0;
	// Particle Stuff

public:
	cGame_Loop();
	~cGame_Loop();

	void Initialize(cGraphics_Setup* _gsetup, cVR_Setup* _vsetup);
	void Setup();
	void Update();
	void Clean_Up();
};
