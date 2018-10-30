/************************************************************************
* Filename:  		renderer_structs.h
* Date:      		10/02/2018
* Mod. Date: 		10/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Additional structs to hold different datatype and make accessing them easier.
*************************************************************************/
#pragma once

#include <atlbase.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>
using namespace DirectX;
#include "basic_structs.h"


struct tMesh
{
	uint32_t nVertex_Count = 0;
	uint32_t nIndex_Count = 0;
	std::vector<tVertex> tVerts;
	std::vector<int> nIndicies;
};

struct tMaterial
{
	tFloat4 tAmbient = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string szAmbient_File_Path = "";
	tFloat4 tDiffuse = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string szDiffuse_File_Path = "";
	tFloat4 tEmissive = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string szEmissive_File_Path = "";
	tFloat4 tNormal = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string szNormal_File_Path = "";
	tFloat4 tReflection = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string szReflection_File_Path = "";
	float fShininess = 0.0f;
	std::string szShininess_File_Path = "";
	tFloat4 tSpecular = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string szSpecular_File_Path = "";
	tFloat4 tTransparency = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string szTransparency_File_Path = "";
};

struct tMaterials
{
	std::vector<tMaterial> tMats;
};

struct tConstantBuffer_VertexShader_WVP
{
	XMFLOAT4X4 fWorld_Matrix;
	XMFLOAT4X4 fView_Matrix;
	XMFLOAT4X4 fProjection_Matrix;
	XMFLOAT4X4 fPose_Matrix;
	XMFLOAT4X4 fHead_Matrix;
	//XMFLOAT4X4 fCamera_Matrix;
	//XMFLOAT4X4 fCamera_Origin;
};


struct	tObject_Id
{
	uint8_t		nObject_Id;
	uint8_t		nVertex_Shader_Id;
	uint8_t		nPixel_Shader_Id;
	uint8_t		nSRV_Id;
	bool		bIsShowing;
};

struct tScene_Objects
{
	int nObject_Count;
	tFloat3								fWorld_Position[32]{};
	XMFLOAT4X4							fWorld_Matrix[32]{};

	CComPtr<ID3D11Buffer>				d3d_Vertex_Buffers[32]{};
	CComPtr<ID3D11Buffer>				d3d_Index_Buffers[32]{};
	tMesh								tMesh_Data[32]{};

	CComPtr<ID3D11VertexShader>			d3d_Vertex_Shaders[32]{};
	std::string							szVS_File_Path[32]{};

	CComPtr<ID3D11PixelShader>			d3d_Pixel_Shaders[32]{};
	std::string							szPS_File_Path[32]{};

	CComPtr<ID3D11Buffer>				tMaterials_Buffers[32]{};
	tMaterials							tMaterials_Data[32]{};

	CComPtr<ID3D11ShaderResourceView>	d3d_SRV[32]{};
	std::string							szSRV_File_Path[32]{};
};




struct tConstantBuffer_Float4
{
	XMFLOAT4 fData = { 0.0f, 0.0f, 0.0f, 0.0f };
};

struct tConstantBuffer_PixelShader
{
	XMFLOAT4 light_pos = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4 light_col = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMFLOAT4 light_nrm = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4 ambient = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4 diffuse = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4 emissive = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4 reflection = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4 shininess = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4 specular = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4 transparency = { 0.0f, 0.0f, 0.0f, 0.0f };
};
