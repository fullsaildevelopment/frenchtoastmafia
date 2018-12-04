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
	float deltaTime = 0.0f;

	tFloat4x4 dragPos;
	tFloat4x4 playerPos;

	void resolveDragonState(tFloat4x4* _dragPos, tFloat4x4 _playerPos, float _dTime);

private:

	void fire();

	void updatePosition();
	void lookAtPoint();

	AI();
	~AI();
};

