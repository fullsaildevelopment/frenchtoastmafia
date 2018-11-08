/************************************************************************
* Filename:  		Collisions.cpp
* Date:      		11/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Handles the collision calculation and detection for the Game.
*************************************************************************/
#include "Collisions.h"


tCollisions::tCollisions()
{
}

tCollisions::~tCollisions()
{
}



tFloat3 tCollisions::Caclulate_Cube_Center(const tVertex cube[])
{
	tFloat3 center;
	center.fX = (cube[1].fPosition.fX - cube[0].fPosition.fX) / 2;
	center.fY = (cube[0].fPosition.fY - cube[2].fPosition.fY) / 2;
	center.fZ = (cube[4].fPosition.fZ - cube[0].fPosition.fZ) / 2;

	return center;
}

bool tCollisions::Detect_AABB_To_AABB(tAABB a, tAABB b)
{
	if ((a.center.fX + a.extents.fX) < (b.center.fX - b.extents.fX) || (a.center.fX - a.extents.fX) > (b.center.fX + b.extents.fX)) return false;
	if ((a.center.fY + a.extents.fY) < (b.center.fY - b.extents.fY) || (a.center.fY - a.extents.fY) > (b.center.fY + b.extents.fY)) return false;
	if ((a.center.fZ + a.extents.fZ) < (b.center.fZ - b.extents.fZ) || (a.center.fZ - a.extents.fZ) > (b.center.fZ + b.extents.fZ)) return false;

	return true;
}
