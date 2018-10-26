#pragma once

#include "Graphic_Setup.h"
#include "Render_Manager.h"
#include "VR.h"
#include "Scene_Manager.h"

class cGame_Loop
{
private:
	cGraphics_Setup *c_Graphics_Setup;
	cRender_Manager c_Render_Manager;
	cVR c_VR;
	cScene_Manager c_Scene_Manager;
	

public:
	cGame_Loop();
	~cGame_Loop();

	void Initialize(cGraphics_Setup _setup);
	void Setup();
	void Update();
	void Clean_Up();
};