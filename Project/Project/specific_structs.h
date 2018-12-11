/************************************************************************
* Filename:  		Specific_Structs.h
* Date:      		02/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Additional specific structs to hold different datatype and make accessing them easier.
*************************************************************************/
#pragma once

#include "Basic_Structs.h"
#include "openvr\headers\openvr.h"
#pragma comment (lib, "openvr_api.lib")
#include "Renderer_Structs.h"

using namespace vr;

struct VREvent_t
{
	EVREventType eventType;
	TrackedDeviceIndex_t trackedDeviceIndex;
	VREvent_Data_t data;
	float eventAgeSeconds;
};

struct tBinary_Screen
{
	int nObject_Count;
	tMesh tMes;
	bool vs_check;
	std::string vs_name;
	bool ps_check;
	std::string ps_name;
	bool srv_check;
	std::string srv_name;
};
