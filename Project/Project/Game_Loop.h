#pragma once

#include "Animation_Manager.h"
#include "Graphic_Setup.h"
#include "Render_Manager.h"
#include "Scene_Manager.h"
#include "VR.h"

class cGame_Loop
{
private:
	int nScene_Id;
	cAnimation_Manager c_Animation_Manager;
	cGraphics_Setup *c_Graphics_Setup;
	cRender_Manager c_Render_Manager;
	cScene_Manager c_Scene_Manager;
	cVR c_VR;
	tScene_Objects t_Object_List;

public:
	cGame_Loop();
	~cGame_Loop();

	void Initialize(cGraphics_Setup* _setup);
	void Setup();
	void Update();
	void Clean_Up();
};