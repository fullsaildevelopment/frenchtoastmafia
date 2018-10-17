/************************************************************************
* Filename:  		renderer_structs.h
* Date:      		10/02/2018
* Mod. Date: 		10/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Additional structs to hold different datatype and make accessing them easier.
*************************************************************************/
#pragma once

#include <DirectXMath.h>
using namespace DirectX;
#include "basic_structs.h"

struct	pipeline_t
{
	uint8_t		pipeline_id;
	uint8_t		vertex_shader_id;
	uint8_t		pixel_shader_id;
	uint8_t		constant_buffer_wvp_id;
};

struct tConstantBuffer_VertexShader_WVPC
{
	XMFLOAT4X4 fWorld_Matrix;
	XMFLOAT4X4 fView_Matrix;
	XMFLOAT4X4 fProjection_Matrix;
	XMFLOAT4X4 fCamera_Matrix;
	XMFLOAT4X4 fCamera_Origin;
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

struct tMesh
{
	uint32_t nVertex_Count = 0;
	uint32_t nIndex_Count = 0;
	std::vector<tVertex> tVerts;
	std::vector<int> nIndicies;
};

struct tMeshes
{
	std::vector<tMesh> tMes;
};

struct tMaterial
{
	tFloat4 tAmbient = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string szAmbient_File_Path = "";
	tFloat4 tDiffuse = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string szDiffuse_File_Path = "";
	tFloat4 tEmissive = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string szEmissive_File_Path = "";
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