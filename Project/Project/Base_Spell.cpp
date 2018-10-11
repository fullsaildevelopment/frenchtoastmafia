/************************************************************************
* Filename:  		Base_Spell.cpp
* Date:      		10/05/2018
* Mod. Date: 		10/09/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Base Spell Module to be inherit by various specific spell
*************************************************************************/
#include "Base_Spell.h"



Base_Spell::Base_Spell()
{
}


Base_Spell::~Base_Spell()
{
}

int Base_Spell::getSpellId()
{
	return m_nSpell_Id;
}

bool Base_Spell::getIsActive()
{
	return m_bIsActive;
}

tFloat4 Base_Spell::getPosition()
{
	return m_tPosition;
}

tFloat4 Base_Spell::getHeading()
{
	return m_tHeading;
}

void Base_Spell::setSpellId(int nSpellId)
{
	m_nSpell_Id = nSpellId;
}

void Base_Spell::setIsActive(bool bActive)
{
	m_bIsActive = bActive;
}

void Base_Spell::setPosition(tFloat4 tPosition)
{
	m_tPosition = tPosition;
}

void Base_Spell::setHeading(tFloat4 tHeading)
{
	m_tHeading = tHeading;
}
