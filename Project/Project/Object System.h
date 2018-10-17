#pragma once
#include <DirectXMath.h>
using namespace DirectX;
#include "basic_structs.h"
#include "renderer_structs.h"

struct object_system
{
	CComPtr<ID3D11Buffer>			constant_buffers[32]{};

	CComPtr<ID3D11Buffer>	vertex_buffers[32]{};
	CComPtr<ID3D11Buffer>	index_buffers[32]{};

	CComPtr<ID3D11VertexShader>	    vertex_shaders[32]{};
	CComPtr<ID3D11PixelShader>		pixel_shaders[32]{};
	XMFLOAT4X4						world_position[32]{};

	tMeshes					meshes_data[32]{};

	CComPtr<ID3D11Buffer>	materials_buffers[32]{};
	tMaterials				materials_data[32]{};
};