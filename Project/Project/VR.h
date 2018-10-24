#pragma once
#include "Camera.h"
#include "openvr\headers\openvr.h"
#include "Render_Manager.h"
#include "EngineMath.h"
#include "D3D11_Template_Gateware_v5d\D3D11_Template_Gateware\Gateware Redistribution R5d\Interface\G_Math\GMatrix.h"
class cVR
{
	cCamera *m_cCameraLeft = nullptr,
		    *m_cCameraRight = nullptr;
	//ModelClass* m_Model = nullptr;
	//ColorShaderClass* m_ColorShader = nullptr;
	cRender_Manager* m_cRenderLeft, *m_cRenderRight;
	//DebugWindowClass* m_DebugWindowLeft, *m_DebugWindowRight;
	GW::MATH::GMatrix *tmp;

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;

	float m_fNearClip;
	float m_fFarClip;
	float m_fScaleSpacing;
	float m_fScale;

	tFloat4x4 m_tMat4HMDPose;
	tFloat4x4 m_tMat4eyePosLeft;
	tFloat4x4 m_tMat4eyePosRight;

	tFloat4x4 m_tMat4ProjectionCenter;
	tFloat4x4 m_tMat4ProjectionLeft;
	tFloat4x4 m_tMat4ProjectionRight;

	vr::IVRSystem *m_pHMD;
	vr::IVRRenderModels *m_pRenderModels;
	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	tFloat4x4 m_tRMat4DevicePose[vr::k_unMaxTrackedDeviceCount];

	int m_nTrackedControllerCount;
	int m_nTrackedControllerCount_Last;
	int m_nValidPoseCount;
	int m_nValidPoseCount_Last;
	bool m_bShowCubes;

	std::string m_strPoseClasses;                            // what classes we saw poses for this frame
	char m_rDevClassChar[vr::k_unMaxTrackedDeviceCount];   // for each device, a character representing its class
/*
	namespace Memory
	{
		template <class T> void SafeDelete(T& t)
		{
			if (t)
			{
				delete t;
				t = nullptr;
			}
		}

		template <class T> void SafeDeleteArr(T& t)
		{
			if (t)
			{
				delete[]t;
				t = nullptr;
			}
		}

		template <class T> void SafeRelease(T& t)
		{
			if (t)
			{
				t->Release();
				t = nullptr;
			}
		}
	}
*/
public:
	cVR();
	~cVR();
	
	tFloat4x4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	tFloat4x4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye);
	void SetupCameras();
	bool init(HWND hWnd);
};

