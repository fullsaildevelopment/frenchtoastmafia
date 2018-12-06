/************************************************************************
* Filename:  		VR.h
* Date:      		24/10/2018
* Mod. Date: 		02/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to VR related task.
*************************************************************************/
#pragma once
#include "dopeSoundSystem.h"
#include "Graphic_Setup.h"
#include "Matrices.h"

using namespace vr;

class cVR
{
private:
	cGraphics_Setup* c_Graphics_Setup;
	
	Matrix4 m_mat4HMDPose;
	Matrix4 m_mat4eyePosLeft;
	Matrix4 m_mat4eyePosRight;

	Matrix4 m_mat4ProjectionCenter;
	Matrix4 m_mat4ProjectionLeft;
	Matrix4 m_mat4ProjectionRight;

	TrackedDevicePose_t m_rTrackedDevicePose[k_unMaxTrackedDeviceCount];
	Matrix4 m_rmat4DevicePose[k_unMaxTrackedDeviceCount];
	bool m_rbShowTrackedDevice[k_unMaxTrackedDeviceCount];

	std::string m_strPoseClasses;                            // what classes we saw poses for this frame
	char m_rDevClassChar[k_unMaxTrackedDeviceCount];   // for each device, a character representing its class

	unsigned int m_uiControllerVertcount = 0;

	int m_iTrackedControllerCount = 0;
	int m_iTrackedControllerCount_Last;
	int m_iValidPoseCount;
	int m_iValidPoseCount_Last;
	bool m_bShowCubes;

	//input
	float moveSpeed = 2.0f;

	float moveMeOnXScotty = 0;
	float moveMeOnYScotty = 0;
	float moveMeOnZScotty = 0;
	float rotationY = 0;

	dopeSoundSystem sound;

	bool swapped = false;
	bool hold_trigger = false;

	bool move_forward = false;
	bool move_backward = false;
	bool move_left = false;
	bool move_right = false;

public:
	cVR();
	~cVR();

	void Initialize(cGraphics_Setup* c_Graphics_Setup);

	

	Matrix4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	Matrix4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye);
	void SetupCameras();
	tFloat4x4 GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye);
	Matrix4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose);
	void UpdateHMDMatrixPose();
	void VR_Render();
	unsigned int get_controller_vert_count();
	int get_tracked_controller_count();
	int is_right_hand_controller(TrackedDeviceIndex_t vr_event);
	void get_controller_pose();
	void update_controller(double dDelta, int nScene_Id, bool *bChange_Scene, bool *bMove_Bullet, tFloat3 *lhand);
	void handle_input(double dDelta, int nScene_Id, bool *bChange_Scene, bool *bMove_Bullet, TrackedDeviceIndex_t unTrackingDevice);
	void swap_controller_roles(vr::TrackedDeviceIndex_t non_tracking_device);
};

