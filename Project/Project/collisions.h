/************************************************************************
* Filename:  		Collisions.h
* Date:      		11/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Handles the collision calculation and detection for the Game.
*************************************************************************/
#pragma once
#include "Physics_Structs.h"

class tCollisions
{
public:
	tCollisions();
	~tCollisions();

	tFloat3 Caclulate_Cube_Center(const tVertex cube[]);
	bool Detect_AABB_To_AABB(tAABB a, tAABB b);
};

