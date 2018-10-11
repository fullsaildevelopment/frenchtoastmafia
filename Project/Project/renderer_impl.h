#pragma once

#include <atlbase.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
using namespace DirectX;

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#include "basic_structs.h"
#include "renderer.h"
#include "renderer_structs.h"
#include "XTime.h"

#include "VertexShader.csh"
#include "PixelShader.csh"

//Ben's includes

#include "Ben_funcs.h"
#include "Ben_variables.h"
#include "WICTextureLoader.h"

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

	XMVECTOR vEye_Vector = { 0.0f, 15.0f, -15.0f, 0.0f };
	XMVECTOR vAt_Vector = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMVECTOR vUp_Vector = { 0.0f, 1.0f, 0.0f, 0.0f };
	XMMATRIX mCamera_Matrix = XMMatrixInverse(nullptr, XMMatrixLookAtLH(vEye_Vector, vAt_Vector, vUp_Vector));
	XMMATRIX mCamera_Origin = mCamera_Matrix;

	XTime cTime;

	void initialize(cView& v)
	{
		//Ben test
		if (true)
		{
			//int materialStuff(const char* fbx_file_path, vector<myLam>* _arenaLamVec, vector<myPhong>* _arenaPhongVec);
			//
			//int blah = materialStuff(filePath2, &arenaLamVec, &arenaPhongVec);
			//int get_scene_poly_count(const char* fbx_file_path);
			//
			//int sceneCount = get_scene_poly_count(filePath2);
			//
			//cout << "Number of lams: " << arenaLamVec.size() << "\n\n";
			//for (int l = 0; l < arenaLamVec.size(); l++)
			//{
			//	cout << "lam " << l + 1 << ":\n";
			//}
			//
			//cout << "Number of phongs: " << arenaPhongVec.size() << "\n\n";
			//for (int p = 0; p < arenaPhongVec.size(); p++)
			//{
			//	cout << "phong " << p + 1 << ":\n";
			//
			//	if (arenaPhongVec[p].ambientFilePath != nullptr)
			//	{
			//		cout << "ambient tex file path:" << arenaPhongVec[p].ambientFilePath << "\n";
			//	}
			//	else
			//	{
			//		cout << "ambient  tex file path: none.\n";
			//	}
			//	cout << "ambient: " << arenaPhongVec[p].ambient[0] << ", " << arenaPhongVec[p].ambient[1] << ", " << arenaPhongVec[p].ambient[2] << "\n";
			//
			//	if (arenaPhongVec[p].diffuseFilePath != nullptr)
			//	{
			//		cout << "diffuse tex file path:" << arenaPhongVec[p].diffuseFilePath << "\n";
			//	}
			//	else
			//	{
			//		cout << "diffuse tex file path: none.\n";
			//	}
			//	cout << "diffuse: " << arenaPhongVec[p].diffuse[0] << ", " << arenaPhongVec[p].diffuse[1] << ", " << arenaPhongVec[p].diffuse[2] << "\n";
			//
			//	if (arenaPhongVec[p].emissiveFilePath != nullptr)
			//	{
			//		cout << "emissive tex file path:" << arenaPhongVec[p].emissiveFilePath << "\n";
			//	}
			//	else
			//	{
			//		cout << "emissive tex file path: none.\n";
			//	}
			//	cout << "emissive: " << arenaPhongVec[p].emissive[0] << ", " << arenaPhongVec[p].emissive[1] << ", " << arenaPhongVec[p].emissive[2] << "\n";
			//
			//	if (arenaPhongVec[p].specularFilePath != nullptr)
			//	{
			//		cout << "specular tex file path:" << arenaPhongVec[p].specularFilePath << "\n";
			//	}
			//	else
			//	{
			//		cout << "specular tex file path: none.\n";
			//	}
			//	cout << "specular: " << arenaPhongVec[p].specular[0] << ", " << arenaPhongVec[p].specular[1] << ", " << arenaPhongVec[p].specular[2] << "\n";
			//
			//	cout << "transparency: " << arenaPhongVec[p].transparency << "\n";
			//	cout << "shininess: " << arenaPhongVec[p].shininess << "\n";
			//	cout << "reflection: " << arenaPhongVec[p].reflection << "\n\n";
			//}
			//
			//if (1)
			//{
			//	bool tr = true;
			//}
			//
			//ofstream oStream;
			//oStream.open("binFile1.bin", ios::binary);
			//if (oStream.is_open())
			//{
			//	int test = sizeof(arenaPhongVec[0]);
			//	for (int i = 0; i < arenaPhongVec.size(); i++)
			//	{
			//		oStream.write((char*)&arenaPhongVec[i], sizeof(arenaPhongVec[i]));
			//	}
			//}
			//
			//
			//oStream.close();
			//
			//
			//ifstream iStream("binFile1.bin", ios::in | ios::binary | ios::ate);
			//iStream.seekg(0, ios::beg);
			//
			//if (iStream.is_open())
			//{
			//	for (int p = 0; p < arenaPhongVec.size(); p++)
			//	{
			//		cout << "Reconstructed Phongs: \n\n";
			//		iStream.read((char*)&arenaPhongVec[p], sizeof(arenaPhongVec[p]));
			//
			//		cout << "phong " << p + 1 << ":\n";
			//
			//		if (arenaPhongVec[p].ambientFilePath != nullptr)
			//		{
			//			cout << "ambient tex file path:" << arenaPhongVec[p].ambientFilePath << "\n";
			//		}
			//		else
			//		{
			//			cout << "ambient  tex file path: none.\n";
			//		}
			//		cout << "ambient: " << arenaPhongVec[p].ambient[0] << ", " << arenaPhongVec[p].ambient[1] << ", " << arenaPhongVec[p].ambient[2] << "\n";
			//
			//		if (arenaPhongVec[p].diffuseFilePath != nullptr)
			//		{
			//			cout << "diffuse tex file path:" << arenaPhongVec[p].diffuseFilePath << "\n";
			//		}
			//		else
			//		{
			//			cout << "diffuse tex file path: none.\n";
			//		}
			//		cout << "diffuse: " << arenaPhongVec[p].diffuse[0] << ", " << arenaPhongVec[p].diffuse[1] << ", " << arenaPhongVec[p].diffuse[2] << "\n";
			//
			//		if (arenaPhongVec[p].emissiveFilePath != nullptr)
			//		{
			//			cout << "emissive tex file path:" << arenaPhongVec[p].emissiveFilePath << "\n";
			//		}
			//		else
			//		{
			//			cout << "emissive tex file path: none.\n";
			//		}
			//		cout << "emissive: " << arenaPhongVec[p].emissive[0] << ", " << arenaPhongVec[p].emissive[1] << ", " << arenaPhongVec[p].emissive[2] << "\n";
			//
			//		if (arenaPhongVec[p].specularFilePath != nullptr)
			//		{
			//			cout << "specular tex file path:" << arenaPhongVec[p].specularFilePath << "\n";
			//		}
			//		else
			//		{
			//			cout << "specular tex file path: none.\n";
			//		}
			//		cout << "specular: " << arenaPhongVec[p].specular[0] << ", " << arenaPhongVec[p].specular[1] << ", " << arenaPhongVec[p].specular[2] << "\n";
			//
			//		cout << "transparency: " << arenaPhongVec[p].transparency << "\n";
			//		cout << "shininess: " << arenaPhongVec[p].shininess << "\n";
			//		cout << "reflection: " << arenaPhongVec[p].reflection << "\n\n";
			//	}
			//
			//	iStream.close();
			//}

				//End of Ben test
		}
		
		//mage calls
		if (true)
		{
			polyCount = get_scene_poly_count(filePath1);
			vertCount = polyCount * 3;
			
			int CPs;
			
			gibVertsPls(filePath1, &myFloats, &cpIndexes, &CPs);
			
			int blah = materialStuff(filePath1, &lamVec, &phongVec);
			
			bool tr = true;
		}

		//arena calls
		if (true)
		{
			arenaPolyCount = get_scene_poly_count(filePath2);
			arenaVertCount = arenaPolyCount * 3;

			int arenaCPs;

			getArenaVerts(filePath2, &arenaPositions, &arenaUVs, &arenaNormals, &arenaIndexes, &arenaCPs);

			int blah = materialStuff(filePath2, &arenaLamVec, &arenaPhongVec);

			bool tr = true;
		}


		//end Ben test

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

		//MAGE CREATION
		if (true)
		{
			//VERTEX SHADER TEST
			if (true)
			{
				ifstream myVSFile("../x64/Debug/VertexShaderTest.cso", std::ifstream::binary);
				if (myVSFile)
				{
					myVSFile.seekg(0, std::ios_base::end);
					unsigned int size = (unsigned int)myVSFile.tellg();
					myVSFile.seekg(0, std::ios_base::beg);

					char* myVSchar = new char[size];
					myVSFile.read(myVSchar, size);

					HRESULT VSresult = d3dDevice->CreateVertexShader(myVSchar, size, nullptr, &mySystem.vertex_shaders[0]);

					D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
					{
						{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
						{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
						{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					};

					HRESULT ILresult = d3dDevice->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), myVSchar, size, &mySystem.input_layouts[0]);

					delete[] myVSchar;
				}
			}

			//PIXEL SHADER TEST
			if (true)
			{
				ifstream myPSFile("../x64/Debug/PixelShaderTest.cso", std::ifstream::binary);
				if (myPSFile)
				{
					myPSFile.seekg(0, std::ios_base::end);
					unsigned int size = (unsigned int)myPSFile.tellg();
					myPSFile.seekg(0, std::ios_base::beg);

					char* myPSchar = new char[size];
					myPSFile.read(myPSchar, size);

					HRESULT PSresult = d3dDevice->CreatePixelShader(myPSchar, size, nullptr, &mySystem.pixel_shaders[0]);

					delete[] myPSchar;
				}
			}

			//CONSTANT BUFFER TEST
			if (true)
			{
				CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
				HRESULT CBresult = d3dDevice->CreateBuffer(&constantBufferDesc, nullptr, &mySystem.constant_buffers[0]);

				//MODEL
				XMStoreFloat4x4(&mySystem.constant_data[0].model, XMMatrixTranslation(5.0f, 0.0f, 0.0f));

				//VIEW

				XMStoreFloat4x4(&mySystem.constant_data[0].view, mCamera_Matrix);

				//PERSPECTIVE
				float fovAngleY = 70.0f * XM_PI / 180.0f;
				float aspectRatio = d3dView_Port.Width / d3dView_Port.Height;

				//XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, 0.1f, 1000.0f);
				XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(45), fWindow_Width / fWindow_Height, 0.1f, 1000.0f);

				XMStoreFloat4x4(&mySystem.constant_data[0].projection, perspectiveMatrix);

				//material buffer
				CD3D11_BUFFER_DESC constantBufferDesc2(sizeof(PhongForShader), D3D11_BIND_SHADER_RESOURCE);
				HRESULT CBresult2 = d3dDevice->CreateBuffer(&constantBufferDesc2, nullptr, &mySystem.material_buffers[0]);

				fillMageMaterial(&mageMaterial, phongVec[0]);

				d3dContext->UpdateSubresource(mySystem.material_buffers[0], 0, NULL, &mageMaterial, 0, 0);

				if (phongVec[0].diffuseFilePath != NULL)
				{
					//wchar_t path = *phongVec[0].diffuseFilePath;
					//HRESULT result = CreateWICTextureFromFile(dev, devcon, &path, (ID3D11Resource**)mageTex[0], &mageSRV[0], D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION);

					HRESULT result = CreateWICTextureFromFile(d3dDevice, d3dContext, L"models\\test\\Idle.fbm\\PPG_3D_Player_D.png", (ID3D11Resource**)mageDiffuseTex[0], &mageDiffuseSRV[0], D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION);

					bool tr = true;
				}

				if (phongVec[0].emissiveFilePath != NULL)
				{
					//wchar_t path = *phongVec[0].diffuseFilePath;
					//HRESULT result = CreateWICTextureFromFile(dev, devcon, &path, (ID3D11Resource**)mageTex[0], &mageSRV[0], D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION);

					HRESULT result = CreateWICTextureFromFile(d3dDevice, d3dContext, L"models\\test\\Idle.fbm\\PPG_3D_Player_emissive.png", (ID3D11Resource**)mageEmissiveTex[0], &mageEmissiveSRV[0], D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION);

					bool tr = true;
				}

				if (phongVec[0].specularFilePath != NULL)
				{
					//wchar_t path = *phongVec[0].diffuseFilePath;
					//HRESULT result = CreateWICTextureFromFile(dev, devcon, &path, (ID3D11Resource**)mageTex[0], &mageSRV[0], D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION);

					HRESULT result = CreateWICTextureFromFile(d3dDevice, d3dContext, L"models\\test\\Idle.fbm\\PPG_3D_Player_spec.png", (ID3D11Resource**)mageSpecularTex[0], &mageSpecularSRV[0], D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION);

					bool tr = true;
				}

				//set sampler

				D3D11_SAMPLER_DESC samplerDesc;
				samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
				samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
				samplerDesc.MipLODBias = 0.0f;
				samplerDesc.MaxAnisotropy = 1;
				samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
				samplerDesc.MinLOD = -FLT_MAX;
				samplerDesc.MaxLOD = FLT_MAX;

				HRESULT hr = d3dDevice->CreateSamplerState(&samplerDesc, &myLinearWrapSampler);

			}

			//VERTEX BUFFER TEST
			if (true)
			{
				PositionUVNormal* mageVerts = new PositionUVNormal[vertCount];

				//construct verts with our custom struct
				//
				for (int i = 0; i < vertCount; ++i)
				{
					//PositionUVNormal temp;
					//
					//int break1 = 30132;
					//int break2 = 50220;
					//
					//temp.pos = { myFloats[i * 3],          myFloats[i * 3 + 1],          myFloats[i * 3 + 2] };
					//
					//temp.uv = { myFloats[i * 2 + break1], myFloats[i * 2 + break1 + 1] };
					//
					//temp.normal = { myFloats[i * 3 + break2], myFloats[i * 3 + break2 + 1], myFloats[i * 3 + break2 + 2] };
					//
					//temp.uv.y = 1 - temp.uv.y;
					//mageVerts[i] = temp;

					PositionUVNormal temp;

					int break1 = vertCount * 3;//30132;
					int break2 = vertCount * 5;//50220;

					temp.pos = { myFloats[i * 3],          myFloats[i * 3 + 1],          myFloats[i * 3 + 2] };

					temp.uv = { myFloats[i * 2 + break1], myFloats[i * 2 + break1 + 1] };

					temp.normal = { myFloats[i * 3 + break2], myFloats[i * 3 + break2 + 1], myFloats[i * 3 + break2 + 2] };

					temp.uv.y = 1 - temp.uv.y;
					mageVerts[i] = temp;

				}

				D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
				vertexBufferData.pSysMem = mageVerts;
				vertexBufferData.SysMemPitch = 0;
				vertexBufferData.SysMemSlicePitch = 0;
				CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(PositionUVNormal) * vertCount, D3D11_BIND_VERTEX_BUFFER);
				d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &mySystem.vertex_buffers[0]);


				//index count
				mySystem.index_counts[0] = (INT32)vertCount;

				delete[] mageVerts;
			}

			//====================DEPTH STENCIL STATES=================

			//DEPTH STENCIL STATE 0
			if (true)
			{
				D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

				// Depth test parameters
				depthStencilDesc.DepthEnable = true;
				depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

				// Stencil test parameters
				depthStencilDesc.StencilEnable = true;
				depthStencilDesc.StencilReadMask = 0xFF;
				depthStencilDesc.StencilWriteMask = 0xFF;

				// Stencil operations if pixel is front-facing
				depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
				depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

				// Stencil operations if pixel is back-facing
				depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
				depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

				// Create depth stencil state
				d3dDevice->CreateDepthStencilState(&depthStencilDesc, &mySystem.depth_stencil_states[0]);
			}

			//====================RASTER STATES========================

			//RASTER STATE 0
			if (true)
			{
				D3D11_RASTERIZER_DESC rasterDesc;
				rasterDesc.FillMode = D3D11_FILL_SOLID;
				rasterDesc.CullMode = D3D11_CULL_BACK;
				rasterDesc.FrontCounterClockwise = false;
				rasterDesc.DepthBias = 0;
				rasterDesc.DepthBiasClamp = 0.0f;
				rasterDesc.SlopeScaledDepthBias = 0.0f;
				rasterDesc.DepthClipEnable = true;
				rasterDesc.ScissorEnable = false;
				rasterDesc.MultisampleEnable = false;
				rasterDesc.AntialiasedLineEnable = false;

				d3dDevice->CreateRasterizerState(&rasterDesc, &mySystem.rasterizer_states[0]);
			}
		}

		//ARENA CREATION
		if (true)
		{
			//PIXEL SHADER TEST
			if (true)
			{
				ifstream myPSFile("../x64/Debug/PixelShaderArena.cso", std::ifstream::binary);
				if (myPSFile)
				{
					myPSFile.seekg(0, std::ios_base::end);
					unsigned int size = (unsigned int)myPSFile.tellg();
					myPSFile.seekg(0, std::ios_base::beg);

					char* myPSchar = new char[size];
					myPSFile.read(myPSchar, size);

					HRESULT PSresult = d3dDevice->CreatePixelShader(myPSchar, size, nullptr, &mySystem.pixel_shaders[1]);

					delete[] myPSchar;
				}
			}

			//CONSTANT BUFFER TEST
			if (true)
			{
				CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
				HRESULT CBresult = d3dDevice->CreateBuffer(&constantBufferDesc, nullptr, &mySystem.constant_buffers[1]);

				//MODEL
				XMStoreFloat4x4(&mySystem.constant_data[1].model, XMMatrixTranslation(5.0f, 0.0f, 0.0f));

				//VIEW

				XMStoreFloat4x4(&mySystem.constant_data[1].view, mCamera_Matrix);

				//PERSPECTIVE
				float fovAngleY = 70.0f * XM_PI / 180.0f;
				float aspectRatio = d3dView_Port.Width / d3dView_Port.Height;

				//XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, 0.1f, 1000.0f);
				XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(45), fWindow_Width / fWindow_Height, 0.1f, 1000.0f);

				XMStoreFloat4x4(&mySystem.constant_data[1].projection, perspectiveMatrix);

				//material buffer
				CD3D11_BUFFER_DESC constantBufferDesc2(sizeof(PhongForShader), D3D11_BIND_SHADER_RESOURCE);
				HRESULT CBresult2 = d3dDevice->CreateBuffer(&constantBufferDesc2, nullptr, &mySystem.material_buffers[1]);

				fillArenaMaterial(&arenaMaterial, arenaPhongVec[1]);

				d3dContext->UpdateSubresource(mySystem.material_buffers[1], 0, NULL, &arenaMaterial, 0, 0);

				if (arenaPhongVec[1].diffuseFilePath != NULL)
				{
					HRESULT result = CreateWICTextureFromFile(d3dDevice, d3dContext, L"models\\Arena\\Arena.fbm\\JBrisnehan_Arena_Diffuse.png", (ID3D11Resource**)arenaDiffuseTex[1], &arenaDiffuseSRV[1], D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION);

					bool tr = true;
				}

			}

			//VERTEX BUFFER TEST
			if (true)
			{
				PositionUVNormal* arenaVerts = new PositionUVNormal[arenaVertCount];

				for (int i = 0; i < arenaVertCount; ++i)
				{
					PositionUVNormal temp;

					temp.pos = { arenaPositions[i * 3],          arenaPositions[i * 3 + 1],          arenaPositions[i * 3 + 2] };

					temp.uv = { arenaUVs[i * 2], arenaUVs[i * 2 + 1] };

					temp.normal = { arenaNormals[i * 3], arenaNormals[i * 3 + 1], arenaNormals[i * 3 + 2] };

					temp.uv.y = 1 - temp.uv.y;
					arenaVerts[i] = temp;

				}

				D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
				vertexBufferData.pSysMem = arenaVerts;
				vertexBufferData.SysMemPitch = 0;
				vertexBufferData.SysMemSlicePitch = 0;
				CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(PositionUVNormal) * arenaVertCount, D3D11_BIND_VERTEX_BUFFER);
				d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &mySystem.vertex_buffers[1]);

				//index count

				mySystem.index_counts[1] = arenaIndexes.size();

				//D3D11_SUBRESOURCE_DATA arenaIndexBufferData = { 0 };
				//arenaIndexBufferData.pSysMem = &arenaIndexes[0];
				//arenaIndexBufferData.SysMemPitch = 0;
				//arenaIndexBufferData.SysMemSlicePitch = 0;
				//CD3D11_BUFFER_DESC arenaIndexBufferDesc(arenaIndexes.size() * sizeof(int), D3D11_BIND_INDEX_BUFFER);
				//d3dDevice->CreateBuffer(&arenaIndexBufferDesc, &arenaIndexBufferData, &mySystem.index_buffers[1]);

				delete[] arenaVerts;
			}

		}

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

		setPipelineMain(myMage);
		setPipelineShadersAndLayout(myMage);
		setPipelineDSS(myMage);
		setPipelineRS(myMage);
		myDraw(myMage);

		setPipelineMain(arena1);
		setPipelineShadersAndLayout(arena1);
		myDraw(arena1);


		// PRESENT
		d3dSwap_Chain->Present(1, 0);
	}

	void setPipelineMain(pipeline_state_t _state)
	{
		//CONSTANT BUFFERS

		XMStoreFloat4x4(&mySystem.constant_data[_state.constant_buffer].model, XMMatrixTranspose(XMLoadFloat4x4(&mySystem.constant_data[_state.constant_buffer].model)));
		XMStoreFloat4x4(&mySystem.constant_data[_state.constant_buffer].view, XMMatrixTranspose(XMMatrixInverse(nullptr, mCamera_Matrix)));
		XMStoreFloat4x4(&mySystem.constant_data[_state.constant_buffer].projection, XMMatrixTranspose(XMLoadFloat4x4(&mySystem.constant_data[_state.constant_buffer].projection)));

		d3dContext->UpdateSubresource(mySystem.constant_buffers[_state.constant_buffer], 0, NULL, &mySystem.constant_data[_state.constant_buffer], 0, 0);

		XMStoreFloat4x4(&mySystem.constant_data[_state.constant_buffer].model, XMMatrixTranspose(XMLoadFloat4x4(&mySystem.constant_data[_state.constant_buffer].model)));
		//XMStoreFloat4x4(&mySystem.constant_data[_state.constant_buffer].view, XMMatrixInverse(nullptr, mCamera_Matrix));
		XMStoreFloat4x4(&mySystem.constant_data[_state.constant_buffer].projection, XMMatrixTranspose(XMLoadFloat4x4(&mySystem.constant_data[_state.constant_buffer].projection)));

		d3dContext->VSSetConstantBuffers(0, 1, &mySystem.constant_buffers[_state.constant_buffer]);

		if (_state.constant_buffer == 0)
		{
			d3dContext->PSSetConstantBuffers(0, 1, &mySystem.material_buffers[0]);

			ID3D11ShaderResourceView* mageTexView[] = { mageDiffuseSRV[0] };
			d3dContext->PSSetShaderResources(0, 1, mageTexView);

			ID3D11ShaderResourceView* mageTexView2[] = { mageEmissiveSRV[0] };
			d3dContext->PSSetShaderResources(1, 1, mageTexView2);

			ID3D11ShaderResourceView* mageTexView3[] = { mageSpecularSRV[0] };
			d3dContext->PSSetShaderResources(2, 1, mageTexView3);

			d3dContext->PSSetSamplers(0, 1, &myLinearWrapSampler);
		} else if (_state.constant_buffer == 1)
		{
			d3dContext->PSSetConstantBuffers(0, 1, &mySystem.material_buffers[1]);

			ID3D11ShaderResourceView* arenaTexView[] = { arenaDiffuseSRV[1] };
			d3dContext->PSSetShaderResources(0, 1, arenaTexView);

		}



		//VERETX BUFFERS

		if (_state.vertex_buffer == 0 || _state.vertex_buffer == 1)
		{
			UINT stride = sizeof(PositionUVNormal);
			UINT offset = 0;
			d3dContext->IASetVertexBuffers(0, 1, &mySystem.vertex_buffers[_state.vertex_buffer], &stride, &offset);

			d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		} 


	}
	void setPipelineShadersAndLayout(pipeline_state_t _state)
	{

		d3dContext->VSSetShader(mySystem.vertex_shaders[_state.vertex_shader], nullptr, 0);

		d3dContext->IASetInputLayout(mySystem.input_layouts[_state.vertex_shader]);

		d3dContext->PSSetShader(mySystem.pixel_shaders[_state.pixel_shader], nullptr, 0);

	}
	void setPipelineDSS(pipeline_state_t _state)
	{
		if (_state.depthStencilState == 0)
		{
			d3dContext->OMSetDepthStencilState(mySystem.depth_stencil_states[0], 0);
		}
	}
	void setPipelineRS(pipeline_state_t _state)
	{
		if (_state.rasterState == 0)
		{
			d3dContext->RSSetState(mySystem.rasterizer_states[0]);
		}
	}
	void myDraw(pipeline_state_t _state)
	{
		if (_state.vertex_buffer == 0)
		{
			d3dContext->Draw(mySystem.index_counts[_state.vertex_buffer], 0);
		} 
		else if (_state.vertex_buffer == 1)
		{
			d3dContext->Draw(mySystem.index_counts[_state.vertex_buffer], 0);
		}

	}

};

