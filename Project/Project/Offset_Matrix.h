/************************************************************************
* Filename:  		Offset_Matrix.h (Recreate from Camera)
* Date:      		05/12/2018
* Mod. Date: 		11/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Offset Matrix applies to Headset and Controller to move player's view and hand
*************************************************************************/
#pragma once

#include "Basic_Structs.h"
#include "Math_Conversion.h"
#include "Renderer_Structs.h"

class cOffset_Matrix
{
private:
	tFloat4x4 tOffset_Matrix;
public:
	cOffset_Matrix();
	~cOffset_Matrix();

	void Initialize();
	void ResetPosition();
	tFloat4 GetHeading();
	tFloat4 GetPosition4();
	tFloat4x4 GetPosition4x4();
	void Update_Offset(double dDelta, tFloat4x4 tHMDPose, tFloat4 fMovement_Vect);
};

