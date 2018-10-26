#pragma once

#include "Camera.h"
#include "defines.h"
#include "EngineMath.h"
#include "math_conversion.h"
#include "openvr\headers\openvr.h"
#include "renderer_structs.h"

// Basic Shaders
#include "VertexShader.csh"
#include "PixelShader.csh"

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

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;

	float m_fNearClip;
	float m_fFarClip;
	float m_fScaleSpacing;
	float m_fScale;

	tFloat4x4 m_mat4HMDPose;
	tFloat4x4 m_mat4eyePosLeft;
	tFloat4x4 m_mat4eyePosRight;

	tFloat4x4 m_mat4ProjectionCenter;
	tFloat4x4 m_mat4ProjectionLeft;
	tFloat4x4 m_mat4ProjectionRight;

	vr::IVRSystem *m_pHMD;
	vr::IVRRenderModels *m_pRenderModels;
	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	tFloat4x4 m_rmat4DevicePose[vr::k_unMaxTrackedDeviceCount];

	int m_iTrackedControllerCount;
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

	tFloat4x4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	tFloat4x4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye);
	void SetupCameras();
	tFloat4x4 GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye);
	tFloat4x4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose);
	void UpdateHMDMatrixPose();
	CComPtr<ID3D11Device> GetDevice();
};

