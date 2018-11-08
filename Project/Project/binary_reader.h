/************************************************************************
* Filename:  		Binary_Reader.cpp
* Date:      		12/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Reader for Binary file with data such as Meshs, Materials, Keyframe for Animations
*************************************************************************/
#pragma once
#include <vector>

#include "Renderer_Structs.h"
#include "Specific_Structs.h"

class cBinary_Reader
{
public:
	cBinary_Reader();
	~cBinary_Reader();

	tMesh Read_Mesh(const char* szRead_Path);
	tMaterials Read_Material(const char* szRead_Path);
	tAnimation_Clip Read_Skeleton(const char * szRead_Path);
	tMesh_Skinned Read_Mesh_Skinned(const char * szRead_Path);
	tBinary_Screen Read_Screen_Binary(const char* szRead_Path);
};

