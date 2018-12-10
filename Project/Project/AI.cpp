#include "AI.h"



AI::AI()
{
}


AI::~AI()
{
}

void AI::resolveDragonState(tScene_Objects* tObject_List, tFloat4x4 _playerPos, double _dTime)
{
	//dragonPos = tObject_List->fWorld_Matrix[2];
	//playerPos = Matrix4_To_tFloat4x4(_playerPos);
	XMMATRIX playerPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(_playerPos));

	if (!aggro)
	{
		//float dist = calcDist(tObject_List->fWorld_Matrix[2], playerPos);
		//if (dist < 20)
		//{
		//	aggro = true;
		//}

		if (playerPos.tW.fX < -5)
		{
			aggro = true;
		}
	}

	if(aggro)
	{
		//moveTimer += _dTime;
		//if (moveTimer >= 4.0f)
		//{
		//	moveTimer = 0.0f;
		//	xMove *= -1;
		//}

		if (tObject_List->fWorld_Matrix[2].tW.fZ > 10.0f)
		{
			xMove = -5;
		}

		if (tObject_List->fWorld_Matrix[2].tW.fZ < -10.0f)
		{
			xMove = 5;
		}

		if (tObject_List->dragHP != 4)
		{
			XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[2]));
			XMMATRIX moveMat = XMMatrixTranslation(0.0f, 0.0f, dragSpeed * xMove * _dTime);

			//XMMATRIX newPosMat = dragonLookAtMatrix(XMMatrixMultiply(moveMat, oldPosMat), playerPosMat);
			XMMATRIX newPosMat = XMMatrixMultiply(moveMat, oldPosMat);


			XMFLOAT4X4 newPos4x4;
			XMStoreFloat4x4(&newPos4x4, newPosMat);
			tObject_List->fWorld_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);
		}

		//projectile stuff

		//if (tObject_List->fWorld_Matrix[3].tW.fX >= -1 || tObject_List->fWorld_Matrix[3].tW.fY < -1)
		if (tObject_List->fWorld_Matrix[3].tW.fY < -5)
		{
			tObject_List->fWorld_Matrix[3].tW.fX = tObject_List->fWorld_Matrix[2].tW.fX + 10;
			tObject_List->fWorld_Matrix[3].tW.fY = tObject_List->fWorld_Matrix[2].tW.fY;
			tObject_List->fWorld_Matrix[3].tW.fZ = tObject_List->fWorld_Matrix[2].tW.fZ;
			tObject_List->fWorld_Matrix[3].tW.fY += 9;

			XMMATRIX oldProjPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[3]));
			XMMATRIX newProjPosMat = lookAtMatrix(oldProjPosMat, playerPosMat);
			XMFLOAT4X4 newProjPos4x4;
			XMStoreFloat4x4(&newProjPos4x4, newProjPosMat);
			tObject_List->fWorld_Matrix[3] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4);
			



		}


		if (tObject_List->dragHP != 4)
		{
			if (tObject_List->dragHP == 3)
			{
				XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[3]));
				XMMATRIX moveMat = XMMatrixTranslation(0.0f, 0.0f, 1.0f);

				XMMATRIX newPosMat = XMMatrixMultiply(moveMat, oldPosMat);
				XMFLOAT4X4 newPos4x4;
				XMStoreFloat4x4(&newPos4x4, newPosMat);
				tObject_List->fWorld_Matrix[3] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);
			}
			else if(tObject_List->dragHP == 2)
			{
				dragSpeed = 2.0f;
				XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[3]));
				XMMATRIX moveMat = XMMatrixTranslation(0.0f, 0.0f, 2.0f);

				XMMATRIX newPosMat = XMMatrixMultiply(moveMat, oldPosMat);
				XMFLOAT4X4 newPos4x4;
				XMStoreFloat4x4(&newPos4x4, newPosMat);
				tObject_List->fWorld_Matrix[3] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);
			}
			else if (tObject_List->dragHP == 1)
			{
				dragSpeed = 3.0f;
				XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[3]));
				XMMATRIX moveMat = XMMatrixTranslation(0.0f, 0.0f, 3.0f);

				XMMATRIX newPosMat = XMMatrixMultiply(moveMat, oldPosMat);
				XMFLOAT4X4 newPos4x4;
				XMStoreFloat4x4(&newPos4x4, newPosMat);
				tObject_List->fWorld_Matrix[3] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);
			}
		}

	}

}

void AI::fire()
{

}

float AI::calcDist(tFloat4x4 _dragonPos, tFloat4x4 _playerPos)
{
	return 10.0f;
}

void AI::updatePosition()
{

}

void AI::lookAtPoint()
{

}

XMMATRIX AI::lookAtMatrix(XMMATRIX _viewer, XMMATRIX _target)
{
	XMVECTOR up = { 0,1,0 };

	XMVECTOR newX;
	XMVECTOR newY;
	XMVECTOR newZ = XMVector3Normalize(_target.r[3] - _viewer.r[3]);
	XMVECTOR newP = _viewer.r[3];

	newX = XMVector3Cross(up, newZ);
	newY = XMVector3Cross(newZ, newX);

	XMMATRIX ret =
	{
		newX.m128_f32[0], newX.m128_f32[1], newX.m128_f32[2], 0,
		newY.m128_f32[0], newY.m128_f32[1], newY.m128_f32[2], 0,
		newZ.m128_f32[0], newZ.m128_f32[1], newZ.m128_f32[2], 0,
		newP.m128_f32[0], newP.m128_f32[1], newP.m128_f32[2], 1,
	};
	return ret;

}

XMMATRIX AI::dragonLookAtMatrix(XMMATRIX _viewer, XMMATRIX _target)
{
	XMVECTOR up = { 0,1,0 };

	XMVECTOR newX;
	XMVECTOR newY;
	XMVECTOR newZ = XMVector3Normalize(_target.r[3] - _viewer.r[3]);
	XMVECTOR newP = _viewer.r[3];

	newX = XMVector3Cross(up, newZ);
	newY = XMVector3Cross(newZ, newX);

	XMMATRIX ret =
	{
		newX.m128_f32[0], newX.m128_f32[1], newX.m128_f32[2], 0,
		newY.m128_f32[0], newY.m128_f32[1], newY.m128_f32[2], 0,
		newZ.m128_f32[0], newZ.m128_f32[1], newZ.m128_f32[2], 0,
		newP.m128_f32[0], newP.m128_f32[1], newP.m128_f32[2], 1,
	};

	ret = XMMatrixMultiply(XMMatrixRotationY(-3.14/2), ret);

	return ret;

}