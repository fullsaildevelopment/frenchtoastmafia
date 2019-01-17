/************************************************************************
* Filename:  		Animation_Manager.h
* Date:      		05/11/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to handle all animation related task.
*************************************************************************/
#pragma once

#include "Graphic_Setup.h"

#include "Renderer_Structs.h"

class cAnimation_Manager
{
private:
	cGraphics_Setup * c_Graphics_Setup;

	float m_fCurrent_Time;
	int currentAnim = 0;

public:
	cAnimation_Manager();
	~cAnimation_Manager();

	void Animate(double dDelta, double dTotal, tScene_Objects* tObject_List);
};

