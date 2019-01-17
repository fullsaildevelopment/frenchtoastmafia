#include "AI.h"



AI::AI()
{
}


AI::~AI()
{
}

void AI::resolveDragonState(tScene_Objects* tObject_List, tFloat4x4 _playerPos, double _dTime, cBase_Spell* _spell)
{
	//dragonPos = tObject_List->fWorld_Matrix[2];
	//playerPos = Matrix4_To_tFloat4x4(_playerPos);
	if (isHit)
	{
		dragHP -= 1;
		//aggro = true;
	}

	XMMATRIX playerPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(_playerPos));

	if (!aggro)
	{
		//float dist = calcDist(tObject_List->fWorld_Matrix[2], playerPos);
		//if (dist < 20)
		//{
		//	aggro = true;
		//}

		if (dragHP < 4)
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

		if (tObject_List->fWorld_Matrix[2].tW.fZ > 50.0f)
		{
			xMove = 5;
		}

		if (tObject_List->fWorld_Matrix[2].tW.fZ < -50.0f)
		{
			xMove = -5;
		}

		if (dragHP != 4)
		{
			XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[2]));
			XMMATRIX moveMat = XMMatrixTranslation(dragSpeed * xMove * _dTime, 0.0f, 0.0f);
			//XMMATRIX moveMat = XMMatrixIdentity();

			XMMATRIX newPosMat = lookAtMatrix(XMMatrixMultiply(moveMat, oldPosMat), playerPosMat);

			newPosMat = XMMatrixMultiply(XMMatrixRotationX(3.14 / 5), newPosMat);

			XMFLOAT4X4 newPos4x4;
			XMStoreFloat4x4(&newPos4x4, newPosMat);
			tObject_List->fWorld_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);

			if (tObject_List->fFireballs_Alive == 0)
			{
				tObject_List->fFireballs_Alive = 3;

				tObject_List->fFireball_State[0] = true;
				tObject_List->fFireball_State[1] = true;
				tObject_List->fFireball_State[2] = true;

				sound.playSoundEffect("Fireball+1.mp3", FMOD_DEFAULT, 0.5f);
				_spell->setIsActive(true);
				tObject_List->fFireball_Matrix[0] = tObject_List->fWorld_Matrix[2];

				XMMATRIX oldProjPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fFireball_Matrix[0]));

				oldProjPosMat = XMMatrixMultiply(XMMatrixTranslation(0, 200, 0), oldProjPosMat);
				oldProjPosMat = XMMatrixMultiply(XMMatrixTranslation(0, 0, 70), oldProjPosMat);
				oldProjPosMat = XMMatrixMultiply(XMMatrixTranslation(2, 0, 0), oldProjPosMat);

				XMMATRIX newProjPosMat = lookAtMatrix(oldProjPosMat, playerPosMat);
				XMMATRIX newProjPosMat2 = XMMatrixMultiply(XMMatrixTranslation(5, 0, 0), newProjPosMat);
				XMMATRIX newProjPosMat3 = XMMatrixMultiply(XMMatrixTranslation(-5, 0, 0), newProjPosMat);


				XMFLOAT4X4 newProjPos4x4;
				XMStoreFloat4x4(&newProjPos4x4, newProjPosMat);
				tObject_List->fFireball_Matrix[0] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4);

				XMFLOAT4X4 newProjPos4x4_2;
				XMStoreFloat4x4(&newProjPos4x4_2, newProjPosMat2);
				tObject_List->fFireball_Matrix[1] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4_2);

				XMFLOAT4X4 newProjPos4x4_3;
				XMStoreFloat4x4(&newProjPos4x4_3, newProjPosMat3);
				tObject_List->fFireball_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4_3);

			}

		}

		//projectile stuff


		if (dragHP <= 3)
		{
			if (dragHP == 3)
			{
				for (int i = 0; i < tObject_List->maxFireballs; i++)
				{
					XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fFireball_Matrix[i]));
					XMMATRIX moveMat = XMMatrixTranslation(0.0f, 0.0f, 250.0f * _dTime);

					XMMATRIX newPosMat = XMMatrixMultiply(moveMat, oldPosMat);
					XMFLOAT4X4 newPos4x4;
					XMStoreFloat4x4(&newPos4x4, newPosMat);
					tObject_List->fFireball_Matrix[i] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);
				}
			}
			else if(dragHP == 2)
			{
				for (int i = 0; i < tObject_List->maxFireballs; i++)
				{
					XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fFireball_Matrix[i]));
					XMMATRIX moveMat = XMMatrixTranslation(0.0f, 0.0f, 350.0f * _dTime);

					XMMATRIX newPosMat = XMMatrixMultiply(moveMat, oldPosMat);
					XMFLOAT4X4 newPos4x4;
					XMStoreFloat4x4(&newPos4x4, newPosMat);
					tObject_List->fFireball_Matrix[i] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);
				}
			}
			else if (dragHP == 1)
			{
				for (int i = 0; i < tObject_List->maxFireballs; i++)
				{
					XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fFireball_Matrix[i]));
					XMMATRIX moveMat = XMMatrixTranslation(0.0f, 0.0f, 450.0f * _dTime);

					XMMATRIX newPosMat = XMMatrixMultiply(moveMat, oldPosMat);
					XMFLOAT4X4 newPos4x4;
					XMStoreFloat4x4(&newPos4x4, newPosMat);
					tObject_List->fFireball_Matrix[i] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);
				}
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

void AI::setIsHit(bool _set)
{
	isHit = _set;
}

bool AI::getIsHit()
{
	return isHit;
}

int AI::getHP()
{
	return dragHP;
}

void AI::resetHP()
{
	dragHP = 4;
	aggro = false;
}