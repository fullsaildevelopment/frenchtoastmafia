#include "Camera.h"

cCamera::cCamera()
{
}


cCamera::~cCamera()
{
}

void cCamera::SetPostion(tFloat4x4 fPosition)
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

	if (fMovement_Vect.fW == 0)
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
