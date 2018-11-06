#pragma once
#include "Graphic_Setup.h"
#include "Matrices.h"
class cVR
{
private:
	cGraphics_Setup * c_Graphics_Setup;

public:
	cVR();
	~cVR();

	void Initialize(cGraphics_Setup* c_Graphics_Setup);

	void VR_Render();
};

