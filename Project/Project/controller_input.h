#pragma once
#include "VR.h"
#include "Graphic_Setup.h"
#include "openvr/headers/openvr.h"

class controller_input
{
private:
	vr::TrackedDeviceIndex_t nController_device_index;
	vr::VRControllerState_t *tController_state;
	vr::TrackingUniverseOrigin eTracking_universe_origin;
	vr::TrackedDevicePose_t tTacked_device_pose;
	vr::ETrackedControllerRole eController_role;

	//vr::k_eControllerAxis_TrackPad trackPad;
	//vr::TrackedDeviceClass cTracked_device;
public:
	controller_input();
	~controller_input();
	void get_controller_input();
	void set_controller_role();
};

