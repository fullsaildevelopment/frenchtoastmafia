/************************************************************************
* Filename:  		Camera.cpp
* Date:      		26/10/2018
* Mod. Date: 		03/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Camera Class for Player's View
*************************************************************************/
#include "Camera.h"

cCamera::cCamera()
{
}

cCamera::~cCamera()
{
}

void cCamera::Initialize()
{
	fView_Matrix.tX.fX = 1.0f;
	fView_Matrix.tX.fY = 0.0f;
	fView_Matrix.tX.fZ = 0.0f;
	fView_Matrix.tX.fW = 0.0f;

	fView_Matrix.tY.fX = 0.0f;
	fView_Matrix.tY.fY = 1.0f;
	fView_Matrix.tY.fZ = 0.0f;
	fView_Matrix.tY.fW = 0.0f;

	fView_Matrix.tZ.fX = 0.0f;
	fView_Matrix.tZ.fY = 0.0f;
	fView_Matrix.tZ.fZ = 1.0f;
	fView_Matrix.tZ.fW = 0.0f;

	fView_Matrix.tW.fX = 0.0f;
	fView_Matrix.tW.fY = 0.0f;
	fView_Matrix.tW.fZ = 0.0f;
	fView_Matrix.tW.fW = 1.0f;
}

void cCamera::SetPosition(tFloat4 fPosition)
{
	fView_Matrix.tW.fX = fPosition.fX;
	fView_Matrix.tW.fY = fPosition.fY;
	fView_Matrix.tW.fZ = fPosition.fZ;
}

void cCamera::SetPosition(tFloat4x4 fPosition)
{
	fView_Matrix = fPosition;
}


tFloat4x4 cCamera::GetPosition()
{
	return fView_Matrix;
}

void cCamera::Translation(tFloat4 fMovement_Vect)
{
	XMFLOAT4X4 xm_fView_Matrix = tFloat4x4_to_XMFLOAT4x4(fView_Matrix);
	XMMATRIX mView_Matrix = XMLoadFloat4x4(&xm_fView_Matrix);
	XMMATRIX mTranslation_Matrix = XMMatrixTranslation(fMovement_Vect.fX, fMovement_Vect.fY, fMovement_Vect.fZ);

	if (fMovement_Vect.fW == 0.0f)
		mView_Matrix = XMMatrixMultiply(mTranslation_Matrix, mView_Matrix);
	else
		mView_Matrix = XMMatrixMultiply(mView_Matrix, mTranslation_Matrix);

	XMStoreFloat4x4(&xm_fView_Matrix, mView_Matrix);
	fView_Matrix = XMFLOAT4x4_to_tFloat4x4(xm_fView_Matrix);
}

void cCamera::Rotation(tFloat4 fRotation_Vect)
{
	XMFLOAT4X4 xm_fView_Matrix = tFloat4x4_to_XMFLOAT4x4(fView_Matrix);
	XMMATRIX mView_Matrix = XMLoadFloat4x4(&xm_fView_Matrix);
	XMMATRIX mRotation_Matrix;
	switch ((int)fRotation_Vect.fW)
	{
	case 0:
	{
		mRotation_Matrix = XMMatrixRotationX(fRotation_Vect.fX);
		mView_Matrix = XMMatrixMultiply(mRotation_Matrix, mView_Matrix);
		break;
	}
	case 1:
	{
		mRotation_Matrix = XMMatrixRotationX(fRotation_Vect.fX);
		mView_Matrix = XMMatrixMultiply(mRotation_Matrix, mView_Matrix);
		break;
	}
	case 2:
	{
		mRotation_Matrix = XMMatrixRotationY(fRotation_Vect.fY);

		XMVECTOR vPosition = XMVectorSet(mView_Matrix.r[3].m128_f32[0], mView_Matrix.r[3].m128_f32[1], mView_Matrix.r[3].m128_f32[2], 1.0f);
		mView_Matrix.r[3] = XMVectorSet(0, 0, 0, 1);
		mView_Matrix = XMMatrixMultiply(mView_Matrix, mRotation_Matrix);
		mView_Matrix.r[3] = vPosition;

		break;
	}
	case 3:
	{
		mRotation_Matrix = XMMatrixRotationY(fRotation_Vect.fY);

		XMVECTOR vPosition = XMVectorSet(mView_Matrix.r[3].m128_f32[0], mView_Matrix.r[3].m128_f32[1], mView_Matrix.r[3].m128_f32[2], 1.0f);
		mView_Matrix.r[3] = XMVectorSet(0, 0, 0, 1);
		mView_Matrix = XMMatrixMultiply(mView_Matrix, mRotation_Matrix);
		mView_Matrix.r[3] = vPosition;

		break;
	}
	default:
		break;
	}

	XMStoreFloat4x4(&xm_fView_Matrix, mView_Matrix);
	fView_Matrix = XMFLOAT4x4_to_tFloat4x4(xm_fView_Matrix);
}

void cCamera::Normalize()
{
	XMFLOAT4X4 xm_fView_Matrix = tFloat4x4_to_XMFLOAT4x4(fView_Matrix);
	XMMATRIX mView_Matrix = XMLoadFloat4x4(&xm_fView_Matrix);

	// NORMALIZING ROTATIONS
	XMVECTOR newZ = mView_Matrix.r[2];
	newZ = XMVector3Normalize(newZ);
	XMVECTOR worldY = XMMatrixIdentity().r[1];
	XMVECTOR newX = XMVector3Cross(worldY, newZ);
	newX = XMVector3Normalize(newX);
	XMVECTOR newY = XMVector3Cross(newZ, newX);
	newY = XMVector3Normalize(newY);

	mView_Matrix.r[0] = newX;
	mView_Matrix.r[1] = newY;
	mView_Matrix.r[2] = newZ;

	XMStoreFloat4x4(&xm_fView_Matrix, mView_Matrix);
	fView_Matrix = XMFLOAT4x4_to_tFloat4x4(xm_fView_Matrix);
}

//void cCamera::Update_Offset(double dDelta, tFloat4 fMovement_Vect)
//{
//	if (fMovement_Vect.fX == 1.0f)
//		Translation(tFloat4{ 0.0f, 0.0f, -5.0f * (float)dDelta, 0.0f });
//
//	if (fMovement_Vect.fY == 1.0f)
//		Translation(tFloat4{ 5.0f * (float)dDelta, 0.0f, 0.0f, 1.0f });
//
//	if (fMovement_Vect.fZ == 1.0f)
//		Translation(tFloat4{ 0.0f, 0.0f, 5.0f * (float)dDelta, 0.0f });
//
//	if (fMovement_Vect.fW == 1.0f)
//		Translation(tFloat4{ -5.0f * (float)dDelta, 0.0f, 0.0f, 1.0f });
//}

void cCamera::Update_Offset(double dDelta, tFloat4x4 tHMDPose, tFloat4 fMovement_Vect)
{
	XMFLOAT4X4 xm_fView_Matrix = tFloat4x4_to_XMFLOAT4x4(fView_Matrix);
	XMMATRIX mView_Matrix = XMLoadFloat4x4(&xm_fView_Matrix);
	XMMATRIX temp = XMMatrixIdentity();

	float x_move = 0.0f;
	float z_move = 0.0f;

	if (fMovement_Vect.fX == 1.0f)
		z_move = -5.0f;

	if (fMovement_Vect.fY == 1.0f)
		x_move = 5.0f;

	if (fMovement_Vect.fZ == 1.0f)
		z_move = 5.0f;

	if (fMovement_Vect.fW == 1.0f)
		x_move = -5.0f;

	//XMMATRIX x_offset = XMMatrixTranslation(tHMDPose.tX.fX * x_move * (float)dDelta, 0.0f, tHMDPose.tX.fZ * z_move *  (float)dDelta);
	//XMMATRIX z_offset = XMMatrixTranslation(tHMDPose.tZ.fX * x_move * (float)dDelta, 0.0f, tHMDPose.tZ.fZ * z_move *  (float)dDelta);
	XMMATRIX t_offset = XMMatrixTranslation(x_move * (float)dDelta, 0.0f, z_move *  (float)dDelta);

	//temp = XMMatrixMultiply(temp, x_offset);
	//temp = XMMatrixMultiply(z_offset, temp);
	temp = XMMatrixMultiply(temp, t_offset);

	mView_Matrix = XMMatrixMultiply(mView_Matrix, temp);

	XMStoreFloat4x4(&xm_fView_Matrix, mView_Matrix);
	fView_Matrix = XMFLOAT4x4_to_tFloat4x4(xm_fView_Matrix);
}
