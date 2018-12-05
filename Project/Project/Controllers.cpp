/************************************************************************
* Filename:  		Controller.cpp
* Date:      		29/11/2018
* Mod. Date: 		04/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Handle Controller related task for VR
*************************************************************************/
#include "Controllers.h"

cControllers::cControllers()
{
}

cControllers::~cControllers()
{
}

void cControllers::Initialize(cVR_Setup* _c_VR_Setup)
{
	c_VR_Setup = _c_VR_Setup;
}

void cControllers::Clean_Up()
{
}

tFloat3 cControllers::Get_Left_Hand()
{
	return tLeft_Hand;
}

tFloat3 cControllers::Get_Right_Hand()
{
	return tRight_Hand;
}

void cControllers::Set_Left_Hand(tFloat3 left)
{
	tLeft_Hand = left;
}

void cControllers::Set_Right_Hand(tFloat3 right)
{
	tRight_Hand = right;
}

int cControllers::Identify_Controller(TrackedDeviceIndex_t vr_event)
{
	ETrackedDeviceClass trackedDeviceClass = c_VR_Setup->Get_HMD()->GetTrackedDeviceClass(vr_event);
	if (trackedDeviceClass != ETrackedDeviceClass::TrackedDeviceClass_Controller)
		return -1;

	ETrackedControllerRole controller_role = c_VR_Setup->Get_HMD()->GetControllerRoleForTrackedDeviceIndex(vr_event);

	if (controller_role == TrackedControllerRole_Invalid)
		return -2;
	else if (controller_role == TrackedControllerRole_LeftHand)
		return 1;
	else if (controller_role == TrackedControllerRole_RightHand)
		return 2;
}

void cControllers::Update_Controller(int nScene_Id, bool *bChange_Scene, bool *bMove_Bullet, tFloat4 *movement, tFloat4x4 offset)
{
	if (!c_VR_Setup->Get_HMD()->IsInputAvailable())
		return;

	std::vector<float> vertdataarray;

	m_uiControllerVertcount = 0;
	m_iTrackedControllerCount = 0;

	for (vr::TrackedDeviceIndex_t unTrackedDevice = vr::k_unTrackedDeviceIndex_Hmd + 1; unTrackedDevice < vr::k_unMaxTrackedDeviceCount; ++unTrackedDevice)
	{
		if (!c_VR_Setup->Get_HMD()->IsTrackedDeviceConnected(unTrackedDevice))
			continue;

		if (c_VR_Setup->Get_HMD()->GetTrackedDeviceClass(unTrackedDevice) != vr::TrackedDeviceClass_Controller)
			continue;

		m_iTrackedControllerCount += 1;

		if (!c_VR_Setup->Get_rTrackedDevicePose()[unTrackedDevice].bPoseIsValid)
			continue;

		if (Identify_Controller(unTrackedDevice) > 0)
		{
			TrackedDevicePose_t trackedDevicePose;
			VRControllerState001_t vr_controller_state;
			c_VR_Setup->Get_HMD()->GetControllerStateWithPose(TrackingUniverseStanding, unTrackedDevice, &vr_controller_state, sizeof(VRControllerState001_t), &trackedDevicePose);
			vr::VREvent_t vrEvent;
			c_VR_Setup->Get_HMD()->PollNextEventWithPose(TrackingUniverseStanding, &vrEvent, sizeof(vrEvent), &trackedDevicePose);
			u_int Axis_Id;

			// -1 = not controller  -2 = role not valid   1 = left controller   2 = right controller
			if (Identify_Controller(vrEvent.trackedDeviceIndex) > 0)
				printf("%d : ", Identify_Controller(vrEvent.trackedDeviceIndex));
			
			switch (vrEvent.data.controller.button)
			{
			case k_EButton_Grip:
				switch (vrEvent.eventType)
				{
				case VREvent_ButtonPress:
					if (Identify_Controller(vrEvent.trackedDeviceIndex) == 1)
						printf("Grip Press\n");
					else if (Identify_Controller(vrEvent.trackedDeviceIndex) == 2)
						printf("Grip Press\n");
					break;

				case VREvent_ButtonUnpress:
					printf("Grip unPress\n");
					break;
				}
				break;

			case k_EButton_SteamVR_Trigger:
				switch (vrEvent.eventType)
				{
				case VREvent_ButtonPress:
					if (Identify_Controller(vrEvent.trackedDeviceIndex) == 1)
						printf("Trigger Press\n");
					else if (Identify_Controller(vrEvent.trackedDeviceIndex) == 2)
					{
						printf("Trigger Press\n");
						if (nScene_Id == 2)
							*bMove_Bullet = true;
						else
							*bChange_Scene = true;
					}
					break;

				case VREvent_ButtonUnpress:
					if (Identify_Controller(vrEvent.trackedDeviceIndex) == 1)
						printf("Trigger unPress\n");
					else
						printf("Trigger unPress\n");

					break;
				}
				break;

			case k_EButton_SteamVR_Touchpad:
				switch (vrEvent.eventType)
				{
				case VREvent_ButtonPress:
					Axis_Id = (u_int)k_EButton_SteamVR_Touchpad - (u_int)vr::k_EButton_Axis0;
					if (Identify_Controller(vrEvent.trackedDeviceIndex) == 1)
					{
						printf("x data: %f\n", vr_controller_state.rAxis[Axis_Id].x);
						printf("y data: %f\n", vr_controller_state.rAxis[Axis_Id].y);

						if (vr_controller_state.rAxis[Axis_Id].y > 0.5f)
						{
							printf("Touchpad Press Up\n");
							movement->fZ = 0.0f;
							movement->fX = 1.0f;
						}

						if (vr_controller_state.rAxis[Axis_Id].y < -0.5f)
						{
							printf("Touchpad Press Down\n");
							movement->fX = 0.0f;
							movement->fZ = 1.0f;
						}

						if (vr_controller_state.rAxis[Axis_Id].x < -0.5f)
						{
							printf("Touchpad Press Left\n");
							movement->fY = 0.0f;
							movement->fW = 1.0f;
						}

						if (vr_controller_state.rAxis[Axis_Id].x > 0.5f)
						{
							printf("Touchpad Press Right\n");
							movement->fW = 0.0f;
							movement->fY = 1.0f;
						}
					}
					else if (Identify_Controller(vrEvent.trackedDeviceIndex) == 2)
						printf("Touchpad Press\n");
					break;

				case VREvent_ButtonUnpress:
					printf("Touchpad unPress\n");
					if (Identify_Controller(vrEvent.trackedDeviceIndex) == 1)
					{
						movement->fX = 0.0f;
						movement->fY = 0.0f;
						movement->fZ = 0.0f;
						movement->fW = 0.0f;
					}
					break;

				case VREvent_ButtonTouch:
					printf("Touchpad Touch\n");
					break;

				case VREvent_ButtonUntouch:
					printf("Touchpad unTouch\n");
					break;

				}
				break;

			case k_EButton_ApplicationMenu:
				switch (vrEvent.eventType)
				{
				case VREvent_ButtonPress:
					if (Identify_Controller(vrEvent.trackedDeviceIndex) == 1)
						printf("ApplicationMenu Press\n");
					else if (Identify_Controller(vrEvent.trackedDeviceIndex) == 2)
						printf("ApplicationMenu Press\n");
					break;

				case VREvent_ButtonUnpress:
					printf("ApplicationMenu unPress\n");
					break;
				}
				break;

			default:
				break;
			}
		}

		const Matrix4 & mat = c_VR_Setup->Get_rmat4DevicePose()[unTrackedDevice];

		if (Identify_Controller(unTrackedDevice) == 1)
		{
			Matrix4 controller_pose = mat * tFloat4x4_To_Matrix4(offset);
			Set_Left_Hand(tFloat3{ controller_pose[12], controller_pose[13], controller_pose[14] });
		}
		else if (Identify_Controller(unTrackedDevice) == 2)
		{
			Matrix4 controller_pose = mat * tFloat4x4_To_Matrix4(offset);
			Set_Right_Hand(tFloat3{ controller_pose[12], controller_pose[13], controller_pose[14] });
		}

		Vector4 center = mat * Vector4(0, 0, 0, 1);

		for (int i = 0; i < 3; ++i)
		{
			Vector3 color(0, 0, 0);
			Vector4 point(0, 0, 0, 1);
			point[i] += 0.05f;  // offset in X, Y, Z
			color[i] = 1.0;  // R, G, B
			point = mat * point;
			vertdataarray.push_back(center.x);
			vertdataarray.push_back(center.y);
			vertdataarray.push_back(center.z);

			vertdataarray.push_back(color.x);
			vertdataarray.push_back(color.y);
			vertdataarray.push_back(color.z);

			vertdataarray.push_back(point.x);
			vertdataarray.push_back(point.y);
			vertdataarray.push_back(point.z);

			vertdataarray.push_back(color.x);
			vertdataarray.push_back(color.y);
			vertdataarray.push_back(color.z);

			m_uiControllerVertcount += 2;
		}

		Vector4 start = mat * Vector4(0, 0, -0.02f, 1);
		Vector4 end = mat * Vector4(0, 0, -39.f, 1);
		Vector3 color(.92f, .92f, .71f);

		vertdataarray.push_back(start.x); vertdataarray.push_back(start.y); vertdataarray.push_back(start.z);
		vertdataarray.push_back(color.x); vertdataarray.push_back(color.y); vertdataarray.push_back(color.z);

		vertdataarray.push_back(end.x); vertdataarray.push_back(end.y); vertdataarray.push_back(end.z);
		vertdataarray.push_back(color.x); vertdataarray.push_back(color.y); vertdataarray.push_back(color.z);
		m_uiControllerVertcount += 2;
	}
}
