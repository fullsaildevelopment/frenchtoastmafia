/************************************************************************
* Filename:  		Camera.h
* Date:      		26/10/2018
* Mod. Date: 		03/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Camera Class for Player's View
*************************************************************************/
#pragma once

#include "Basic_Structs.h"
#include "Math_Conversion.h"
#include "Renderer_Structs.h"

class cCamera
{
private:
	tFloat4x4 fView_Matrix;
	float fY_Data;
public:
	cCamera();
	~cCamera();

	void Initialize();
	void SetPosition(tFloat4 fPosition);
	void SetPosition(tFloat4x4 fPosition);
	tFloat4x4 GetPosition();

	void Translation(tFloat4 fMovement_Vect);
	void Rotation(tFloat4 fRotation_Vect);
	void Normalize();

	void Update_Offset(double dDelta, tFloat4 fMovement_Vect);
};

