#pragma once

#include "basic_structs.h"
#include "renderer_structs.h"

struct tBinary_Screen
{
	int nObject_Count;
	tMesh tMes;
	bool vs_check;
	std::string vs_name;
	bool ps_check;
	std::string ps_name;
	bool srv_check;
	std::string srv_name;
};

struct RHS_to_LHS
{
	tFloat4x4 head;
	tFloat4x4 pose;
	tFloat4x4 proj;
};