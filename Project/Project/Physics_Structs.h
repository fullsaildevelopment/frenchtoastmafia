/************************************************************************
* Filename:  		Physics_Structs.h
* Date:      		11/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Additional physics specific-structs to hold different datatype and make accessing them easier.
*************************************************************************/
#pragma once

#include "Basic_Structs.h"

struct tAABB
{
	tFloat3 center;
	tFloat3 extents;
};
