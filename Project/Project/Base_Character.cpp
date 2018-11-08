/************************************************************************
* Filename:  		Base_Character.cpp
* Date:      		05/10/2018
* Mod. Date: 		09/10/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Base Character Module to be inherit by Player and AI
*************************************************************************/
#include "Base_Character.h"

Base_Character::Base_Character()
{
}


Base_Character::~Base_Character()
{
}


/***************
* Accessors
***************/

bool Base_Character::getIsAlive()
{
	return m_bIsAlive;
}

bool Base_Character::getIsMovable()
{
	return m_bIsMovable;
}

bool Base_Character::getIsGrounded()
{
	return m_bIsGrounded;
}

bool Base_Character::getIsCasting()
{
	return m_bIsCasting;
}

bool Base_Character::getIsCharging()
{
	return m_bIsCharging;
}

tFloat4 Base_Character::getPosition()
{
	return m_tPosition;
}

tFloat4 Base_Character::getHeading()
{
	return m_tHeading;
}


/***************
* Mutators
***************/

void Base_Character::setIsAlive(bool bAlive)
{
	m_bIsAlive = bAlive;
}

void Base_Character::setIsMovable(bool bMovable)
{
	m_bIsMovable = bMovable;
}

void Base_Character::setIsGrounded(bool bGrounded)
{
	m_bIsGrounded = bGrounded;
}

void Base_Character::setIsCasting(bool bCasting)
{
	m_bIsCasting = bCasting;
}

void Base_Character::setIsCharging(bool bCharging)
{
	m_bIsCharging = bCharging;
}

void Base_Character::setPosition(tFloat4 tPosition)
{
	m_tPosition = tPosition;
}

void Base_Character::setHeading(tFloat4 tHeading)
{
	m_tHeading = tHeading;
}

