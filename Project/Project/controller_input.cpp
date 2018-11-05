#include "controller_input.h"



controller_input::controller_input()
{
	
}

controller_input::~controller_input()
{
}

void controller_input::get_controller_input()
{
	if (vr::EVRState == vr::VRState_Ready)
	{
		if (vr::EVREventType == vr::VREvent_TrackedDeviceActivated)  // VREvent_TrackedDeviceDeactivated     VREvent_TrackedDeviceUpdated    VREvent_TrackedDeviceRoleChanged
		{
			switch (switch_on)  // controller
			{
			case vr::k_EButton_SteamVR_Trigger:

				break;
			case vr::k_EButton_Grip:

				break;
			case vr::k_EButton_SteamVR_Touchpad:
				switch ()  // touchpad events
				{
				case vr::VREvent_ButtonPress:

					break;
				case vr::VREvent_ButtonUnpress:

					break;
				case vr::VREvent_ButtonTouch:

					break;
				case vr::VREvent_ButtonUntouch:

					break;
				}
				break;

			case vr::k_EButton_ApplicationMenu:
				switch () // appliction events
				{
				case vr::VREvent_ButtonPress:

					break;
				case vr::VREvent_ButtonUnpress:

					break;
				}
				break;

			default:
				break;
			}
		}
	}
}

void controller_input::set_controller_role()
{
	vr::ETrackedDeviceClass eTracked_devices;

	if (eTracked_devices != vr::TrackedDeviceClass_Controller)
	{
		return;
	}

	if (eController_role == vr::TrackedControllerRole_Invalid)
	{

	}
	else if (eController_role == vr::TrackedControllerRole_RightHand)
	{

	}
	else if (eController_role == vr::TrackedControllerRole_LeftHand)
	{

	}
}