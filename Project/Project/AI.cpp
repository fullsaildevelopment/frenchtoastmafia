#include "AI.h"



AI::AI()
{
}


AI::~AI()
{
}

void AI::resolveDragonState(tScene_Objects* tObject_List, Matrix4 _playerPos, double _dTime)
{
	dragonPos = tObject_List->fWorld_Matrix[2];
	playerPos = Matrix4_To_tFloat4x4(_playerPos);

	if (!aggro)
	{
		if (calcDist(dragonPos, playerPos) < 20)
		{
			aggro = true;
		}
	}

	if(aggro)
	{
		moveTimer += _dTime;
		if (moveTimer >= 2.0f)
		{
			moveTimer = 0.0f;
			xMove *= -1;
		}

		XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(dragonPos));
		XMMATRIX moveMat = XMMatrixTranslation(xMove, 0.0f, 0.0f);

		XMMATRIX newPosMat = XMMatrixMultiply(moveMat, oldPosMat);
		XMFLOAT4X4 newPos4x4;
		XMStoreFloat4x4(&newPos4x4, newPosMat);
		tObject_List->fWorld_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);

		//projectile stuff
		//projectileTimer += _dTime;
		//if (projectileTimer >= 3.0)
		//{
		//	projectileTimer = 0.0f;
		//
		//
		//}


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
