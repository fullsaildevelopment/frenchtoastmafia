#pragma once
#include "physic_structs.h"

class tCollisions
{
public:
	tCollisions();
	~tCollisions();

	tFloat3 Caclulate_Cube_Center(const tVertex cube[]);
	bool Detect_AABB_To_AABB(tAABB a, tAABB b);
};

