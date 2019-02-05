#pragma once
#include "basic_structs.h"
#include "Renderer_Structs.h"
#include "Matrices.h"
#include "math_conversion.h"
#include "Base_Spell.h"
#include "dopeSoundSystem.h"

class AI
{
public:

	bool dragAlive = true;
	bool aggro = false;
	bool lookingAtPlayer = false;

	float speed = 5.0f;

	dopeSoundSystem sound;

	void resolveDragonState(tScene_Objects* tObject_List, tFloat4x4 _playerPos, double _dTime, cBase_Spell* _spell);
	void setIsHit(bool _set);
	bool getIsHit();

	void setIsHitIce(bool _set);
	bool getIsHitIce();

	int getHP();
	void resetHP();

	float getSpeed();

	AI();
	~AI();

private:

	int dragHP = 5;

	//tFloat4x4 dragonPos;
	tFloat4x4 dragonMouthPos;

	tFloat4x4 playerPos;
	float deltaTime = 0.0f;
	float moveTimer = 2.0f;

	float xMove = 5.0f;
	float yMove = 0.0f;
	float zMove = 0.0f;

	float dragSpeed = 10.0f;

	bool isHit = false;
	bool isHitIce = false;

	float freezeTime = 3.5f;
	float freezeCountdown = 0.0f;

	void fire();

	float calcDist(tFloat4x4 _dragonPos, tFloat4x4 _playerPos);
	void updatePosition();
	void lookAtPoint();
	XMMATRIX lookAtMatrix(XMMATRIX _viewer, XMMATRIX _target);
	XMMATRIX dragonLookAtMatrix(XMMATRIX _viewer, XMMATRIX _target);
};

