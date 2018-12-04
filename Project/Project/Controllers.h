/************************************************************************
* Filename:  		Controller.h
* Date:      		29/11/2018
* Mod. Date: 		03/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Handle Controller related task for VR
*************************************************************************/
#pragma once
#include "Math_Conversion.h"
#include "VR_Setup.h"

class cControllers
{
private:
	tFloat3 tLeft_Hand, tRight_Hand;
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
	
	tFloat3 Get_Left_Hand();
	tFloat3 Get_Right_Hand();

	void Set_Left_Hand(tFloat3 left);
	void Set_Right_Hand(tFloat3 right);

	int Identify_Controller(TrackedDeviceIndex_t vr_event);
	void Update_Controller(int nScene_Id, bool *bChange_Scene, bool *bMove_Bullet, tFloat4 *movement, tFloat4x4 offset);
};

