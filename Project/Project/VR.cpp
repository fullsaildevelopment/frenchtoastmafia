/************************************************************************
* Filename:  		VR.cpp
* Date:      		24/10/2018
* Mod. Date: 		02/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to VR related task.
*************************************************************************/
#include "VR.h"

cVR::cVR()
{
}

cVR::~cVR()
{
}

void cVR::Initialize(cGraphics_Setup* _setup)
{
	c_Graphics_Setup = _setup;
}

void cVR::VR_Render()
{
	vr::Texture_t leftEyeTexture = { c_Graphics_Setup->Get_Texture_Left_Eye().Get(), vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::EVRCompositorError error1 = vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
	vr::Texture_t rightEyeTexture = { c_Graphics_Setup->Get_Texture_Right_Eye().Get(), vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

	c_Graphics_Setup->UpdateHMDMatrixPose();
}
