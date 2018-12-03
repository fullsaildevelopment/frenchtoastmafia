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

	return matrixObj.invert();
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

tFloat4x4 cHead_Mount::GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye)
{
	tFloat4x4 out_mat;
	Matrix4 matMVP;
	if (nEye == vr::Eye_Left)
	{
		matMVP = c_VR_Setup->Get_mat4ProjectionLeft() * c_VR_Setup->Get_mat4eyePosLeft() * c_VR_Setup->Get_mat4HMDPose();
	}
	else if (nEye == vr::Eye_Right)
	{
		matMVP = c_VR_Setup->Get_mat4ProjectionRight() * c_VR_Setup->Get_mat4eyePosRight() * c_VR_Setup->Get_mat4HMDPose();
	}

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

void cHead_Mount::UpdateHMDMatrixPose(tFloat4x4 offset)
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
		//c_VR_Setup->Set_mat4HMDPose(m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd].invert());
		Matrix4 hmd = m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd];
		hmd = hmd * tFloat4x4_To_Matrix4(offset);
		hmd = hmd.invert();
		c_VR_Setup->Set_mat4HMDPose(hmd);
	}
	c_VR_Setup->Set_rTrackedDevicePose(m_rTrackedDevicePose);
	c_VR_Setup->Set_rmat4DevicePose(m_rmat4DevicePose);
}

void cHead_Mount::VR_Render(tFloat4x4 offset)
{
	vr::Texture_t leftEyeTexture = { c_Graphics_Setup->Get_Texture_Left_Eye().Get(), vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::EVRCompositorError error1 = vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
	vr::Texture_t rightEyeTexture = { c_Graphics_Setup->Get_Texture_Right_Eye().Get(), vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

	UpdateHMDMatrixPose(offset);
}
