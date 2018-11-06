#include "VR.h"


cVR::cVR()
{
}


cVR::~cVR()
{
}

void cVR::Initialize(cGraphics_Setup* _setup)
{
	c_Graphics_Setup = _setup;
}

void cVR::VR_Render()
{
	vr::Texture_t leftEyeTexture = { c_Graphics_Setup->Get_Texture_Left_Eye() , vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::EVRCompositorError error1 = vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
	vr::Texture_t rightEyeTexture = { c_Graphics_Setup->Get_Texture_Right_Eye(), vr::TextureType_DirectX, vr::ColorSpace_Auto };
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

	c_Graphics_Setup->UpdateHMDMatrixPose();
}

void cVR::update_controller()
{
	cGraphics_Setup gx_setup;
	std::vector<float> vert_DATA;

	vr::TrackedDeviceIndex_t non_tracking_device;

	if (!gx_setup.get_m_pHMD().IsInputAvailable())
	{
		return;
	}

	int tracked_controller_count;
	unsigned int controller_vert_count;

	tracked_controller_count = gx_setup.get_tracked_controller_count();
	controller_vert_count = gx_setup.get_controller_vert_count();

	for (non_tracking_device = vr::k_unTrackedDeviceIndex_Hmd + 1; non_tracking_device < vr::k_unMaxTrackedDeviceCount; non_tracking_device++)
	{
		if (!gx_setup.get_m_pHMD().IsTrackedDeviceConnected(non_tracking_device))
		{
			continue;
		}

		if (gx_setup.get_m_pHMD().GetTrackedDeviceClass(non_tracking_device) != vr::TrackedDeviceClass_Controller)
		{
			continue;
		}

		tracked_controller_count += 1;

		if (!gx_setup.get_tracked_device_pose()[unTrackedDevice].bPoseIsValid)
		{
			continue;
		}

		const Matrix4 &matrix = gx_setup.get_matrix4_device_pose()[non_tracking_device];

		Vector4 center_point;
		Vector4 temp_vec;
		temp_vec = { 0, 0, 0, 1 };

		center_point = (matrix * temp_vec);

		for (int k = 0; k < 3; k++)
		{
			Vector3 color(1, 0, 0);
			Vector4 vr_point(0, 0, 0, 1);

			color[k] = 1.0f;
			vr_point[k] += 0.05f;


		}
	}
}
