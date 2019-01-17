/************************************************************************
* Filename:  		Head_Mount.cpp
* Date:      		28/11/2018
* Mod. Date: 		12/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Handle Head Mount related task for VR
*************************************************************************/
#include "Head_Mount.h"

cHead_Mount::cHead_Mount()
{
}

cHead_Mount::~cHead_Mount()
{
}

void cHead_Mount::Initialize(cGraphics_Setup* _c_Graphics_Setup, cVR_Setup* _c_VR_Setup)
{
	c_Graphics_Setup = _c_Graphics_Setup;
	c_VR_Setup = _c_VR_Setup;
}

void cHead_Mount::Clean_Up()
{
}

Matrix4 cHead_Mount::GetHMDMatrixPoseEye(vr::Hmd_Eye nEye)
{
	if (!c_VR_Setup->Get_HMD())
		return Matrix4();

	vr::HmdMatrix34_t matEye = c_VR_Setup->Get_HMD()->GetEyeToHeadTransform(nEye);
	Matrix4 matrixObj(
		matEye.m[0][0], matEye.m[1][0], matEye.m[2][0], 0.0,
		matEye.m[0][1], matEye.m[1][1], matEye.m[2][1], 0.0,
		matEye.m[0][2], matEye.m[1][2], matEye.m[2][2], 0.0,
		matEye.m[0][3], matEye.m[1][3], matEye.m[2][3], 1.0f
	);

	return matrixObj;
}

Matrix4 cHead_Mount::GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye)
{
	if (!c_VR_Setup->Get_HMD())
		return Matrix4();

	vr::HmdMatrix44_t matProj = c_VR_Setup->Get_HMD()->GetProjectionMatrix(nEye, c_VR_Setup->Get_fNearClip(), c_VR_Setup->Get_fFarClip());
	Matrix4 matrixObj(
		matProj.m[0][0], matProj.m[1][0], matProj.m[2][0], matProj.m[3][0],
		matProj.m[0][1], matProj.m[1][1], matProj.m[2][1], matProj.m[3][1],
		matProj.m[0][2], matProj.m[1][2], matProj.m[2][2], matProj.m[3][2],
		matProj.m[0][3], matProj.m[1][3], matProj.m[2][3], matProj.m[3][3]
	);

	return matrixObj;
}

void cHead_Mount::SetupCameras()
{
	c_VR_Setup->Set_mat4ProjectionLeft(GetHMDMatrixProjectionEye(vr::Eye_Left));
	c_VR_Setup->Set_mat4ProjectionRight(GetHMDMatrixProjectionEye(vr::Eye_Right));
	c_VR_Setup->Set_mat4eyePosLeft(GetHMDMatrixPoseEye(vr::Eye_Left));
	c_VR_Setup->Set_mat4eyePosRight(GetHMDMatrixPoseEye(vr::Eye_Right));
}

tFloat4x4 cHead_Mount::GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye, Matrix4 offset)
{
	tFloat4x4 out_mat;

	out_mat.tX.fX = 1.0f;
	out_mat.tX.fY = 0.0f;
	out_mat.tX.fZ = 0.0f;
	out_mat.tX.fW = 0.0f;

	out_mat.tY.fX = 0.0f;
	out_mat.tY.fY = 1.0f;
	out_mat.tY.fZ = 0.0f;
	out_mat.tY.fW = 0.0f;

	out_mat.tZ.fX = 0.0f;
	out_mat.tZ.fY = 0.0f;
	out_mat.tZ.fZ = 1.0f;
	out_mat.tZ.fW = 0.0f;

	out_mat.tW.fX = 0.0f;
	out_mat.tW.fY = 0.0f;
	out_mat.tW.fZ = 0.0f;
	out_mat.tW.fW = 1.0f;

	Matrix4 matMVP = Matrix4();
	if (nEye == vr::Eye_Left)
		matMVP = c_VR_Setup->Get_mat4ProjectionLeft() * (offset * c_VR_Setup->Get_mat4eyePosLeft() * c_VR_Setup->Get_mat4HMDPose()).invert();
	else if (nEye == vr::Eye_Right)
		matMVP = c_VR_Setup->Get_mat4ProjectionRight() * (offset * c_VR_Setup->Get_mat4eyePosRight() * c_VR_Setup->Get_mat4HMDPose()).invert();

	out_mat = Matrix4_To_tFloat4x4(matMVP);
	return out_mat;
}

Matrix4 cHead_Mount::ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t & matPose)
{
	Matrix4 matrixObj(
		matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0,
		matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0,
		matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0,
		matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
	);
	return matrixObj;
}

void cHead_Mount::UpdateHMDMatrixPose()
{
	if (!c_VR_Setup->Get_HMD())
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

			if (m_rDevClassChar[nDevice] == 0)
			{
				switch (c_VR_Setup->Get_HMD()->GetTrackedDeviceClass(nDevice))
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
		Matrix4 hmd = m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd];
		c_VR_Setup->Set_mat4HMDPose(hmd);
	}
	c_VR_Setup->Set_rTrackedDevicePose(m_rTrackedDevicePose);
	c_VR_Setup->Set_rmat4DevicePose(m_rmat4DevicePose);
}

void cHead_Mount::VR_Render()
{
	c_Graphics_Setup->Get_Swap_Chain().Get()->Present(1, 0);

	vr::Texture_t leftEyeTexture = { c_Graphics_Setup->Get_Texture_Left_Eye().Get(), vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::EVRCompositorError error1 = vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
	vr::Texture_t rightEyeTexture = { c_Graphics_Setup->Get_Texture_Right_Eye().Get(), vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

	UpdateHMDMatrixPose();
}

tFloat4x4 cHead_Mount::Get_mat4HMDPose()
{
	tFloat4x4 hmd = Matrix4_To_tFloat4x4(c_VR_Setup->Get_mat4HMDPose());
	return hmd;
}

tFloat4x4 cHead_Mount::Get_CurrentLook(tFloat4x4 offset)
{
	return Matrix4_To_tFloat4x4(tFloat4x4_To_Matrix4(offset) * c_VR_Setup->Get_mat4HMDPose());
}
