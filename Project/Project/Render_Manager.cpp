#include "Render_Manager.h"

cRender_Manager::cRender_Manager()
{
}

cRender_Manager::~cRender_Manager()
{
}

void cRender_Manager::Initialize(HWND _hwnd)
{
	// BACKEND SETUP
	hWnd = _hwnd;

	XMFLOAT4X4 fCamera_Matrix;
	XMMATRIX mCamera_Matrix = XMMatrixInverse(nullptr, XMMatrixLookAtLH({ 0.0f, 15.0f, -25.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }));
	XMStoreFloat4x4(&fCamera_Matrix, mCamera_Matrix);
	tFloat4x4 tCamera_Matrix = XMFLOAT4x4_to_tFloat4x4(fCamera_Matrix);
	cCam.SetPostion(tCamera_Matrix);

	// Get Current Window Size
	RECT current_window_size;
	GetClientRect(hWnd, &current_window_size);
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
	d3dSwap_Chain_Desc.OutputWindow = hWnd;
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
	d3dZ_Buffer_Desc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT; //DXGI_FORMAT_D32_FLOAT
	d3dZ_Buffer_Desc.SampleDesc.Count = 1;
	d3dZ_Buffer_Desc.SampleDesc.Quality = 0;
	d3dZ_Buffer_Desc.Usage = D3D11_USAGE_DEFAULT;
	d3dZ_Buffer_Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	d3dZ_Buffer_Desc.CPUAccessFlags = 0;
	d3dZ_Buffer_Desc.MiscFlags = 0;

	d3dDevice->CreateTexture2D(&d3dZ_Buffer_Desc, nullptr, &d3dZ_Buffer.p);

	// DEPTH STENCIL STATE
	ZeroMemory(&d3dDSS_Desc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	d3dDSS_Desc.DepthEnable = true;
	d3dDSS_Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	d3dDSS_Desc.DepthFunc = D3D11_COMPARISON_LESS;
	// Stencil test parameters
	d3dDSS_Desc.StencilEnable = true;
	d3dDSS_Desc.StencilReadMask = 0xFF;
	d3dDSS_Desc.StencilWriteMask = 0xFF;
	// Stencil operations if pixel is front-facing
	d3dDSS_Desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	d3dDSS_Desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	d3dDSS_Desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	d3dDSS_Desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	// Stencil operations if pixel is back-facing
	d3dDSS_Desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	d3dDSS_Desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	d3dDSS_Desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	d3dDSS_Desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	d3dDevice->CreateDepthStencilState(&d3dDSS_Desc, &d3dDSS);

	// DEPTH STENCIL VIEW
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
	d3dDevice->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, &d3dPixel_Shader.p);
	d3dDevice->CreatePixelShader(PixelShader_Screen, sizeof(PixelShader_Screen), NULL, &d3dPixel_Shader_Screen.p);

	// INPUT ELEMENT
	D3D11_INPUT_ELEMENT_DESC d3dInput_Element[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	d3dDevice->CreateInputLayout(d3dInput_Element, ARRAYSIZE(d3dInput_Element), VertexShader, sizeof(VertexShader), &d3dInput_Layout.p);

	// CONSTANT BUFFER - WORLD VIEW PROJECTION CAMERA
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

	cSM.SetDevice(d3dDevice);
}

tScene_Objects cRender_Manager::GetScene(int nScene_Id)
{
	tScene_Objects tScene = cSM.GetScene(nScene_Id);
	return tScene;
}

void cRender_Manager::Load(tScene_Objects *tScene)
{
	for (int i = 0; i < tScene->nObject_Count; i++)
	{
		CComPtr<ID3D11Buffer> d3d_tmp_vertex_buffer;
		CComPtr<ID3D11Buffer> d3d_tmp_index_buffer;
		CComPtr<ID3D11ShaderResourceView> d3d_tmp_srv;

		D3D11_BUFFER_DESC d3dBuffer_Desc;
		D3D11_SUBRESOURCE_DATA d3dSRD;

		// VERTEX
		tVertex *tmp_verts = new tVertex[tScene->tMesh_Data[i].nVertex_Count];
		for (int j = 0; j < tScene->tMesh_Data[i].nVertex_Count; j++)
		{
			tmp_verts[j] = tScene->tMesh_Data[i].tVerts[j];
		}

		ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
		d3dBuffer_Desc.ByteWidth = sizeof(tVertex) * tScene->tMesh_Data[i].nVertex_Count;
		d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
		d3dBuffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		d3dBuffer_Desc.CPUAccessFlags = NULL;
		d3dBuffer_Desc.MiscFlags = 0;
		d3dBuffer_Desc.StructureByteStride = 0;

		ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
		d3dSRD.pSysMem = tmp_verts;
		d3dSRD.SysMemPitch = 0;
		d3dSRD.SysMemSlicePitch = 0;

		d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_tmp_vertex_buffer);
		tScene->d3d_Vertex_Buffers[i] = d3d_tmp_vertex_buffer;

		// INDEX
		int *tmp_inds = new int[tScene->tMesh_Data[i].nIndex_Count];
		for (int j = 0; j < tScene->tMesh_Data[i].nIndex_Count; j++)
		{
			tmp_inds[j] = tScene->tMesh_Data[i].nIndicies[j];
		}

		ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
		d3dBuffer_Desc.ByteWidth = sizeof(unsigned int) * tScene->tMesh_Data[i].nIndex_Count;
		d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
		d3dBuffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		d3dBuffer_Desc.CPUAccessFlags = NULL;
		d3dBuffer_Desc.MiscFlags = 0;
		d3dBuffer_Desc.StructureByteStride = 0;

		ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
		d3dSRD.pSysMem = tmp_inds;
		d3dSRD.SysMemPitch = 0;
		d3dSRD.SysMemSlicePitch = 0;

		d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_tmp_index_buffer.p);
		tScene->d3d_Index_Buffers[i] = d3d_tmp_index_buffer;

		//VERTEX SHADERS
		if (i == 1)
			d3dDevice->CreateVertexShader(VertexShader_Arena, sizeof(VertexShader_Arena), NULL, &tScene->d3d_Vertex_Shaders[1]);

		//PIXEL SHADERS
		if(i == 1)
			d3dDevice->CreatePixelShader(PixelShader_Arena, sizeof(PixelShader_Arena), NULL, &tScene->d3d_Pixel_Shaders[1]);

		// MATERIALS	

		//// SRV
		if (i == 1)
		{
			std::wstring ws_tmp_srv = std::wstring(tScene->tMaterials_Data[1].tMats[0].szDiffuse_File_Path.begin(), tScene->tMaterials_Data[1].tMats[0].szDiffuse_File_Path.end());
			const wchar_t* tmp_srv = ws_tmp_srv.c_str();
			CreateWICTextureFromFile(d3dDevice, d3dContext, tmp_srv, nullptr, &tScene->d3d_SRV[i], 0);
		}
		
		//tScene->d3d_SRV[i] = d3d_tmp_srv;
	}

}

void cRender_Manager::Unload(tScene_Objects tScene)
{
}

void cRender_Manager::Draw(tScene_Objects tScene)
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
	d3dContext->OMSetDepthStencilState(d3dDSS, 1);
	d3dContext->OMSetRenderTargets(1, tmp_rtv, d3dDSV);
	d3dContext->RSSetViewports(1, &d3dView_Port);
	// SKY BLUE
	float clear_color[4] = { 0.000000000f, 0.749019623f, 1.000000000f, 1.000000000f };
	// WHITE
	//float clear_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	d3dContext->ClearRenderTargetView(d3dRTV, clear_color);
	d3dContext->ClearDepthStencilView(d3dDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

	XMFLOAT4X4 fCamera_Matrix = tFloat4x4_to_XMFLOAT4x4(cCam.GetPosition());
	XMMATRIX mCamera_Matrix = XMLoadFloat4x4(&fCamera_Matrix);

	// Get Current Window Size
	RECT current_window_size;
	GetClientRect(hWnd, &current_window_size);
	float fWindow_Height = (float)current_window_size.bottom - (float)current_window_size.top;
	float fWindow_Width = (float)current_window_size.right - (float)current_window_size.left;
	
	// CONTROLS
	{
		tFloat4 change_data;

		// A - move left
		if (GetAsyncKeyState('A'))
		{
			change_data = { ((float)cTime.Delta() * 25), 0.0f, 0.0f, 0.0f };
			cCam.Translation(change_data);
		}

		// D - move right
		if (GetAsyncKeyState('D'))
		{
			change_data = { -((float)cTime.Delta() * 25), 0.0f, 0.0f, 0.0f };
			cCam.Translation(change_data);
		}

		// Q - move up
		if (GetAsyncKeyState('Q'))
		{
			change_data = { 0.0f, -((float)cTime.Delta() * 25), 0.0f, 1.0f };
			cCam.Translation(change_data);
		}

		// E - move down
		if (GetAsyncKeyState('E'))
		{
			change_data = { 0.0f, ((float)cTime.Delta() * 25), 0.0f, 1.0f };
			cCam.Translation(change_data);
		}

		// S - move out
		if (GetAsyncKeyState('S'))
		{
			change_data = { 0.0f, 0.0f, ((float)cTime.Delta() * 25), 0.0f };
			cCam.Translation(change_data);
		}

		// W - move in
		if (GetAsyncKeyState('W'))
		{
			change_data = { 0.0f, 0.0f, -((float)cTime.Delta() * 25), 0.0f };
			cCam.Translation(change_data);
		}

		// I - look up
		if (GetAsyncKeyState('I'))
		{
			change_data = { -(float)cTime.Delta(), 0.0f, 0.0f, 0.0f };
			cCam.Rotation(change_data);
		}

		// K - look down
		if (GetAsyncKeyState('K'))
		{
			change_data = { (float)cTime.Delta(), 0.0f, 0.0f, 1.0f };
			cCam.Rotation(change_data);
		}

		// L - look right
		if (GetAsyncKeyState('L'))
		{
			change_data = { 0.0f, (float)cTime.Delta(), 0.0f, 2.0f };
			cCam.Rotation(change_data);
		}

		// J - look left
		if (GetAsyncKeyState('J'))
		{
			change_data = { 0.0f, -(float)cTime.Delta(), 0.0f, 3.0f };
			cCam.Rotation(change_data);
		}

		cCam.Normalize();
	}
//	// CONSTANT BUFFERS
//	{
//		// CONSTANT BUFFER - WVPC
//		{
//			// STORE DATA
//
//			XMStoreFloat4x4(&tWVPC.fWorld_Matrix, XMMatrixIdentity());
//			XMStoreFloat4x4(&tWVPC.fView_Matrix, XMMatrixInverse(nullptr, mCamera_Matrix));
//			XMStoreFloat4x4(&tWVPC.fProjection_Matrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(45), fWindow_Width / fWindow_Height, 0.1f, 1000.0f));
//			XMStoreFloat4x4(&tWVPC.fCamera_Matrix, mCamera_Matrix);
//
//			// MAP DATA
//			d3dContext->Map(d3dConstant_Buffer_WVPC, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMSR);
//			memcpy(d3dMSR.pData, &tWVPC, sizeof(tConstantBuffer_VertexShader_WVPC));
//			d3dContext->Unmap(d3dConstant_Buffer_WVPC, 0);
//			ID3D11Buffer *tmp_wvpc_buffer[] = { d3dConstant_Buffer_WVPC };
//			d3dContext->VSSetConstantBuffers(0, 1, tmp_wvpc_buffer);
//		}
//	}


	unsigned int verts_size = sizeof(tVertex);
	unsigned int off_set = 0;

	XMStoreFloat4x4(&tWVPC.fView_Matrix, XMMatrixInverse(nullptr, mCamera_Matrix));
	XMStoreFloat4x4(&tWVPC.fProjection_Matrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(45), fWindow_Width / fWindow_Height, fNearClip, fFarClip));
	XMStoreFloat4x4(&tWVPC.fCamera_Matrix, mCamera_Matrix);

	for (int i = 0; i < 3; i++)
	{
		// CONSTANT BUFFER - WVPC
		{
			// STORE DATA

			tWVPC.fWorld_Matrix = tScene.fWorld_Matrix[i];

			// MAP DATA
			d3dContext->Map(d3dConstant_Buffer_WVPC, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMSR);
			memcpy(d3dMSR.pData, &tWVPC, sizeof(tConstantBuffer_VertexShader_WVPC));
			d3dContext->Unmap(d3dConstant_Buffer_WVPC, 0);
			ID3D11Buffer *tmp_wvpc_buffer[] = { d3dConstant_Buffer_WVPC };
			d3dContext->VSSetConstantBuffers(0, 1, tmp_wvpc_buffer);
		}

		ID3D11Buffer *ts_v_buffer[] = { tScene.d3d_Vertex_Buffers[i] };
		d3dContext->IASetVertexBuffers(0, 1, ts_v_buffer, &verts_size, &off_set);
		d3dContext->IASetIndexBuffer(tScene.d3d_Index_Buffers[i], DXGI_FORMAT_R32_UINT, 0);
		d3dContext->IASetInputLayout(d3dInput_Layout);
		d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		if (i != 1)
		{
			d3dContext->VSSetShader(d3dVertex_Shader, NULL, 0);
			d3dContext->PSSetShader(d3dPixel_Shader, NULL, 0);
		}
		else
		{
			d3dContext->VSSetShader( tScene.d3d_Vertex_Shaders[1], NULL, 0);
			d3dContext->PSSetShader( tScene.d3d_Pixel_Shaders[1], NULL, 0);
			d3dContext->PSSetShaderResources(0, 1, &tScene.d3d_SRV[1].p);
		}
		//d3dContext->PSSetShader(d3dPixel_Shader_Screen, NULL, 0);
		//ID3D11ShaderResourceView *tmp_intro_srv[] = { tScene.d3d_SRV[0] };
		//d3dContext->PSSetShaderResources(0, 1, tmp_intro_srv);
		//if (i != 1)
			d3dContext->DrawIndexed(tScene.tMesh_Data[i].nIndex_Count, 0, 0);
	}
	

	d3dSwap_Chain->Present(1, 0);
}

void cRender_Manager::DrawToTexture()
{
}
