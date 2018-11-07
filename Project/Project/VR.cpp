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

	if (!vr::IVRSystem::IsInputAvailable())
	{
		return;
	}

	int tracked_controller_count;
	unsigned int controller_vert_count;

	tracked_controller_count = gx_setup.get_tracked_controller_count();
	controller_vert_count = gx_setup.get_controller_vert_count();

	for (non_tracking_device = vr::k_unTrackedDeviceIndex_Hmd + 1; non_tracking_device < vr::k_unMaxTrackedDeviceCount; non_tracking_device++)
	{
		if (!vr::IVRSystem::IsTrackedDeviceConnected(non_tracking_device))
		{
			continue;
		}

		if (vr::IVRSystem::GetTrackedDeviceClass(non_tracking_device) != vr::TrackedDeviceClass_Controller)
		{
			continue;
		}

		tracked_controller_count += 1;

		cGraphics_Setup::tTracked_device_pose track_pose;

		if (!track_pose.m_rTrackedDevicePose[non_tracking_device].bPoseIsValid)
		{
			continue;
		}

		cGraphics_Setup::tMatrix4_device_pose matrix_pose;

		const Matrix4 &matrix = matrix_pose.m_rmat4DevicePose[non_tracking_device];

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

			vr_point = (vr_point * matrix);

			vert_DATA.push_back(center_point.x);
			vert_DATA.push_back(center_point.y);
			vert_DATA.push_back(center_point.z);

			vert_DATA.push_back(color.x);
			vert_DATA.push_back(color.y);
			vert_DATA.push_back(color.z);

			vert_DATA.push_back(vr_point.x);
			vert_DATA.push_back(vr_point.y);
			vert_DATA.push_back(vr_point.z);

			vert_DATA.push_back(color.x);
			vert_DATA.push_back(color.y);
			vert_DATA.push_back(color.z);

			controller_vert_count += 2;
		}

		Vector4 starting_point;
		starting_point = matrix * Vector4(0, 0, -0.02f, 1);

		Vector4 end_point;
		end_point = matrix * Vector4(0, 0, -39.0f, 1);

		Vector3 color(0.6f, 0.0f, 1.0f);

		vert_DATA.push_back(starting_point.x);
		vert_DATA.push_back(starting_point.y);
		vert_DATA.push_back(starting_point.z);

		vert_DATA.push_back(color.x);
		vert_DATA.push_back(color.y);
		vert_DATA.push_back(color.z);

		vert_DATA.push_back(end_point.x);
		vert_DATA.push_back(end_point.y);
		vert_DATA.push_back(end_point.z);

		vert_DATA.push_back(color.x);
		vert_DATA.push_back(color.y);
		vert_DATA.push_back(color.z);

		controller_vert_count += 2;
	}


	//if (gx_setup.get_controller_axis_vertex_buffer() == nullptr && vert_DATA.size() > 0)
	//{
	//	size_t nSize_array;

	//	nSize_array = sizeof(float) * vert_DATA.size();
	//	nSize_array *= vr::k_unMaxTrackedDeviceCount;

	//	// create committed Resource d3d12 stuff
	//}

	//if (gx_setup.get_controller_axis_vertex_buffer && vert_DATA.size() > 0)
	//{
	//	UINT8 *pMappedBuffer;
	//	// CD3DX12_RANGE stuff

	//}
}
