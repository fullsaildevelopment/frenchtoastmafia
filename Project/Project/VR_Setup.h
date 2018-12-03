/************************************************************************
* Filename:  		VR_Setup.h
* Date:      		28/11/2018
* Mod. Date: 		03/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Initialization of VR system
*************************************************************************/
#pragma once

#include "Matrices.h"
#include "openvr\headers\openvr.h"
#pragma comment (lib, "openvr_api.lib")
#include "Specific_Structs.h"

using namespace vr;

class cVR_Setup
{
private:
	float m_fNearClip;
	float m_fFarClip;
	float m_fScaleSpacing;
	float m_fScale;

	IVRSystem *m_pHMD;
	IVRRenderModels *m_pRenderModels;

	Matrix4 m_mat4HMDPose;
	Matrix4 m_mat4eyePosLeft;
	Matrix4 m_mat4eyePosRight;
	Matrix4 m_mat4ProjectionLeft;
	Matrix4 m_mat4ProjectionRight;

	TrackedDevicePose_t m_rTrackedDevicePose[k_unMaxTrackedDeviceCount];
	Matrix4 m_rmat4DevicePose[k_unMaxTrackedDeviceCount];

public:
	cVR_Setup();
	~cVR_Setup();

	void Initialize();
	void Clean_Up();

	IVRSystem* Get_HMD();

	float Get_fNearClip();
	float Get_fFarClip();
	float Get_fScaleSpacing();
	float Get_fScale();

	Matrix4 Get_mat4HMDPose();
	Matrix4 Get_mat4eyePosLeft();
	Matrix4 Get_mat4eyePosRight();
	Matrix4 Get_mat4ProjectionLeft();
	Matrix4 Get_mat4ProjectionRight();

	void Set_mat4HMDPose(Matrix4 _mat4HMDPose);
	void Set_mat4eyePosLeft(Matrix4 _mat4eyePosLeft);
	void Set_mat4eyePosRight(Matrix4 _mat4eyePosRight);
	void Set_mat4ProjectionLeft(Matrix4 _mat4ProjectionLeft);
	void Set_mat4ProjectionRight(Matrix4 _mat4ProjectionRight);

	TrackedDevicePose_t* Get_rTrackedDevicePose();
	void Set_rTrackedDevicePose(TrackedDevicePose_t _rTrackedDevicePose[k_unMaxTrackedDeviceCount]);
	Matrix4* Get_rmat4DevicePose();
	void Set_rmat4DevicePose(Matrix4 _rmat4DevicePose[k_unMaxTrackedDeviceCount]);
};

