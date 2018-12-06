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

	/***************
	* Accessors
	***************/
	/*****************************************************************
	* Get_HMD():					Get the pointer to the HMD
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						IVRSystem*
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	IVRSystem* Get_HMD();
	/*****************************************************************
	* Get_fNearClip():				Get the NearClip
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						float
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	float Get_fNearClip();
	/*****************************************************************
	* Get_fFarClip():				Get the FarClip
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						float
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	float Get_fFarClip();
	/*****************************************************************
	* Get_fScaleSpacing():			Get the Scale Spacing
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						float
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	float Get_fScaleSpacing();
	/*****************************************************************
	* Get_fScale():					Get the Scale
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						float
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	float Get_fScale();
	/*****************************************************************
	* Get_mat4HMDPose():			Get the HMDPose (Position of Headset)
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						Matrix4
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	Matrix4 Get_mat4HMDPose();
	/*****************************************************************
	* Get_mat4eyePosLeft():			Get the eyePoseLeft (Position of Left Eye)
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						Matrix4
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	Matrix4 Get_mat4eyePosLeft();
	/*****************************************************************
	* Get_mat4eyePosRight():		Get the eyePoseRight (Position of Right Eye)
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						Matrix4
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	Matrix4 Get_mat4eyePosRight();
	/*****************************************************************
	* Get_mat4ProjectionLeft():		Get the ProjectionLeft (Projection of Left Eye)
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						Matrix4
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	Matrix4 Get_mat4ProjectionLeft();
	/*****************************************************************
	* Get_mat4ProjectionRight():	Get the ProjectionRight (Projection of Right Eye)
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						Matrix4
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	Matrix4 Get_mat4ProjectionRight();
	/*****************************************************************
	* Get_rTrackedDevicePose():		Get the TrackedDevicePose
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						TrackedDevicePose_t*
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	TrackedDevicePose_t* Get_rTrackedDevicePose();
	/*****************************************************************
	* Get_rmat4DevicePose():		Get the DevicePose
	*
	* Ins:							none
	*
	* Outs:							none
	*
	* Returns:						Matrix4*
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	Matrix4* Get_rmat4DevicePose();


	/***************
	* Mutators
	***************/
	/*****************************************************************
	* Set_mat4HMDPose():			Set the HMDPose (Position of Headset)
	*
	* Ins:							Matrix4
	*
	* Outs:							none
	*
	* Returns:						void
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	void Set_mat4HMDPose(Matrix4 _mat4HMDPose);
	/*****************************************************************
	* Set_mat4eyePosLeft():			Set the eyePoseLeft (Position of Left Eye)
	*
	* Ins:							Matrix4
	*
	* Outs:							none
	*
	* Returns:						void
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	void Set_mat4eyePosLeft(Matrix4 _mat4eyePosLeft);
	/*****************************************************************
	* Set_mat4eyePosRight():		Set the eyePoseRight (Position of Right Eye)
	*
	* Ins:							Matrix4
	*
	* Outs:							none
	*
	* Returns:						void
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	void Set_mat4eyePosRight(Matrix4 _mat4eyePosRight);
	/*****************************************************************
	* Set_mat4ProjectionLeft():		Set the ProjectionLeft (Projection of Left Eye)
	*
	* Ins:							Matrix4
	*
	* Outs:							none
	*
	* Returns:						void
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	void Set_mat4ProjectionLeft(Matrix4 _mat4ProjectionLeft);
	/*****************************************************************
	* Set_mat4ProjectionRight():	Set the ProjectionRight (Projection of Right Eye)
	*
	* Ins:							Matrix4
	*
	* Outs:							none
	*
	* Returns:						void
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	void Set_mat4ProjectionRight(Matrix4 _mat4ProjectionRight);
	/*****************************************************************
	* Set_rTrackedDevicePose():		Set the TrackedDevicePose
	*
	* Ins:							TrackedDevicePose_t[]
	*
	* Outs:							none
	*
	* Returns:						void
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	void Set_rTrackedDevicePose(TrackedDevicePose_t _rTrackedDevicePose[k_unMaxTrackedDeviceCount]);
	/*****************************************************************
	* Set_rmat4DevicePose():		Set the HMDPose (Position of Headset)
	*
	* Ins:							Matrix4[]
	*
	* Outs:							none
	*
	* Returns:						void
	*
	* Mod. Date:					30/11/2018
	* Mod. Initials:				WM
	*****************************************************************/
	void Set_rmat4DevicePose(Matrix4 _rmat4DevicePose[k_unMaxTrackedDeviceCount]);
};

