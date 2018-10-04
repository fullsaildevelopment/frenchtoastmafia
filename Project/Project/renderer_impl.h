#pragma once

#include <atlbase.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
using namespace DirectX;

#include "basic_structs.h"
#include "renderer.h"
#include "renderer_structs.h"
#include "XTime.h"

#include "VertexShader.csh"
#include "PixelShader.csh"

struct cRenderer::tImpl
{
	// platform/api specific members, functions, etc.
	HWND _hWnd;
	tImpl(native_handle_t hWnd) { _hWnd = (HWND)hWnd; }

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

	CComPtr<ID3D11VertexShader> d3dVertex_Shader;

	CComPtr<ID3D11PixelShader> d3dPixel_Shader;

	//CComPtr<ID3D11DomainShader> d3dDomain_Shader;
	//CComPtr<ID3D11GeometryShader> d3dGeometry_Shader;
	//CComPtr<ID3D11HullShader> d3dHull_Shader;

	CComPtr<ID3D11Buffer> d3dConstant_Buffer_WVP;

	CComPtr<ID3D11Buffer> d3d_test_cube_vertex_buffer;
	CComPtr<ID3D11Buffer> d3d_test_cube_index_buffer;

	tConstantBuffer t_constant_buffer;

	XMFLOAT4X4 cam_float4x4;
	XMFLOAT4 eye_float4 = XMFLOAT4(0.0f, 15.0f, -15.0f, 0.0f);
	XMFLOAT4 at_float4 = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	XMFLOAT4 up_float4 = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);

	XMVECTOR vEye_Vector = XMLoadFloat4(&eye_float4);// { 0.0f, 15.0f, -15.0f, 0.0f };
	XMVECTOR vAt_Vector = XMLoadFloat4(&at_float4);// { 0.0f, 0.0f, 0.0f, 0.0f };
	XMVECTOR vUp_Vector = XMLoadFloat4(&up_float4);// { 0.0f, 1.0f, 0.0f, 0.0f };
	XMMATRIX mCamera_Matrix = XMMatrixInverse(nullptr, XMMatrixLookAtLH(vEye_Vector, vAt_Vector, vUp_Vector));
	XMMATRIX mCamera_Origin = mCamera_Matrix;

	XTime cTime;

	void initialize(cView& v)
	{
		// Get Current Window Size
		RECT current_window_size;
		GetClientRect(_hWnd, &current_window_size);
		float fWindow_Height = (float)current_window_size.bottom - (float)current_window_size.top;
		float fWindow_Width = (float)current_window_size.right - (float)current_window_size.left;

		// DEVICE AND SWAP CHAIN
		ZeroMemory(&d3dSwap_Chain_Desc, sizeof(DXGI_SWAP_CHAIN_DESC));
		d3dSwap_Chain_Desc.BufferCount = 1;
		d3dSwap_Chain_Desc.BufferDesc.Width = (unsigned int)fWindow_Width;
		d3dSwap_Chain_Desc.BufferDesc.Height = (unsigned int)fWindow_Height;
		d3dSwap_Chain_Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		d3dSwap_Chain_Desc.BufferDesc.RefreshRate.Numerator = 60;
		d3dSwap_Chain_Desc.BufferDesc.RefreshRate.Denominator = 1;
		d3dSwap_Chain_Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		d3dSwap_Chain_Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		d3dSwap_Chain_Desc.OutputWindow = _hWnd;
		d3dSwap_Chain_Desc.SampleDesc.Count = 1;
		d3dSwap_Chain_Desc.SampleDesc.Quality = 0;
		d3dSwap_Chain_Desc.Windowed = TRUE;

		D3D_FEATURE_LEVEL d3dFeature_Level = D3D_FEATURE_LEVEL_10_0;
		D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &d3dSwap_Chain_Desc, &d3dSwap_Chain, &d3dDevice, &d3dFeature_Level, &d3dContext);
		
		// SWAPPING BACK BUFFER
		ID3D11Texture2D *back_buffer;
		d3dSwap_Chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
		d3dDevice->CreateRenderTargetView(back_buffer, NULL, &d3dRTV.p);
		back_buffer->Release();

		// VIEW PORT
		d3dView_Port.Height = (float)d3dSwap_Chain_Desc.BufferDesc.Height;
		d3dView_Port.Width = (float)d3dSwap_Chain_Desc.BufferDesc.Width;
		d3dView_Port.TopLeftX = 0;
		d3dView_Port.TopLeftY = 0;
		d3dView_Port.MinDepth = 0;
		d3dView_Port.MaxDepth = 1;

		// Z BUFFER
		ZeroMemory(&d3dZ_Buffer_Desc, sizeof(D3D11_TEXTURE2D_DESC));
		d3dZ_Buffer_Desc.Width = (unsigned int)d3dSwap_Chain_Desc.BufferDesc.Width;
		d3dZ_Buffer_Desc.Height = (unsigned int)d3dSwap_Chain_Desc.BufferDesc.Height;
		d3dZ_Buffer_Desc.MipLevels = 1;
		d3dZ_Buffer_Desc.ArraySize = 1;
		d3dZ_Buffer_Desc.Format = DXGI_FORMAT_D32_FLOAT;
		d3dZ_Buffer_Desc.SampleDesc.Count = 1;
		d3dZ_Buffer_Desc.SampleDesc.Quality = 0;
		d3dZ_Buffer_Desc.Usage = D3D11_USAGE_DEFAULT;
		d3dZ_Buffer_Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		d3dZ_Buffer_Desc.CPUAccessFlags = 0;
		d3dZ_Buffer_Desc.MiscFlags = 0;

		d3dDevice->CreateTexture2D(&d3dZ_Buffer_Desc, nullptr, &d3dZ_Buffer.p);

		// DEPTH STENCIL
		ZeroMemory(&d3dDSV_Desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		d3dDSV_Desc.Format = d3dZ_Buffer_Desc.Format;
		d3dDSV_Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		d3dDSV_Desc.Texture2D.MipSlice = 0;

		d3dDevice->CreateDepthStencilView(d3dZ_Buffer, nullptr, &d3dDSV.p);

		// RASTERIZER STATE
		ZeroMemory(&d3dRasterizer_Desc, sizeof(D3D11_RASTERIZER_DESC));
		d3dRasterizer_Desc.FillMode = D3D11_FILL_SOLID;
		d3dRasterizer_Desc.CullMode = D3D11_CULL_BACK;
		d3dRasterizer_Desc.DepthBias = 0;
		d3dRasterizer_Desc.SlopeScaledDepthBias = 0.0f;
		d3dRasterizer_Desc.DepthBiasClamp = 0.0f;
		d3dRasterizer_Desc.DepthClipEnable = TRUE;
		d3dRasterizer_Desc.ScissorEnable = FALSE;
		d3dRasterizer_Desc.MultisampleEnable = FALSE;
		d3dRasterizer_Desc.AntialiasedLineEnable = FALSE;

		d3dDevice->CreateRasterizerState(&d3dRasterizer_Desc, &d3dRasterizer_State.p);

		// SAMPLER STATE
		ZeroMemory(&d3dSampler_State_Desc, sizeof(D3D11_SAMPLER_DESC));
		d3dSampler_State_Desc.Filter = D3D11_FILTER_ANISOTROPIC;
		d3dSampler_State_Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		d3dSampler_State_Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		d3dSampler_State_Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		d3dSampler_State_Desc.MipLODBias = 0.0;
		d3dSampler_State_Desc.MaxAnisotropy = 16;
		d3dSampler_State_Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		d3dSampler_State_Desc.MinLOD = 0;
		d3dSampler_State_Desc.MaxLOD = 0;

		d3dDevice->CreateSamplerState(&d3dSampler_State_Desc, &d3dSampler_State.p);

		// CONSTANT BUFFER - WORLD VIEW PROJECTION
		ZeroMemory(&d3dConstant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
		d3dConstant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer);
		d3dConstant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
		d3dConstant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		d3dConstant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		d3dConstant_Buffer_Desc.MiscFlags = 0;
		d3dConstant_Buffer_Desc.StructureByteStride = 0;

		d3dDevice->CreateBuffer(&d3dConstant_Buffer_Desc, nullptr, &d3dConstant_Buffer_WVP.p);

		// VERTEX BUFFER
		tVertex *test_cube = new tVertex[8];
		for (unsigned int i = 0; i < 8; i++)
		{
			test_cube[i].fPosition.m_x = 1.0f;
			test_cube[i].fPosition.m_y = 1.0f;
			test_cube[i].fPosition.m_z = 1.0f;
			test_cube[i].fPosition.m_w = 1.0f;

			if (i % 2 == 0)
				test_cube[i].fPosition.m_x *= -1.0f;

			if (i == 2 || i == 3 || i == 6 || i == 7)
				test_cube[i].fPosition.m_y *= -1.0f;

			if (i < 4)
				test_cube[i].fPosition.m_z *= -1.0f;
		}

		ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
		d3dBuffer_Desc.ByteWidth = sizeof(tVertex) * 8;
		d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
		d3dBuffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		d3dBuffer_Desc.CPUAccessFlags = NULL;
		d3dBuffer_Desc.MiscFlags = 0;
		d3dBuffer_Desc.StructureByteStride = 0;

		ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
		d3dSRD.pSysMem = test_cube;
		d3dSRD.SysMemPitch = 0;
		d3dSRD.SysMemSlicePitch = 0;

		d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_test_cube_vertex_buffer);

		// INDEX BUFFER

		unsigned int test_cube_indicies[36] =
		{
			0,1,2,
			1,3,2,
			4,0,6,
			0,2,6,
			5,4,7,
			4,6,7,
			1,5,3,
			5,7,3,
			4,5,0,
			5,2,0
		};

		ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
		d3dBuffer_Desc.ByteWidth = sizeof(unsigned int) * 36;
		d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
		d3dBuffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		d3dBuffer_Desc.CPUAccessFlags = NULL;
		d3dBuffer_Desc.MiscFlags = 0;
		d3dBuffer_Desc.StructureByteStride = 0;

		ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
		d3dSRD.pSysMem = test_cube_indicies;
		d3dSRD.SysMemPitch = 0;
		d3dSRD.SysMemSlicePitch = 0;

		d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_test_cube_index_buffer);
		
		// SHADERS
		d3dDevice->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &d3dVertex_Shader.p);
		d3dDevice->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, &d3dPixel_Shader.p);
		
		// INPUT ELEMENT
		D3D11_INPUT_ELEMENT_DESC d3dInput_Element[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		d3dDevice->CreateInputLayout(d3dInput_Element, ARRAYSIZE(d3dInput_Element), VertexShader, sizeof(VertexShader), &d3dInput_Layout.p);
	}
	void draw_view(cView& v)
	{
		// SIGNALS
		cTime.Signal();

		// RESIZE / RESET RTV AND VP
		d3dContext->OMSetRenderTargets(0, 0, 0);
		d3dRTV.Release();
		d3dSwap_Chain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		ID3D11Texture2D *back_buffer;
		d3dSwap_Chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
		d3dDevice->CreateRenderTargetView(back_buffer, NULL, &d3dRTV);
		ID3D11RenderTargetView *tmp_rtv[] = { d3dRTV };
		d3dContext->OMSetRenderTargets(1, tmp_rtv, d3dDSV);
		d3dContext->RSSetViewports(1, &d3dView_Port);
		// SKY BLUE
		float clear_color[4] = { 0.000000000f, 0.749019623f, 1.000000000f, 1.000000000f };
		// WHITE
		//float clear_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		d3dContext->ClearRenderTargetView(d3dRTV, clear_color);
		d3dContext->ClearDepthStencilView(d3dDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

		// CONTROLS
		// A - move left
		if (GetAsyncKeyState('A'))
			mCamera_Matrix = XMMatrixMultiply(XMMatrixTranslation(-((float)cTime.Delta() * 25), 0.0f, 0.0f), mCamera_Matrix);

		// D - move right
		if (GetAsyncKeyState('D'))
			mCamera_Matrix = XMMatrixMultiply(XMMatrixTranslation((float)cTime.Delta() * 25, 0.0f, 0.0f), mCamera_Matrix);

		// Q - move up
		if (GetAsyncKeyState('Q'))
			mCamera_Matrix = XMMatrixMultiply(mCamera_Matrix, XMMatrixTranslation(0.0f, (float)cTime.Delta() * 25, 0.0f));

		// E - move down
		if (GetAsyncKeyState('E'))
			mCamera_Matrix = XMMatrixMultiply(mCamera_Matrix, XMMatrixTranslation(0.0f, -((float)cTime.Delta() * 25), 0.0f));

		// S - move out
		if (GetAsyncKeyState('S'))
			mCamera_Matrix = XMMatrixMultiply(XMMatrixTranslation(0.0f, 0.0f, -((float)cTime.Delta() * 25)), mCamera_Matrix);

		// W - move in
		if (GetAsyncKeyState('W'))
			mCamera_Matrix = XMMatrixMultiply(XMMatrixTranslation(0.0f, 0.0f, (float)cTime.Delta() * 25), mCamera_Matrix);

		// I - look up
		if (GetAsyncKeyState('I'))
			mCamera_Matrix = XMMatrixMultiply(XMMatrixRotationX(-((float)cTime.Delta())), mCamera_Matrix);

		// K - look down
		if (GetAsyncKeyState('K'))
			mCamera_Matrix = XMMatrixMultiply(XMMatrixRotationX((float)cTime.Delta()), mCamera_Matrix);

		// L - look right
		if (GetAsyncKeyState('L'))
		{
			XMVECTOR pos = XMVectorSet(mCamera_Matrix.r[3].m128_f32[0], mCamera_Matrix.r[3].m128_f32[1], mCamera_Matrix.r[3].m128_f32[2], 1.0f);
			mCamera_Matrix.r[3] = XMVectorSet(0, 0, 0, 1);
			mCamera_Matrix = XMMatrixMultiply(mCamera_Matrix, XMMatrixRotationY((float)cTime.Delta()));
			mCamera_Matrix.r[3] = pos;
		}

		// J - look left
		if (GetAsyncKeyState('J'))
		{
			XMVECTOR pos = XMVectorSet(mCamera_Matrix.r[3].m128_f32[0], mCamera_Matrix.r[3].m128_f32[1], mCamera_Matrix.r[3].m128_f32[2], 1.0f);
			mCamera_Matrix.r[3] = XMVectorSet(0, 0, 0, 1);
			mCamera_Matrix = XMMatrixMultiply(mCamera_Matrix, XMMatrixRotationY(-((float)cTime.Delta())));
			mCamera_Matrix.r[3] = pos;
		}

		// R - reset
		if (GetAsyncKeyState('R'))
		{
			mCamera_Matrix = mCamera_Origin;
			cTime.Restart();
		}

		// NORMALIZING ROTATIONS
		XMVECTOR newZ = mCamera_Matrix.r[2];
		newZ = XMVector3Normalize(newZ);
		XMVECTOR worldY = XMMatrixIdentity().r[1];
		XMVECTOR newX = XMVector3Cross(worldY, newZ);
		newX = XMVector3Normalize(newX);
		XMVECTOR newY = XMVector3Cross(newZ, newX);
		newY = XMVector3Normalize(newY);

		mCamera_Matrix.r[0] = newX;
		mCamera_Matrix.r[1] = newY;
		mCamera_Matrix.r[2] = newZ;

		// Get Current Window Size
		RECT current_window_size;
		GetClientRect(_hWnd, &current_window_size);
		float fWindow_Height = (float)current_window_size.bottom - (float)current_window_size.top;
		float fWindow_Width = (float)current_window_size.right - (float)current_window_size.left;

		// CONSTANT BUFFER
		XMStoreFloat4x4(&t_constant_buffer.fWorld_Matrix, XMMatrixIdentity());
		XMStoreFloat4x4(&t_constant_buffer.fView_Matrix, XMMatrixInverse(nullptr, mCamera_Matrix));
		XMStoreFloat4x4(&t_constant_buffer.fProjection_Matrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(45), fWindow_Width / fWindow_Height, 0.1f, 1000.0f));
		XMStoreFloat4x4(&t_constant_buffer.fCamera_Matrix, mCamera_Matrix);
		XMStoreFloat4x4(&t_constant_buffer.fCamera_Origin, mCamera_Origin);

		// MAPPING CONSTANT BUFFER
		d3dContext->Map(d3dConstant_Buffer_WVP, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMSR);
		memcpy(d3dMSR.pData, &t_constant_buffer, sizeof(tConstantBuffer));
		d3dContext->Unmap(d3dConstant_Buffer_WVP, 0);
		ID3D11Buffer *tmp_c_buffer[] = { d3dConstant_Buffer_WVP };
		d3dContext->VSSetConstantBuffers(0, 1, tmp_c_buffer);

		// DRAWS
		unsigned int verts_size = sizeof(tVertex);
		unsigned int off_set = 0;

		ID3D11Buffer *tmp_v_buffer[] = { d3d_test_cube_vertex_buffer };
		d3dContext->IASetVertexBuffers(0, 1, tmp_v_buffer, &verts_size, &off_set);
		d3dContext->IASetIndexBuffer(d3d_test_cube_index_buffer, DXGI_FORMAT_R32_UINT, 0);
		d3dContext->IASetInputLayout(d3dInput_Layout);
		d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		d3dContext->VSSetShader(d3dVertex_Shader, NULL, 0);
		d3dContext->PSSetShader(d3dPixel_Shader, NULL, 0);
		d3dContext->DrawIndexed(36, 0, 0);

		// PRESENT
		d3dSwap_Chain->Present(1, 0);
	}
};