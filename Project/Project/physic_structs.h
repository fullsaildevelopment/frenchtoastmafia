/************************************************************************
* Filename:  		renderer_structs.h
* Date:      		10/11/2018
* Mod. Date: 		10/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Additional structs to hold different datatype and make accessing them easier.
*************************************************************************/
#pragma once

#include "basic_structs.h"

struct tAABB
{
	tFloat3 center;
	tFloat3 extents;
};
