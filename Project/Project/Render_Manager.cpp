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

		if (nScene_Id == 2)
		{
			//VERTEX SHADERS
			if (i == 1)
				c_Graphics_Setup->Get_Device()->CreateVertexShader(VertexShader_Arena, sizeof(VertexShader_Arena), NULL, &t_Object_List->d3d_Vertex_Shaders[i]);
			else
				c_Graphics_Setup->Get_Device()->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &t_Object_List->d3d_Vertex_Shaders[i]);


			//PIXEL SHADERS
			if (i == 0)
				c_Graphics_Setup->Get_Device()->CreatePixelShader(PixelShader_Mage, sizeof(PixelShader_Mage), NULL, &t_Object_List->d3d_Pixel_Shaders[i]);
			else if (i == 1)
				c_Graphics_Setup->Get_Device()->CreatePixelShader(PixelShader_Arena, sizeof(PixelShader_Arena), NULL, &t_Object_List->d3d_Pixel_Shaders[i]);
			else if (i == 2)
				c_Graphics_Setup->Get_Device()->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, &t_Object_List->d3d_Pixel_Shaders[i]);
			else if (i == 3)
				c_Graphics_Setup->Get_Device()->CreatePixelShader(PixelShader, sizeof(PixelShader_Dragon), NULL, &t_Object_List->d3d_Pixel_Shaders[i]);

			
			//// SRV
			//if (t_Object_List->tMaterials_Data[i].tMats[0].szAmbient_File_Path)
			//{
			//	std::wstring ws_tmp_srv = std::wstring(t_Object_List->tMaterials_Data[1].tMats[0].szAmbient_File_Path.begin(), t_Object_List->tMaterials_Data[i].tMats[0].szAmbient_File_Path.end());
			//	const wchar_t* tmp_srv = ws_tmp_srv.c_str();
			//	CreateWICTextureFromFile(c_Graphics_Setup->Get_Device(), c_Graphics_Setup->Get_Context(), tmp_srv, nullptr, &t_Object_List->d3d_SRV[i], 0);
			//}

			
		}
		// MATERIALS	
		
		//if (nScene_Id < 2 || nScene_Id > 3)
		//{
		//	c_Graphics_Setup->Get_Device()->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, &t_Object_List->d3d_Vertex_Shaders[0]);
		//	c_Graphics_Setup->Get_Device()->CreatePixelShader(PixelShader_Screen, sizeof(PixelShader_Screen), NULL, &t_Object_List->d3d_Pixel_Shaders[0]);
		//	std::wstring ws_tmp_srv = std::wstring(t_Object_List->szSRV_File_Path[0].begin(), t_Object_List->szSRV_File_Path[0].end());
		//	const wchar_t* tmp_srv = ws_tmp_srv.c_str();
		//	CreateDDSTextureFromFile(c_Graphics_Setup->Get_Device(), tmp_srv, nullptr, &t_Object_List->d3d_SRV[0].p);
		//}
	}

	// SRV List
	// 0 - mage - diffuse
	// 1 - mage - emissive
	// 2 - mage - specular
	// 3 - mage - normal

	// 4 - arena - diffuse

	// 5 - priest - diffuse
	// 6 - priest - normal

	// 7 - dragon - diffuse


	HRESULT result;
	// MAGE
	std::wstring d_tmp = std::wstring(t_Object_List->tMaterials_Data[0].tMats[0].szDiffuse_File_Path.begin(), t_Object_List->tMaterials_Data[0].tMats[0].szDiffuse_File_Path.end());
	const wchar_t* diffuse_path = d_tmp.c_str();
	result = CreateWICTextureFromFile(c_Graphics_Setup->Get_Device(), c_Graphics_Setup->Get_Context(), diffuse_path, nullptr, &t_Object_List->d3d_SRV[0], 0);

	std::wstring e_tmp = std::wstring(t_Object_List->tMaterials_Data[0].tMats[0].szEmissive_File_Path.begin(), t_Object_List->tMaterials_Data[0].tMats[0].szEmissive_File_Path.end());
	const wchar_t* emissive_path = e_tmp.c_str();
	result = CreateWICTextureFromFile(c_Graphics_Setup->Get_Device(), c_Graphics_Setup->Get_Context(), emissive_path, nullptr, &t_Object_List->d3d_SRV[1], 0);

	std::wstring s_tmp = std::wstring(t_Object_List->tMaterials_Data[0].tMats[0].szSpecular_File_Path.begin(), t_Object_List->tMaterials_Data[0].tMats[0].szSpecular_File_Path.end());
	const wchar_t* specular_path = s_tmp.c_str();
	result = CreateWICTextureFromFile(c_Graphics_Setup->Get_Device(), c_Graphics_Setup->Get_Context(), specular_path, nullptr, &t_Object_List->d3d_SRV[2], 0);

	std::wstring n_tmp = std::wstring(t_Object_List->tMaterials_Data[0].tMats[0].szNormal_File_Path.begin(), t_Object_List->tMaterials_Data[0].tMats[0].szNormal_File_Path.end());
	const wchar_t* normal_path = n_tmp.c_str();
	result = CreateWICTextureFromFile(c_Graphics_Setup->Get_Device(), c_Graphics_Setup->Get_Context(), normal_path, nullptr, &t_Object_List->d3d_SRV[3], 0);
	{
		cps_mage.light_pos = { 0.0f, 0.0f, -2.0f, 1.0f };

		cps_mage.ambient.x = t_Object_List->tMaterials_Data[0].tMats[0].tAmbient.fX;
		cps_mage.ambient.y = t_Object_List->tMaterials_Data[0].tMats[0].tAmbient.fY;
		cps_mage.ambient.z = t_Object_List->tMaterials_Data[0].tMats[0].tAmbient.fZ;
		cps_mage.ambient.w = t_Object_List->tMaterials_Data[0].tMats[0].tAmbient.fW;

		cps_mage.diffuse.x = t_Object_List->tMaterials_Data[0].tMats[0].tDiffuse.fX;
		cps_mage.diffuse.y = t_Object_List->tMaterials_Data[0].tMats[0].tDiffuse.fY;
		cps_mage.diffuse.z = t_Object_List->tMaterials_Data[0].tMats[0].tDiffuse.fZ;
		cps_mage.diffuse.w = t_Object_List->tMaterials_Data[0].tMats[0].tDiffuse.fW;

		cps_mage.emissive.x = t_Object_List->tMaterials_Data[0].tMats[0].tEmissive.fX;
		cps_mage.emissive.y = t_Object_List->tMaterials_Data[0].tMats[0].tEmissive.fY;
		cps_mage.emissive.z = t_Object_List->tMaterials_Data[0].tMats[0].tEmissive.fZ;
		cps_mage.emissive.w = t_Object_List->tMaterials_Data[0].tMats[0].tEmissive.fW;

		cps_mage.reflection.x = t_Object_List->tMaterials_Data[0].tMats[0].tReflection.fX;
		cps_mage.reflection.y = t_Object_List->tMaterials_Data[0].tMats[0].tReflection.fY;
		cps_mage.reflection.z = t_Object_List->tMaterials_Data[0].tMats[0].tReflection.fZ;
		cps_mage.reflection.w = t_Object_List->tMaterials_Data[0].tMats[0].tReflection.fW;

		cps_mage.shininess.x = t_Object_List->tMaterials_Data[0].tMats[0].fShininess;

		cps_mage.specular.x = t_Object_List->tMaterials_Data[0].tMats[0].tSpecular.fX;
		cps_mage.specular.y = t_Object_List->tMaterials_Data[0].tMats[0].tSpecular.fY;
		cps_mage.specular.z = t_Object_List->tMaterials_Data[0].tMats[0].tSpecular.fZ;
		cps_mage.specular.w = t_Object_List->tMaterials_Data[0].tMats[0].tSpecular.fW;

		cps_mage.transparency.x = t_Object_List->tMaterials_Data[0].tMats[0].tTransparency.fX;
		cps_mage.transparency.y = t_Object_List->tMaterials_Data[0].tMats[0].tTransparency.fY;
		cps_mage.transparency.z = t_Object_List->tMaterials_Data[0].tMats[0].tTransparency.fZ;
		cps_mage.transparency.w = t_Object_List->tMaterials_Data[0].tMats[0].tTransparency.fW;

		// CONSTANT BUFFER - Mage
		ZeroMemory(&d3d_Constant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
		d3d_Constant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_PixelShader);
		d3d_Constant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
		d3d_Constant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		d3d_Constant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		d3d_Constant_Buffer_Desc.MiscFlags = 0;
		d3d_Constant_Buffer_Desc.StructureByteStride = 0;

		c_Graphics_Setup->Get_Device()->CreateBuffer(&d3d_Constant_Buffer_Desc, nullptr, &t_Object_List->tMaterials_Buffers[0].p);
	}

	// ARENA

	d_tmp = std::wstring(t_Object_List->tMaterials_Data[1].tMats[0].szDiffuse_File_Path.begin(), t_Object_List->tMaterials_Data[1].tMats[0].szDiffuse_File_Path.end());
	diffuse_path = d_tmp.c_str();
	result = CreateWICTextureFromFile(c_Graphics_Setup->Get_Device(), c_Graphics_Setup->Get_Context(), diffuse_path, nullptr, &t_Object_List->d3d_SRV[4], 0);
	{
		cps_arena.light_pos = { 0.0f, 0.0f, -2.0f, 1.0f };

		cps_arena.ambient.x = t_Object_List->tMaterials_Data[1].tMats[0].tAmbient.fX;
		cps_arena.ambient.y = t_Object_List->tMaterials_Data[1].tMats[0].tAmbient.fY;
		cps_arena.ambient.z = t_Object_List->tMaterials_Data[1].tMats[0].tAmbient.fZ;
		cps_arena.ambient.w = t_Object_List->tMaterials_Data[1].tMats[0].tAmbient.fW;

		cps_arena.diffuse.x = t_Object_List->tMaterials_Data[1].tMats[0].tDiffuse.fX;
		cps_arena.diffuse.y = t_Object_List->tMaterials_Data[1].tMats[0].tDiffuse.fY;
		cps_arena.diffuse.z = t_Object_List->tMaterials_Data[1].tMats[0].tDiffuse.fZ;
		cps_arena.diffuse.w = t_Object_List->tMaterials_Data[1].tMats[0].tDiffuse.fW;

		cps_arena.emissive.x = t_Object_List->tMaterials_Data[1].tMats[0].tEmissive.fX;
		cps_arena.emissive.y = t_Object_List->tMaterials_Data[1].tMats[0].tEmissive.fY;
		cps_arena.emissive.z = t_Object_List->tMaterials_Data[1].tMats[0].tEmissive.fZ;
		cps_arena.emissive.w = t_Object_List->tMaterials_Data[1].tMats[0].tEmissive.fW;

		cps_arena.reflection.x = t_Object_List->tMaterials_Data[1].tMats[0].tReflection.fX;
		cps_arena.reflection.y = t_Object_List->tMaterials_Data[1].tMats[0].tReflection.fY;
		cps_arena.reflection.z = t_Object_List->tMaterials_Data[1].tMats[0].tReflection.fZ;
		cps_arena.reflection.w = t_Object_List->tMaterials_Data[1].tMats[0].tReflection.fW;

		cps_arena.shininess.x = t_Object_List->tMaterials_Data[1].tMats[0].fShininess;

		cps_arena.specular.x = t_Object_List->tMaterials_Data[1].tMats[0].tSpecular.fX;
		cps_arena.specular.y = t_Object_List->tMaterials_Data[1].tMats[0].tSpecular.fY;
		cps_arena.specular.z = t_Object_List->tMaterials_Data[1].tMats[0].tSpecular.fZ;
		cps_arena.specular.w = t_Object_List->tMaterials_Data[1].tMats[0].tSpecular.fW;

		cps_arena.transparency.x = t_Object_List->tMaterials_Data[1].tMats[0].tTransparency.fX;
		cps_arena.transparency.y = t_Object_List->tMaterials_Data[1].tMats[0].tTransparency.fY;
		cps_arena.transparency.z = t_Object_List->tMaterials_Data[1].tMats[0].tTransparency.fZ;
		cps_arena.transparency.w = t_Object_List->tMaterials_Data[1].tMats[0].tTransparency.fW;

		// CONSTANT BUFFER - Arena
		ZeroMemory(&d3d_Constant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
		d3d_Constant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_PixelShader);
		d3d_Constant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
		d3d_Constant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		d3d_Constant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		d3d_Constant_Buffer_Desc.MiscFlags = 0;
		d3d_Constant_Buffer_Desc.StructureByteStride = 0;

		c_Graphics_Setup->Get_Device()->CreateBuffer(&d3d_Constant_Buffer_Desc, nullptr, &t_Object_List->tMaterials_Buffers[1].p);
	}
	//
	//// PRIEST
	//
	//d_tmp = std::wstring(t_Object_List->tMaterials_Data[2].tMats[0].szDiffuse_File_Path.begin(), t_Object_List->tMaterials_Data[2].tMats[0].szDiffuse_File_Path.end());
	//diffuse_path = d_tmp.c_str();
	//result = CreateWICTextureFromFile(c_Graphics_Setup->Get_Device(), c_Graphics_Setup->Get_Context(), diffuse_path, nullptr, &t_Object_List->d3d_SRV[5], 0);
	//
	//n_tmp = std::wstring(t_Object_List->tMaterials_Data[2].tMats[0].szNormal_File_Path.begin(), t_Object_List->tMaterials_Data[2].tMats[0].szNormal_File_Path.end());
	//normal_path = n_tmp.c_str();
	//result = CreateWICTextureFromFile(c_Graphics_Setup->Get_Device(), c_Graphics_Setup->Get_Context(), normal_path, nullptr, &t_Object_List->d3d_SRV[6], 0);

	// Dragon

	d_tmp = std::wstring(t_Object_List->tMaterials_Data[3].tMats[0].szDiffuse_File_Path.begin(), t_Object_List->tMaterials_Data[3].tMats[0].szDiffuse_File_Path.end());
	diffuse_path = d_tmp.c_str();
	result = CreateWICTextureFromFile(c_Graphics_Setup->Get_Device(), c_Graphics_Setup->Get_Context(), diffuse_path, nullptr, &t_Object_List->d3d_SRV[7], 0);
	{
		cps_dragon.light_pos = { 0.0f, 0.0f, -2.0f, 1.0f };

		cps_dragon.ambient.x = t_Object_List->tMaterials_Data[3].tMats[0].tAmbient.fX;
		cps_dragon.ambient.y = t_Object_List->tMaterials_Data[3].tMats[0].tAmbient.fY;
		cps_dragon.ambient.z = t_Object_List->tMaterials_Data[3].tMats[0].tAmbient.fZ;
		cps_dragon.ambient.w = t_Object_List->tMaterials_Data[3].tMats[0].tAmbient.fW;

		cps_dragon.diffuse.x = t_Object_List->tMaterials_Data[3].tMats[0].tDiffuse.fX;
		cps_dragon.diffuse.y = t_Object_List->tMaterials_Data[3].tMats[0].tDiffuse.fY;
		cps_dragon.diffuse.z = t_Object_List->tMaterials_Data[3].tMats[0].tDiffuse.fZ;
		cps_dragon.diffuse.w = t_Object_List->tMaterials_Data[3].tMats[0].tDiffuse.fW;

		cps_dragon.emissive.x = t_Object_List->tMaterials_Data[3].tMats[0].tEmissive.fX;
		cps_dragon.emissive.y = t_Object_List->tMaterials_Data[3].tMats[0].tEmissive.fY;
		cps_dragon.emissive.z = t_Object_List->tMaterials_Data[3].tMats[0].tEmissive.fZ;
		cps_dragon.emissive.w = t_Object_List->tMaterials_Data[3].tMats[0].tEmissive.fW;

		cps_dragon.reflection.x = t_Object_List->tMaterials_Data[3].tMats[0].tReflection.fX;
		cps_dragon.reflection.y = t_Object_List->tMaterials_Data[3].tMats[0].tReflection.fY;
		cps_dragon.reflection.z = t_Object_List->tMaterials_Data[3].tMats[0].tReflection.fZ;
		cps_dragon.reflection.w = t_Object_List->tMaterials_Data[3].tMats[0].tReflection.fW;

		cps_dragon.shininess.x = t_Object_List->tMaterials_Data[3].tMats[0].fShininess;

		cps_dragon.specular.x = t_Object_List->tMaterials_Data[3].tMats[0].tSpecular.fX;
		cps_dragon.specular.y = t_Object_List->tMaterials_Data[3].tMats[0].tSpecular.fY;
		cps_dragon.specular.z = t_Object_List->tMaterials_Data[3].tMats[0].tSpecular.fZ;
		cps_dragon.specular.w = t_Object_List->tMaterials_Data[3].tMats[0].tSpecular.fW;

		cps_dragon.transparency.x = t_Object_List->tMaterials_Data[3].tMats[0].tTransparency.fX;
		cps_dragon.transparency.y = t_Object_List->tMaterials_Data[3].tMats[0].tTransparency.fY;
		cps_dragon.transparency.z = t_Object_List->tMaterials_Data[3].tMats[0].tTransparency.fZ;
		cps_dragon.transparency.w = t_Object_List->tMaterials_Data[3].tMats[0].tTransparency.fW;

		// CONSTANT BUFFER - dragon
		ZeroMemory(&d3d_Constant_Buffer_Desc, sizeof(D3D11_BUFFER_DESC));
		d3d_Constant_Buffer_Desc.ByteWidth = sizeof(tConstantBuffer_PixelShader);
		d3d_Constant_Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;
		d3d_Constant_Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		d3d_Constant_Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		d3d_Constant_Buffer_Desc.MiscFlags = 0;
		d3d_Constant_Buffer_Desc.StructureByteStride = 0;

		c_Graphics_Setup->Get_Device()->CreateBuffer(&d3d_Constant_Buffer_Desc, nullptr, &t_Object_List->tMaterials_Buffers[3].p);
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
		unsigned int off_set = 0;

		for (int i = 0; i < t_Object_List.nObject_Count; i++)
		{
			// CONSTANT BUFFER - WVPC
			{
				tWVP.fWorld_Matrix = tFloat4x4_to_XMFLOAT4x4(t_Object_List.fWorld_Matrix[i]);

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
			if (i != 2)
				c_Graphics_Setup->Get_Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			else
			{
				c_Graphics_Setup->Get_Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			}
			//if (i != 1)
			//{
			//	c_Graphics_Setup->Get_Context()->VSSetShader(c_Graphics_Setup->Get_Vertex_Shader(), NULL, 0);
			//	c_Graphics_Setup->Get_Context()->PSSetShader(c_Graphics_Setup->Get_Pixel_Shader(), NULL, 0);
			//}
			//else
			//{
			c_Graphics_Setup->Get_Context()->VSSetShader(t_Object_List.d3d_Vertex_Shaders[i], NULL, 0);
			c_Graphics_Setup->Get_Context()->PSSetShader(t_Object_List.d3d_Pixel_Shaders[i], NULL, 0);

			if (i == 0)
			{
				c_Graphics_Setup->Get_Context()->PSSetShaderResources(0, 1, &t_Object_List.d3d_SRV[0].p);
				c_Graphics_Setup->Get_Context()->PSSetShaderResources(1, 1, &t_Object_List.d3d_SRV[1].p);
				c_Graphics_Setup->Get_Context()->PSSetShaderResources(2, 1, &t_Object_List.d3d_SRV[2].p);
				//c_Graphics_Setup->Get_Context()->PSSetShaderResources(3, 1, &t_Object_List.d3d_SRV[3].p);

				c_Graphics_Setup->Get_Context()->Map(t_Object_List.tMaterials_Buffers[0], 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
				memcpy(d3d_MSR.pData, &cps_mage, sizeof(tConstantBuffer_PixelShader));
				c_Graphics_Setup->Get_Context()->Unmap(t_Object_List.tMaterials_Buffers[0], 0);
				ID3D11Buffer *tmp_con_buffer[] = { t_Object_List.tMaterials_Buffers[0] };
				c_Graphics_Setup->Get_Context()->PSSetConstantBuffers(0, 1, tmp_con_buffer);

			}
			else if (i == 1)
			{
				c_Graphics_Setup->Get_Context()->PSSetShaderResources(0, 1, &t_Object_List.d3d_SRV[4].p);

				c_Graphics_Setup->Get_Context()->Map(t_Object_List.tMaterials_Buffers[1], 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
				memcpy(d3d_MSR.pData, &cps_arena, sizeof(tConstantBuffer_PixelShader));
				c_Graphics_Setup->Get_Context()->Unmap(t_Object_List.tMaterials_Buffers[1], 0);
				ID3D11Buffer *tmp_con_buffer[] = { t_Object_List.tMaterials_Buffers[1] };
				c_Graphics_Setup->Get_Context()->PSSetConstantBuffers(0, 1, tmp_con_buffer);
			}
			else if (i == 3)
			{
				c_Graphics_Setup->Get_Context()->PSSetShaderResources(0, 1, &t_Object_List.d3d_SRV[7].p);

				c_Graphics_Setup->Get_Context()->Map(t_Object_List.tMaterials_Buffers[3], 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d_MSR);
				memcpy(d3d_MSR.pData, &cps_arena, sizeof(tConstantBuffer_PixelShader));
				c_Graphics_Setup->Get_Context()->Unmap(t_Object_List.tMaterials_Buffers[3], 0);
				ID3D11Buffer *tmp_con_buffer[] = { t_Object_List.tMaterials_Buffers[3] };
				c_Graphics_Setup->Get_Context()->PSSetConstantBuffers(0, 1, tmp_con_buffer);
			}
			//else if (i == 2)
			//{
			//	c_Graphics_Setup->Get_Context()->PSSetShaderResources(0, 1, &t_Object_List.d3d_SRV[5].p);
			//	c_Graphics_Setup->Get_Context()->PSSetShaderResources(0, 1, &t_Object_List.d3d_SRV[6].p);
			//}

			//}
			//d3dContext->PSSetShader(d3dPixel_Shader_Screen, NULL, 0);
			//ID3D11ShaderResourceView *tmp_intro_srv[] = { tScene.d3d_SRV[0] };
			//d3dContext->PSSetShaderResources(0, 1, tmp_intro_srv);
			if (i != 2)
				c_Graphics_Setup->Get_Context()->DrawIndexed(t_Object_List.tMesh_Data[i].nIndex_Count, 0, 0);
		}
	}

	c_Graphics_Setup->Get_Swap_Chain()->Present(1, 0);
}

void cRender_Manager::DrawToTexture()
{
}
