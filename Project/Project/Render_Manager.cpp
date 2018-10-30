#include "Render_Manager.h"

cRender_Manager::cRender_Manager()
{
}

cRender_Manager::~cRender_Manager()
{
}

void cRender_Manager::Initialize(cGraphics_Setup* _setup)
{
	c_Graphics_Setup = _setup;

	// CONSTANT BUFFER - WORLD VIEW PROJECTION CAMERA
	ZeroMemory(&d3d_Constant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
	d3d_Constant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_VertexShader_WVP);
	d3d_Constant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
	d3d_Constant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	d3d_Constant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	d3d_Constant_Buffer_Desc.MiscFlags = 0;
	d3d_Constant_Buffer_Desc.StructureByteStride = 0;

	c_Graphics_Setup->Get_Device()->CreateBuffer(&d3d_Constant_Buffer_Desc, nullptr, &d3d_Constant_Buffer_WVP.p);
}

void cRender_Manager::Load(int nScene_Id, tScene_Objects* t_Object_List)
{
	for (int i = 0; i < t_Object_List->nObject_Count; i++)
	{
		CComPtr<ID3D11Buffer> d3d_tmp_vertex_buffer;
		CComPtr<ID3D11Buffer> d3d_tmp_index_buffer;
		CComPtr<ID3D11ShaderResourceView> d3d_tmp_srv;

		D3D11_BUFFER_DESC d3dBuffer_Desc;
		D3D11_SUBRESOURCE_DATA d3dSRD;

		// VERTEX
		tVertex *tmp_verts = new tVertex[t_Object_List->tMesh_Data[i].nVertex_Count];
		for (int j = 0; j < t_Object_List->tMesh_Data[i].nVertex_Count; j++)
		{
			tmp_verts[j] = t_Object_List->tMesh_Data[i].tVerts[j];
		}

		ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
		d3dBuffer_Desc.ByteWidth = sizeof(tVertex) * t_Object_List->tMesh_Data[i].nVertex_Count;
		d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
		d3dBuffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		d3dBuffer_Desc.CPUAccessFlags = NULL;
		d3dBuffer_Desc.MiscFlags = 0;
		d3dBuffer_Desc.StructureByteStride = 0;

		ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
		d3dSRD.pSysMem = tmp_verts;
		d3dSRD.SysMemPitch = 0;
		d3dSRD.SysMemSlicePitch = 0;

		c_Graphics_Setup->Get_Device()->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_tmp_vertex_buffer);
		t_Object_List->d3d_Vertex_Buffers[i] = d3d_tmp_vertex_buffer;

		// INDEX
		int *tmp_inds = new int[t_Object_List->tMesh_Data[i].nIndex_Count];
		for (int j = 0; j < t_Object_List->tMesh_Data[i].nIndex_Count; j++)
		{
			tmp_inds[j] = t_Object_List->tMesh_Data[i].nIndicies[j];
		}

		ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
		d3dBuffer_Desc.ByteWidth = sizeof(unsigned int) * t_Object_List->tMesh_Data[i].nIndex_Count;
		d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
		d3dBuffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		d3dBuffer_Desc.CPUAccessFlags = NULL;
		d3dBuffer_Desc.MiscFlags = 0;
		d3dBuffer_Desc.StructureByteStride = 0;

		ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
		d3dSRD.pSysMem = tmp_inds;
		d3dSRD.SysMemPitch = 0;
		d3dSRD.SysMemSlicePitch = 0;

		c_Graphics_Setup->Get_Device()->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_tmp_index_buffer.p);
		t_Object_List->d3d_Index_Buffers[i] = d3d_tmp_index_buffer;

		//VERTEX SHADERS
		//if (i == 1)
		//	d3dDevice->CreateVertexShader(VertexShader_Arena, sizeof(VertexShader_Arena), NULL, &tScene->d3d_Vertex_Shaders[1]);
		//
		////PIXEL SHADERS
		//if(i == 1)
		//	d3dDevice->CreatePixelShader(PixelShader_Arena, sizeof(PixelShader_Arena), NULL, &tScene->d3d_Pixel_Shaders[1]);
		//
		//// MATERIALS	
		//
		////// SRV
		//if (i == 1)
		//{
		//	std::wstring ws_tmp_srv = std::wstring(tScene->tMaterials_Data[1].tMats[0].szDiffuse_File_Path.begin(), tScene->tMaterials_Data[1].tMats[0].szDiffuse_File_Path.end());
		//	const wchar_t* tmp_srv = ws_tmp_srv.c_str();
		//	CreateWICTextureFromFile(d3dDevice, d3dContext, tmp_srv, nullptr, &tScene->d3d_SRV[i], 0);
		//}

		if (nScene_Id < 2 || nScene_Id > 3)
		{
			c_Graphics_Setup->Get_Device()->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &t_Object_List->d3d_Vertex_Shaders[0]);
			c_Graphics_Setup->Get_Device()->CreatePixelShader(PixelShader_Screen, sizeof(PixelShader_Screen), NULL, &t_Object_List->d3d_Pixel_Shaders[0]);
			std::wstring ws_tmp_srv = std::wstring(t_Object_List->szSRV_File_Path[0].begin(), t_Object_List->szSRV_File_Path[0].end());
			const wchar_t* tmp_srv = ws_tmp_srv.c_str();
			CreateDDSTextureFromFile(c_Graphics_Setup->Get_Device(), tmp_srv, nullptr, &t_Object_List->d3d_SRV[0].p);
		}
	}
}

void cRender_Manager::Unload()
{
}

void cRender_Manager::Draw(int nScene_Id, tScene_Objects t_Object_List)
{
	for (int _eyeID = 0; _eyeID < 2; _eyeID++)
	{
		// SIGNALS
		cTime.Signal();

		if (_eyeID == 0)
		{
			ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV_Left() };
			c_Graphics_Setup->Get_Context()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV());
		}
		else
		{
			ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV_Right() };
			c_Graphics_Setup->Get_Context()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV());
		}

		// RESIZE / RESET RTV AND VP
		//c_Graphics_Setup->Get_Context()->OMSetRenderTargets(0, 0, 0);
		//c_Graphics_Setup->Get_RTV().Release();
		//c_Graphics_Setup->Get_Swap_Chain()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		//ID3D11Texture2D *back_buffer;
		//c_Graphics_Setup->Get_Swap_Chain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
		//c_Graphics_Setup->Get_Device()->CreateRenderTargetView(back_buffer, NULL, &c_Graphics_Setup->Get_RTV());
		//ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV() };
		////c_Graphics_Setup->Get_Context()->OMSetDepthStencilState(c_Graphics_Setup->Get_Depth_Stencil_State(), 1);
		//c_Graphics_Setup->Get_Context()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV());
		//c_Graphics_Setup->Get_Context()->RSSetViewports(1, &c_Graphics_Setup->Get_View_Port());
		// SKY BLUE
		float clear_color[4] = { 1.000000000f, 0.000000000f, 0.83137255f, 1.000000000f };
		// WHITE
		//float clear_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		c_Graphics_Setup->Get_Context()->ClearRenderTargetView(c_Graphics_Setup->Get_RTV(), clear_color);
		c_Graphics_Setup->Get_Context()->ClearDepthStencilView(c_Graphics_Setup->Get_DSV(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		//XMFLOAT4X4 fCamera_Matrix = tFloat4x4_to_XMFLOAT4x4(cCam.GetPosition());
		//XMMATRIX mCamera_Matrix = XMLoadFloat4x4(&fCamera_Matrix);

		// Get Current Window Size
		/*RECT current_window_size;
		GetClientRect(hWnd, &current_window_size);
		float fWindow_Height = (float)current_window_size.bottom - (float)current_window_size.top;
		float fWindow_Width = (float)current_window_size.right - (float)current_window_size.left;*/

		// CONTROLS

	/*
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
		*/

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
		
		XMStoreFloat4x4(&tWVP.fView_Matrix, XMMatrixIdentity());
		if (_eyeID == 0)
		{
			tFloat4x4 temp_Projection;

			temp_Projection = c_Graphics_Setup->GetCurrentViewProjectionMatrix(vr::Eye_Left);

			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Graphics_Setup->get_Camera_Left().Normalize2(temp_Projection));

			//tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Graphics_Setup->GetCurrentViewProjectionMatrix(vr::Eye_Left));

			//tWVP.fProjection_Matrix._31 *= -1;
			//tWVP.fProjection_Matrix._32 *= -1;
			//tWVP.fProjection_Matrix._33 *= -1;
		}
		else
		{
			tFloat4x4 temp_Projection;

			temp_Projection = c_Graphics_Setup->GetCurrentViewProjectionMatrix(vr::Eye_Right);

			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Graphics_Setup->get_Camera_Right().Normalize2(temp_Projection));

			//tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Graphics_Setup->GetCurrentViewProjectionMatrix(vr::Eye_Right));

			//tWVP.fProjection_Matrix._31 *= -1;
			//tWVP.fProjection_Matrix._32 *= -1;
			//tWVP.fProjection_Matrix._33 *= -1;
		}

		//XMStoreFloat4x4(&tWVP.fProjection_Matrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(45), 1424 / 720, fNearClip, fFarClip));
		//XMStoreFloat4x4(&tWVPC.fCamera_Matrix, mCamera_Matrix);

		unsigned int verts_size = sizeof(tVertex);
		unsigned int off_set = 0;

		for (int i = 0; i < 1; i++)
		{
			// CONSTANT BUFFER - WVPC
			{
				// STORE DATA

				if (!objSet)
				{
					//tempWorld = tempWorld * XMMatrixRotationY(3.14 / 2);
					tempWorld = XMMatrixMultiply(tempWorld, XMMatrixTranslation(t_Object_List.fWorld_Position->fX, t_Object_List.fWorld_Position->fY, t_Object_List.fWorld_Position->fZ));
					objSet = true;
				}
				//if (GetAsyncKeyState('S'))
				//{
				//	tempWorld = XMMatrixMultiply(tempWorld, XMMatrixTranslation(-1, 0, 0));
				//}
				//if (GetAsyncKeyState('W'))
				//{
				//	tempWorld = XMMatrixMultiply(tempWorld, XMMatrixTranslation(1, 0, 0));
				//}
				//if (GetAsyncKeyState('A'))
				//{
				//	tempWorld = XMMatrixMultiply(tempWorld, XMMatrixTranslation(0, 0, 1));
				//}
				//if (GetAsyncKeyState('D'))
				//{
				//	tempWorld = XMMatrixMultiply(tempWorld, XMMatrixTranslation(0, 0, -1));
				//}

				XMStoreFloat4x4(&tWVP.fWorld_Matrix, tempWorld);

				//tWVP.fWorld_Matrix = t_Object_List.fWorld_Matrix[i];

				// MAP DATA
				c_Graphics_Setup->Get_Context()->Map(d3d_Constant_Buffer_WVP, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
				memcpy(d3d_MSR.pData, &tWVP, sizeof(tConstantBuffer_VertexShader_WVP));
				c_Graphics_Setup->Get_Context()->Unmap(d3d_Constant_Buffer_WVP, 0);
				ID3D11Buffer *tmp_wvpc_buffer[] = { d3d_Constant_Buffer_WVP };
				c_Graphics_Setup->Get_Context()->VSSetConstantBuffers(0, 1, tmp_wvpc_buffer);
			}

			ID3D11Buffer *ts_v_buffer[] = { t_Object_List.d3d_Vertex_Buffers[i] };
			c_Graphics_Setup->Get_Context()->IASetVertexBuffers(0, 1, ts_v_buffer, &verts_size, &off_set);
			c_Graphics_Setup->Get_Context()->IASetIndexBuffer(t_Object_List.d3d_Index_Buffers[i], DXGI_FORMAT_R32_UINT, 0);
			c_Graphics_Setup->Get_Context()->IASetInputLayout(c_Graphics_Setup->Get_Input_Layout());
			c_Graphics_Setup->Get_Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			//if (i != 1)
			//{
			//	c_Graphics_Setup->Get_Context()->VSSetShader(c_Graphics_Setup->Get_Vertex_Shader(), NULL, 0);
			//	c_Graphics_Setup->Get_Context()->PSSetShader(c_Graphics_Setup->Get_Pixel_Shader(), NULL, 0);
			//}
			//else
			//{
			c_Graphics_Setup->Get_Context()->VSSetShader(t_Object_List.d3d_Vertex_Shaders[i], NULL, 0);
			c_Graphics_Setup->Get_Context()->PSSetShader(t_Object_List.d3d_Pixel_Shaders[i], NULL, 0);
			c_Graphics_Setup->Get_Context()->PSSetShaderResources(0, 1, &t_Object_List.d3d_SRV[i].p);
			//}
			//d3dContext->PSSetShader(d3dPixel_Shader_Screen, NULL, 0);
			//ID3D11ShaderResourceView *tmp_intro_srv[] = { tScene.d3d_SRV[0] };
			//d3dContext->PSSetShaderResources(0, 1, tmp_intro_srv);
			//if (i != 1)
			c_Graphics_Setup->Get_Context()->DrawIndexed(t_Object_List.tMesh_Data[i].nIndex_Count, 0, 0);
		}
	}

	c_Graphics_Setup->Get_Swap_Chain()->Present(1, 0);
}

void cRender_Manager::DrawToTexture()
{
}
