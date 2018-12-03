/************************************************************************
* Filename:  		Controller.h
* Date:      		29/11/2018
* Mod. Date: 		03/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Handle Controller related task for VR
*************************************************************************/
#pragma once
#include "VR_Setup.h"

class cControllers
{
private:
	cVR_Setup* c_VR_Setup;

	TrackedDevicePose_t m_rTrackedDevicePose[k_unMaxTrackedDeviceCount];
	Matrix4 m_rmat4DevicePose[k_unMaxTrackedDeviceCount];

	unsigned int m_uiControllerVertcount;
	unsigned int m_iTrackedControllerCount;

public:
	cControllers();
	~cControllers();

	void Initialize(cVR_Setup* _c_VR_Setup);
	void Clean_Up();
	
	int Identify_Controller(TrackedDeviceIndex_t vr_event);
	void Update_Controller(int nScene_Id, bool *bChange_Scene, bool *bMove_Bullet, tFloat3 *lhand, tFloat4 *movement);
};

