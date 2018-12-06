/************************************************************************
* Filename:  		Render_Manager.cpp
* Date:      		02/10/2018
* Mod. Date: 		04/12/2018
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
	dragonTint.fX = 0.0f;
	dragonTint.fZ = 0.0f;
	dragonTint.fY = 0.0f;
	dragonTint.fW = 1.0f;

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
			{
				c_Graphics_Setup->Get_Device().Get()->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &tObject_List->d3d_Vertex_Shaders[i]);

			}

			//PIXEL SHADERS
			c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(PixelShader_Mage, sizeof(PixelShader_Mage), NULL, &tObject_List->d3d_Pixel_Shaders[i]);
			//c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, &tObject_List->d3d_Pixel_Shaders[i]);

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

			// CONSTANT BUFFER - PIXEL SHADER

			ZeroMemory(&d3d_Constant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
			d3d_Constant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_PixelShader);
			d3d_Constant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
			d3d_Constant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			d3d_Constant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			d3d_Constant_Buffer_Desc.MiscFlags = 0;
			d3d_Constant_Buffer_Desc.StructureByteStride = 0;

			c_Graphics_Setup->Get_Device().Get()->CreateBuffer(&d3d_Constant_Buffer_Desc, nullptr, tObject_List->tMaterials_Buffers[i].GetAddressOf());
		}
	}
}

void cRender_Manager::Unload(tScene_Objects* tObject_List)
{
	ZeroMemory(&tObject_List, sizeof(tScene_Objects));
}

void cRender_Manager::Draw_Personal(tScene_Objects* tObject_List, cHead_Mount c_Head_Mount, cControllers c_Controllers)
{

	float clear_color[4] = { 1.000000000f, 0.000000000f, 0.83137255f, 1.000000000f };

	for (int _eyeID = 0; _eyeID < 3; _eyeID++)
	{
		if (_eyeID == 0)
		{
			ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV_Left().Get() };
			c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV().Get());
			//c_Graphics_Setup->Get_Context().Get()->ClearRenderTargetView(c_Graphics_Setup->Get_RTV_Left().Get(), clear_color);
		}
		else if (_eyeID == 1)
		{
			ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV_Right().Get() };
			c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV().Get());
			//c_Graphics_Setup->Get_Context().Get()->ClearRenderTargetView(c_Graphics_Setup->Get_RTV_Right().Get(), clear_color);
		}
		else// if (_eyeID == 2)
		{
			ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV().Get() };
			c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV().Get());
			//c_Graphics_Setup->Get_Context().Get()->ClearRenderTargetView(c_Graphics_Setup->Get_RTV().Get(), clear_color);
		}

		c_Graphics_Setup->Get_Context().Get()->ClearDepthStencilView(c_Graphics_Setup->Get_DSV().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		XMStoreFloat4x4(&tWVP.fView_Matrix, XMMatrixIdentity());
		if (_eyeID == 0)
			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Head_Mount.GetCurrentViewProjectionMatrix(vr::Eye_Left));
		else
			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Head_Mount.GetCurrentViewProjectionMatrix(vr::Eye_Right));

		unsigned int verts_size = sizeof(tVertex);
		unsigned int verts_skinned_size = sizeof(tVertex_Skinned);
		unsigned int off_set = 0;

		for (int i = 0; i < tObject_List->nObject_Count; i++)
		{
			// CONSTANT BUFFER - WVPC
			{
				if (i == 0)
				{
					tFloat4x4 temp = tObject_List->fWorld_Matrix[i];
					//temp.tW.fX = c_Controllers.Get_Left_Hand().fX;
					//temp.tW.fY = c_Controllers.Get_Left_Hand().fY;
					//temp.tW.fZ = c_Controllers.Get_Left_Hand().fZ;
					temp = c_Controllers.Get_Left_Hand();
					tWVP.fWorld_Matrix = tFloat4x4_to_XMFLOAT4x4(temp);
				}
				else
				{
					tFloat4x4 temp = tObject_List->fWorld_Matrix[i];
					//temp.tW.fX = c_Controllers.Get_Right_Hand().fX;
					//temp.tW.fY = c_Controllers.Get_Right_Hand().fY;
					//temp.tW.fZ = c_Controllers.Get_Right_Hand().fZ;
					temp = c_Controllers.Get_Right_Hand();
					tWVP.fWorld_Matrix = tFloat4x4_to_XMFLOAT4x4(temp);
				}

				// MAP DATA
				c_Graphics_Setup->Get_Context().Get()->Map(d3d_Constant_Buffer_WVP.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
				memcpy(d3d_MSR.pData, &tWVP, sizeof(tConstantBuffer_VertexShader_WVP));
				c_Graphics_Setup->Get_Context().Get()->Unmap(d3d_Constant_Buffer_WVP.Get(), 0);
				ID3D11Buffer *tmp_wvpc_buffer[] = { d3d_Constant_Buffer_WVP.Get() };
				c_Graphics_Setup->Get_Context().Get()->VSSetConstantBuffers(0, 1, tmp_wvpc_buffer);
			}

			if (tObject_List->bIs_Animated[i])
			{
				for (int j = 0; j < 99; j++)
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
			c_Graphics_Setup->Get_Context().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			c_Graphics_Setup->Get_Context().Get()->VSSetShader(tObject_List->d3d_Vertex_Shaders[i].Get(), NULL, 0);
			c_Graphics_Setup->Get_Context().Get()->PSSetShader(tObject_List->d3d_Pixel_Shaders[i].Get(), NULL, 0);
			c_Graphics_Setup->Get_Context().Get()->PSSetShaderResources(0, 1, tObject_List->d3d_SRV[i][0].GetAddressOf());

			tCB_PS.ambient.x = tObject_List->tMaterials_Data[i].tMats[0].tAmbient.fX;
			tCB_PS.ambient.y = tObject_List->tMaterials_Data[i].tMats[0].tAmbient.fY;
			tCB_PS.ambient.z = tObject_List->tMaterials_Data[i].tMats[0].tAmbient.fZ;
			tCB_PS.ambient.w = tObject_List->tMaterials_Data[i].tMats[0].tAmbient.fW;

			tCB_PS.diffuse.x = tObject_List->tMaterials_Data[i].tMats[0].tDiffuse.fX;
			tCB_PS.diffuse.y = tObject_List->tMaterials_Data[i].tMats[0].tDiffuse.fY;
			tCB_PS.diffuse.z = tObject_List->tMaterials_Data[i].tMats[0].tDiffuse.fZ;
			tCB_PS.diffuse.w = tObject_List->tMaterials_Data[i].tMats[0].tDiffuse.fW;

			tCB_PS.emissive.x = tObject_List->tMaterials_Data[i].tMats[0].tEmissive.fX;
			tCB_PS.emissive.y = tObject_List->tMaterials_Data[i].tMats[0].tEmissive.fY;
			tCB_PS.emissive.z = tObject_List->tMaterials_Data[i].tMats[0].tEmissive.fZ;
			tCB_PS.emissive.w = tObject_List->tMaterials_Data[i].tMats[0].tEmissive.fW;

			tCB_PS.reflection.x = tObject_List->tMaterials_Data[i].tMats[0].tReflection.fX;
			tCB_PS.reflection.y = tObject_List->tMaterials_Data[i].tMats[0].tReflection.fY;
			tCB_PS.reflection.z = tObject_List->tMaterials_Data[i].tMats[0].tReflection.fZ;
			tCB_PS.reflection.w = tObject_List->tMaterials_Data[i].tMats[0].tReflection.fW;

			tCB_PS.shininess.x = tObject_List->tMaterials_Data[i].tMats[0].fShininess;

			tCB_PS.specular.x = tObject_List->tMaterials_Data[i].tMats[0].tSpecular.fX;
			tCB_PS.specular.y = tObject_List->tMaterials_Data[i].tMats[0].tSpecular.fY;
			tCB_PS.specular.z = tObject_List->tMaterials_Data[i].tMats[0].tSpecular.fZ;
			tCB_PS.specular.w = tObject_List->tMaterials_Data[i].tMats[0].tSpecular.fW;

			tCB_PS.transparency.x = tObject_List->tMaterials_Data[i].tMats[0].tTransparency.fX;
			tCB_PS.transparency.y = tObject_List->tMaterials_Data[i].tMats[0].tTransparency.fY;
			tCB_PS.transparency.z = tObject_List->tMaterials_Data[i].tMats[0].tTransparency.fZ;
			tCB_PS.transparency.w = tObject_List->tMaterials_Data[i].tMats[0].tTransparency.fW;

			tCB_PS.tint.x = 0.0f;
			tCB_PS.tint.y = 0.0f;
			tCB_PS.tint.z = 0.0f;
			tCB_PS.tint.w = 1.0f;

			c_Graphics_Setup->Get_Context().Get()->Map(tObject_List->tMaterials_Buffers[i].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
			memcpy(d3d_MSR.pData, &tCB_PS, sizeof(tConstantBuffer_PixelShader));
			c_Graphics_Setup->Get_Context().Get()->Unmap(tObject_List->tMaterials_Buffers[i].Get(), 0);
			ID3D11Buffer *tmp_con_buffer[] = { tObject_List->tMaterials_Buffers[i].Get() };
			c_Graphics_Setup->Get_Context().Get()->PSSetConstantBuffers(0, 1, tmp_con_buffer);

			if (tObject_List->bIs_Animated[i])
				c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Skinned_Data[i].nIndex_Count, 0, 0);
			else
				c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Data[i].nIndex_Count, 0, 0);

		}
	}

	//c_Graphics_Setup->Get_Swap_Chain().Get()->Present(1, 0);
}


void cRender_Manager::Draw_World(int nScene_Id, tScene_Objects* tObject_List, bool *bChange_Scene, bool *bMove_Bullet, cHead_Mount c_Head_Mount)
{
	if (nScene_Id == 2)
	{
		//if (tObject_List->dragAlive == false)
		//{
		//	dragonAlive = false;
		//	*bChange_Scene = true;
		//}
		//dragon controls
		if (GetAsyncKeyState('E') && flashTimer == 0.0f)
		{
			isHit = true;
		}
		if (isHit)
		{
			isHit = false;
			flashTimer = flashTime;
			sound.playSoundEffect("DragonSound1.mp3", FMOD_DEFAULT);
			tObject_List->dragHP -= 1;
			if (tObject_List->dragHP == 3)
			{
				dragonTint = { 0.0f, 0.0f, 1.0f, 1.0f };
			}
			if (tObject_List->dragHP == 2)
			{
				dragonTint = { 1.0f, 1.0f, 0.0f, 1.0f };
			}
			if (tObject_List->dragHP == 1)
			{
				dragonTint = { 1.0f, 0.0f, 0.0f, 1.0f };
			}

			if (tObject_List->dragHP <= 0)
			{
				*bChange_Scene = true;
			}

		}

		if (flashTimer < 0.0f)
		{
			flashTimer = 0.0f;
			dragonTint = { 0.0f, 0.0f, 0.0f, 1.0f };
		}
		if (flashTimer > 0.0f)
		{
			flashTimer -= cTime.Delta();
		}

		if (tObject_List->fWorld_Matrix[3].tW.fX >= -1)
		{
			if (tObject_List->dragHP != 0)
			{
				sound.playSoundEffect("Fireball+1.mp3", FMOD_DEFAULT);
			}
			//tObject_List->fWorld_Matrix[3].tW.fX = tObject_List->fWorld_Matrix[2].tW.fX + 4;
			//tObject_List->fWorld_Matrix[3].tW.fY = tObject_List->fWorld_Matrix[2].tW.fY;
			//tObject_List->fWorld_Matrix[3].tW.fZ = tObject_List->fWorld_Matrix[2].tW.fZ;
			//tObject_List->fWorld_Matrix[3].tW.fY += 4;
			//tObject_List->fWorld_Matrix[3].tW.fX = -8;
			//tObject_List->fWorld_Matrix[3].tW.fY = 8;
		}

		// Bullet
		if (*bMove_Bullet == true)
		{
			tObject_List->fWorld_Matrix[4].tW.fX -= 0.1;
			tObject_List->fWorld_Matrix[4].tW.fY += 0.1;
		}

		// Collision
		{
			tAABB_Bullet.center.fX = tObject_List->fWorld_Matrix[4].tW.fX;
			tAABB_Bullet.center.fY = tObject_List->fWorld_Matrix[4].tW.fY;
			tAABB_Bullet.center.fZ = tObject_List->fWorld_Matrix[4].tW.fZ;

			tAABB_Bullet.extents.fX = 0.2f;
			tAABB_Bullet.extents.fY = 0.13f;
			tAABB_Bullet.extents.fZ = 0.2f;

			tAABB_Dragon.center.fX = tObject_List->fWorld_Matrix[2].tW.fX;
			tAABB_Dragon.center.fY = tObject_List->fWorld_Matrix[2].tW.fY;
			tAABB_Dragon.center.fZ = tObject_List->fWorld_Matrix[2].tW.fZ;

			tAABB_Dragon.extents.fX = 17.0f;
			tAABB_Dragon.extents.fY = 9.0f;
			tAABB_Dragon.extents.fZ = 17.0f;

			bCollided = t_Collisions.Detect_AABB_To_AABB(tAABB_Bullet, tAABB_Dragon);

			if (bCollided)
			{
				tObject_List->fWorld_Matrix[4].tW.fX = -0.1;
				tObject_List->fWorld_Matrix[4].tW.fY = 0.1;
				tObject_List->fWorld_Matrix[4].tW.fX = -0.1;
				*bMove_Bullet = false;
				isHit = true;
			}
		}

	}

	// SIGNALS
	cTime.Signal();
	float clear_color[4] = { 0.000000000f, 1.000000000f, 0.48235f, 1.000000000f };

	for (int _eyeID = 0; _eyeID < 3; _eyeID++)
	{
		if (_eyeID == 0)
		{
			ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV_Left().Get() };
			c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV().Get());
			c_Graphics_Setup->Get_Context().Get()->ClearRenderTargetView(c_Graphics_Setup->Get_RTV_Left().Get(), clear_color);
		}
		else if (_eyeID == 1)
		{
			ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV_Right().Get() };
			c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV().Get());
			c_Graphics_Setup->Get_Context().Get()->ClearRenderTargetView(c_Graphics_Setup->Get_RTV_Right().Get(), clear_color);
		}
		else if (_eyeID == 2)
		{
			ID3D11RenderTargetView *tmp_rtv[] = { c_Graphics_Setup->Get_RTV().Get() };
			c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(1, tmp_rtv, c_Graphics_Setup->Get_DSV().Get());
			c_Graphics_Setup->Get_Context().Get()->ClearRenderTargetView(c_Graphics_Setup->Get_RTV().Get(), clear_color);
		}


		XMStoreFloat4x4(&tWVP.fView_Matrix, XMMatrixIdentity());
		if (_eyeID == 0)
			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Head_Mount.GetCurrentViewProjectionMatrix(vr::Eye_Left));
		else
			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Head_Mount.GetCurrentViewProjectionMatrix(vr::Eye_Right));


		unsigned int verts_size = sizeof(tVertex);
		unsigned int verts_skinned_size = sizeof(tVertex_Skinned);
		unsigned int off_set = 0;

		for (int i = 0; i < tObject_List->nObject_Count; i++)
		{

			//Kill Dragon on zero health
			if (((i == 2) || (i == 3)) && tObject_List->dragHP == 0)
			{
				continue;
			}

			// TO TURN OFF OBJECTS
			if (i == 4)
			{
				continue;
			}

			// CONSTANT BUFFER - WVPC
			{
				//if (i == 7)
				//{
				//	tFloat4x4 temp = tObject_List->fWorld_Matrix[i];
				//	temp.tW.fX += lhand.fX;
				//	temp.tW.fY += lhand.fY;
				//	temp.tW.fZ += lhand.fZ;
				//	tWVP.fWorld_Matrix = tFloat4x4_to_XMFLOAT4x4(temp);
				//}
				//else
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
			c_Graphics_Setup->Get_Context().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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

				tCB_PS.ambient.x = tObject_List->tMaterials_Data[i].tMats[0].tAmbient.fX;
				tCB_PS.ambient.y = tObject_List->tMaterials_Data[i].tMats[0].tAmbient.fY;
				tCB_PS.ambient.z = tObject_List->tMaterials_Data[i].tMats[0].tAmbient.fZ;
				tCB_PS.ambient.w = tObject_List->tMaterials_Data[i].tMats[0].tAmbient.fW;

				tCB_PS.diffuse.x = tObject_List->tMaterials_Data[i].tMats[0].tDiffuse.fX;
				tCB_PS.diffuse.y = tObject_List->tMaterials_Data[i].tMats[0].tDiffuse.fY;
				tCB_PS.diffuse.z = tObject_List->tMaterials_Data[i].tMats[0].tDiffuse.fZ;
				tCB_PS.diffuse.w = tObject_List->tMaterials_Data[i].tMats[0].tDiffuse.fW;

				tCB_PS.emissive.x = tObject_List->tMaterials_Data[i].tMats[0].tEmissive.fX;
				tCB_PS.emissive.y = tObject_List->tMaterials_Data[i].tMats[0].tEmissive.fY;
				tCB_PS.emissive.z = tObject_List->tMaterials_Data[i].tMats[0].tEmissive.fZ;
				tCB_PS.emissive.w = tObject_List->tMaterials_Data[i].tMats[0].tEmissive.fW;

				tCB_PS.reflection.x = tObject_List->tMaterials_Data[i].tMats[0].tReflection.fX;
				tCB_PS.reflection.y = tObject_List->tMaterials_Data[i].tMats[0].tReflection.fY;
				tCB_PS.reflection.z = tObject_List->tMaterials_Data[i].tMats[0].tReflection.fZ;
				tCB_PS.reflection.w = tObject_List->tMaterials_Data[i].tMats[0].tReflection.fW;

				tCB_PS.shininess.x = tObject_List->tMaterials_Data[i].tMats[0].fShininess;

				tCB_PS.specular.x = tObject_List->tMaterials_Data[i].tMats[0].tSpecular.fX;
				tCB_PS.specular.y = tObject_List->tMaterials_Data[i].tMats[0].tSpecular.fY;
				tCB_PS.specular.z = tObject_List->tMaterials_Data[i].tMats[0].tSpecular.fZ;
				tCB_PS.specular.w = tObject_List->tMaterials_Data[i].tMats[0].tSpecular.fW;

				tCB_PS.transparency.x = tObject_List->tMaterials_Data[i].tMats[0].tTransparency.fX;
				tCB_PS.transparency.y = tObject_List->tMaterials_Data[i].tMats[0].tTransparency.fY;
				tCB_PS.transparency.z = tObject_List->tMaterials_Data[i].tMats[0].tTransparency.fZ;
				tCB_PS.transparency.w = tObject_List->tMaterials_Data[i].tMats[0].tTransparency.fW;

				tCB_PS.tint.x = 0.0f;
				tCB_PS.tint.y = 0.0f;
				tCB_PS.tint.z = 0.0f;
				tCB_PS.tint.w = 1.0f;

				if (i == 2)
					tCB_PS.tint = tFloat4_to_XMFLOAT4(dragonTint);

				if (i == 4)
					tCB_PS.tint.z = 1.0f;

				c_Graphics_Setup->Get_Context().Get()->Map(tObject_List->tMaterials_Buffers[i].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
				memcpy(d3d_MSR.pData, &tCB_PS, sizeof(tConstantBuffer_PixelShader));
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

	//c_Graphics_Setup->Get_Swap_Chain().Get()->Present(1, 0);
}
