/************************************************************************
* Filename:  		Scene_Manager.h
* Date:      		24/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to handle all objects within a scene and related task.
*************************************************************************/
#pragma once

#include "Binary_Reader.h"
#include "Math_Conversion.h"
#include "Renderer_Structs.h"
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"

class cScene_Manager
{
private:
	cBinary_Reader cBinary_Read;

public:
	cScene_Manager();
	~cScene_Manager();

	tScene_Objects* Get_Personal_Scene();
	tScene_Objects* Get_Personal_Scene2();
	tScene_Objects* Get_World_Scene(int nScene_Id);
	tScene_Objects* Get_Spell_Book();
	tScene_Objects* Get_Spell_Node_Fireball();
	tScene_Objects* Get_Spell_Node_Icebolt();
	tScene_Objects* Get_Spell_Node_Shield();
	tScene_Objects* Get_UI();
};

