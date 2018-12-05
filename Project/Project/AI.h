#pragma once
#include "basic_structs.h"
#include "Renderer_Structs.h"

class AI
{
public:

	bool alive = true;
	bool aggro = false;
	bool lookingAtPlayer = false;

	int HP = 3;
	float speed = 5.0f;

	tFloat4x4 dragPos;
	tFloat4x4 playerPos;

	void resolveDragonState(tScene_Objects* tObject_List, double _dTime);

	AI();
	~AI();

private:

	tFloat4x4 dragonPos;
	tFloat4x4 playerPos;
	float deltaTime = 0.0f;

	void fire();

	float calcDist(tFloat4x4 _dragonPos, tFloat4x4 _playerPos);
	void updatePosition();
	void lookAtPoint();
};

