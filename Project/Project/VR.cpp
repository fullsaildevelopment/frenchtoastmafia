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
	//update_controller();

	vr::Texture_t leftEyeTexture = { c_Graphics_Setup->Get_Texture_Left_Eye() , vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::EVRCompositorError error1 = vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
	vr::Texture_t rightEyeTexture = { c_Graphics_Setup->Get_Texture_Right_Eye(), vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

	c_Graphics_Setup->UpdateHMDMatrixPose();
}


