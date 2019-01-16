/************************************************************************
* Filename:  		Render_Manager.cpp
* Date:      		02/10/2018
* Mod. Date: 		12/12/2018
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
	//tVertex line_vert_array[line_vert_count];
	line_vert = new particle[50];    // The array that is meant to hold the particles to draw
									 // tVertex
	quad_indexes[0] = 0;
	quad_indexes[1] = 2;
	quad_indexes[2] = 3;
	quad_indexes[3] = 0;
	quad_indexes[4] = 1;
	quad_indexes[5] = 2;

	quad_indexes[6] = 4;
	quad_indexes[7] = 7;
	quad_indexes[8] = 6;
	quad_indexes[9] = 4;
	quad_indexes[10] = 5;
	quad_indexes[11] = 7;

	quad_indexes[12] = 8;
	quad_indexes[13] = 11;
	quad_indexes[14] = 10;
	quad_indexes[15] = 8;
	quad_indexes[16] = 9;
	quad_indexes[17] = 11;

	quad_indexes[18] = 12;
	quad_indexes[19] = 15;
	quad_indexes[20] = 14;
	quad_indexes[21] = 12;
	quad_indexes[22] = 13;
	quad_indexes[23] = 15;

	quad_indexes[24] = 16;
	quad_indexes[25] = 19;
	quad_indexes[26] = 18;
	quad_indexes[27] = 16;
	quad_indexes[28] = 17;
	quad_indexes[29] = 19;

	quad_indexes[30] = 20;
	quad_indexes[31] = 23;
	quad_indexes[32] = 22;
	quad_indexes[33] = 20;
	quad_indexes[34] = 21;
	quad_indexes[35] = 23;

	quad_indexes[36] = 24;
	quad_indexes[37] = 27;
	quad_indexes[38] = 26;
	quad_indexes[39] = 24;
	quad_indexes[40] = 25;
	quad_indexes[41] = 27;

	quad_indexes[42] = 28;
	quad_indexes[43] = 31;
	quad_indexes[44] = 30;
	quad_indexes[45] = 28;
	quad_indexes[46] = 29;
	quad_indexes[47] = 31;

	quad_indexes[48] = 32;
	quad_indexes[49] = 35;
	quad_indexes[50] = 34;
	quad_indexes[51] = 32;
	quad_indexes[52] = 33;
	quad_indexes[53] = 35;

	quad_indexes[54] = 36;
	quad_indexes[55] = 39;
	quad_indexes[56] = 38;
	quad_indexes[57] = 36;
	quad_indexes[58] = 37;
	quad_indexes[59] = 39;

	quad_indexes[60] = 40;
	quad_indexes[61] = 43;
	quad_indexes[62] = 42;
	quad_indexes[63] = 40;
	quad_indexes[64] = 41;
	quad_indexes[65] = 43;

	quad_indexes[66] = 44;
	quad_indexes[67] = 47;
	quad_indexes[68] = 46;
	quad_indexes[69] = 44;
	quad_indexes[70] = 45;
	quad_indexes[71] = 47;

	quad_indexes[72] = 48;
	quad_indexes[73] = 51;
	quad_indexes[74] = 50;
	quad_indexes[75] = 48;
	quad_indexes[76] = 49;
	quad_indexes[77] = 51;

	quad_indexes[78] = 52;
	quad_indexes[79] = 55;
	quad_indexes[80] = 54;
	quad_indexes[81] = 52;
	quad_indexes[82] = 53;
	quad_indexes[83] = 55;

	quad_indexes[84] = 56;
	quad_indexes[85] = 59;
	quad_indexes[86] = 58;
	quad_indexes[87] = 56;
	quad_indexes[88] = 57;
	quad_indexes[89] = 59;

	quad_indexes[90] = 60;
	quad_indexes[91] = 63;
	quad_indexes[92] = 62;
	quad_indexes[93] = 60;
	quad_indexes[94] = 61;
	quad_indexes[95] = 63;

	quad_indexes[96] = 64;
	quad_indexes[97] = 67;
	quad_indexes[98] = 66;
	quad_indexes[99] = 64;
	quad_indexes[100] = 65;
	quad_indexes[101] = 67;

	quad_indexes[102] = 68;
	quad_indexes[103] = 71;
	quad_indexes[104] = 70;
	quad_indexes[105] = 68;
	quad_indexes[106] = 69;
	quad_indexes[107] = 71;

	quad_indexes[108] = 72;
	quad_indexes[109] = 75;
	quad_indexes[110] = 74;
	quad_indexes[111] = 72;
	quad_indexes[112] = 73;
	quad_indexes[113] = 75;

	quad_indexes[114] = 76;
	quad_indexes[115] = 79;
	quad_indexes[116] = 78;
	quad_indexes[117] = 76;
	quad_indexes[118] = 77;
	quad_indexes[119] = 79;

	quad_indexes[120] = 80;
	quad_indexes[121] = 83;
	quad_indexes[122] = 82;
	quad_indexes[123] = 80;
	quad_indexes[124] = 81;
	quad_indexes[125] = 83;

	quad_indexes[126] = 84;
	quad_indexes[127] = 87;
	quad_indexes[128] = 86;
	quad_indexes[129] = 84;
	quad_indexes[130] = 85;
	quad_indexes[131] = 87;

	quad_indexes[132] = 88;
	quad_indexes[133] = 91;
	quad_indexes[134] = 90;
	quad_indexes[135] = 88;
	quad_indexes[136] = 89;
	quad_indexes[137] = 91;

	quad_indexes[138] = 92;
	quad_indexes[139] = 95;
	quad_indexes[140] = 94;
	quad_indexes[141] = 92;
	quad_indexes[142] = 93;
	quad_indexes[143] = 95;

	quad_indexes[144] = 96;
	quad_indexes[145] = 99;
	quad_indexes[146] = 98;
	quad_indexes[147] = 96;
	quad_indexes[148] = 97;
	quad_indexes[149] = 99;

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

	// CONSTANT BUFFER - Particles
	ZeroMemory(&particle_Const_Buff_Desc, sizeof(D3D11_BUFFER_DESC));
	particle_Const_Buff_Desc.ByteWidth = sizeof(tConstantBuffer_VertexShader_Bullet);
	particle_Const_Buff_Desc.Usage = D3D11_USAGE_DYNAMIC;
	particle_Const_Buff_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	particle_Const_Buff_Desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	particle_Const_Buff_Desc.MiscFlags = 0;
	particle_Const_Buff_Desc.StructureByteStride = 0;

	ZeroMemory(&particle_Const_Buff_Data, sizeof(D3D11_SUBRESOURCE_DATA));
	particle_Const_Buff_Data.SysMemSlicePitch = 0;
	particle_Const_Buff_Data.SysMemPitch = 0;
	particle_Const_Buff_Data.pSysMem = &tPart;

	c_Graphics_Setup->Get_Device().Get()->CreateBuffer(&particle_Const_Buff_Desc, &particle_Const_Buff_Data, particle_Constant_Buffer.GetAddressOf());
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

void cRender_Manager::Draw_Personal(tScene_Objects* tObject_List, cHead_Mount c_Head_Mount, cControllers c_Controllers, tFloat4x4 offset, cBase_Spell c_Player_Fireball)
{
	float clear_color[4] = { 0.000000000f, 1.000000000f, 0.48235f, 1.000000000f };
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
			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Head_Mount.GetCurrentViewProjectionMatrix(vr::Eye_Left, tFloat4x4_To_Matrix4(offset)));
		else
			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Head_Mount.GetCurrentViewProjectionMatrix(vr::Eye_Right, tFloat4x4_To_Matrix4(offset)));

		unsigned int verts_size = sizeof(tVertex);
		unsigned int verts_skinned_size = sizeof(tVertex_Skinned);
		unsigned int off_set = 0;

		for (int i = 0; i < tObject_List->nObject_Count; i++)
		{
			// CONSTANT BUFFER - WVPC
			{
				if (i == 0)
				{
					tFloat4x4 temp = c_Controllers.Get_Left_Hand();
					tWVP.fWorld_Matrix = tFloat4x4_to_XMFLOAT4x4(temp);
				}
				else if (i == 1)
				{
					tFloat4x4 temp = c_Controllers.Get_Right_Hand();
					tWVP.fWorld_Matrix = tFloat4x4_to_XMFLOAT4x4(temp);
				}
				else
				{
					tFloat4x4 temp = tObject_List->fWorld_Matrix[i];
					temp.tW.fX = c_Player_Fireball.getPosition4().fX;
					temp.tW.fY = c_Player_Fireball.getPosition4().fY;
					temp.tW.fZ = c_Player_Fireball.getPosition4().fZ + 1;
					temp.tZ.fX = c_Player_Fireball.getHeading().fX;
					temp.tZ.fY = c_Player_Fireball.getHeading().fY;
					temp.tZ.fZ = c_Player_Fireball.getHeading().fZ;
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

			//if (i != 2)
			//{
				if (tObject_List->bIs_Animated[i])
					c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Skinned_Data[i].nIndex_Count, 0, 0);
				else
					c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Data[i].nIndex_Count, 0, 0);
			//}
			//else
			//{
			//	if (c_Player_Fireball.getIsActive())
			//	{
			//		if (tObject_List->bIs_Animated[i])
			//			c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Skinned_Data[i].nIndex_Count, 0, 0);
			//		else
			//			c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Data[i].nIndex_Count, 0, 0);
			//	}
			//}
		}
	}

	//c_Graphics_Setup->Get_Swap_Chain().Get()->Present(1, 0);
}


void cRender_Manager::Draw_World(int nScene_Id, tScene_Objects* tObject_List, bool *bChange_Scene, bool *bMove_Bullet, cHead_Mount c_Head_Mount, tFloat4x4 offset, double totalTime, cBase_Spell c_Player_Fireball, AI* _AI, bool dragon_hit, double timeDelta)
{
	keyboardInputs(tObject_List);

	//if (GetAsyncKeyState('E') && flashTimer == 0.0f)
	//{
	//	isHit = true;
	//}
	if (_AI->getIsHit())
	{
		flashTimer = flashTime;
		sound.playSoundEffect("DragonSound1.mp3", FMOD_DEFAULT, 0.45f);

		//tObject_List->dragHP -= 1;
		if (_AI->getHP() == 3)
		{
			dragonTint = { 0.0f, 0.0f, 1.0f, 1.0f };
		}
		if (_AI->getHP() == 2)
		{
			dragonTint = { 1.0f, 1.0f, 0.0f, 1.0f };
		}
		if (_AI->getHP() == 1)
		{
			dragonTint = { 1.0f, 0.0f, 0.0f, 1.0f };
		}

		if (_AI->getHP() <= 0)
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

	if (tObject_List->fWorld_Matrix[3].tW.fY < -5)
	{
		if (_AI->getHP() != 0)
		{
			sound.playSoundEffect("Fireball+1.mp3", FMOD_DEFAULT, 0.5f);
		}
	}

	// Bullet
	/*if (*bMove_Bullet == true)
	{
		tObject_List->fWorld_Matrix[4].tW.fX -= 0.1;
		tObject_List->fWorld_Matrix[4].tW.fY += 0.1;
	}*/

	//// Collision
	//{
	//	tAABB_Bullet.center.fX = tObject_List->fWorld_Matrix[4].tW.fX;
	//	tAABB_Bullet.center.fY = tObject_List->fWorld_Matrix[4].tW.fY;
	//	tAABB_Bullet.center.fZ = tObject_List->fWorld_Matrix[4].tW.fZ;
	//
	//	tAABB_Bullet.extents.fX = 0.2f;
	//	tAABB_Bullet.extents.fY = 0.13f;
	//	tAABB_Bullet.extents.fZ = 0.2f;
	//
	//	tAABB_Dragon.center.fX = tObject_List->fWorld_Matrix[2].tW.fX;
	//	tAABB_Dragon.center.fY = tObject_List->fWorld_Matrix[2].tW.fY;
	//	tAABB_Dragon.center.fZ = tObject_List->fWorld_Matrix[2].tW.fZ;
	//
	//	tAABB_Dragon.extents.fX = 17.0f;
	//	tAABB_Dragon.extents.fY = 9.0f;
	//	tAABB_Dragon.extents.fZ = 17.0f;
	//
	//	bCollided = t_Collisions.Detect_AABB_To_AABB(tAABB_Bullet, tAABB_Dragon);
	//
	//	if (bCollided)
	//	{
	//		tObject_List->fWorld_Matrix[4].tW.fX = -0.1;
	//		tObject_List->fWorld_Matrix[4].tW.fY = 0.1;
	//		tObject_List->fWorld_Matrix[4].tW.fX = -0.1;
	//		*bMove_Bullet = false;
	//		isHit = true;
	//	}
	//}
	// SIGNALS
	cTime.Signal();
	float clear_color[4] = { 0.2078f, 0.2078f, 0.2078f, 1.0f };  //{ 0.000000000f, 1.000000000f, 0.48235f, 1.000000000f };

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

		c_Graphics_Setup->Get_Context().Get()->ClearDepthStencilView(c_Graphics_Setup->Get_DSV().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		XMStoreFloat4x4(&tWVP.fView_Matrix, XMMatrixIdentity());
		if (_eyeID == 0)
			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Head_Mount.GetCurrentViewProjectionMatrix(vr::Eye_Left, tFloat4x4_To_Matrix4(offset)));
		else
			tWVP.fProjection_Matrix = tFloat4x4_to_XMFLOAT4x4(c_Head_Mount.GetCurrentViewProjectionMatrix(vr::Eye_Right, tFloat4x4_To_Matrix4(offset)));


		unsigned int verts_size = sizeof(tVertex);
		unsigned int verts_skinned_size = sizeof(tVertex_Skinned);
		unsigned int off_set = 0;

		for (int i = 0; i < tObject_List->nObject_Count; i++)
		{
			// TO TURN OFF OBJECTS
			if ((i == 3) && _AI->aggro == false)
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

			if (i != 4)
			{
				if (tObject_List->bIs_Animated[i])
					c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Skinned_Data[i].nIndex_Count, 0, 0);
				else
					c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Data[i].nIndex_Count, 0, 0);
			}
			else
			{
				if (c_Player_Fireball.getIsActive())
				{
					if (tObject_List->bIs_Animated[i])
						c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Skinned_Data[i].nIndex_Count, 0, 0);
					else
						c_Graphics_Setup->Get_Context().Get()->DrawIndexed(tObject_List->tMesh_Data[i].nIndex_Count, 0, 0);
				}
			}
		}

		// sixeof(particle) * 300
		static std::array<tVertex, 100> preAlloc_particle;  // send this to the processor

															// PARTICLES
		if (nScene_Id == 2 && line_vert != nullptr)
		{
			//tObject_List->fWorld_Matrix->tW.fX
			//preAlloc_particle[];
			//for (int k = 0, l = 0; k < 100; k += 2, l++) // if there is no break point in the getter and setter this array break on a random index
			//{
			//	random_color = 53 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (203 - 53)));
			//	random_alpha = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			//	preAlloc_particle[k].fPosition.fX = line_vert[l].prev_Position.fX;    // line_vert = null
			//	preAlloc_particle[k].fPosition.fY = line_vert[l].prev_Position.fY;
			//	preAlloc_particle[k].fPosition.fZ = line_vert[l].prev_Position.fZ;
			//	preAlloc_particle[k].fPosition.fW = 1.0f;

			//	preAlloc_particle[k + 1].fPosition.fX = line_vert[l].position.fX;
			//	preAlloc_particle[k + 1].fPosition.fY = line_vert[l].position.fY;
			//	preAlloc_particle[k + 1].fPosition.fZ = line_vert[l].position.fZ;
			//	preAlloc_particle[k + 1].fPosition.fW = 1.0f;

			//	preAlloc_particle[k].fColor.fX = line_vert[l].color.fX;   // 0.2078f  // line_vert[l].color.fX;
			//	preAlloc_particle[k].fColor.fY = line_vert[l].color.fY;   // 0.2078f   * timer +/ - 5
			//	preAlloc_particle[k].fColor.fZ = line_vert[l].color.fZ;   // 0.2078f
			//	preAlloc_particle[k].fColor.fW = line_vert[l].color.fW;      // 1.0f

			//	preAlloc_particle[k + 1].fColor.fX = line_vert[l].color.fX;   // 0.2078f
			//	preAlloc_particle[k + 1].fColor.fY = line_vert[l].color.fY;   // 0.2078f
			//	preAlloc_particle[k + 1].fColor.fZ = line_vert[l].color.fZ;   // 0.2078f
			//	preAlloc_particle[k + 1].fColor.fW = line_vert[l].color.fW;      // 1.0f

			//	

			//	line_vert_count = preAlloc_particle.size();
			//}

			for (int k = 0, l = 0; k < 100; k += 4, l++) // if there is no break point in the getter and setter this array break on a random index
			{
				random_color = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5 - 1)));
				random_alpha = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

				preAlloc_particle[k].fPosition.fX = line_vert[l].prev_Position.fX;    // line_vert = null
				preAlloc_particle[k].fPosition.fY = line_vert[l].prev_Position.fY;
				preAlloc_particle[k].fPosition.fZ = line_vert[l].prev_Position.fZ;
				preAlloc_particle[k].fPosition.fW = 1.0f;

				preAlloc_particle[k + 1].fPosition.fX = line_vert[l].position.fX;
				preAlloc_particle[k + 1].fPosition.fY = line_vert[l].position.fY;
				preAlloc_particle[k + 1].fPosition.fZ = line_vert[l].position.fZ;
				preAlloc_particle[k + 1].fPosition.fW = 1.0f;

				preAlloc_particle[k].fColor.fX = line_vert[l].color.fX;   // 0.2078f  // line_vert[l].color.fX;
				preAlloc_particle[k].fColor.fY = line_vert[l].color.fY;   // 0.2078f   * timer +/ - 5
				preAlloc_particle[k].fColor.fZ = line_vert[l].color.fZ;   // 0.2078f
				preAlloc_particle[k].fColor.fW = 0.3f;      // 1.0f

				preAlloc_particle[k + 1].fColor.fX = line_vert[l].color.fX;   // 0.2078f
				preAlloc_particle[k + 1].fColor.fY = line_vert[l].color.fY;   // 0.2078f
				preAlloc_particle[k + 1].fColor.fZ = line_vert[l].color.fZ;   // 0.2078f
				preAlloc_particle[k + 1].fColor.fW = 0.3f;      // 1.0f

				// Extra vertices to make quad

				preAlloc_particle[k + 2].fPosition.fX = line_vert[l].prev_Position.fX + random_color;
				preAlloc_particle[k + 2].fPosition.fY = line_vert[l].prev_Position.fY + random_color;
				preAlloc_particle[k + 2].fPosition.fZ = line_vert[l].prev_Position.fZ + random_color;
				preAlloc_particle[k + 2].fPosition.fW = 1.0f;

				preAlloc_particle[k + 3].fPosition.fX = line_vert[l].position.fX + random_color;
				preAlloc_particle[k + 3].fPosition.fY = line_vert[l].position.fY + random_color;
				preAlloc_particle[k + 3].fPosition.fZ = line_vert[l].position.fZ + random_color;
				preAlloc_particle[k + 3].fPosition.fW = 1.0f;

				preAlloc_particle[k + 2].fColor.fX = line_vert[l].color.fX;
				preAlloc_particle[k + 2].fColor.fY = line_vert[l].color.fY;
				preAlloc_particle[k + 2].fColor.fZ = line_vert[l].color.fZ;
				preAlloc_particle[k + 2].fColor.fW = 0.3f;

				preAlloc_particle[k + 3].fColor.fX = line_vert[l].color.fX;
				preAlloc_particle[k + 3].fColor.fY = line_vert[l].color.fY;
				preAlloc_particle[k + 3].fColor.fZ = line_vert[l].color.fZ;
				preAlloc_particle[k + 3].fColor.fW = 0.3f;

				// Extra vertices to make quad

				// UV's

				preAlloc_particle[k].fTexture_Coordinate.fX = 0;
				preAlloc_particle[k].fTexture_Coordinate.fY = 0;

				preAlloc_particle[k + 1].fTexture_Coordinate.fX = 1;
				preAlloc_particle[k + 1].fTexture_Coordinate.fY = 0;

				preAlloc_particle[k + 2].fTexture_Coordinate.fX = 0;
				preAlloc_particle[k + 2].fTexture_Coordinate.fY = 1;

				preAlloc_particle[k + 3].fTexture_Coordinate.fX = 1;
				preAlloc_particle[k + 3].fTexture_Coordinate.fY = 1;

				// UV's

				line_vert_count = preAlloc_particle.size();
			}

			D3D11_BLEND_DESC particle_Blend_DESC;
			ZeroMemory(&particle_Blend_DESC, sizeof(D3D11_BLEND_DESC));
			particle_Blend_DESC.RenderTarget[0].BlendEnable = TRUE;
			particle_Blend_DESC.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			particle_Blend_DESC.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			particle_Blend_DESC.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			particle_Blend_DESC.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			particle_Blend_DESC.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			particle_Blend_DESC.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			particle_Blend_DESC.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			particle_Blend_DESC.AlphaToCoverageEnable = 0;
			particle_Blend_DESC.IndependentBlendEnable = 0;

			c_Graphics_Setup->Get_Device().Get()->CreateBlendState(&particle_Blend_DESC, particle_Blend_State.GetAddressOf());

			D3D11_SAMPLER_DESC particle_Sample_State_DESC;
			ZeroMemory(&particle_Sample_State_DESC, sizeof(D3D11_SAMPLER_DESC));
			particle_Sample_State_DESC.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
			particle_Sample_State_DESC.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
			particle_Sample_State_DESC.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
			particle_Sample_State_DESC.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			particle_Sample_State_DESC.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			particle_Sample_State_DESC.MaxAnisotropy = 1.0f;
			particle_Sample_State_DESC.MaxLOD = D3D11_FLOAT32_MAX;
			particle_Sample_State_DESC.MinLOD = 0.0f;
			particle_Sample_State_DESC.MipLODBias = 0.0f;

			HRESULT tex = CreateDDSTextureFromFile(c_Graphics_Setup->Get_Device().Get(), L"smoke_texture.dds", nullptr, particle_Shader_Resource_View.GetAddressOf());
			c_Graphics_Setup->Get_Device().Get()->CreateSamplerState(&particle_Sample_State_DESC, particle_Sample_State.GetAddressOf());


			D3D11_BUFFER_DESC particle_Vertex_Buffer_DESC;
			ZeroMemory(&particle_Vertex_Buffer_DESC, sizeof(D3D11_BUFFER_DESC));
			particle_Vertex_Buffer_DESC.CPUAccessFlags = NULL;
			particle_Vertex_Buffer_DESC.Usage = D3D11_USAGE_IMMUTABLE;
			particle_Vertex_Buffer_DESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			particle_Vertex_Buffer_DESC.MiscFlags = 0.0f;
			particle_Vertex_Buffer_DESC.ByteWidth = sizeof(tVertex) * 100;
			particle_Vertex_Buffer_DESC.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA particle_Vertex_Buffer_DATA;
			ZeroMemory(&particle_Vertex_Buffer_DATA, sizeof(D3D11_SUBRESOURCE_DATA));
			particle_Vertex_Buffer_DATA.pSysMem = &preAlloc_particle;
			particle_Vertex_Buffer_DATA.SysMemPitch = 0;
			particle_Vertex_Buffer_DATA.SysMemSlicePitch = 0;

			D3D11_BUFFER_DESC particle_Index_Buffer_DESC;
			ZeroMemory(&particle_Index_Buffer_DESC, sizeof(D3D11_BUFFER_DESC));
			particle_Index_Buffer_DESC.CPUAccessFlags = 0;
			particle_Index_Buffer_DESC.Usage = D3D11_USAGE_DEFAULT;
			particle_Index_Buffer_DESC.BindFlags = D3D11_BIND_INDEX_BUFFER;
			particle_Index_Buffer_DESC.ByteWidth = sizeof(UINT) * 150;
			particle_Index_Buffer_DESC.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA particle_Index_Buffer_DATA;
			ZeroMemory(&particle_Index_Buffer_DATA, sizeof(D3D11_SUBRESOURCE_DATA));
			particle_Index_Buffer_DATA.pSysMem = &quad_indexes[0];
			particle_Index_Buffer_DATA.SysMemPitch = 0;
			particle_Index_Buffer_DATA.SysMemSlicePitch = 0;

			c_Graphics_Setup->Get_Device()->CreateBuffer(&particle_Vertex_Buffer_DESC, &particle_Vertex_Buffer_DATA, particle_Vertex_Buffer.GetAddressOf());
			c_Graphics_Setup->Get_Device()->CreateBuffer(&particle_Index_Buffer_DESC, &particle_Index_Buffer_DATA, particle_Index_Buffer.GetAddressOf());

			//D3D11_MAPPED_SUBRESOURCE mapped_Particle_Buffer;
			//c_Graphics_Setup->Get_Context().Get()->Map(particle_Vertex_Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
			//memcpy(mapped_Particle_Buffer.pData, preAlloc_particle.data(), sizeof(tVertex) * 888);
			//c_Graphics_Setup->Get_Context().Get()->Unmap(particle_Vertex_Buffer.Get(), 0);

			c_Graphics_Setup->Get_Device().Get()->CreateVertexShader(Particle_Vertex_Shader, sizeof(Particle_Vertex_Shader), NULL, particle_Vertex_Shader.GetAddressOf());
			c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(Particle_Pixel_Shader, sizeof(Particle_Pixel_Shader), NULL, particle_Pixel_Shader.GetAddressOf());

			UINT Offsett[1] = { 0 };
			UINT Stride[1] = { sizeof(tVertex) };

			//c_Graphics_Setup->Get_Context().Get()->ClearDepthStencilView(c_Graphics_Setup->Get_DSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
			//c_Graphics_Setup->Get_Context().Get()->OMSetRenderTargets(1, c_Graphics_Setup->Get_RTV().GetAddressOf(), 0);
			//c_Graphics_Setup->Get_Context().Get()->ClearRenderTargetView(c_Graphics_Setup->Get_RTV().Get(),);
			//c_Graphics_Setup->Get_Context().Get()->RSSetViewports(1, &c_Graphics_Setup->Get_View_Port());

			// Set particles position
			tObject_List->fWorld_Matrix->tW.fX;
			tObject_List->fWorld_Matrix->tW.fY;
			tObject_List->fWorld_Matrix->tW.fZ - 2;
			//tObject_List->fWorld_Matrix->tW.fW + 50;

			tWVP.fWorld_Matrix = tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[4]);

			// particle constant buffer goes here

			tPart.direction.z = timeDelta;
			tPart.direction.w = totalTime;

			c_Graphics_Setup->Get_Context().Get()->Map(particle_Constant_Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &particle_Constant_Mapped_RS);
			memcpy(particle_Constant_Mapped_RS.pData, &tPart, sizeof(tConstantBuffer_VertexShader_Bullet));
			c_Graphics_Setup->Get_Context().Get()->Unmap(particle_Constant_Buffer.Get(), 0);

			// particle constant buffer goes here

			c_Graphics_Setup->Get_Context().Get()->Map(d3d_Constant_Buffer_WVP.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
			memcpy(d3d_MSR.pData, &tWVP, sizeof(tConstantBuffer_VertexShader_WVP));
			c_Graphics_Setup->Get_Context().Get()->Unmap(d3d_Constant_Buffer_WVP.Get(), 0);

			//tObject_List->fWorld_Matrix[4]    // BULLETS WORLD POSITION

			c_Graphics_Setup->Get_Context().Get()->VSSetConstantBuffers(0, 1, d3d_Constant_Buffer_WVP.GetAddressOf());

			c_Graphics_Setup->Get_Context().Get()->IASetVertexBuffers(0, 1, particle_Vertex_Buffer.GetAddressOf(), Stride, Offsett);
			c_Graphics_Setup->Get_Context().Get()->IASetIndexBuffer(particle_Index_Buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			c_Graphics_Setup->Get_Context().Get()->IASetInputLayout(c_Graphics_Setup->Get_Input_Layout().Get());
			c_Graphics_Setup->Get_Context().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			c_Graphics_Setup->Get_Context().Get()->OMSetBlendState(particle_Blend_State.Get(), blend_Ratio, 0xffffffff);

			c_Graphics_Setup->Get_Context().Get()->VSSetShader(particle_Vertex_Shader.Get(), NULL, 0);
			c_Graphics_Setup->Get_Context().Get()->PSSetShader(particle_Pixel_Shader.Get(), NULL, 0);

			ID3D11ShaderResourceView *temp_particle_Shader_Resource_View[1] = { particle_Shader_Resource_View.Get() };
			c_Graphics_Setup->Get_Context().Get()->PSSetShaderResources(0, 1, temp_particle_Shader_Resource_View);

			if (c_Player_Fireball.getIsActive())
				c_Graphics_Setup->Get_Context().Get()->DrawIndexed(50, 0, 0);  // 50  // 100
			// PARTICLES

			// DRAGON PARTICLES

			if (dragon_hit == true)
			{
				static std::array<tVertex, 100> preAlloc_particle_D;

				for (int k = 0, l = 0; k < 100; k += 2, l++) // if there is no break point in the getter and setter this array break on a random index
				{
					random_color = 53 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (203 - 53)));
					random_alpha = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

					preAlloc_particle_D[k].fPosition.fX = line_vert[l].prev_Position.fX;    // line_vert = null
					preAlloc_particle_D[k].fPosition.fY = line_vert[l].prev_Position.fY;
					preAlloc_particle_D[k].fPosition.fZ = line_vert[l].prev_Position.fZ;
					preAlloc_particle[k].fPosition.fW = 1.0f;

					preAlloc_particle_D[k + 1].fPosition.fX = line_vert[l].position.fX;
					preAlloc_particle_D[k + 1].fPosition.fY = line_vert[l].position.fY;
					preAlloc_particle_D[k + 1].fPosition.fZ = line_vert[l].position.fZ;
					preAlloc_particle_D[k + 1].fPosition.fW = 1.0f;

					preAlloc_particle_D[k].fColor.fX = line_vert[l].color.fX;   // 0.2078f  // line_vert[l].color.fX;
					preAlloc_particle_D[k].fColor.fY = line_vert[l].color.fY;   // 0.2078f   * timer +/ - 5
					preAlloc_particle_D[k].fColor.fZ = line_vert[l].color.fZ;   // 0.2078f
					preAlloc_particle_D[k].fColor.fW = line_vert[l].color.fW;      // 1.0f

					preAlloc_particle_D[k + 1].fColor.fX = line_vert[l].color.fX;   // 0.2078f
					preAlloc_particle_D[k + 1].fColor.fY = line_vert[l].color.fY;   // 0.2078f
					preAlloc_particle_D[k + 1].fColor.fZ = line_vert[l].color.fZ;   // 0.2078f
					preAlloc_particle_D[k + 1].fColor.fW = line_vert[l].color.fW;      // 1.0f



					line_vert_count_D = preAlloc_particle_D.size();
				}

				D3D11_BUFFER_DESC particle_Vertex_Buffer_DESC;
				ZeroMemory(&particle_Vertex_Buffer_DESC, sizeof(D3D11_BUFFER_DESC));
				particle_Vertex_Buffer_DESC.CPUAccessFlags = NULL;
				particle_Vertex_Buffer_DESC.Usage = D3D11_USAGE_IMMUTABLE;
				particle_Vertex_Buffer_DESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				particle_Vertex_Buffer_DESC.MiscFlags = 0.0f;
				particle_Vertex_Buffer_DESC.ByteWidth = sizeof(tVertex) * 100;
				particle_Vertex_Buffer_DESC.StructureByteStride = 0;

				D3D11_SUBRESOURCE_DATA particle_Vertex_Buffer_DATA;
				ZeroMemory(&particle_Vertex_Buffer_DATA, sizeof(D3D11_SUBRESOURCE_DATA));
				particle_Vertex_Buffer_DATA.pSysMem = &preAlloc_particle_D;
				particle_Vertex_Buffer_DATA.SysMemPitch = 0;
				particle_Vertex_Buffer_DATA.SysMemSlicePitch = 0;

				c_Graphics_Setup->Get_Device()->CreateBuffer(&particle_Vertex_Buffer_DESC, &particle_Vertex_Buffer_DATA, particle_Vertex_Buffer.GetAddressOf());

				//D3D11_MAPPED_SUBRESOURCE mapped_Particle_Buffer;
				//c_Graphics_Setup->Get_Context().Get()->Map(particle_Vertex_Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
				//memcpy(mapped_Particle_Buffer.pData, preAlloc_particle.data(), sizeof(tVertex) * 888);
				//c_Graphics_Setup->Get_Context().Get()->Unmap(particle_Vertex_Buffer.Get(), 0);

				c_Graphics_Setup->Get_Device().Get()->CreateVertexShader(Particle_Vertex_Shader, sizeof(Particle_Vertex_Shader), NULL, particle_Vertex_Shader.GetAddressOf());
				c_Graphics_Setup->Get_Device().Get()->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, particle_Pixel_Shader.GetAddressOf());

				UINT Offsett[1] = { 0 };
				UINT Stride[1] = { sizeof(tVertex) };

				//tObject_List->fWorld_Matrix->tW.fW + 50;

				float x = tObject_List->fWorld_Matrix[2].tW.fX + 125;  // + 125
				float y = tObject_List->fWorld_Matrix[2].tW.fY + 80;  // + 100
				float z = tObject_List->fWorld_Matrix[2].tW.fZ;
				tFloat4x4 matrix = tObject_List->fWorld_Matrix[2];
				matrix.tW.fX = x;
				matrix.tW.fY = y;
				matrix.tW.fZ = z;

				tWVP.fWorld_Matrix = tFloat4x4_to_XMFLOAT4x4(matrix);

				// particle constant buffer goes here

				tPart.direction.z = timeDelta;
				tPart.direction.w = totalTime;

				c_Graphics_Setup->Get_Context().Get()->Map(particle_Constant_Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &particle_Constant_Mapped_RS);
				memcpy(particle_Constant_Mapped_RS.pData, &tPart, sizeof(tConstantBuffer_VertexShader_Bullet));
				c_Graphics_Setup->Get_Context().Get()->Unmap(particle_Constant_Buffer.Get(), 0);

				// particle constant buffer goes here

				c_Graphics_Setup->Get_Context().Get()->Map(d3d_Constant_Buffer_WVP.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
				memcpy(d3d_MSR.pData, &tWVP, sizeof(tConstantBuffer_VertexShader_WVP));
				c_Graphics_Setup->Get_Context().Get()->Unmap(d3d_Constant_Buffer_WVP.Get(), 0);

				//tObject_List->fWorld_Matrix[4]    // BULLETS WORLD POSITION

				c_Graphics_Setup->Get_Context().Get()->VSSetConstantBuffers(0, 1, d3d_Constant_Buffer_WVP.GetAddressOf());

				c_Graphics_Setup->Get_Context().Get()->IASetVertexBuffers(0, 1, particle_Vertex_Buffer.GetAddressOf(), Stride, Offsett);
				c_Graphics_Setup->Get_Context().Get()->IASetInputLayout(c_Graphics_Setup->Get_Input_Layout().Get());
				c_Graphics_Setup->Get_Context().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

				c_Graphics_Setup->Get_Context().Get()->VSSetShader(particle_Vertex_Shader.Get(), NULL, 0);
				c_Graphics_Setup->Get_Context().Get()->PSSetShader(particle_Pixel_Shader.Get(), NULL, 0);

				c_Graphics_Setup->Get_Context().Get()->Draw(50, 0);  // 50  // 100
			}

			// DRAGON PARTICLES

		}

		//c_Graphics_Setup->Get_Swap_Chain().Get()->Present(1, 0);
	}
}

particle* cRender_Manager::get_particle_array()  // void  // tVertex
{
	return line_vert;
}

void cRender_Manager::set_particle_array(particle* p_arr)  // Gets called twice when break point is in the function
{
	/*for (int i = 0; i < 300; i++)
	{
	line_vert[i].position.fX = p_arr[i].position.fX;
	line_vert[i].position.fY = p_arr[i].position.fY;
	line_vert[i].position.fZ = p_arr[i].position.fZ;

	line_vert[i].prev_Position.fX = p_arr[i].prev_Position.fX;
	line_vert[i].prev_Position.fY = p_arr[i].prev_Position.fY;
	line_vert[i].prev_Position.fZ = p_arr[i].prev_Position.fZ;

	line_vert[i].color.fX = p_arr[i].color.fX;
	line_vert[i].color.fY = p_arr[i].color.fY;
	line_vert[i].color.fZ = p_arr[i].color.fZ;
	line_vert[i].color.fW = p_arr[i].color.fW;
	}*/
	line_vert = p_arr;   // has data the first time but isn't showing an array, is NULL the second time
}

//tScene_Objects* cRender_Manager::get_object_world()
//{
//	return;
//}

void cRender_Manager::keyboardInputs(tScene_Objects* tObject_List)
{
	if (GetAsyncKeyState('J'))
	{
		XMMATRIX oldPos = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[5]));
		XMMATRIX moveMat = XMMatrixTranslation(0, 0, 20);

		XMMATRIX newMat = XMMatrixMultiply(moveMat, oldPos);
		XMFLOAT4X4 newMat2;
		XMStoreFloat4x4(&newMat2, newMat);
		tObject_List->fWorld_Matrix[5] = XMFLOAT4x4_to_tFloat4x4(newMat2);
	}
	if (GetAsyncKeyState('L'))
	{
		XMMATRIX oldPos = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[5]));
		XMMATRIX moveMat = XMMatrixTranslation(0, 0, -20);

		XMMATRIX newMat = XMMatrixMultiply(moveMat, oldPos);
		XMFLOAT4X4 newMat2;
		XMStoreFloat4x4(&newMat2, newMat);
		tObject_List->fWorld_Matrix[5] = XMFLOAT4x4_to_tFloat4x4(newMat2);
	}
	if (GetAsyncKeyState('I'))
	{
		XMMATRIX oldPos = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[5]));
		XMMATRIX moveMat = XMMatrixTranslation(-20, 0, 0);

		XMMATRIX newMat = XMMatrixMultiply(moveMat, oldPos);
		XMFLOAT4X4 newMat2;
		XMStoreFloat4x4(&newMat2, newMat);
		tObject_List->fWorld_Matrix[5] = XMFLOAT4x4_to_tFloat4x4(newMat2);
	}
	if (GetAsyncKeyState('K'))
	{
		XMMATRIX oldPos = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[5]));
		XMMATRIX moveMat = XMMatrixTranslation(20, 0, 0);

		XMMATRIX newMat = XMMatrixMultiply(moveMat, oldPos);
		XMFLOAT4X4 newMat2;
		XMStoreFloat4x4(&newMat2, newMat);
		tObject_List->fWorld_Matrix[5] = XMFLOAT4x4_to_tFloat4x4(newMat2);
	}
}
