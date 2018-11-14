/************************************************************************
* Filename:  		Render_Manager.cpp
* Date:      		02/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to handle all rendering related task.
*************************************************************************/

#include "Render_Manager.h"

cRender_Manager::cRender_Manager()
{
}

cRender_Manager::~cRender_Manager()
{
}

void cRender_Manager::Initialize(cGraphics_Setup* _setup)
{
	nAnimation_Frame = 0;
	c_Graphics_Setup = _setup;

	// CONSTANT BUFFER - WORLD VIEW PROJECTION CAMERA
	ZeroMemory(&d3d_Constant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
	d3d_Constant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_VertexShader_WVP);
	d3d_Constant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
	d3d_Constant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	d3d_Constant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	d3d_Constant_Buffer_Desc.MiscFlags = 0;
	d3d_Constant_Buffer_Desc.StructureByteStride = 0;

	c_Graphics_Setup->Get_Device().Get()->CreateBuffer(&d3d_Constant_Buffer_Desc, nullptr, d3d_Constant_Buffer_WVP.GetAddressOf());

	// CONSTANT BUFFER - Animation
	ZeroMemory(&d3d_Constant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
	d3d_Constant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_VertexShader_Animation);
	d3d_Constant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
	d3d_Constant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	d3d_Constant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	d3d_Constant_Buffer_Desc.MiscFlags = 0;
	d3d_Constant_Buffer_Desc.StructureByteStride = 0;

	c_Graphics_Setup->Get_Device().Get()->CreateBuffer(&d3d_Constant_Buffer_Desc, nullptr, d3d_Constant_Buffer_Animation.GetAddressOf());
}

void cRender_Manager::Load_Data(int nScene_Id, tScene_Objects* tObject_List)
{
	for (int i = 0; i < tObject_List->nObject_Count; i++)
	{
		ComPtr<ID3D11Buffer> d3d_tmp_vertex_buffer;
		ComPtr<ID3D11Buffer> d3d_tmp_index_buffer;
		ComPtr<ID3D11ShaderResourceView> d3d_tmp_srv;

		D3D11_BUFFER_DESC d3dBuffer_Desc;
		D3D11_SUBRESOURCE_DATA d3dSRD;

		if (!tObject_List->bIs_Animated[i])
		{
			// VERTEX
			tVertex *tmp_verts = new tVertex[tObject_List->tMesh_Data[i].nVertex_Count];
			for (int j = 0; j < tObject_List->tMesh_Data[i].nVertex_Count; j++)
			{
				tmp_verts[j] = tObject_List->tMesh_Data[i].tVerts[j];
			}

			ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
			d3dBuffer_Desc.ByteWidth = sizeof(tVertex) * tObject_List->tMesh_Data[i].nVertex_Count;
			d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
			d3dBuffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			d3dBuffer_Desc.CPUAccessFlags = NULL;
			d3dBuffer_Desc.MiscFlags = 0;
			d3dBuffer_Desc.StructureByteStride = 0;

			ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
			d3dSRD.pSysMem = tmp_verts;
			d3dSRD.SysMemPitch = 0;
			d3dSRD.SysMemSlicePitch = 0;

			c_Graphics_Setup->Get_Device().Get()->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_tmp_vertex_buffer);
			tObject_List->d3d_Vertex_Buffers[i] = d3d_tmp_vertex_buffer;

			// INDEX
			int *tmp_inds = new int[tObject_List->tMesh_Data[i].nIndex_Count];
			for (unsigned int j = 0; j < tObject_List->tMesh_Data[i].nIndex_Count; j++)
			{
				tmp_inds[j] = tObject_List->tMesh_Data[i].nIndicies[j];
			}

			ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
			d3dBuffer_Desc.ByteWidth = sizeof(unsigned int) * tObject_List->tMesh_Data[i].nIndex_Count;
			d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
			d3dBuffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			d3dBuffer_Desc.CPUAccessFlags = NULL;
			d3dBuffer_Desc.MiscFlags = 0;
			d3dBuffer_Desc.StructureByteStride = 0;

			ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
			d3dSRD.pSysMem = tmp_inds;
			d3dSRD.SysMemPitch = 0;
			d3dSRD.SysMemSlicePitch = 0;

			c_Graphics_Setup->Get_Device().Get()->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, d3d_tmp_index_buffer.GetAddressOf());
			tObject_List->d3d_Index_Buffers[i] = d3d_tmp_index_buffer;
		}
		else
		{
			// VERTEX SKINNED
			tVertex_Skinned *tmp_verts = new tVertex_Skinned[tObject_List->tMesh_Skinned_Data[i].nVertex_Count];
			for (unsigned int j = 0; j < tObject_List->tMesh_Skinned_Data[i].nVertex_Count; j++)
			{
				tmp_verts[j] = tObject_List->tMesh_Skinned_Data[i].tVerts[j];
			}

			ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
			d3dBuffer_Desc.ByteWidth = sizeof(tVertex_Skinned) * tObject_List->tMesh_Skinned_Data[i].nVertex_Count;
			d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
			d3dBuffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			d3dBuffer_Desc.CPUAccessFlags = NULL;
			d3dBuffer_Desc.MiscFlags = 0;
			d3dBuffer_Desc.StructureByteStride = 0;

			ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
			d3dSRD.pSysMem = tmp_verts;
			d3dSRD.SysMemPitch = 0;
			d3dSRD.SysMemSlicePitch = 0;

			c_Graphics_Setup->Get_Device().Get()->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_tmp_vertex_buffer);
			tObject_List->d3d_Vertex_Buffers[i] = d3d_tmp_vertex_buffer;

			// INDEX
			int *tmp_inds = new int[tObject_List->tMesh_Skinned_Data[i].nIndex_Count];
			for (unsigned int j = 0; j < tObject_List->tMesh_Skinned_Data[i].nIndex_Count; j++)
			{
				tmp_inds[j] = tObject_List->tMesh_Skinned_Data[i].nIndicies[j];
			}

			ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
			d3dBuffer_Desc.ByteWidth = sizeof(unsigned int) * tObject_List->tMesh_Skinned_Data[i].nIndex_Count;
			d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
			d3dBuffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			d3dBuffer_Desc.CPUAccessFlags = NULL;
			d3dBuffer_Desc.MiscFlags = 0;
			d3dBuffer_Desc.StructureByteStride = 0;

			ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
			d3dSRD.pSysMem = tmp_inds;
			d3dSRD.SysMemPitch = 0;
			d3dSRD.SysMemSlicePitch = 0;

			c_Graphics_Setup->Get_Device().Get()->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, d3d_tmp_index_buffer.GetAddressOf());
			tObject_List->d3d_Index_Buffers[i] = d3d_tmp_index_buffer;
		}

		if (nScene_Id < 2 || nScene_Id == 3)
		{
			c_Graphics_Setup->Get_Device().Get()->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &tObject_List->d3d_Vertex_Shaders[i]);
			c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(PixelShader_Screen, sizeof(PixelShader_Screen), NULL, &tObject_List->d3d_Pixel_Shaders[i]);
			std::wstring ws_tmp_srv = std::wstring(tObject_List->szSRV_File_Path.begin(), tObject_List->szSRV_File_Path.end());
			const wchar_t* tmp_srv = ws_tmp_srv.c_str();
			CreateDDSTextureFromFile(c_Graphics_Setup->Get_Device().Get(), tmp_srv, nullptr, tObject_List->d3d_SRV[i][0].GetAddressOf());
		}
		else //if (nScene_Id == 2)
		{
			//VERTEX SHADERS
			if (tObject_List->bIs_Animated[i])
				c_Graphics_Setup->Get_Device().Get()->CreateVertexShader(VertexShader_Animation, sizeof(VertexShader_Animation), NULL, &tObject_List->d3d_Vertex_Shaders[i]);
			else
				c_Graphics_Setup->Get_Device().Get()->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &tObject_List->d3d_Vertex_Shaders[i]);

			//PIXEL SHADERS
			if (i == 0)
			{
				c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(PixelShader_Mage, sizeof(PixelShader_Mage), NULL, &tObject_List->d3d_Pixel_Shaders[i]);
			}
			else if (i == 1)
			{
				c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(PixelShader_Arena, sizeof(PixelShader_Arena), NULL, &tObject_List->d3d_Pixel_Shaders[i]);
			}
			else if (i == 2)
			{
				c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, &tObject_List->d3d_Pixel_Shaders[i]);
			}
			else if (i == 3)
			{
				c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(PixelShader_Dragon, sizeof(PixelShader_Dragon), NULL, &tObject_List->d3d_Pixel_Shaders[i]);
			}
			else if (i == 4)
			{
				c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(PixelShader_Fireball, sizeof(PixelShader_Fireball), NULL, &tObject_List->d3d_Pixel_Shaders[i]);
			}
			else if (i == 5)
			{
				c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(PixelShader_Priest, sizeof(PixelShader_Priest), NULL, &tObject_List->d3d_Pixel_Shaders[i]);
			}

			// SRV
			int k = 0;
			for (int j = 0; j < tObject_List->tMaterials_Data[i].tMats.size(); j++)
			{
				std::wstring wstr_tmp;
				const wchar_t* path_tmp;
				if (tObject_List->tMaterials_Data[i].tMats[j].tAmbient.fW != 0)
				{
					wstr_tmp = std::wstring(tObject_List->tMaterials_Data[i].tMats[j].szAmbient_File_Path.begin(), tObject_List->tMaterials_Data[i].tMats[j].szAmbient_File_Path.end());
					path_tmp = wstr_tmp.c_str();
					CreateWICTextureFromFile(c_Graphics_Setup->Get_Device().Get(), c_Graphics_Setup->Get_Context().Get(), path_tmp, nullptr, &tObject_List->d3d_SRV[i][k], 0);
					k++;
				}

				if (tObject_List->tMaterials_Data[i].tMats[j].tDiffuse.fW != 0)
				{
					wstr_tmp = std::wstring(tObject_List->tMaterials_Data[i].tMats[j].szDiffuse_File_Path.begin(), tObject_List->tMaterials_Data[i].tMats[j].szDiffuse_File_Path.end());
					path_tmp = wstr_tmp.c_str();
					CreateWICTextureFromFile(c_Graphics_Setup->Get_Device().Get(), c_Graphics_Setup->Get_Context().Get(), path_tmp, nullptr, &tObject_List->d3d_SRV[i][k], 0);
					k++;
				}

				if (tObject_List->tMaterials_Data[i].tMats[j].tEmissive.fW != 0)
				{
					wstr_tmp = std::wstring(tObject_List->tMaterials_Data[i].tMats[j].szEmissive_File_Path.begin(), tObject_List->tMaterials_Data[i].tMats[j].szEmissive_File_Path.end());
					path_tmp = wstr_tmp.c_str();
					CreateWICTextureFromFile(c_Graphics_Setup->Get_Device().Get(), c_Graphics_Setup->Get_Context().Get(), path_tmp, nullptr, &tObject_List->d3d_SRV[i][k], 0);
					k++;
				}

				if (tObject_List->tMaterials_Data[i].tMats[j].tNormal.fW != 0)
				{
					wstr_tmp = std::wstring(tObject_List->tMaterials_Data[i].tMats[j].szNormal_File_Path.begin(), tObject_List->tMaterials_Data[i].tMats[j].szNormal_File_Path.end());
					path_tmp = wstr_tmp.c_str();
					CreateWICTextureFromFile(c_Graphics_Setup->Get_Device().Get(), c_Graphics_Setup->Get_Context().Get(), path_tmp, nullptr, &tObject_List->d3d_SRV[i][k], 0);
					k++;
				}

				if (tObject_List->tMaterials_Data[i].tMats[j].tReflection.fW != 0)
				{
					wstr_tmp = std::wstring(tObject_List->tMaterials_Data[i].tMats[j].szReflection_File_Path.begin(), tObject_List->tMaterials_Data[i].tMats[j].szReflection_File_Path.end());
					path_tmp = wstr_tmp.c_str();
					CreateWICTextureFromFile(c_Graphics_Setup->Get_Device().Get(), c_Graphics_Setup->Get_Context().Get(), path_tmp, nullptr, &tObject_List->d3d_SRV[i][k], 0);
					k++;
				}

				if (tObject_List->tMaterials_Data[i].tMats[j].fShininess != 0)
				{
					wstr_tmp = std::wstring(tObject_List->tMaterials_Data[i].tMats[j].szShininess_File_Path.begin(), tObject_List->tMaterials_Data[i].tMats[j].szShininess_File_Path.end());
					path_tmp = wstr_tmp.c_str();
					CreateWICTextureFromFile(c_Graphics_Setup->Get_Device().Get(), c_Graphics_Setup->Get_Context().Get(), path_tmp, nullptr, &tObject_List->d3d_SRV[i][k], 0);
					k++;
				}

				if (tObject_List->tMaterials_Data[i].tMats[j].tSpecular.fW != 0)
				{
					wstr_tmp = std::wstring(tObject_List->tMaterials_Data[i].tMats[j].szSpecular_File_Path.begin(), tObject_List->tMaterials_Data[i].tMats[j].szSpecular_File_Path.end());
					path_tmp = wstr_tmp.c_str();
					CreateWICTextureFromFile(c_Graphics_Setup->Get_Device().Get(), c_Graphics_Setup->Get_Context().Get(), path_tmp, nullptr, &tObject_List->d3d_SRV[i][k], 0);
					k++;
				}

				if (tObject_List->tMaterials_Data[i].tMats[j].tTransparency.fW != 0)
				{
					wstr_tmp = std::wstring(tObject_List->tMaterials_Data[i].tMats[j].szTransparency_File_Path.begin(), tObject_List->tMaterials_Data[i].tMats[j].szTransparency_File_Path.end());
					path_tmp = wstr_tmp.c_str();
					CreateWICTextureFromFile(c_Graphics_Setup->Get_Device().Get(), c_Graphics_Setup->Get_Context().Get(), path_tmp, nullptr, &tObject_List->d3d_SRV[i][k], 0);
					k++;
				}
			}
		}
	}
}

void cRender_Manager::Unload(tScene_Objects* tObject_List)
{
	ZeroMemory(&tObject_List, sizeof(tScene_Objects));
}

void cRender_Manager::Draw(int nScene_Id, tScene_Objects* tObject_List)
{
	for (int _eyeID = 0; _eyeID < 2; _eyeID++)
	{
		// SIGNALS
		cTime.Signal();

		if (_eyeID == 0)
		{
			ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV_Left().Get() };
			c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV().Get());
		}
		else
		{
			ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV_Right().Get() };
			c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV().Get());
		}

		// RESIZE / RESET RTV AND VP
		//c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(0, 0, 0);
		//c_Graphics_Setup->Get_RTV().Release();
		//c_Graphics_Setup->Get_Swap_Chain()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		//ID3D11Texture2D *back_buffer;
		//c_Graphics_Setup->Get_Swap_Chain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
		//c_Graphics_Setup->Get_Device().Get()->CreateRenderTargetView(back_buffer, NULL, &c_Graphics_Setup->Get_RTV());
		//ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV() };
		////c_Graphics_Setup->Get_Context().Get()->OMSetDepthStencilState(c_Graphics_Setup->Get_Depth_Stencil_State(), 1);
		//c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV());
		//c_Graphics_Setup->Get_Context().Get()->RSSetViewports(1, &c_Graphics_Setup->Get_View_Port());
		// SKY BLUE
		float clear_color[4] = { 1.000000000f, 0.000000000f, 0.83137255f, 1.000000000f };
		// WHITE
		//float clear_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		c_Graphics_Setup->Get_Context().Get()->ClearRenderTargetView(c_Graphics_Setup->Get_RTV().Get(), clear_color);
		c_Graphics_Setup->Get_Context().Get()->ClearDepthStencilView(c_Graphics_Setup->Get_DSV().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

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

			// S - move backwards
			if (GetAsyncKeyState('S'))
			{
				change_data = { 0.0f, 0.0f, ((float)cTime.Delta() * 25), 0.0f };
				cCam.Translation(change_data);
			}

			// W - move forward
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
		if (nScene_Id == 2)
		{
			//dragon controls
			if (GetAsyncKeyState('E') && flashTimer == 0.0f)
			{
				isHit = true;
			}
			if (isHit)
			{
				isHit = false;
				flashTimer = flashTime;
				dragonHealth -= 1;
				if (dragonHealth == 6)
				{
					cps_dragon.tint = { 0.0f, 0.0f, 1.0f, 1.0f };
				}
				if (dragonHealth == 5)
				{
					cps_dragon.tint = { 0.0f, 1.0f, 1.0f, 1.0f };
				}
				if (dragonHealth == 4)
				{
					cps_dragon.tint = { 0.0f, 1.0f, 0.0f, 1.0f };
				}
				if (dragonHealth == 3)
				{
					cps_dragon.tint = { 1.0f, 1.0f, 0.0f, 1.0f };
				}
				if (dragonHealth == 2)
				{
					cps_dragon.tint = { 1.0f, 0.5f, 0.0f, 1.0f };
				}
				if (dragonHealth == 1)
				{
					cps_dragon.tint = { 1.0f, 0.0f, 0.0f, 1.0f };
				}

				if (dragonHealth <= 0)
				{
					dragonAlive = false;
				}

			}

			if (flashTimer < 0.0f)
			{
				flashTimer = 0.0f;
				cps_dragon.tint = { 0.0f, 0.0f, 0.0f, 1.0f };
			}
			if (flashTimer > 0.0f)
			{
				flashTimer -= cTime.Delta();
			}

			if (dragonHealth > 3)
			{
				tObject_List->fWorld_Matrix[4].tW.fX += 0.1;
				tObject_List->fWorld_Matrix[4].tW.fY -= 0.1;
			}
			else
			{
				tObject_List->fWorld_Matrix[4].tW.fX += 0.3;
				tObject_List->fWorld_Matrix[4].tW.fY -= 0.3;
			}

			if (tObject_List->fWorld_Matrix[4].tW.fX >= -1)
			{
				sound.playSoundEffect("Fireball+1.mp3", FMOD_DEFAULT);
				tObject_List->fWorld_Matrix[4].tW.fX = -10;
				tObject_List->fWorld_Matrix[4].tW.fY = 10;
			}
		}

		XMStoreFloat4x4(&tWVP.fView_Matrix, XMMatrixIdentity());
		if (_eyeID == 0)
		{
			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Graphics_Setup->GetCurrentViewProjectionMatrix(vr::Eye_Left));
		}
		else
		{
			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Graphics_Setup->GetCurrentViewProjectionMatrix(vr::Eye_Right));
		}

		unsigned int verts_size = sizeof(tVertex);
		unsigned int verts_skinned_size = sizeof(tVertex_Skinned);
		unsigned int off_set = 0;

		for (int i = 0; i < tObject_List->nObject_Count; i++)
		{
			// TO TURN OFF OBJECTS
			if (((i == 3) || (i == 4)) && !dragonAlive)
			{
				continue;
			}
			if (i == 5)
			{
				continue;
			}
			// CONSTANT BUFFER - WVPC
			{
				tWVP.fWorld_Matrix = tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[i]);

				// MAP DATA
				c_Graphics_Setup->Get_Context().Get()->Map(d3d_Constant_Buffer_WVP.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
				memcpy(d3d_MSR.pData, &tWVP, sizeof(tConstantBuffer_VertexShader_WVP));
				c_Graphics_Setup->Get_Context().Get()->Unmap(d3d_Constant_Buffer_WVP.Get(), 0);
				ID3D11Buffer *tmp_wvpc_buffer[] = { d3d_Constant_Buffer_WVP.Get() };
				c_Graphics_Setup->Get_Context().Get()->VSSetConstantBuffers(0, 1, tmp_wvpc_buffer);
			}

			if (tObject_List->bIs_Animated[i])
			{
				for (int j = 0; j < 28; j++)
					tAnim.fAnimation_Data[j] = tFloat4x4_to_XMFLOAT4x4(tObject_List->tAnim_Data[i].tTweened[j]);

				c_Graphics_Setup->Get_Context().Get()->Map(d3d_Constant_Buffer_Animation.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
				memcpy(d3d_MSR.pData, &tAnim, sizeof(tConstantBuffer_VertexShader_Animation));
				c_Graphics_Setup->Get_Context().Get()->Unmap(d3d_Constant_Buffer_Animation.Get(), 0);
				ID3D11Buffer *tmp_anim_buffer[] = { d3d_Constant_Buffer_Animation.Get() };
				c_Graphics_Setup->Get_Context().Get()->VSSetConstantBuffers(1, 1, tmp_anim_buffer);
			}


			ID3D11Buffer *ts_v_buffer[] = { tObject_List->d3d_Vertex_Buffers[i].Get() };
			if (tObject_List->bIs_Animated[i])
				c_Graphics_Setup->Get_Context().Get()->IASetVertexBuffers(0, 1, ts_v_buffer, &verts_skinned_size, &off_set);
			else
				c_Graphics_Setup->Get_Context().Get()->IASetVertexBuffers(0, 1, ts_v_buffer, &verts_size, &off_set);
			c_Graphics_Setup->Get_Context().Get()->IASetIndexBuffer(tObject_List->d3d_Index_Buffers[i].Get(), DXGI_FORMAT_R32_UINT, 0);
			c_Graphics_Setup->Get_Context().Get()->IASetInputLayout(c_Graphics_Setup->Get_Input_Layout().Get());
			if (i != 2)
				c_Graphics_Setup->Get_Context().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			else
			{
				c_Graphics_Setup->Get_Context().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			}
			//if (i != 1)
			//{
			//	c_Graphics_Setup->Get_Context().Get()->VSSetShader(c_Graphics_Setup->Get_Vertex_Shader(), NULL, 0);
			//	c_Graphics_Setup->Get_Context().Get()->PSSetShader(c_Graphics_Setup->Get_Pixel_Shader(), NULL, 0);
			//}
			//else
			//{
			c_Graphics_Setup->Get_Context().Get()->VSSetShader(tObject_List->d3d_Vertex_Shaders[i].Get(), NULL, 0);
			c_Graphics_Setup->Get_Context().Get()->PSSetShader(tObject_List->d3d_Pixel_Shaders[i].Get(), NULL, 0);

			if (nScene_Id < 2 || nScene_Id == 3)
			{
				c_Graphics_Setup->Get_Context().Get()->PSSetShaderResources(0, 1, tObject_List->d3d_SRV[0][0].GetAddressOf());
			}
			else
			{
				if (i == 0)
				{
					c_Graphics_Setup->Get_Context().Get()->PSSetShaderResources(0, 1, tObject_List->d3d_SRV[i][0].GetAddressOf());
					c_Graphics_Setup->Get_Context().Get()->PSSetShaderResources(1, 1, tObject_List->d3d_SRV[i][1].GetAddressOf());
					c_Graphics_Setup->Get_Context().Get()->PSSetShaderResources(2, 1, tObject_List->d3d_SRV[i][2].GetAddressOf());
				}
				else
				{
					c_Graphics_Setup->Get_Context().Get()->PSSetShaderResources(0, 1, tObject_List->d3d_SRV[i][0].GetAddressOf());
				}

				if (i == 0)
				{
					c_Graphics_Setup->Get_Context().Get()->Map(tObject_List->tMaterials_Buffers[i].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
					memcpy(d3d_MSR.pData, &cps_mage, sizeof(tConstantBuffer_PixelShader));
					c_Graphics_Setup->Get_Context().Get()->Unmap(tObject_List->tMaterials_Buffers[i].Get(), 0);
					ID3D11Buffer *tmp_con_buffer[] = { tObject_List->tMaterials_Buffers[i].Get() };
					c_Graphics_Setup->Get_Context().Get()->PSSetConstantBuffers(0, 1, tmp_con_buffer);
				}

				switch (i)
				{
				case 0:
					break;
				case 1:
					memcpy(d3d_MSR.pData, &cps_arena, sizeof(tConstantBuffer_PixelShader));
					break;
				case 3:
					memcpy(d3d_MSR.pData, &cps_dragon, sizeof(tConstantBuffer_PixelShader));
					break;
				case 4:
					memcpy(d3d_MSR.pData, &cps_fireball, sizeof(tConstantBuffer_PixelShader));
					break;
					//case 5:
					//	memcpy(d3d_MSR.pData, &cps_priest, sizeof(tConstantBuffer_PixelShader));
					//	break;
				default:
					break;
				}
				c_Graphics_Setup->Get_Context().Get()->Unmap(tObject_List->tMaterials_Buffers[i].Get(), 0);
				ID3D11Buffer *tmp_con_buffer[] = { tObject_List->tMaterials_Buffers[i].Get() };
				c_Graphics_Setup->Get_Context().Get()->PSSetConstantBuffers(0, 1, tmp_con_buffer);
			}

			if (tObject_List->bIs_Animated[i])
				c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Skinned_Data[i].nIndex_Count, 0, 0);
			else
				c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Data[i].nIndex_Count, 0, 0);
		}
	}

	c_Graphics_Setup->Get_Swap_Chain().Get()->Present(1, 0);
}
