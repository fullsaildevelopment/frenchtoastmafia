#pragma once
#include "basic_structs.h"
#include "Renderer_Structs.h"
#include "Matrices.h"
#include "math_conversion.h"

class AI
{
public:

	bool alive = true;
	bool aggro = false;
	bool lookingAtPlayer = false;

	int HP = 3;
	float speed = 5.0f;

	void resolveDragonState(tScene_Objects* tObject_List, Matrix4 _playerPos, double _dTime);

	AI();
	~AI();

private:

	tFloat4x4 dragonPos;
	tFloat4x4 dragonMouthPos;

	tFloat4x4 playerPos;
	float deltaTime = 0.0f;
	float moveTimer = 2.0f;

	float xMove = 1.0f;
	float yMove = 0.0f;
	float zMove = 0.0f;

	float projectileTimer = 0.0f;

	void fire();

	float calcDist(tFloat4x4 _dragonPos, tFloat4x4 _playerPos);
	void updatePosition();
	void lookAtPoint();
};

