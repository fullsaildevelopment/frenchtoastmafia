/************************************************************************
* Filename:  		Offset_Matrix.cpp (Recreate from Camera)
* Date:      		05/12/2018
* Mod. Date: 		12/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Offset Matrix applies to Headset and Controller to move player's view and hand
*************************************************************************/
#include "Offset_Matrix.h"

cOffset_Matrix::cOffset_Matrix()
{
}

cOffset_Matrix::~cOffset_Matrix()
{
}

void cOffset_Matrix::Initialize()
{
	ResetPosition();
}

void cOffset_Matrix::ResetPosition()
{
	tOffset_Matrix.tX.fX = 1.0f;
	tOffset_Matrix.tX.fY = 0.0f;
	tOffset_Matrix.tX.fZ = 0.0f;
	tOffset_Matrix.tX.fW = 0.0f;
	
	tOffset_Matrix.tY.fX = 0.0f;
	tOffset_Matrix.tY.fY = 1.0f;
	tOffset_Matrix.tY.fZ = 0.0f;
	tOffset_Matrix.tY.fW = 0.0f;
	
	tOffset_Matrix.tZ.fX = 0.0f;
	tOffset_Matrix.tZ.fY = 0.0f;
	tOffset_Matrix.tZ.fZ = 1.0f;
	tOffset_Matrix.tZ.fW = 0.0f;
	
	tOffset_Matrix.tW.fX = 0.0f;
	tOffset_Matrix.tW.fY = 0.0f;
	tOffset_Matrix.tW.fZ = 0.0f;
	tOffset_Matrix.tW.fW = 1.0f;
}

tFloat4 cOffset_Matrix::GetHeading()
{
	return tFloat4{ tOffset_Matrix.tZ.fX, tOffset_Matrix.tZ.fY, tOffset_Matrix.tZ.fZ, tOffset_Matrix.tZ.fW };
}

tFloat4 cOffset_Matrix::GetPosition4()
{
	return tFloat4{ tOffset_Matrix.tW.fX, tOffset_Matrix.tW.fY, tOffset_Matrix.tW.fZ, tOffset_Matrix.tW.fW };
}

tFloat4x4 cOffset_Matrix::GetPosition4x4()
{
	return tOffset_Matrix;
}

void cOffset_Matrix::Update_Offset(double dDelta, tFloat4x4 tHMDPose, tFloat4 fMovement_Vect)
{
	XMFLOAT4X4 xmf_Offset_Matrix = tFloat4x4_to_XMFLOAT4x4(tOffset_Matrix);
	XMMATRIX xmm_Offset_Matrix = XMLoadFloat4x4(&xmf_Offset_Matrix);
	XMMATRIX temp = XMMatrixIdentity();

	float x_move = 0.0f;
	float z_move = 0.0f;

	if (fMovement_Vect.fX == 1.0f)
		z_move = -15.0f;

	if (fMovement_Vect.fY == 1.0f)
		x_move = 15.0f;

	if (fMovement_Vect.fZ == 1.0f)
		z_move = 15.0f;

	if (fMovement_Vect.fW == 1.0f)
		x_move = -15.0f;

	XMMATRIX x_offset = XMMatrixTranslation(tHMDPose.tX.fX * x_move * (float)dDelta, 0.0f, tHMDPose.tX.fZ * x_move * (float)dDelta);
	XMMATRIX z_offset = XMMatrixTranslation(tHMDPose.tZ.fX * z_move * (float)dDelta, 0.0f, tHMDPose.tZ.fZ * z_move * (float)dDelta);

	temp = XMMatrixMultiply(temp, x_offset);
	temp = XMMatrixMultiply(temp, z_offset);

	xmm_Offset_Matrix = XMMatrixMultiply(temp, xmm_Offset_Matrix);

	XMStoreFloat4x4(&xmf_Offset_Matrix, xmm_Offset_Matrix);
	tOffset_Matrix = XMFLOAT4x4_to_tFloat4x4(xmf_Offset_Matrix);
}