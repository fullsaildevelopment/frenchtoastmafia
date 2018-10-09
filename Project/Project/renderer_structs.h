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