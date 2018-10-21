#pragma once

#include "Camera.h"
#include "renderer_structs.h"
#include "Scene_Manager.h"

// Basic Shaders
#include "VertexShader.csh"
#include "PixelShader.csh"
#include "PixelShader_Screen.csh"

class cRender_Manager
{
private:
	// HWND
	HWND hWnd;

	// BACKEND
	CComPtr<ID3D11Device> d3dDevice;
	CComPtr<ID3D11DeviceContext> d3dContext;
	CComPtr<IDXGISwapChain> d3dSwap_Chain;
	CComPtr<ID3D11Texture2D> d3dZ_Buffer;
	CComPtr<ID3D11DepthStencilView> d3dDSV;
	CComPtr<ID3D11RasterizerState> d3dRasterizer_State;
	CComPtr<ID3D11SamplerState> d3dSampler_State;
	CComPtr<ID3D11InputLayout> d3dInput_Layout;
	CComPtr<ID3D11RenderTargetView> d3dRTV;

	DXGI_SWAP_CHAIN_DESC d3dSwap_Chain_Desc;
	D3D11_VIEWPORT d3dView_Port;
	D3D11_TEXTURE2D_DESC d3dZ_Buffer_Desc;
	D3D11_DEPTH_STENCIL_VIEW_DESC d3dDSV_Desc;
	D3D11_RASTERIZER_DESC d3dRasterizer_Desc;
	D3D11_SAMPLER_DESC d3dSampler_State_Desc;

	D3D11_BUFFER_DESC d3dBuffer_Desc;
	D3D11_BUFFER_DESC d3dConstant_Buffer_Desc;
	D3D11_SUBRESOURCE_DATA d3dSRD;
	D3D11_MAPPED_SUBRESOURCE d3dMSR;

	cCamera cCam;

	// SHADERS
	CComPtr<ID3D11VertexShader> d3dVertex_Shader;

	CComPtr<ID3D11PixelShader> d3dPixel_Shader;
	CComPtr<ID3D11PixelShader> d3dPixel_Shader_Screen;

	// WVPC
	CComPtr<ID3D11Buffer> d3dConstant_Buffer_WVPC;
	tConstantBuffer_VertexShader_WVPC tWVPC;
	XMFLOAT4X4 fCamera_Matrix;
	XMFLOAT4X4 fCamera_Origin;

	// Scene
	cScene_Manager cSM;

public:
	cRender_Manager(HWND _hwnd);
	~cRender_Manager();

	void Initialize();
	tScene_Objects GetScene();
	void Load();
	void Unload();
	void Draw(tScene_Objects tScene);
	void DrawToTexture();
};

