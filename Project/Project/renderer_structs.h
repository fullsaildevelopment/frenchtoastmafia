/************************************************************************
* Filename:  		Renderer_Structs.h
* Date:      		02/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Additional render-specific structs to hold different datatype and make accessing them easier.
*************************************************************************/
#pragma once

#include <wrl.h>
using Microsoft::WRL::ComPtr;
//#include <atlbase.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>
using namespace DirectX;
#include "Basic_Structs.h"


struct tMesh
{
	uint32_t nVertex_Count = 0;
	uint32_t nIndex_Count = 0;
	std::vector<tVertex> tVerts;
	std::vector<int> nIndicies;
};
struct tMesh_Skinned
{
	uint32_t nVertex_Count = 0;
	uint32_t nIndex_Count = 0;
	std::vector<tVertex_Skinned> tVerts;
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
	// Count
	int nObject_Count;

	// Position
	tFloat3								fWorld_Position[15]{};
	tFloat4x4							fWorld_Matrix[15]{};

	tFloat4x4							fFireball_Matrix[3]{};
	bool								fFireball_State[3]{};
	int									fFireballs_Alive = 0;
	int									maxFireballs = 3;
	tFloat4x4							dragReset;

	// Vertex and Index Data
	bool								bIs_Animated[15]{};

	tMesh								tMesh_Data[15]{};
	tMesh_Skinned						tMesh_Skinned_Data[15]{};

	ComPtr<ID3D11Buffer>				d3d_Vertex_Buffers[15]{};
	ComPtr<ID3D11Buffer>				d3d_Index_Buffers[15]{};

	// Material
	tMaterials							tMaterials_Data[15]{};
	ComPtr<ID3D11Buffer>				tMaterials_Buffers[15]{};

	// SRV
	std::string							szSRV_File_Path[15];
	ComPtr<ID3D11ShaderResourceView>	d3d_SRV[15][10]{};

	// Animation
	tAnimation_Clip						tAnim_Clip[15][8]{};
	tAnimation_Data						tAnim_Data[15]{}; // try to combine with clip when create binary writer

	int									currAnim[15]{};

	// Vertex Shaders
	ComPtr<ID3D11VertexShader>			d3d_Vertex_Shaders[15]{};

	// Pixel Shaders
	ComPtr<ID3D11PixelShader>			d3d_Pixel_Shaders[15]{};

	//int									dragHP = 4;
};


struct tConstantBuffer_VertexShader_WVP
{
	XMFLOAT4X4 fWorld_Matrix;
	XMFLOAT4X4 fView_Matrix;
	XMFLOAT4X4 fProjection_Matrix;
};

struct tConstantBuffer_VertexShader_Bullet
{
	XMFLOAT4 direction = { 0.0f, 0.0f, 0.0f, 0.0f };
};

struct tConstantBuffer_VertexShader_Animation
{
	XMFLOAT4X4 fAnimation_Data[99];
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
	XMFLOAT4 tint = { 0.0f, 0.0f, 0.0f, 1.0f };
};

struct tConstantBuffer_PixelShader_Alpha
{
	//XMFLOAT2 alpha;
};
