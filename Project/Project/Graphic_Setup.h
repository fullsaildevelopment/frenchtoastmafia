#pragma once

#include "Camera.h"
#include "defines.h"
#include "math_conversion.h"
#include "Matrices.h"
#include "openvr\headers\openvr.h"
//#include "openvr-master\headers\openvr.h"
//#pragma comment (lib, "openvr_api.lib")
#include "renderer_structs.h"
#include "specific_structs.h"
//#include "Matrices.h"

// Basic Shaders
#include "VertexShader.csh"
#include "PixelShader.csh"

using namespace vr;

class cGraphics_Setup
{
private:
	// HWND
	HWND hWnd;

	// RENDER
	CComPtr<ID3D11Device> d3d_Device;
	CComPtr<ID3D11DeviceContext> d3d_Context;
	CComPtr<IDXGISwapChain> d3d_Swap_Chain;
	CComPtr<ID3D11Texture2D> d3d_Z_Buffer;
	CComPtr<ID3D11DepthStencilView> d3d_DSV;
	CComPtr<ID3D11DepthStencilState> d3d_DSS;
	CComPtr<ID3D11DepthStencilState> d3d_2D_DSS;
	CComPtr<ID3D11RasterizerState> d3d_Rasterizer_State;
	CComPtr<ID3D11SamplerState> d3d_Sampler_State;
	CComPtr<ID3D11InputLayout> d3d_Input_Layout;
	CComPtr<ID3D11RenderTargetView> d3d_RTV;

	DXGI_SWAP_CHAIN_DESC d3d_Swap_Chain_Desc;
	D3D11_VIEWPORT d3d_View_Port;
	D3D11_TEXTURE2D_DESC d3d_Z_Buffer_Desc;
	D3D11_RENDER_TARGET_VIEW_DESC d3d_RTV_Desc;
	D3D11_DEPTH_STENCIL_DESC d3d_DSS_Desc;
	D3D11_DEPTH_STENCIL_DESC d3d_2D_DS_Desc;
	D3D11_DEPTH_STENCIL_VIEW_DESC d3d_DSV_Desc;
	D3D11_RASTERIZER_DESC d3d_Rasterizer_Desc;
	D3D11_SAMPLER_DESC d3d_Sampler_State_Desc;


	// SHADERS
	CComPtr<ID3D11VertexShader> d3d_Vertex_Shader;
	CComPtr<ID3D11PixelShader> d3d_Pixel_Shader;

	// VR
	cCamera *m_cCameraLeft = nullptr,
			*m_cCameraRight = nullptr;



	CComPtr<ID3D11Texture2D> d3d_Render_Left_Eye;
	CComPtr<ID3D11ShaderResourceView> d3d_SRV_Left_Eye;
	CComPtr<ID3D11RenderTargetView> d3d_RTV_Left_Eye;

	CComPtr<ID3D11Texture2D> d3d_Render_Right_Eye;
	CComPtr<ID3D11ShaderResourceView> d3d_SRV_Right_Eye;
	CComPtr<ID3D11RenderTargetView> d3d_RTV_Right_Eye;

	CComPtr<ID3D11Resource> m_pControllerAxisVertexBuffer;

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;

	float m_fNearClip;
	float m_fFarClip;
	float m_fScaleSpacing;
	float m_fScale;

	Matrix4 m_mat4HMDPose;
	Matrix4 m_mat4eyePosLeft;
	Matrix4 m_mat4eyePosRight;

	Matrix4 m_mat4ProjectionCenter;
	Matrix4 m_mat4ProjectionLeft;
	Matrix4 m_mat4ProjectionRight;

	vr::IVRSystem *m_pHMD;
	vr::IVRRenderModels *m_pRenderModels;
	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	Matrix4 m_rmat4DevicePose[vr::k_unMaxTrackedDeviceCount];

	unsigned int m_uiControllerVertcount = 0;

	int m_iTrackedControllerCount = 0;
	int m_iTrackedControllerCount_Last;
	int m_iValidPoseCount;
	int m_iValidPoseCount_Last;
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
	cGraphics_Setup(HWND _hwnd);
	~cGraphics_Setup();

	void Initialize();
	void Clean_Up();

	struct tTracked_device_pose
	{
		vr::TrackedDevicePose_t m_rTrackedDevicePose[64];
	};

	struct tMatrix4_device_pose
	{
		Matrix4 m_rmat4DevicePose[64];
	};

	Matrix4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	Matrix4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye);
	void SetupCameras();
	tFloat4x4 GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye);
	Matrix4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose);
	void UpdateHMDMatrixPose();

	CComPtr<ID3D11Device> Get_Device();
	CComPtr<ID3D11DeviceContext> Get_Context();
	CComPtr<ID3D11RenderTargetView> Get_RTV();
	CComPtr<ID3D11RenderTargetView> Get_RTV_Left();
	CComPtr<ID3D11RenderTargetView> Get_RTV_Right();
	CComPtr<ID3D11DepthStencilView> Get_DSV();
	CComPtr<ID3D11InputLayout> Get_Input_Layout();
	CComPtr<ID3D11VertexShader> Get_Vertex_Shader();
	CComPtr<ID3D11PixelShader> Get_Pixel_Shader();
	CComPtr<IDXGISwapChain> Get_Swap_Chain();
	D3D11_VIEWPORT Get_View_Port();
	CComPtr<ID3D11DepthStencilState> Get_Depth_Stencil_State();
	CComPtr<ID3D11Texture2D> Get_Texture_Left_Eye();
	CComPtr<ID3D11Texture2D> Get_Texture_Right_Eye();
	cCamera get_Camera_Left();
	cCamera get_Camera_Right();
	//IVRSystem get_m_pHMD();
	unsigned int get_controller_vert_count();
	int get_tracked_controller_count();
	//tTracked_device_pose get_tracked_device_pose();
	//Matrix4 get_matrix4_device_pose();
	CComPtr<ID3D11Resource> get_controller_axis_vertex_buffer();
};

