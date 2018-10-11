#pragma once

#include <DirectXMath.h>
#include "basic_structs.h"

struct tConstantBuffer
{
	XMFLOAT4X4 fWorld_Matrix;
	XMFLOAT4X4 fView_Matrix;
	XMFLOAT4X4 fProjection_Matrix;
	XMFLOAT4X4 fCamera_Matrix;
	XMFLOAT4X4 fCamera_Origin;
};

//Ben

struct ModelViewProjectionConstantBuffer
{
	DirectX::XMFLOAT4X4 model;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};

struct PhongForShader
{
	XMFLOAT3 ambient;
	XMFLOAT3 diffuse;
	XMFLOAT3 emissive;
	XMFLOAT3 specular;

	float transparency;
	float shininess;
	float reflection;
};

struct PositionColor
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 color;
};

struct PositionUVNormal
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 uv;
	DirectX::XMFLOAT3 normal;
};

struct	pipeline_state_t
{
	uint8_t		vertex_shader;
	uint8_t		pixel_shader;

	uint8_t		constant_buffer;

	uint8_t		vertex_buffer;

	uint8_t		depthStencilState;
	uint8_t		rasterState;
}default_pipeline;

struct graphics_system
{
	//1
	ID3D11VertexShader*		vertex_shaders[32]{};
	ID3D11InputLayout*		input_layouts[32]{};

	//2
	ID3D11PixelShader*		pixel_shaders[32]{};

	//3
	ID3D11Buffer*			constant_buffers[32]{};
	ModelViewProjectionConstantBuffer constant_data[32]{};


	//4
	ID3D11Buffer*			vertex_buffers[32]{};
	ID3D11Buffer*			index_buffers[32]{};
	INT32					index_counts[32]{};


	//misc
	//ID3D11RenderTargetView* render_target_views[256]{};
	//ID3D11DepthStencilView* depth_stencil_views[256]{};
	ID3D11DepthStencilState* depth_stencil_states[32]{};
	ID3D11RasterizerState* rasterizer_states[32]{};
	//etc...

	ID3D11Buffer*			material_buffers[32]{};
};