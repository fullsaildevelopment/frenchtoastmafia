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


Matrix4 cVR::GetHMDMatrixPoseEye(vr::Hmd_Eye nEye)
{
	if (!c_Graphics_Setup->Get_HMD())
		return Matrix4();

	vr::HmdMatrix34_t matEyeRight = c_Graphics_Setup->Get_HMD()->GetEyeToHeadTransform(nEye);
	Matrix4 matrixObj(
		matEyeRight.m[0][0], matEyeRight.m[1][0], matEyeRight.m[2][0], 0.0,
		matEyeRight.m[0][1], matEyeRight.m[1][1], matEyeRight.m[2][1], 0.0,
		matEyeRight.m[0][2], matEyeRight.m[1][2], matEyeRight.m[2][2], 0.0,
		matEyeRight.m[0][3], matEyeRight.m[1][3], matEyeRight.m[2][3], 1.0f
	);

	return matrixObj.invert();
}

Matrix4 cVR::GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye)
{
	if (!c_Graphics_Setup->Get_HMD())
		return Matrix4();
	// TODO check here
	vr::HmdMatrix44_t mat = c_Graphics_Setup->Get_HMD()->GetProjectionMatrix(nEye, fNearClip, fFarClip);

	Matrix4 tmpMatrix(
		mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
		mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
		mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
		mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
	);

	return tmpMatrix;
}

void cVR::SetupCameras()
{
	m_mat4ProjectionLeft = GetHMDMatrixProjectionEye(vr::Eye_Left);
	m_mat4ProjectionRight = GetHMDMatrixProjectionEye(vr::Eye_Right);
	m_mat4eyePosLeft = GetHMDMatrixPoseEye(vr::Eye_Left);
	m_mat4eyePosRight = GetHMDMatrixPoseEye(vr::Eye_Right);
}

tFloat4x4 cVR::GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye)
{
	tFloat4x4 out_mat;
	Matrix4 matMVP;
	if (nEye == vr::Eye_Left)
	{
		matMVP = m_mat4ProjectionLeft * m_mat4eyePosLeft * m_mat4HMDPose;
	}
	else if (nEye == vr::Eye_Right)
	{
		matMVP = m_mat4ProjectionRight * m_mat4eyePosRight * m_mat4HMDPose;
	}

	out_mat = Matrix4_To_tFloat4x4(matMVP);
	return out_mat;
}

Matrix4 cVR::ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose)
{
	Matrix4 matrixObj(
		matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0,
		matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0,
		matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0,
		matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
	);
	return matrixObj;
}

void cVR::UpdateHMDMatrixPose()
{
	if (!c_Graphics_Setup->Get_HMD())
		return;

	vr::VRCompositor()->WaitGetPoses(m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

	m_iValidPoseCount = 0;
	m_strPoseClasses = "";
	for (int nDevice = 0; nDevice < vr::k_unMaxTrackedDeviceCount; ++nDevice)
	{
		if (m_rTrackedDevicePose[nDevice].bPoseIsValid)
		{
			m_iValidPoseCount++;
			m_rmat4DevicePose[nDevice] = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking);

			//if (c_Graphics_Setup->Get_HMD()->GetTrackedDeviceClass(nDevice) != vr::TrackedDeviceClass_HMD)
			//{
			//	m_rmat4DevicePose[nDevice] = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking);
			//}
			//else
			//{
			//	m_rmat4DevicePose[nDevice] = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking);
			//	m_rmat4DevicePose[nDevice].rotateY(rotationY);
			//	m_rmat4DevicePose[nDevice].translate(moveMeOnXScotty, moveMeOnYScotty, moveMeOnZScotty);
			//}

			if (m_rDevClassChar[nDevice] == 0)
			{
				switch (c_Graphics_Setup->Get_HMD()->GetTrackedDeviceClass(nDevice))
				{
				case vr::TrackedDeviceClass_Controller:        m_rDevClassChar[nDevice] = 'C'; break;
				case vr::TrackedDeviceClass_HMD:               m_rDevClassChar[nDevice] = 'H'; break;
				case vr::TrackedDeviceClass_Invalid:           m_rDevClassChar[nDevice] = 'I'; break;
				case vr::TrackedDeviceClass_GenericTracker:    m_rDevClassChar[nDevice] = 'O'; break;
				case vr::TrackedDeviceClass_TrackingReference: m_rDevClassChar[nDevice] = 'T'; break;
				default:                                       m_rDevClassChar[nDevice] = '?'; break;
				}
			}
			m_strPoseClasses += m_rDevClassChar[nDevice];
		}
	}

	if (m_rTrackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
	{
		//Matrix4 offset_matrix(
		//	1, 0, 0, 0,
		//	0, 1, 0, 0,
		//	0, 0, 1, 0,
		//	0, 0, 0, 1
		//);
		//
		//if (move_forward)
		//{
		//	movement_matrix[14] = 25 * dDelta;
		//	m_mat4HMDPose.translate(0, 0, 25 * dDelta);
		//
		//}

		m_mat4HMDPose = m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd].invert();

		//m_mat4HMDPose = m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd];
		//m_mat4HMDPose = m_mat4HMDPose * offset_matrix;
		//m_mat4HMDPose = m_mat4HMDPose.invert();
	}
}

void cVR::VR_Render()
{
	vr::Texture_t leftEyeTexture = { c_Graphics_Setup->Get_Texture_Left_Eye().Get(), vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::EVRCompositorError error1 = vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
	vr::Texture_t rightEyeTexture = { c_Graphics_Setup->Get_Texture_Right_Eye().Get(), vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

	UpdateHMDMatrixPose();
}


unsigned int cVR::get_controller_vert_count()
{
	return m_uiControllerVertcount;
}

int cVR::get_tracked_controller_count()
{
	return m_iTrackedControllerCount;
}

int cVR::is_right_hand_controller(TrackedDeviceIndex_t vr_event)
{
	//VREvent_t vr_event;

	ETrackedDeviceClass trackedDeviceClass;
	trackedDeviceClass = c_Graphics_Setup->Get_HMD()->GetTrackedDeviceClass(vr_event);

	if (trackedDeviceClass != ETrackedDeviceClass::TrackedDeviceClass_Controller)
	{
		return -1;
	}

	ETrackedControllerRole controller_role;

	controller_role = c_Graphics_Setup->Get_HMD()->GetControllerRoleForTrackedDeviceIndex(vr_event);
	
	if (controller_role == TrackedControllerRole_Invalid)
	{
		return -2;
	}
	else if (controller_role == TrackedControllerRole_LeftHand)
	{
		return 1;
	}
	else if (controller_role == TrackedControllerRole_RightHand)
	{
		return 2;
	}
}

void cVR::get_controller_pose()
{
	for (unsigned int ID = 0; ID < k_unMaxTrackedDeviceCount; ID++)
	{
		ETrackedDeviceClass tracked_device_class;

		tracked_device_class = c_Graphics_Setup->Get_HMD()->GetTrackedDeviceClass(ID);

		if (tracked_device_class != ETrackedDeviceClass::TrackedDeviceClass_Controller || !c_Graphics_Setup->Get_HMD()->IsTrackedDeviceConnected(ID))
		{
			continue;
		}

		VRControllerState_t vr_controller_state;
		TrackedDevicePose_t tracked_device_pose;

		c_Graphics_Setup->Get_HMD()->GetControllerStateWithPose(TrackingUniverseStanding, ID, &vr_controller_state, sizeof(vr_controller_state), &tracked_device_pose);
	}
}

void cVR::update_controller(double dDelta, int nScene_Id, bool *bChange_Scene, bool *bMove_Bullet, tFloat3 *lhand)
{
	std::vector<float> vert_DATA;

	vr::TrackedDeviceIndex_t non_tracking_device;

	if (!c_Graphics_Setup->Get_HMD()->IsInputAvailable())
	{
		return;
	}

	int tracked_controller_count;
	unsigned int controller_vert_count;

	tracked_controller_count = m_iTrackedControllerCount;
	controller_vert_count = m_uiControllerVertcount;

	for (non_tracking_device = vr::k_unTrackedDeviceIndex_Hmd + 1; non_tracking_device < vr::k_unMaxTrackedDeviceCount; non_tracking_device++)
	{
		if (!c_Graphics_Setup->Get_HMD()->IsTrackedDeviceConnected(non_tracking_device))
		{
			continue;
		}

		if (c_Graphics_Setup->Get_HMD()->GetTrackedDeviceClass(non_tracking_device) != vr::TrackedDeviceClass_Controller)
		{
			continue;
		}

		tracked_controller_count += 1;

		if (!m_rTrackedDevicePose[non_tracking_device].bPoseIsValid)
		{
			continue;
		}

		if (is_right_hand_controller(non_tracking_device) > 0)
		{
			handle_input(dDelta, nScene_Id, bChange_Scene, bMove_Bullet, non_tracking_device);
		}

		const Matrix4 &matrix = m_rmat4DevicePose[non_tracking_device];   // controller matrix   // draw a object using that matrix

																		  //if (is_right_hand_controller(vr::even))
		if (is_right_hand_controller(non_tracking_device) == 2)
		{

		}

		else if (is_right_hand_controller(non_tracking_device) == 1)
		{
			lhand->fX = matrix[12];
			lhand->fY = matrix[13];
			lhand->fZ = matrix[14];
		}

		Vector4 center_point;
		Vector4 temp_vec;
		temp_vec = { 0, 0, 0, 1 };

		center_point = (matrix * temp_vec);

		for (int k = 0; k < 3; k++)
		{
			Vector3 color(1, 0, 0);
			Vector4 vr_point(0, 0, 0, 1);

			color[k] = 1.0f;
			vr_point[k] += 0.05f;

			vr_point = (vr_point * matrix);

			vert_DATA.push_back(center_point.x);
			vert_DATA.push_back(center_point.y);
			vert_DATA.push_back(center_point.z);

			vert_DATA.push_back(color.x);
			vert_DATA.push_back(color.y);
			vert_DATA.push_back(color.z);

			vert_DATA.push_back(vr_point.x);
			vert_DATA.push_back(vr_point.y);
			vert_DATA.push_back(vr_point.z);

			vert_DATA.push_back(color.x);
			vert_DATA.push_back(color.y);
			vert_DATA.push_back(color.z);

			controller_vert_count += 2;
		}

		Vector4 starting_point;
		starting_point = matrix * Vector4(0, 0, -0.02f, 1);

		Vector4 end_point;
		end_point = matrix * Vector4(0, 0, -39.0f, 1);

		Vector3 color(0.6f, 0.0f, 1.0f);

		vert_DATA.push_back(starting_point.x);
		vert_DATA.push_back(starting_point.y);
		vert_DATA.push_back(starting_point.z);

		vert_DATA.push_back(color.x);
		vert_DATA.push_back(color.y);
		vert_DATA.push_back(color.z);

		vert_DATA.push_back(end_point.x);
		vert_DATA.push_back(end_point.y);
		vert_DATA.push_back(end_point.z);

		vert_DATA.push_back(color.x);
		vert_DATA.push_back(color.y);
		vert_DATA.push_back(color.z);

		controller_vert_count += 2;
	}
}

void cVR::handle_input(double dDelta, int nScene_Id, bool *bChange_Scene, bool *bMove_Bullet, TrackedDeviceIndex_t unTrackingDevice)
{
	TrackedDevicePose_t trackedDevicePose;
	VRControllerState001_t vr_controller_state;
	c_Graphics_Setup->Get_HMD()->GetControllerStateWithPose(TrackingUniverseStanding, unTrackingDevice, &vr_controller_state, sizeof(VRControllerState001_t), &trackedDevicePose);
	vr::VREvent_t vrEvent;
	c_Graphics_Setup->Get_HMD()->PollNextEventWithPose(TrackingUniverseStanding, &vrEvent, sizeof(vrEvent), &trackedDevicePose);
	u_int Axis_Id;
	
	// -1 = not controller  -2 = role not valid   1 = left controller   2 = right controller
	if (is_right_hand_controller(vrEvent.trackedDeviceIndex) > 0)
	{
		printf("%d : ", is_right_hand_controller(vrEvent.trackedDeviceIndex));
		switch (vrEvent.data.controller.button)
		{
		case k_EButton_Grip:
			switch (vrEvent.eventType)
			{
			case VREvent_ButtonPress:
				if (is_right_hand_controller(vrEvent.trackedDeviceIndex) == 1)
				{
					printf("Grip Press\n");
				}
				else if (is_right_hand_controller(vrEvent.trackedDeviceIndex) == 2)
				{
					printf("Grip Press\n");
					break;
				}

			case VREvent_ButtonUnpress:
				printf("Grip unPress\n");
				break;
			}
			break;

		case k_EButton_SteamVR_Trigger:
			switch (vrEvent.eventType)
			{
			case VREvent_ButtonPress:
				if (is_right_hand_controller(vrEvent.trackedDeviceIndex) == 1)
				{
					printf("Trigger Press\n");
				}
				else if (is_right_hand_controller(vrEvent.trackedDeviceIndex) == 2)
				{
					printf("Trigger Press\n");
					if (nScene_Id == 2)
					{
						*bMove_Bullet = true;
					}
					else
						*bChange_Scene = true;
				}
				break;

			case VREvent_ButtonUnpress:
				if (is_right_hand_controller(vrEvent.trackedDeviceIndex) == 1)
				{
					printf("Trigger unPress\n");
				}
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
				if (is_right_hand_controller(vrEvent.trackedDeviceIndex) == 1)
				{
					printf("x data: %f\n", vr_controller_state.rAxis[Axis_Id].x);
					printf("y data: %f\n", vr_controller_state.rAxis[Axis_Id].y);

					if (vr_controller_state.rAxis[Axis_Id].y > 0.0f)
					{
						printf("Touchpad Press Up\n");
						move_backward = false;
						move_forward = true;
					}

					if (vr_controller_state.rAxis[Axis_Id].y < 0.0f)
					{
						printf("Touchpad Press Down\n");
						move_forward = false;
						move_backward = true;
					}

					if (vr_controller_state.rAxis[Axis_Id].x < 0.0f)
					{
						printf("Touchpad Press Left\n");

						move_right = false;
						move_left = true;
					}

					if (vr_controller_state.rAxis[Axis_Id].x > 0.0f)
					{
						printf("Touchpad Press Right\n");

						move_left = false;
						move_right = true;
					}

					//Movement_Handler(dDelta);
				}
				else if (is_right_hand_controller(vrEvent.trackedDeviceIndex) == 2)
				{
					printf("Touchpad Press\n");
				}
				break;

			case VREvent_ButtonUnpress:
				printf("Touchpad unPress\n");
				if (is_right_hand_controller(vrEvent.trackedDeviceIndex) == 1)
				{
					move_forward = false;
					move_backward = false;
					move_left = false;
					move_right = false;
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
				if (is_right_hand_controller(vrEvent.trackedDeviceIndex) == 1)
				{
					printf("ApplicationMenu Press\n");
				}
				else if (is_right_hand_controller(vrEvent.trackedDeviceIndex) == 2)
				{
					printf("ApplicationMenu Press\n");
					break;
				}

			case VREvent_ButtonUnpress:
				printf("ApplicationMenu unPress\n");
				break;
			}
			break;

		default:
			break;
		}
	}
}

void cVR::swap_controller_roles(vr::TrackedDeviceIndex_t non_tracking_device)
{
	ETrackedControllerRole controller_role;

	controller_role = c_Graphics_Setup->Get_HMD()->GetControllerRoleForTrackedDeviceIndex(non_tracking_device);

	if (controller_role == TrackedControllerRole_LeftHand)
	{
		controller_role = TrackedControllerRole_RightHand;
	}
	else if (controller_role == TrackedControllerRole_RightHand)
	{
		controller_role = TrackedControllerRole_LeftHand;
	}
}
