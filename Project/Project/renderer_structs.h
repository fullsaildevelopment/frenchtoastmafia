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
#include "basic_structs.h"

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