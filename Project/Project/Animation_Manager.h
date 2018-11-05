#pragma once

#include "Graphic_Setup.h"

#include "renderer_structs.h"

class cAnimation_Manager
{
private:

	cGraphics_Setup * c_Graphics_Setup;

public:
	cAnimation_Manager();
	~cAnimation_Manager();

	void Animate(tScene_Objects* t_Object_List);
};

