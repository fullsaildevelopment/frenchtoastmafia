/************************************************************************
* Filename:  		Graphic_Setup.h
* Date:      		26/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Combine Initialization of Render system and VR system to remove circular requirment.
					(Concept idea suggested by Lari Norri)
*************************************************************************/
#pragma once

#include "Camera.h"
#include "defines.h"
#include "Math_Conversion.h"
#include "Matrices.h"
#include "openvr\headers\openvr.h"
#pragma comment (lib, "openvr_api.lib")
#include "Renderer_Structs.h"
#include "Specific_Structs.h"

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
	ComPtr<ID3D11Device> d3d_Device;
	ComPtr<ID3D11DeviceContext> d3d_Context;
	ComPtr<IDXGISwapChain> d3d_Swap_Chain;
	ComPtr<ID3D11Texture2D> d3d_Z_Buffer;
	ComPtr<ID3D11DepthStencilView> d3d_DSV;
	ComPtr<ID3D11DepthStencilState> d3d_DSS;
	ComPtr<ID3D11DepthStencilState> d3d_2D_DSS;
	ComPtr<ID3D11RasterizerState> d3d_Rasterizer_State;
	ComPtr<ID3D11SamplerState> d3d_Sampler_State;
	ComPtr<ID3D11InputLayout> d3d_Input_Layout;
	ComPtr<ID3D11RenderTargetView> d3d_RTV;

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
	ComPtr<ID3D11VertexShader> d3d_Vertex_Shader;
	ComPtr<ID3D11PixelShader> d3d_Pixel_Shader;

	// VR
	cCamera *m_cCameraLeft = nullptr,
			*m_cCameraRight = nullptr;

	ComPtr<ID3D11Texture2D> d3d_Render_Left_Eye;
	ComPtr<ID3D11ShaderResourceView> d3d_SRV_Left_Eye;
	ComPtr<ID3D11RenderTargetView> d3d_RTV_Left_Eye;

	ComPtr<ID3D11Texture2D> d3d_Render_Right_Eye;
	ComPtr<ID3D11ShaderResourceView> d3d_SRV_Right_Eye;
	ComPtr<ID3D11RenderTargetView> d3d_RTV_Right_Eye;

	float m_fNearClip;
	float m_fFarClip;
	float m_fScaleSpacing;
	float m_fScale;

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;

	vr::IVRSystem *m_pHMD;
	vr::IVRRenderModels *m_pRenderModels;
public:
	cGraphics_Setup(HWND _hwnd);
	~cGraphics_Setup();

	void Initialize();
	void Clean_Up();

	vr::IVRSystem* Get_HMD();
	ComPtr<ID3D11Device> Get_Device();
	ComPtr<ID3D11DeviceContext> Get_Context();
	ComPtr<ID3D11RenderTargetView> Get_RTV();
	ComPtr<ID3D11RenderTargetView> Get_RTV_Left();
	ComPtr<ID3D11RenderTargetView> Get_RTV_Right();
	ComPtr<ID3D11DepthStencilView> Get_DSV();
	ComPtr<ID3D11InputLayout> Get_Input_Layout();
	ComPtr<ID3D11VertexShader> Get_Vertex_Shader();
	ComPtr<ID3D11PixelShader> Get_Pixel_Shader();
	ComPtr<IDXGISwapChain> Get_Swap_Chain();
	D3D11_VIEWPORT Get_View_Port();
	ComPtr<ID3D11DepthStencilState> Get_Depth_Stencil_State();
	ComPtr<ID3D11Texture2D> Get_Texture_Left_Eye();
	ComPtr<ID3D11Texture2D> Get_Texture_Right_Eye();
	cCamera get_Camera_Left();
	cCamera get_Camera_Right();
};
