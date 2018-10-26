#include "Render_Manager.h"

cRender_Manager::cRender_Manager()
{
}

cRender_Manager::~cRender_Manager()
{
}

void cRender_Manager::Initialize(cGraphics_Setup *c_Graphics_Setup)
{
	// CONSTANT BUFFER - WORLD VIEW PROJECTION CAMERA
	ZeroMemory(&d3d_Constant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
	d3d_Constant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_VertexShader_WVPC);
	d3d_Constant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
	d3d_Constant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	d3d_Constant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	d3d_Constant_Buffer_Desc.MiscFlags = 0;
	d3d_Constant_Buffer_Desc.StructureByteStride = 0;

	c_Graphics_Setup->GetDevice()->CreateBuffer(&d3d_Constant_Buffer_Desc, nullptr, &d3d_Constant_Buffer_WVPC.p);
}

//tScene_Objects cRender_Manager::GetScene(int nScene_Id)
//{
//	tScene_Objects tScene = cSM.GetScene(nScene_Id);
//	return tScene;
//}

void cRender_Manager::Load()
{
/*
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
*/
}

void cRender_Manager::Unload()
{
}

void cRender_Manager::Draw()
{
/*
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
*/
}

void cRender_Manager::DrawToTexture()
{
}
