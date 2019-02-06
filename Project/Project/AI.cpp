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
	if (isHitIce)
	{
		freezeCountdown = freezeTime;
	}
	if (freezeCountdown > 0.01f)
	{
		freezeCountdown -= _dTime;
	}
	if (freezeCountdown <= 0.01f)
	{
		freezeCountdown = 0.0f;
	}
	if (freezeCountdown > 0.0f)
	{
		dragSpeed = 5.0f;
	}
	else
	{
		dragSpeed = 10.0f;
	}

	XMMATRIX playerPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(_playerPos));

	if (!aggro)
	{
		//float dist = calcDist(tObject_List->fWorld_Matrix[2], playerPos);
		//if (dist < 20)
		//{
		//	aggro = true;
		//}

		if (dragHP < 5)
		{
			aggro = true;
		}
	}

	if (aggro)
	{
		//moveTimer += _dTime;
		//if (moveTimer >= 4.0f)
		//{
		//	moveTimer = 0.0f;
		//	xMove *= -1;
		//}

		if (tObject_List->fWorld_Matrix[2].tW.fZ > 100.0f)
		{
			xMove = 200 * _dTime;
		}

		if (tObject_List->fWorld_Matrix[2].tW.fZ < -100.0f)
		{
			xMove = -200 * _dTime;
		}

		if (dragHP < 5)
		{
			XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fWorld_Matrix[2]));

			XMMATRIX moveMat;
			if (dragHP > 0)
			{
				moveMat = XMMatrixTranslation(dragSpeed * xMove * _dTime, 0.0f, 0.0f);
			}
			else
			{
				moveMat = XMMatrixTranslation(0, 0.0f, 0.0f);
				tObject_List->currAnim[2] = 3;
			}

			if (dragHP < 3 && tObject_List->fWorld_Matrix[2].tW.fY < 60)
			{
				moveMat = XMMatrixMultiply(XMMatrixTranslation(0.0f, 50.0f * _dTime, 0.0f), moveMat);
			}

			XMMATRIX centerMat = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

			//XMMATRIX moveMat = XMMatrixIdentity();

			XMMATRIX newPosMat = lookAtMatrix(oldPosMat, centerMat);

			newPosMat = XMMatrixMultiply(moveMat, newPosMat);

			newPosMat = lookAtMatrix(newPosMat, playerPosMat);

			//XMMATRIX newPosMat = lookAtMatrix(XMMatrixMultiply(moveMat, oldPosMat), playerPosMat);

			newPosMat = XMMatrixMultiply(XMMatrixRotationX(3.14 / 5), newPosMat);

			float test = newPosMat.r[3].m128_f32[0];
			if (test < -155)
			{
				//newPosMat = XMMatrixMultiply(XMMatrixTranslation(10.0f, 0.0f, 0.0f), newPosMat);
				newPosMat.r[3].m128_f32[0] += 5;
			}

			XMFLOAT4X4 newPos4x4;
			XMStoreFloat4x4(&newPos4x4, newPosMat);
			tObject_List->fWorld_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);

			if (tObject_List->fFireballs_Alive == 0 && dragHP >= 3 && tObject_List->currAnim[2] != 1)
			{
				tObject_List->fFireballs_Alive = 3;

				tObject_List->fFireball_State[0] = true;
				tObject_List->fFireball_State[1] = true;
				tObject_List->fFireball_State[2] = true;

				sound.playSoundEffect("Fireball+1.mp3", FMOD_DEFAULT, 0.5f);
				_spell->setIsActive(true);
				tObject_List->fFireball_Matrix[0] = tObject_List->fWorld_Matrix[2];

				XMMATRIX oldProjPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fFireball_Matrix[0]));

				oldProjPosMat = XMMatrixMultiply(XMMatrixTranslation(0, 50, 0), oldProjPosMat);
				//oldProjPosMat = XMMatrixMultiply(XMMatrixTranslation(0, 0, 70), oldProjPosMat);
				//oldProjPosMat = XMMatrixMultiply(XMMatrixTranslation(2, 0, 0), oldProjPosMat);

				XMMATRIX newProjPosMat = lookAtMatrix(oldProjPosMat, playerPosMat);
				XMMATRIX newProjPosMat2 = XMMatrixMultiply(XMMatrixTranslation(10, 0, 0), newProjPosMat);
				XMMATRIX newProjPosMat3 = XMMatrixMultiply(XMMatrixTranslation(-10, 0, 0), newProjPosMat);


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
			else if (tObject_List->fFireballs_Alive == 0 && dragHP <= 2 && tObject_List->currAnim[2] != 1)
			{
				tObject_List->fFireballs_Alive = 9;

				for (int l = 0; l < tObject_List->fFireballs_Alive; l++)
				{
					tObject_List->fFireball_State[l] = true;
				}

				sound.playSoundEffect("Fireball+1.mp3", FMOD_DEFAULT, 0.5f);
				_spell->setIsActive(true);

				tObject_List->fFireball_Matrix[0] = _playerPos;
				XMMATRIX oldProjPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fFireball_Matrix[0]));

				oldProjPosMat = XMMatrixMultiply(oldProjPosMat, XMMatrixTranslation(-100, 300, 0));

				int modNum = 100;
				int addNum = 5;


				XMMATRIX newProjPosMat = lookAtMatrix(oldProjPosMat, playerPosMat);
				XMMATRIX newProjPosMat2 = XMMatrixMultiply(XMMatrixTranslation((rand() % modNum) + addNum, 0, 0), newProjPosMat);
				XMMATRIX newProjPosMat3 = XMMatrixMultiply(XMMatrixTranslation(((rand() % modNum) + addNum) * -1, 0, 0), newProjPosMat);
				XMMATRIX newProjPosMat4 = XMMatrixMultiply(XMMatrixTranslation(0, 0, (rand() % modNum) + addNum), newProjPosMat);
				XMMATRIX newProjPosMat5 = XMMatrixMultiply(XMMatrixTranslation(0, 0, ((rand() % modNum) + addNum) * -1), newProjPosMat);

				XMMATRIX newProjPosMat6 = XMMatrixMultiply(XMMatrixTranslation((rand() % modNum) + addNum, 0, (rand() % modNum) + addNum), newProjPosMat);
				XMMATRIX newProjPosMat7 = XMMatrixMultiply(XMMatrixTranslation((rand() % modNum) + addNum, 0, ((rand() % modNum) + addNum) * -1), newProjPosMat);
				XMMATRIX newProjPosMat8 = XMMatrixMultiply(XMMatrixTranslation(((rand() % modNum) + addNum) * -1, 0, (rand() % modNum) + addNum), newProjPosMat);
				XMMATRIX newProjPosMat9 = XMMatrixMultiply(XMMatrixTranslation(((rand() % modNum) + addNum) * -1, 0, ((rand() % modNum) + addNum) * -1), newProjPosMat);

				XMFLOAT4X4 newProjPos4x4;
				XMStoreFloat4x4(&newProjPos4x4, newProjPosMat);
				tObject_List->fFireball_Matrix[0] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4);

				XMFLOAT4X4 newProjPos4x4_2;
				XMStoreFloat4x4(&newProjPos4x4_2, newProjPosMat2);
				tObject_List->fFireball_Matrix[1] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4_2);

				XMFLOAT4X4 newProjPos4x4_3;
				XMStoreFloat4x4(&newProjPos4x4_3, newProjPosMat3);
				tObject_List->fFireball_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4_3);

				XMFLOAT4X4 newProjPos4x4_4;
				XMStoreFloat4x4(&newProjPos4x4_4, newProjPosMat4);
				tObject_List->fFireball_Matrix[3] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4_4);

				XMFLOAT4X4 newProjPos4x4_5;
				XMStoreFloat4x4(&newProjPos4x4_5, newProjPosMat5);
				tObject_List->fFireball_Matrix[4] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4_5);

				XMFLOAT4X4 newProjPos4x4_6;
				XMStoreFloat4x4(&newProjPos4x4_6, newProjPosMat6);
				tObject_List->fFireball_Matrix[5] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4_6);

				XMFLOAT4X4 newProjPos4x4_7;
				XMStoreFloat4x4(&newProjPos4x4_7, newProjPosMat7);
				tObject_List->fFireball_Matrix[6] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4_7);

				XMFLOAT4X4 newProjPos4x4_8;
				XMStoreFloat4x4(&newProjPos4x4_8, newProjPosMat8);
				tObject_List->fFireball_Matrix[7] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4_8);

				XMFLOAT4X4 newProjPos4x4_9;
				XMStoreFloat4x4(&newProjPos4x4_9, newProjPosMat9);
				tObject_List->fFireball_Matrix[8] = XMFLOAT4x4_to_tFloat4x4(newProjPos4x4_9);

				for (int k = 0; k < tObject_List->fFireballs_Alive; k++)
				{
					tObject_List->fAlert_Matrix[k] = tObject_List->fFireball_Matrix[k];
					tObject_List->fAlert_Matrix[k].tW.fY = -2.5;
					tObject_List->fAlert_Matrix[k].tW.fX += 100;

					tObject_List->fAlert_Matrix[k].tX.fXYZ = { 1, 0, 0 };
					tObject_List->fAlert_Matrix[k].tY.fXYZ = { 0, 1, 0 };
					tObject_List->fAlert_Matrix[k].tZ.fXYZ = { 0, 0, 1 };
				}

			}

		}

		//projectile stuff


		if (dragHP <= 5)
		{
			if (dragHP > 3)
			{
				for (int i = 0; i < tObject_List->maxFireballs; i++)
				{
					XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fFireball_Matrix[i]));
					XMMATRIX moveMat = XMMatrixTranslation(0.0f, 0.0f, 200.0f * _dTime);

					XMMATRIX newPosMat = XMMatrixMultiply(moveMat, oldPosMat);
					XMFLOAT4X4 newPos4x4;
					XMStoreFloat4x4(&newPos4x4, newPosMat);
					tObject_List->fFireball_Matrix[i] = XMFLOAT4x4_to_tFloat4x4(newPos4x4);
				}
			}
			else if (dragHP == 3)
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
			else if (dragHP == 2)
			{
				for (int i = 0; i < tObject_List->maxFireballs; i++)
				{
					XMMATRIX oldPosMat = XMLoadFloat4x4(&tFloat4x4_to_XMFLOAT4x4(tObject_List->fFireball_Matrix[i]));
					XMMATRIX moveMat = XMMatrixTranslation(0.0f, 0.0f, 100.0f * _dTime);

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
					XMMATRIX moveMat = XMMatrixTranslation(0.0f, 0.0f, 150.0f * _dTime);

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

	ret = XMMatrixMultiply(XMMatrixRotationY(-3.14 / 2), ret);

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

void AI::setIsHitIce(bool _set)
{
	isHitIce = _set;
}

bool AI::getIsHitIce()
{
	return isHitIce;
}

int AI::getHP()
{
	return dragHP;
}

void AI::resetHP()
{
	dragHP = 5;
	aggro = false;
}

float AI::getSpeed()
{
	return dragSpeed;
}