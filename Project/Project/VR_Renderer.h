#pragma once
#include "Camera.h"
#include "defines.h"
#include "renderer_structs.h"
#include "Scene_Manager.h"
#include "XTime.h"

// Basic Shaders
#include "VertexShader.csh"
#include "PixelShader.csh"
#include "PixelShader_Screen.csh"

// Object Shaders
#include "VertexShader_Arena.csh"
#include "PixelShader_Arena.csh"

#include "Camera.h"
#include "openvr\headers\openvr.h"
#include "Render_Manager.h"
#include "EngineMath.h"
#include "GWR5d\Interface\G_Math\GMatrix.h"

class cVR_Renderer
{
private:
	// BACKEND
	CComPtr<ID3D11Device> d3dDevice;
	CComPtr<ID3D11DeviceContext> d3dContext;
	CComPtr<IDXGISwapChain> d3dSwap_Chain;
	CComPtr<ID3D11Texture2D> d3dZ_Buffer;
	CComPtr<ID3D11DepthStencilView> d3dDSV;
	CComPtr<ID3D11DepthStencilState> d3dDSS;
	CComPtr<ID3D11DepthStencilState> d3dDSS_2;
	CComPtr<ID3D11RasterizerState> d3dRasterizer_State;
	CComPtr<ID3D11SamplerState> d3dSampler_State;
	CComPtr<ID3D11InputLayout> d3dInput_Layout;
	CComPtr<ID3D11RenderTargetView> d3dRTV;

	DXGI_SWAP_CHAIN_DESC d3dSwap_Chain_Desc;
	D3D11_VIEWPORT d3dView_Port;
	D3D11_TEXTURE2D_DESC d3dZ_Buffer_Desc;
	D3D11_DEPTH_STENCIL_DESC d3dDSS_Desc;
	D3D11_DEPTH_STENCIL_VIEW_DESC d3dDSV_Desc;
	D3D11_RASTERIZER_DESC d3dRasterizer_Desc;
	D3D11_SAMPLER_DESC d3dSampler_State_Desc;

	D3D11_BUFFER_DESC d3dBuffer_Desc;
	D3D11_BUFFER_DESC d3dConstant_Buffer_Desc;
	D3D11_SUBRESOURCE_DATA d3dSRD;
	D3D11_MAPPED_SUBRESOURCE d3dMSR;

	// RENDER TO TEXTURE
	CComPtr<ID3D11Texture2D> d3d_R2T_Left;
	CComPtr<ID3D11RenderTargetView> d3d_RTV_R2T_Left;
	CComPtr<ID3D11ShaderResourceView> d3d_SRV_R2T_Left;

	CComPtr<ID3D11Texture2D> d3d_R2T_Right;
	CComPtr<ID3D11RenderTargetView> d3d_RTV_R2T_Right;
	CComPtr<ID3D11ShaderResourceView> d3d_SRV_R2T_Right;

	// SHADERS
	CComPtr<ID3D11VertexShader> d3dVertex_Shader;

	CComPtr<ID3D11PixelShader> d3dPixel_Shader;
	CComPtr<ID3D11PixelShader> d3dPixel_Shader_Screen;

	// WVPC
	CComPtr<ID3D11Buffer> d3dConstant_Buffer_WVPC;
	tConstantBuffer_VertexShader_WVPC tWVPC;
	XMFLOAT4X4 fCamera_Matrix;
	XMFLOAT4X4 fCamera_Origin;

	// TIME
	XTime cTime;

	// Scene
	cScene_Manager cSM;

	//VR

	cCamera *m_cCameraLeft = nullptr,
		    *m_cCameraRight = nullptr;
	//ModelClass* m_Model = nullptr;
	//ColorShaderClass* m_ColorShader = nullptr;
	//cRender_Manager* m_cRenderLeft, *m_cRenderRight;
	//DebugWindowClass* m_DebugWindowLeft, *m_DebugWindowRight;

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;

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

public:

	void Initialize(HWND _hwnd);
	tScene_Objects GetScene(int nScene_Id);
	void Load(tScene_Objects *tScene);
	void Unload(tScene_Objects tScene);
	void Draw(tScene_Objects tScene);
	void DrawToTexture();

	//VR

	tFloat4x4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	tFloat4x4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye);
	void SetupCameras();
	bool Initialize(HWND hWnd);

	cVR_Renderer();
	~cVR_Renderer();
};

