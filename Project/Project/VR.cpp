#include "VR.h"


cVR::cVR()
{
}


cVR::~cVR()
{
}

tFloat4x4 cVR::GetHMDMatrixPoseEye(vr::Hmd_Eye nEye)
{
	if (!m_pHMD)
	{
		return tFloat4x4();
	}

	vr::HmdMatrix34_t matEyeRight = m_pHMD->GetEyeToHeadTransform(nEye);
	tFloat4x4 in_mat, out_mat;

	in_mat.tX.fX = matEyeRight.m[0][0];
	in_mat.tX.fY = matEyeRight.m[1][0];
	in_mat.tX.fZ = matEyeRight.m[2][0];
	in_mat.tX.fW = 0.0f;

	in_mat.tY.fX = matEyeRight.m[0][1];
	in_mat.tY.fY = matEyeRight.m[1][1];
	in_mat.tY.fZ = matEyeRight.m[2][1];
	in_mat.tY.fW = 0.0f;
		  
	in_mat.tZ.fX = matEyeRight.m[0][2];
	in_mat.tZ.fY = matEyeRight.m[1][2];
	in_mat.tZ.fZ = matEyeRight.m[2][2];
	in_mat.tZ.fW = 0.0f;
		  
	in_mat.tW.fX = matEyeRight.m[0][3];
	in_mat.tW.fY = matEyeRight.m[1][3];
	in_mat.tW.fZ = matEyeRight.m[2][3];
	in_mat.tW.fW = 1.0f;

	out_mat = TMATRIX_To_tFloat4x4(Matrix_Inverse(tFloat4x4_To_TMATRIX(in_mat)));

	return out_mat;
}

tFloat4x4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye)
{
	if (!m_pHMD)
		return tFloat4x4();
	// TODO check here
	vr::HmdMatrix44_t mat = m_pHMD->GetProjectionMatrix(nEye, m_fNearClip, m_fFarClip);

	tFloat4x4 out_mat;

	out.tX.fX = mat.m[0][0];
	out.tX.fY = mat.m[1][0];
	out.tX.fZ = mat.m[2][0];
	out.tX.fW = mat.m[3][0];

	out.tY.fX = mat.m[0][1];
	out.tY.fY = mat.m[1][1];
	out.tY.fZ = mat.m[2][1];
	out.tY.fW = mat.m[3][1];

	out.tZ.fX = mat.m[0][2];
	out.tZ.fY = mat.m[1][2];
	out.tZ.fZ = mat.m[2][2];
	out.tZ.fW = mat.m[3][2];

	out.tW.fX = mat.m[0][3];
	out.tW.fY = mat.m[1][3];
	out.tW.fZ = mat.m[2][3];
	out.tW.fW = mat.m[3][3];

	return out_mat;
}

void SetupCameras()
{
	m_tMat4ProjectionLeft = GetHMDMatrixProjectionEye(vr::Eye_Left);
	m_tMat4ProjectionRight = GetHMDMatrixProjectionEye(vr::Eye_Right);
	m_tMat4eyePosLeft = GetHMDMatrixPoseEye(vr::Eye_Left);
	m_tMat4eyePosRight = GetHMDMatrixPoseEye(vr::Eye_Right);

}

tFloat4x4 GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye)
{
	tFloat4x4 matMVP;
	if (nEye == vr::Eye_Left)
	{
		matMVP = TMATRIX_To_tFloat4x4(Matrix_Matrix_Multiply(Matrix_Matrix_Multiply(tFloat4x4_To_TMATRIX(m_tMat4ProjectionLeft), tFloat4x4_To_TMATRIX(m_tMat4eyePosLeft)), tFloat4x4_To_TMATRIX(m_tMat4HMDPose)));
	}
	else if (nEye == vr::Eye_Right)
	{
		matMVP = TMATRIX_To_tFloat4x4(Matrix_Matrix_Multiply(Matrix_Matrix_Multiply(tFloat4x4_To_TMATRIX(m_tMat4ProjectionRight), tFloat4x4_To_TMATRIX(m_tMat4eyePosRight)), tFloat4x4_To_TMATRIX(m_tMat4HMDPose)));
	}

	return matMVP;
}

tFloat4x4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose)
{
	tFloat4x4 tMatrixObj;

	tMatrixObj.tX.fX = matPose.m[0][0];
	tMatrixObj.tX.fY = matPose.m[1][0];
	tMatrixObj.tX.fZ = matPose.m[2][0];
	tMatrixObj.tX.fW = 0.0f;

	tMatrixObj.tY.fX = matPose.m[0][1];
	tMatrixObj.tY.fY = matPose.m[1][1];
	tMatrixObj.tY.fZ = matPose.m[2][1];
	tMatrixObj.tY.fW = 0.0f;

	tMatrixObj.tZ.fX = matPose.m[0][2];
	tMatrixObj.tZ.fY = matPose.m[1][2];
	tMatrixObj.tZ.fZ = matPose.m[2][2];
	tMatrixObj.tZ.fW = 0.0f;

	tMatrixObj.tW.fX = matPose.m[0][3];
	tMatrixObj.tW.fY = matPose.m[1][3];
	tMatrixObj.tW.fZ = matPose.m[2][3];
	tMatrixObj.tW.fW = 1.0f;

	return tMatrixObj;
}

void UpdateHMDMatrixPose()
{
	if (!m_pHMD)
		return;

	vr::VRCompositor()->WaitGetPoses(m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

	m_nValidPoseCount = 0;
	m_strPoseClasses = "";
	for (int nDevice = 0; nDevice < vr::k_unMaxTrackedDeviceCount; ++nDevice)
	{
		if (m_rTrackedDevicePose[nDevice].bPoseIsValid)
		{
			m_nValidPoseCount++;
			m_tMat4HMDPose[nDevice] = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking);
			if (m_rDevClassChar[nDevice] == 0)
			{
				switch (m_pHMD->GetTrackedDeviceClass(nDevice))
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
		m_mat4HMDPose = m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd].invert();
	}
	else
	{
		dprintf("pose not valid");
	}
}

bool cVR::Initialize(HWND hWnd)
{
	// Create the camera object.
	m_cCameraLeft = new cCamera;
	if (!m_cCameraLeft)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_cCameraLeft->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the camera object.
	m_CameraRight = new CameraClass;
	if (!m_CameraRight)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_CameraRight->SetPosition(1.5f, 0.0f, -10.0f);

	// Create the render to texture object.
	m_cRenderLeft = new cRender_Manager;
	if (!m_cRenderLeft)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_cRenderLeft->Initialize(pDevice, m_nRenderWidth, m_nRenderHeight);
	if (!result)
	{
		return false;
	}

	m_RenderTextureRight = new RenderTextureClass;
	if (!m_RenderTextureRight)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTextureRight->Initialize(pDevice, m_nRenderWidth, m_nRenderHeight);
	if (!result)
	{
		return false;
	}
}