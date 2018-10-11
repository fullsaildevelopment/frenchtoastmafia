/************************************************************************
* Filename:  		math_conversion.h
* Date:      		10/11/2018
* Mod. Date: 		10/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Additional math to convert between datatype or structure types.
*************************************************************************/
#pragma once

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
using namespace DirectX;
#include "basic_structs.h"

inline XMFLOAT4X4 tFloat4x4_to_XMFLOAT4x4(tFloat4x4 fIn)
{
	XMFLOAT4X4 fOut;

	fOut.m[0][0] = fIn.tX.fX;
	fOut.m[0][1] = fIn.tX.fY;
	fOut.m[0][2] = fIn.tX.fZ;
	fOut.m[0][3] = fIn.tX.fW;

	fOut.m[1][0] = fIn.tY.fX;
	fOut.m[1][1] = fIn.tY.fY;
	fOut.m[1][2] = fIn.tY.fZ;
	fOut.m[1][3] = fIn.tY.fW;

	fOut.m[2][0] = fIn.tZ.fX;
	fOut.m[2][1] = fIn.tZ.fY;
	fOut.m[2][2] = fIn.tZ.fZ;
	fOut.m[2][3] = fIn.tZ.fW;

	fOut.m[3][0] = fIn.tW.fX;
	fOut.m[3][1] = fIn.tW.fY;
	fOut.m[3][2] = fIn.tW.fZ;
	fOut.m[3][3] = fIn.tW.fW;

	return fOut;
}

inline tFloat4x4 XMFLOAT4x4_to_tFloat4x4(XMFLOAT4X4 fIn)
{
	tFloat4x4 fOut;

	fOut.tX.fX = fIn.m[0][0];
	fOut.tX.fY = fIn.m[0][1];
	fOut.tX.fZ = fIn.m[0][2];
	fOut.tX.fW = fIn.m[0][3];

	fOut.tY.fX = fIn.m[1][0];
	fOut.tY.fY = fIn.m[1][1];
	fOut.tY.fZ = fIn.m[1][2];
	fOut.tY.fW = fIn.m[1][3];

	fOut.tZ.fX = fIn.m[2][0];
	fOut.tZ.fY = fIn.m[2][1];
	fOut.tZ.fZ = fIn.m[2][2];
	fOut.tZ.fW = fIn.m[2][3];

	fOut.tW.fX = fIn.m[3][0];
	fOut.tW.fY = fIn.m[3][1];
	fOut.tW.fZ = fIn.m[3][2];
	fOut.tW.fW = fIn.m[3][3];

	return fOut;
}