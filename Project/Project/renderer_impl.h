/************************************************************************
* Filename:  		renderer_impl.h
* Date:      		10/02/2018
* Mod. Date: 		10/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Main Rendering file
*************************************************************************/
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
#include "binary_reader.h"
#include "collisions.h"
#include "renderer.h"
#include "renderer_structs.h"
#include "Object System.h"
#include "WICTextureLoader.h"
#include "XTime.h"

#include "VertexShader.csh"
#include "VertexShader_Bullet.csh"
#include "VertexShader_Arena.csh"

#include "PixelShader.csh"
#include "PixelShader_Mage.csh"
#include "PixelShader_Arena.csh"


struct cRenderer::tImpl
{
	// platform/api specific members, functions, etc.
	HWND _hWnd;
	tImpl(native_handle_t hWnd) { _hWnd = (HWND)hWnd; }

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
	
	// SHADERS
	CComPtr<ID3D11VertexShader> d3dVertex_Shader;
	CComPtr<ID3D11VertexShader> d3dVertex_Shader_Bullet;

	CComPtr<ID3D11PixelShader> d3dPixel_Shader;
	CComPtr<ID3D11PixelShader> d3dPixel_Shader_Mage;

	//CComPtr<ID3D11DomainShader> d3dDomain_Shader;
	//CComPtr<ID3D11GeometryShader> d3dGeometry_Shader;
	//CComPtr<ID3D11HullShader> d3dHull_Shader;

	// WVPC
	CComPtr<ID3D11Buffer> d3dConstant_Buffer_WVPC;
	tConstantBuffer_VertexShader_WVPC tWVPC;
	XMFLOAT4X4 fCamera_Matrix;
	XMFLOAT4X4 fCamera_Origin;

	// TIME
	XTime cTime;

	// COLLISIONS
	tCollisions tColl;
	// OBJECTS
	cBinary_Reader cBinary_Read;

	//OBJECT SYSYEM
	object_system tObject_System;

	// DUMMY
	tVertex *test_dummy = new tVertex[8];
	CComPtr<ID3D11Buffer> d3dConstant_Buffer_DUMMY;
	tConstantBuffer_Float4 tDUMMY;
	CComPtr<ID3D11Buffer> d3d_test_dummy_vertex_buffer;
	CComPtr<ID3D11Buffer> d3d_test_dummy_index_buffer;
	bool test_dummy_toggle = false;

	// BULLET
	tVertex *test_bullet = new tVertex[8];
	CComPtr<ID3D11Buffer> d3dConstant_Buffer_BULLET;
	tConstantBuffer_Float4 tBULLET;
	CComPtr<ID3D11Buffer> d3d_test_bullet_vertex_buffer;
	CComPtr<ID3D11Buffer> d3d_test_bullet_index_buffer;
	bool test_bullet_toggle = false;
	bool didCollide = false;

	// MAGE
	CComPtr<ID3D11Buffer> d3dConstant_Buffer_MAGE;
	CComPtr<ID3D11Buffer> d3d_test_mage_vertex_buffer;
	CComPtr<ID3D11Buffer> d3d_test_mage_index_buffer;
	tConstantBuffer_PixelShader cps_mage;
	tMesh tMage = cBinary_Read.Read_Mesh("mesh.bin");
	int nMage_Vertex_Count = (int)tMage.nVertex_Count;
	int nMage_Index_Count = (int)tMage.nIndex_Count;
	tVertex *test_mage = new tVertex[nMage_Vertex_Count];
	tMaterials mage_mats = cBinary_Read.Read_Material("material.bin");
	CComPtr<ID3D11ShaderResourceView> mage_srv_diffuse;
	CComPtr<ID3D11ShaderResourceView> mage_srv_emissive;
	CComPtr<ID3D11ShaderResourceView> mage_srv_specular;

	// ARENA
	pipeline_t tArenaIDs = { 0, 0, 0, 0 };
	tConstantBuffer_PixelShader cps_arena;
	tMesh  tArena = cBinary_Read.Read_Mesh("ArenaMesh.bin");
	int nArena_Vertex_Count = (int)tArena.nVertex_Count;
	int nArena_Index_Count = (int)tArena.nIndex_Count;
	tVertex *test_arena = new tVertex[nArena_Vertex_Count];
	tMaterials arena_mats = cBinary_Read.Read_Material("ArenaMat.bin");
	CComPtr<ID3D11ShaderResourceView> arena_srv_diffuse;
	CComPtr<ID3D11ShaderResourceView> arena_srv_emissive;
	CComPtr<ID3D11ShaderResourceView> arena_srv_specular;


	void initialize(cView& c_View)
	{

		
		// BACKEND SETUP
		{
			XMMATRIX mCamera_Matrix = XMMatrixInverse(nullptr, XMMatrixLookAtLH({ 0.0f, 15.0f, -15.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }));
			XMStoreFloat4x4(&fCamera_Matrix, mCamera_Matrix);
			fCamera_Origin = fCamera_Matrix;

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

			// SHADERS
			d3dDevice->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &d3dVertex_Shader.p);
			d3dDevice->CreateVertexShader(VertexShader_Bullet, sizeof(VertexShader_Bullet), NULL, &d3dVertex_Shader_Bullet.p);
			d3dDevice->CreateVertexShader(VertexShader_Arena, sizeof(VertexShader_Arena), NULL, &tObject_System.vertex_shaders[tArenaIDs.vertex_shader_id].p);

			d3dDevice->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, &d3dPixel_Shader.p);
			d3dDevice->CreatePixelShader(PixelShader_Mage, sizeof(PixelShader_Mage), NULL, &d3dPixel_Shader_Mage.p);
			d3dDevice->CreatePixelShader(PixelShader_Arena, sizeof(PixelShader_Arena), NULL, &tObject_System.pixel_shaders[tArenaIDs.pixel_shader_id].p);

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

		// CONSTANT BUFFERS
		{
			// CONSTANT BUFFER - WORLD VIEW PROJECTION
			{
				ZeroMemory(&d3dConstant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dConstant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_VertexShader_WVPC);
				d3dConstant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
				d3dConstant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				d3dConstant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				d3dConstant_Buffer_Desc.MiscFlags = 0;
				d3dConstant_Buffer_Desc.StructureByteStride = 0;

				d3dDevice->CreateBuffer(&d3dConstant_Buffer_Desc, nullptr, &d3dConstant_Buffer_WVPC.p);
			}
			// CONSTANT BUFFER - BULLET
			{
				ZeroMemory(&d3dConstant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dConstant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_Float4);
				d3dConstant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
				d3dConstant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				d3dConstant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				d3dConstant_Buffer_Desc.MiscFlags = 0;
				d3dConstant_Buffer_Desc.StructureByteStride = 0;

				d3dDevice->CreateBuffer(&d3dConstant_Buffer_Desc, nullptr, &d3dConstant_Buffer_BULLET.p);
			}

			// CONSTANT BUFFER - DUMMY
			{
				ZeroMemory(&d3dConstant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dConstant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_Float4);
				d3dConstant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
				d3dConstant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				d3dConstant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				d3dConstant_Buffer_Desc.MiscFlags = 0;
				d3dConstant_Buffer_Desc.StructureByteStride = 0;

				d3dDevice->CreateBuffer(&d3dConstant_Buffer_Desc, nullptr, &d3dConstant_Buffer_DUMMY.p);
			}

			// CONSTANT BUFFER - MAGE
			{
				ZeroMemory(&d3dConstant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dConstant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_PixelShader);
				d3dConstant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
				d3dConstant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				d3dConstant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				d3dConstant_Buffer_Desc.MiscFlags = 0;
				d3dConstant_Buffer_Desc.StructureByteStride = 0;

				d3dDevice->CreateBuffer(&d3dConstant_Buffer_Desc, nullptr, &d3dConstant_Buffer_MAGE.p);
			}

			// CONSTANT BUFFER - ARENA
			{
				ZeroMemory(&d3dConstant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dConstant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_PixelShader);
				d3dConstant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
				d3dConstant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				d3dConstant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				d3dConstant_Buffer_Desc.MiscFlags = 0;
				d3dConstant_Buffer_Desc.StructureByteStride = 0;

				d3dDevice->CreateBuffer(&d3dConstant_Buffer_Desc, nullptr, &tObject_System.constant_buffers[tArenaIDs.constant_buffer_wvp_id].p);
			}
		}

		// VERTEX AND INDEX BUFFERS
		{
			// DUMMY
			{
				// VERTEX BUFFER
				// Create
				for (unsigned int i = 0; i < 8; i++)
				{
					test_dummy[i].fPosition.fX = 2.0f;
					test_dummy[i].fPosition.fY = 4.0f;
					test_dummy[i].fPosition.fZ = 2.0f;
					test_dummy[i].fPosition.fW = 1.0f;
				
					if (i % 2 == 0)
						test_dummy[i].fPosition.fX *= -1.0f;
				
					if (i == 2 || i == 3 || i == 6 || i == 7)
						test_dummy[i].fPosition.fY *= -1.0f;
				
					if (i < 4)
						test_dummy[i].fPosition.fZ *= -1.0f;
				}
				

				// Move
				for (unsigned int i = 0; i < 8; i++)
				{
					test_dummy[i].fPosition.fZ += 15.0f;
				}

				ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dBuffer_Desc.ByteWidth = sizeof(tVertex) * 8;
				d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
				d3dBuffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				d3dBuffer_Desc.CPUAccessFlags = NULL;
				d3dBuffer_Desc.MiscFlags = 0;
				d3dBuffer_Desc.StructureByteStride = 0;

				ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
				d3dSRD.pSysMem = test_dummy;
				d3dSRD.SysMemPitch = 0;
				d3dSRD.SysMemSlicePitch = 0;

				d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_test_dummy_vertex_buffer);

				// INDEX BUFFER

				unsigned int test_dummy_indicies[36] =
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
					5,1,0,
					2,3,6,
					3,7,6
				};

				ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dBuffer_Desc.ByteWidth = sizeof(unsigned int) * 36;
				d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
				d3dBuffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				d3dBuffer_Desc.CPUAccessFlags = NULL;
				d3dBuffer_Desc.MiscFlags = 0;
				d3dBuffer_Desc.StructureByteStride = 0;

				ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
				d3dSRD.pSysMem = test_dummy_indicies;
				d3dSRD.SysMemPitch = 0;
				d3dSRD.SysMemSlicePitch = 0;

				d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_test_dummy_index_buffer);
			}

			// BULLET
			{
				// VERTEX BUFFER
				for (unsigned int i = 0; i < 8; i++)
				{
					test_bullet[i].fPosition.fX = 1.0f;
					test_bullet[i].fPosition.fY = 1.0f;
					test_bullet[i].fPosition.fZ = 1.0f;
					test_bullet[i].fPosition.fW = 1.0f;

					if (i % 2 == 0)
						test_bullet[i].fPosition.fX *= -1.0f;

					if (i == 2 || i == 3 || i == 6 || i == 7)
						test_bullet[i].fPosition.fY *= -1.0f;

					if (i < 4)
						test_bullet[i].fPosition.fZ *= -1.0f;
				}

				ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dBuffer_Desc.ByteWidth = sizeof(tVertex) * 8;
				d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
				d3dBuffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				d3dBuffer_Desc.CPUAccessFlags = NULL;
				d3dBuffer_Desc.MiscFlags = 0;
				d3dBuffer_Desc.StructureByteStride = 0;

				ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
				d3dSRD.pSysMem = test_bullet;
				d3dSRD.SysMemPitch = 0;
				d3dSRD.SysMemSlicePitch = 0;

				d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_test_bullet_vertex_buffer);

				// INDEX BUFFER

				unsigned int test_bullet_indicies[36] =
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
					5,1,0,
					2,3,6,
					3,7,6
				};

				ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dBuffer_Desc.ByteWidth = sizeof(unsigned int) * 36;
				d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
				d3dBuffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				d3dBuffer_Desc.CPUAccessFlags = NULL;
				d3dBuffer_Desc.MiscFlags = 0;
				d3dBuffer_Desc.StructureByteStride = 0;

				ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
				d3dSRD.pSysMem = test_bullet_indicies;
				d3dSRD.SysMemPitch = 0;
				d3dSRD.SysMemSlicePitch = 0;

				d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_test_bullet_index_buffer);
			}

			// MAGE
			{
				// VERTEX BUFFER

				for (int i = 0; i < nMage_Vertex_Count; i++)
				{
					test_mage[i] = tMage.tVerts[i];
				}

				// Move
				for (int i = 0; i < nMage_Vertex_Count; i++)
				{
					test_mage[i].fPosition.fX -= 15.0f;
				}

				ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dBuffer_Desc.ByteWidth = sizeof(tVertex) * nMage_Vertex_Count;
				d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
				d3dBuffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				d3dBuffer_Desc.CPUAccessFlags = NULL;
				d3dBuffer_Desc.MiscFlags = 0;
				d3dBuffer_Desc.StructureByteStride = 0;

				ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
				d3dSRD.pSysMem = test_mage;
				d3dSRD.SysMemPitch = 0;
				d3dSRD.SysMemSlicePitch = 0;

				d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_test_mage_vertex_buffer);

				// INDEX BUFFER

				int* nMage_Indicies = new int[nMage_Index_Count];
				for (int i = 0; i < nMage_Index_Count; i++)
				{
					nMage_Indicies[i] = tMage.nIndicies[i];
				}

				ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dBuffer_Desc.ByteWidth = sizeof(unsigned int) * nMage_Index_Count;
				d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
				d3dBuffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				d3dBuffer_Desc.CPUAccessFlags = NULL;
				d3dBuffer_Desc.MiscFlags = 0;
				d3dBuffer_Desc.StructureByteStride = 0;

				ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
				d3dSRD.pSysMem = nMage_Indicies;
				d3dSRD.SysMemPitch = 0;
				d3dSRD.SysMemSlicePitch = 0;

				d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_test_mage_index_buffer);

				// SRV

				std::wstring d_tmp = std::wstring(mage_mats.tMats[0].szDiffuse_File_Path.begin(), mage_mats.tMats[0].szDiffuse_File_Path.end());
				const wchar_t* diffuse_path = d_tmp.c_str();
				HRESULT result = CreateWICTextureFromFile(d3dDevice, d3dContext, diffuse_path, nullptr, &mage_srv_diffuse.p, 0);

				std::wstring e_tmp = std::wstring(mage_mats.tMats[0].szEmissive_File_Path.begin(), mage_mats.tMats[0].szEmissive_File_Path.end());
				const wchar_t* emissive_path = e_tmp.c_str();
				CreateWICTextureFromFile(d3dDevice, d3dContext, emissive_path, nullptr, &mage_srv_emissive.p, 0);

				std::wstring s_tmp = std::wstring(mage_mats.tMats[0].szSpecular_File_Path.begin(), mage_mats.tMats[0].szSpecular_File_Path.end());
				const wchar_t* specular_path = s_tmp.c_str();
				CreateWICTextureFromFile(d3dDevice, d3dContext, specular_path, nullptr, &mage_srv_specular.p, 0);
			}

			// ARENA
			{
				// VERTEX BUFFER

				for (int i = 0; i < nArena_Vertex_Count; i++)
				{
					test_arena[i] = tArena.tVerts[i];
				}

				// Move
				for (int i = 0; i < nArena_Vertex_Count; i++)
				{
					test_arena[i].fPosition.fX -= 15.0f;
				}

				ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dBuffer_Desc.ByteWidth = sizeof(tVertex) * nArena_Vertex_Count;
				d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
				d3dBuffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				d3dBuffer_Desc.CPUAccessFlags = NULL;
				d3dBuffer_Desc.MiscFlags = 0;
				d3dBuffer_Desc.StructureByteStride = 0;

				ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
				d3dSRD.pSysMem = test_arena;
				d3dSRD.SysMemPitch = 0;
				d3dSRD.SysMemSlicePitch = 0;

				d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &tObject_System.vertex_buffers[tArenaIDs.pipeline_id]);

				// INDEX BUFFER

				int* nArena_Indicies = new int[nArena_Index_Count];
				for (int i = 0; i < nArena_Index_Count; i++)
				{
					nArena_Indicies[i] = tArena.nIndicies[i];
				}

				ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
				d3dBuffer_Desc.ByteWidth = sizeof(unsigned int) * nArena_Index_Count;
				d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
				d3dBuffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				d3dBuffer_Desc.CPUAccessFlags = NULL;
				d3dBuffer_Desc.MiscFlags = 0;
				d3dBuffer_Desc.StructureByteStride = 0;

				ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
				d3dSRD.pSysMem = nArena_Indicies;
				d3dSRD.SysMemPitch = 0;
				d3dSRD.SysMemSlicePitch = 0;

				d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &tObject_System.index_buffers[tArenaIDs.pipeline_id]);

				// SRV

				std::wstring d_tmp = std::wstring(arena_mats.tMats[0].szDiffuse_File_Path.begin(), arena_mats.tMats[0].szDiffuse_File_Path.end());
				const wchar_t* diffuse_path = d_tmp.c_str();
				HRESULT result = CreateWICTextureFromFile(d3dDevice, d3dContext, diffuse_path, nullptr, &arena_srv_diffuse.p, 0);

				//std::wstring e_tmp = std::wstring(arena_mats.tMats[0].szEmissive_File_Path.begin(), arena_mats.tMats[0].szEmissive_File_Path.end());
				//const wchar_t* emissive_path = e_tmp.c_str();
				//CreateWICTextureFromFile(d3dDevice, d3dContext, emissive_path, nullptr, &arena_srv_emissive.p, 0);
				//
				//std::wstring s_tmp = std::wstring(arena_mats.tMats[0].szSpecular_File_Path.begin(), arena_mats.tMats[0].szSpecular_File_Path.end());
				//const wchar_t* specular_path = s_tmp.c_str();
				//CreateWICTextureFromFile(d3dDevice, d3dContext, specular_path, nullptr, &arena_srv_specular.p, 0);
			}
		}
	}

	void draw_view(cView& c_View)
	{
		// SIGNALS
		cTime.Signal();

		// RESIZE / RESET RTV AND VP
		{
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
		}

		if (didCollide)
		{
			tBULLET.fData.w = 0;
			tBULLET.fData.z = 0;
			test_bullet_toggle = false;
		}

		// MOVE BULLET
		if (test_bullet_toggle)
		{
			tBULLET.fData.z += (float)cTime.Delta() * 10;
		}

		// AABB CHECKS
		tAABB aabb_bullet, aabb_dummy;
		aabb_bullet.center = { 0.0, 0.0f, 0.0f };
		aabb_bullet.center.fZ += tBULLET.fData.z;
		aabb_bullet.extents = { 1.0, 1.0f, 1.0f };
		aabb_dummy.center = { 0.0, 0.0f, 15.0f };
		aabb_dummy.extents = { 2.0, 4.0f, 2.0f };
		didCollide = tColl.Detect_AABB_To_AABB(aabb_bullet, aabb_dummy);

		if (didCollide)
		{
			if (tDUMMY.fData.w == 0)
				tDUMMY.fData.w = 1;
			else
				tDUMMY.fData.w = 0;
		}

		XMMATRIX mCamera_Matrix = XMLoadFloat4x4(&fCamera_Matrix);
		XMMATRIX mCamera_Origin = XMLoadFloat4x4(&fCamera_Origin);

		// CONTROLS
		{
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

			// F - switch color
			if (GetAsyncKeyState('F'))
			{
				if (!test_bullet_toggle)
				{
					test_bullet_toggle = true;
					tBULLET.fData.w = 1;
				}
			}
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

		XMStoreFloat4x4(&fCamera_Matrix, mCamera_Matrix);
		c_View.setCamera_Matrix(fCamera_Matrix);

		// Get Current Window Size
		RECT current_window_size;
		GetClientRect(_hWnd, &current_window_size);
		float fWindow_Height = (float)current_window_size.bottom - (float)current_window_size.top;
		float fWindow_Width = (float)current_window_size.right - (float)current_window_size.left;

		// CONSTANT BUFFERS
		{
			// CONSTANT BUFFER - WVPC
			{
				// STORE DATA
				XMStoreFloat4x4(&tWVPC.fWorld_Matrix, XMMatrixIdentity());
				XMStoreFloat4x4(&tWVPC.fView_Matrix, XMMatrixInverse(nullptr, mCamera_Matrix));
				XMStoreFloat4x4(&tWVPC.fProjection_Matrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(45), fWindow_Width / fWindow_Height, 0.1f, 3000.0f));
				XMStoreFloat4x4(&tWVPC.fCamera_Matrix, mCamera_Matrix);
				XMStoreFloat4x4(&tWVPC.fCamera_Origin, mCamera_Origin);

				// MAP DATA
				d3dContext->Map(d3dConstant_Buffer_WVPC, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMSR);
				memcpy(d3dMSR.pData, &tWVPC, sizeof(tConstantBuffer_VertexShader_WVPC));
				d3dContext->Unmap(d3dConstant_Buffer_WVPC, 0);
				ID3D11Buffer *tmp_wvpc_buffer[] = { d3dConstant_Buffer_WVPC };
				d3dContext->VSSetConstantBuffers(0, 1, tmp_wvpc_buffer);
			}

			// CONSTANT BUFFER - DUMMY
			{
				// MAP DATA
				d3dContext->Map(d3dConstant_Buffer_DUMMY, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMSR);
				memcpy(d3dMSR.pData, &tDUMMY, sizeof(tConstantBuffer_Float4));
				d3dContext->Unmap(d3dConstant_Buffer_DUMMY, 0);
				ID3D11Buffer *tmp_dummy_buffer[] = { d3dConstant_Buffer_DUMMY };
				d3dContext->PSSetConstantBuffers(0, 1, tmp_dummy_buffer);
			}

			// CONSTANT BUFFER - BULLET
			{
				// MAP DATA
				d3dContext->Map(d3dConstant_Buffer_BULLET, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMSR);
				memcpy(d3dMSR.pData, &tBULLET, sizeof(tConstantBuffer_Float4));
				d3dContext->Unmap(d3dConstant_Buffer_BULLET, 0);
				ID3D11Buffer *tmp_bullet_buffer[] = { d3dConstant_Buffer_BULLET };
				d3dContext->VSSetConstantBuffers(1, 1, tmp_bullet_buffer);
			}


			// CONSTANT BUFFER - MAGE
			{
				// STORE DATA
				cps_mage.light_pos = { 15.0f, 20.0f, 15.0f, 1.0f };

				cps_mage.ambient.x = mage_mats.tMats[0].tAmbient.fX;
				cps_mage.ambient.y = mage_mats.tMats[0].tAmbient.fY;
				cps_mage.ambient.z = mage_mats.tMats[0].tAmbient.fZ;
				cps_mage.ambient.w = mage_mats.tMats[0].tAmbient.fW;

				cps_mage.diffuse.x = mage_mats.tMats[0].tDiffuse.fX;
				cps_mage.diffuse.y = mage_mats.tMats[0].tDiffuse.fY;
				cps_mage.diffuse.z = mage_mats.tMats[0].tDiffuse.fZ;
				cps_mage.diffuse.w = mage_mats.tMats[0].tDiffuse.fW;

				cps_mage.emissive.x = mage_mats.tMats[0].tEmissive.fX;
				cps_mage.emissive.y = mage_mats.tMats[0].tEmissive.fY;
				cps_mage.emissive.z = mage_mats.tMats[0].tEmissive.fZ;
				cps_mage.emissive.w = mage_mats.tMats[0].tEmissive.fW;

				cps_mage.reflection.x = mage_mats.tMats[0].tReflection.fX;
				cps_mage.reflection.y = mage_mats.tMats[0].tReflection.fY;
				cps_mage.reflection.z = mage_mats.tMats[0].tReflection.fZ;
				cps_mage.reflection.w = mage_mats.tMats[0].tReflection.fW;

				cps_mage.shininess.x = mage_mats.tMats[0].fShininess;

				cps_mage.specular.x = mage_mats.tMats[0].tSpecular.fX;
				cps_mage.specular.y = mage_mats.tMats[0].tSpecular.fY;
				cps_mage.specular.z = mage_mats.tMats[0].tSpecular.fZ;
				cps_mage.specular.w = mage_mats.tMats[0].tSpecular.fW;

				cps_mage.transparency.x = mage_mats.tMats[0].tTransparency.fX;
				cps_mage.transparency.y = mage_mats.tMats[0].tTransparency.fY;
				cps_mage.transparency.z = mage_mats.tMats[0].tTransparency.fZ;
				cps_mage.transparency.w = mage_mats.tMats[0].tTransparency.fW;

				// MAP DATA
				d3dContext->Map(d3dConstant_Buffer_MAGE, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMSR);
				memcpy(d3dMSR.pData, &cps_mage, sizeof(tConstantBuffer_PixelShader));
				d3dContext->Unmap(d3dConstant_Buffer_MAGE, 0);
				ID3D11Buffer *tmp_mage_buffer[] = { d3dConstant_Buffer_MAGE };
				d3dContext->PSSetConstantBuffers(1, 1, tmp_mage_buffer);
			}

			// CONSTANT BUFFER - ARENA
			{
				// STORE DATA
				cps_arena.light_pos = { 15.0f, 20.0f, 15.0f, 1.0f };

				cps_arena.ambient.x = arena_mats.tMats[0].tAmbient.fX;
				cps_arena.ambient.y = arena_mats.tMats[0].tAmbient.fY;
				cps_arena.ambient.z = arena_mats.tMats[0].tAmbient.fZ;
				cps_arena.ambient.w = arena_mats.tMats[0].tAmbient.fW;

				cps_arena.diffuse.x = arena_mats.tMats[0].tDiffuse.fX;
				cps_arena.diffuse.y = arena_mats.tMats[0].tDiffuse.fY;
				cps_arena.diffuse.z = arena_mats.tMats[0].tDiffuse.fZ;
				cps_arena.diffuse.w = arena_mats.tMats[0].tDiffuse.fW;

				cps_arena.emissive.x = arena_mats.tMats[0].tEmissive.fX;
				cps_arena.emissive.y = arena_mats.tMats[0].tEmissive.fY;
				cps_arena.emissive.z = arena_mats.tMats[0].tEmissive.fZ;
				cps_arena.emissive.w = arena_mats.tMats[0].tEmissive.fW;

				cps_arena.reflection.x = arena_mats.tMats[0].tReflection.fX;
				cps_arena.reflection.y = arena_mats.tMats[0].tReflection.fY;
				cps_arena.reflection.z = arena_mats.tMats[0].tReflection.fZ;
				cps_arena.reflection.w = arena_mats.tMats[0].tReflection.fW;

				cps_arena.shininess.x = arena_mats.tMats[0].fShininess;

				cps_arena.specular.x = arena_mats.tMats[0].tSpecular.fX;
				cps_arena.specular.y = arena_mats.tMats[0].tSpecular.fY;
				cps_arena.specular.z = arena_mats.tMats[0].tSpecular.fZ;
				cps_arena.specular.w = arena_mats.tMats[0].tSpecular.fW;

				cps_arena.transparency.x = arena_mats.tMats[0].tTransparency.fX;
				cps_arena.transparency.y = arena_mats.tMats[0].tTransparency.fY;
				cps_arena.transparency.z = arena_mats.tMats[0].tTransparency.fZ;
				cps_arena.transparency.w = arena_mats.tMats[0].tTransparency.fW;

				// MAP DATA
				d3dContext->Map(tObject_System.constant_buffers[tArenaIDs.constant_buffer_wvp_id], 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMSR);
				memcpy(d3dMSR.pData, &cps_arena, sizeof(tConstantBuffer_PixelShader));
				d3dContext->Unmap(tObject_System.constant_buffers[tArenaIDs.constant_buffer_wvp_id], 0);
				ID3D11Buffer *tmp_mage_buffer[] = { tObject_System.constant_buffers[tArenaIDs.constant_buffer_wvp_id] };
				d3dContext->PSSetConstantBuffers(1, 1, tmp_mage_buffer);
			}
		}
		// DRAWS
		{
			unsigned int verts_size = sizeof(tVertex);
			unsigned int off_set = 0;

			// DUMMY
			{
				ID3D11Buffer *tmp_v_buffer[] = { d3d_test_dummy_vertex_buffer };
				d3dContext->IASetVertexBuffers(0, 1, tmp_v_buffer, &verts_size, &off_set);
				d3dContext->IASetIndexBuffer(d3d_test_dummy_index_buffer, DXGI_FORMAT_R32_UINT, 0);
				d3dContext->IASetInputLayout(d3dInput_Layout);
				d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				d3dContext->VSSetShader(d3dVertex_Shader, NULL, 0);
				d3dContext->PSSetShader(d3dPixel_Shader, NULL, 0);
				d3dContext->DrawIndexed(36, 0, 0);
			}

			// BULLET
			{
				ID3D11Buffer *tmp_v_buffer[] = { d3d_test_bullet_vertex_buffer };
				d3dContext->IASetVertexBuffers(0, 1, tmp_v_buffer, &verts_size, &off_set);
				d3dContext->IASetIndexBuffer(d3d_test_bullet_index_buffer, DXGI_FORMAT_R32_UINT, 0);
				d3dContext->IASetInputLayout(d3dInput_Layout);
				d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				d3dContext->VSSetShader(d3dVertex_Shader_Bullet, NULL, 0);
				d3dContext->PSSetShader(d3dPixel_Shader, NULL, 0);
				if (test_bullet_toggle)
					d3dContext->DrawIndexed(36, 0, 0);
			}

			// MAGE
			{
				ID3D11Buffer *tmp_v_buffer[] = { d3d_test_mage_vertex_buffer };
				d3dContext->IASetVertexBuffers(0, 1, tmp_v_buffer, &verts_size, &off_set);
				d3dContext->IASetIndexBuffer(d3d_test_mage_index_buffer, DXGI_FORMAT_R32_UINT, 0);
				d3dContext->IASetInputLayout(d3dInput_Layout);
				d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				d3dContext->VSSetShader(d3dVertex_Shader, NULL, 0);
				d3dContext->PSSetShader(d3dPixel_Shader_Mage, NULL, 0);
				ID3D11ShaderResourceView *mage_srv_d[] = { mage_srv_diffuse };
				d3dContext->PSSetShaderResources(0, 1, mage_srv_d);
				ID3D11ShaderResourceView *mage_srv_e[] = { mage_srv_emissive };
				d3dContext->PSSetShaderResources(1, 1, mage_srv_e);
				ID3D11ShaderResourceView *mage_srv_s[] = { mage_srv_specular };
				d3dContext->PSSetShaderResources(2, 1, mage_srv_s);
				d3dContext->DrawIndexed(nMage_Index_Count, 0, 0);
			}

			// ARENA
			{
				ID3D11Buffer *tmp_v_buffer[] = { tObject_System.vertex_buffers[tArenaIDs.pipeline_id] };
				d3dContext->IASetVertexBuffers(0, 1, tmp_v_buffer, &verts_size, &off_set);
				d3dContext->IASetIndexBuffer(tObject_System.index_buffers[tArenaIDs.pipeline_id], DXGI_FORMAT_R32_UINT, 0);
				d3dContext->IASetInputLayout(d3dInput_Layout);
				d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				d3dContext->VSSetShader(tObject_System.vertex_shaders[tArenaIDs.vertex_shader_id], NULL, 0);
				d3dContext->PSSetShader(tObject_System.pixel_shaders[tArenaIDs.pixel_shader_id], NULL, 0);
				ID3D11ShaderResourceView *arena_srv_d[] = { arena_srv_diffuse };
				d3dContext->PSSetShaderResources(0, 1, arena_srv_d);
				//ID3D11ShaderResourceView *arena_srv_e[] = { arena_srv_emissive };
				//d3dContext->PSSetShaderResources(1, 1, arena_srv_e);
				//ID3D11ShaderResourceView *arena_srv_s[] = { arena_srv_specular };
				//d3dContext->PSSetShaderResources(2, 1, arena_srv_s);
				d3dContext->DrawIndexed(nArena_Index_Count, 0, 0);
			}

			// PRESENT
			d3dSwap_Chain->Present(1, 0);
		}
	}
};
