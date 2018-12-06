/************************************************************************
* Filename:  		VR.h
* Date:      		24/10/2018
* Mod. Date: 		02/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to VR related task.
*************************************************************************/
#pragma once
#include "Graphic_Setup.h"
#include "Matrices.h"
class cVR
{
private:
	cGraphics_Setup* c_Graphics_Setup;

public:
	cVR();
	~cVR();

	void Initialize(cGraphics_Setup* c_Graphics_Setup);

	void VR_Render();

	//void update_controller();
};

