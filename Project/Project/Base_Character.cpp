/************************************************************************
* Filename:  		Base_Character.cpp
* Date:      		05/10/2018
* Mod. Date: 		12/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Base Character Module to be inherit by Player and AI
*************************************************************************/
#include "Base_Character.h"

cBase_Character::cBase_Character()
{
	m_tPosition = {
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				  };
}


cBase_Character::~cBase_Character()
{
}


/***************
* Accessors
***************/

bool cBase_Character::getIsAlive()
{
	return m_bIsAlive;
}

int cBase_Character::getHealth()
{
	return m_nHealth;
}

bool cBase_Character::getIsMovable()
{
	return m_bIsMovable;
}

bool cBase_Character::getIsGrounded()
{
	return m_bIsGrounded;
}

bool cBase_Character::getIsCasting()
{
	return m_bIsCasting;
}

bool cBase_Character::getIsCharging()
{
	return m_bIsCharging;
}

tFloat4 cBase_Character::getPosition4()
{
	return m_tPosition.tW;
}

tFloat4x4 cBase_Character::getPosition4x4()
{
	return m_tPosition;
}

tFloat4 cBase_Character::getHeading()
{
	return m_tHeading;
}


/***************
* Mutators
***************/

void cBase_Character::setIsAlive(bool bAlive)
{
	m_bIsAlive = bAlive;
}

void cBase_Character::setHealth(int change)
{
	m_nHealth += change;
}

void cBase_Character::resetHealth()
{
	m_nHealth = 100;
}

void cBase_Character::setIsMovable(bool bMovable)
{
	m_bIsMovable = bMovable;
}

void cBase_Character::setIsGrounded(bool bGrounded)
{
	m_bIsGrounded = bGrounded;
}

void cBase_Character::setIsCasting(bool bCasting)
{
	m_bIsCasting = bCasting;
}

void cBase_Character::setIsCharging(bool bCharging)
{
	m_bIsCharging = bCharging;
}

void cBase_Character::setPosition4(tFloat4 tPosition)
{
	m_tPosition.tW = tPosition;
}

void cBase_Character::setPosition4x4(tFloat4x4 tPosition)
{
	m_tPosition = tPosition;
}

void cBase_Character::setHeading(tFloat4 tHeading)
{
	m_tHeading = tHeading;
}


//tFloat4x4 cBase_Character::getPosition4x4()
//{
//	tFloat4x4 temp
//		=
//	{
//		1, 0, 0, 0,
//		0, 1, 0, 0,
//		0, 0, 1, 0,
//		0, 0, 0, 1
//	};
//
//	return temp;
//}
