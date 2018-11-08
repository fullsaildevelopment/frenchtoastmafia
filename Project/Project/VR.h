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

	static const uint32_t vr::k_unControllerStateAxisCount = 5;  // the number of axes in the controller state

	struct VRControllerState001_t
	{
		// If packet num matches that on your prior call, then the controller state hasn't been changed since 
	// your last call and there is no need to process it
		uint32_t unPacketNum;

		// bit flags for each of the buttons. Use ButtonMaskFromId to turn an ID into a mask
		uint64_t ulButtonPressed;
		uint64_t ulButtonTouched;

		// Axis data for the controller's analog inputs
		vr::VRControllerAxis_t rAxis[vr::k_unControllerStateAxisCount];
	};

	void Initialize(cGraphics_Setup* c_Graphics_Setup);

	void VR_Render();

	void update_controller();
};

