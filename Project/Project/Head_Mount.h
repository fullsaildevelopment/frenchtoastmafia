/************************************************************************
* Filename:  		Head_Mount.h
* Date:      		28/11/2018
* Mod. Date: 		03/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Handle Head Mount related task for VR
*************************************************************************/
#pragma once
#include "Graphic_Setup.h"
#include "VR_Setup.h"

class cHead_Mount
{
private:
	cGraphics_Setup* c_Graphics_Setup;
	cVR_Setup* c_VR_Setup;

	TrackedDevicePose_t m_rTrackedDevicePose[k_unMaxTrackedDeviceCount];
	Matrix4 m_rmat4DevicePose[k_unMaxTrackedDeviceCount];

	std::string m_strPoseClasses;                            // what classes we saw poses for this frame
	char m_rDevClassChar[k_unMaxTrackedDeviceCount];   // for each device, a character representing its class

	int m_iValidPoseCount;

public:
	cHead_Mount();
	~cHead_Mount();

	void Initialize(cGraphics_Setup* c_Graphics_Setup, cVR_Setup* _c_VR_Setup);
	void Clean_Up();

	Matrix4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	Matrix4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye);
	void SetupCameras();
	tFloat4x4 GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye);
	Matrix4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose);
	void UpdateHMDMatrixPose(tFloat4x4 offset);
	void VR_Render(tFloat4x4 offset);

	Matrix4 Get_HMDPose();
	tFloat4x4 GetStuff(vr::Hmd_Eye nEye);
};

