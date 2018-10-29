#pragma once
#include <vector>

#include "renderer_structs.h"
#include "specific_structs.h"

class cBinary_Reader
{
public:
	cBinary_Reader();
	~cBinary_Reader();

	tMesh Read_Mesh(const char* szRead_Path);
	tMaterials Read_Material(const char* szRead_Path);
	//anim_clip read_skeleton(const char * read_path);
	//mesh_skinned read_skinned(const char* read_path);
	tBinary_Screen Read_Screen_Binary(const char* read_file_path);
};

