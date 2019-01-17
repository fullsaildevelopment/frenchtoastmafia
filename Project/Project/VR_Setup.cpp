/************************************************************************
* Filename:  		VR_Setup.cpp
* Date:      		28/11/2018
* Mod. Date: 		03/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Initialization of VR system
*************************************************************************/
#include "VR_Setup.h"

cVR_Setup::cVR_Setup()
{
}

cVR_Setup::~cVR_Setup()
{
}

void cVR_Setup::Initialize()
{
	EVRInitError eError = VRInitError_None;
	m_pHMD = VR_Init(&eError, VRApplication_Scene);
	m_pRenderModels = (IVRRenderModels *)VR_GetGenericInterface(IVRRenderModels_Version, &eError);
	
	m_fFarClip = 1000.0f;
	m_fNearClip = 0.1f;
	m_fScale = 0.3f;
	m_fScaleSpacing = 4.0f;

	m_mat4HMDPose = Matrix4();
	m_mat4eyePosLeft = Matrix4();
	m_mat4eyePosRight = Matrix4();
	m_mat4ProjectionLeft = Matrix4();
	m_mat4ProjectionRight = Matrix4();
}

void cVR_Setup::Clean_Up()
{
}

/***************
* Accessors
***************/

IVRSystem* cVR_Setup::Get_HMD()
{
	return m_pHMD;
}

float cVR_Setup::Get_fNearClip()
{
	return m_fNearClip;
}

float cVR_Setup::Get_fFarClip()
{
	return m_fFarClip;
}

float cVR_Setup::Get_fScaleSpacing()
{
	return m_fScaleSpacing;
}

float cVR_Setup::Get_fScale()
{
	return m_fScale;
}

Matrix4 cVR_Setup::Get_mat4HMDPose()
{
	return m_mat4HMDPose;
}

Matrix4 cVR_Setup::Get_mat4eyePosLeft()
{
	return m_mat4eyePosLeft;
}

Matrix4 cVR_Setup::Get_mat4eyePosRight()
{
	return m_mat4eyePosRight;
}

Matrix4 cVR_Setup::Get_mat4ProjectionLeft()
{
	return m_mat4ProjectionLeft;
}

Matrix4 cVR_Setup::Get_mat4ProjectionRight()
{
	return m_mat4ProjectionRight;
}

TrackedDevicePose_t* cVR_Setup::Get_rTrackedDevicePose()
{
	return m_rTrackedDevicePose;
}

Matrix4* cVR_Setup::Get_rmat4DevicePose()
{
	return m_rmat4DevicePose;
}

/***************
* Mutators
***************/

void cVR_Setup::Set_mat4HMDPose(Matrix4 _mat4HMDPose)
{
	m_mat4HMDPose = _mat4HMDPose;
}

void cVR_Setup::Set_mat4eyePosLeft(Matrix4 _mat4eyePosLeft)
{
	m_mat4eyePosLeft = _mat4eyePosLeft;
}

void cVR_Setup::Set_mat4eyePosRight(Matrix4 _mat4eyePosRight)
{
	m_mat4eyePosRight = _mat4eyePosRight;
}

void cVR_Setup::Set_mat4ProjectionLeft(Matrix4 _mat4ProjectionLeft)
{
	m_mat4ProjectionLeft = _mat4ProjectionLeft;
}

void cVR_Setup::Set_mat4ProjectionRight(Matrix4 _mat4ProjectionRight)
{
	m_mat4ProjectionRight = _mat4ProjectionRight;
}

void cVR_Setup::Set_rTrackedDevicePose(TrackedDevicePose_t _rTrackedDevicePose[k_unMaxTrackedDeviceCount])
{
	for (int i = 0; i < k_unMaxTrackedDeviceCount; i++)
	{
		m_rTrackedDevicePose[i] = _rTrackedDevicePose[i];
	}
}

void cVR_Setup::Set_rmat4DevicePose(Matrix4 _rmat4DevicePose[k_unMaxTrackedDeviceCount])
{
	for (int i = 0; i < k_unMaxTrackedDeviceCount; i++)
	{
		m_rmat4DevicePose[i] = _rmat4DevicePose[i];
	}
}
