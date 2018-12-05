#include "AI.h"



AI::AI()
{
}


AI::~AI()
{
}

void AI::resolveDragonState(tScene_Objects* tObject_List, double _dTime)
{
	dragonPos = tObject_List->fWorld_Matrix[2];

	if (!aggro)
	{
		if (calcDist(dragonPos, playerPos) < 20)
		{
			aggro = true;
		}
	}
	else
	{

	}

}

void AI::fire()
{

}

float AI::calcDist(tFloat4x4 _dragonPos, tFloat4x4 _playerPos)
{

}

void AI::updatePosition()
{

}

void AI::lookAtPoint()
{

}
