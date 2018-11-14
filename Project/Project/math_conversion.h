/************************************************************************
* Filename:  		Math_Conversion.h
* Date:      		11/10/2018
* Mod. Date: 		08/11/2018
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
#include "Basic_Structs.h"
#include "Matrices.h"

inline XMFLOAT4 tFloat4_to_XMFLOAT4(tFloat4 fIn)
{
	XMFLOAT4 fOut;

	fOut.x = fIn.fX;
	fOut.y = fIn.fY;
	fOut.z = fIn.fZ;
	fOut.w = fIn.fW;

	return fOut;
}

inline tFloat4 XMFLOAT4_to_tFloat4(XMFLOAT4 fIn)
{
	tFloat4 fOut;

	fOut.fX = fIn.x;
	fOut.fY = fIn.y;
	fOut.fZ = fIn.z;
	fOut.fW = fIn.w;

	return fOut;
}

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

inline tFloat4x4 Matrix4_To_tFloat4x4(Matrix4 fIn)
{
	tFloat4x4 fOut;

	fOut.tX.fX = fIn[0];
	fOut.tX.fY = fIn[1];
	fOut.tX.fZ = fIn[2];
	fOut.tX.fW = fIn[3];

	fOut.tY.fX = fIn[4];
	fOut.tY.fY = fIn[5];
	fOut.tY.fZ = fIn[6];
	fOut.tY.fW = fIn[7];

	fOut.tZ.fX = fIn[8];
	fOut.tZ.fY = fIn[9];
	fOut.tZ.fZ = fIn[10];
	fOut.tZ.fW = fIn[11];

	fOut.tW.fX = fIn[12];
	fOut.tW.fY = fIn[13];
	fOut.tW.fZ = fIn[14];
	fOut.tW.fW = fIn[15];

	return fOut;
}

inline tAnimation_Data Create_Inverse_Bind_Pose(tKeyframe tKey)
{
	tAnimation_Data tOutput;
	int nJoint_Size = (int)tKey.tJoints.size();

	for (int i = 0; i < nJoint_Size; i++)
	{
		tFloat4x4 tJoint_Data = tKey.tJoints[i].tData;
		XMFLOAT4X4 xmf_Joint_Data = tFloat4x4_to_XMFLOAT4x4(tJoint_Data);
		XMMATRIX xmm_Joint_Data = XMLoadFloat4x4(&xmf_Joint_Data);
		xmm_Joint_Data = XMMatrixInverse(nullptr, xmm_Joint_Data);
		XMFLOAT4X4 xmf_Out;
		XMStoreFloat4x4(&xmf_Out, xmm_Joint_Data);
		tFloat4x4 tOut = XMFLOAT4x4_to_tFloat4x4(xmf_Out);
		tOutput.tInverse[i] = tOut;
	}

	return tOutput;
}

inline tFloat4 Joint_Position_Lerp(tFloat3 prev, tFloat3 next, float ratio)
{
	tFloat4 tOut;
	// (B - A) * R + A
	tOut.fX = (next.fX - prev.fX) * ratio + prev.fX;
	tOut.fY = (next.fY - prev.fY) * ratio + prev.fY;
	tOut.fZ = (next.fZ - prev.fZ) * ratio + prev.fZ;
	tOut.fW = 1;

	return tOut;
}
