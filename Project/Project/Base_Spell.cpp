/************************************************************************
* Filename:  		Base_Spell.cpp
* Date:      		05/10/2018
* Mod. Date: 		11/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Base Spell Module to be inherit by various specific spell
*************************************************************************/
#include "Base_Spell.h"



cBase_Spell::cBase_Spell()
{
}


cBase_Spell::~cBase_Spell()
{
}

int cBase_Spell::getSpellId()
{
	return m_nSpell_Id;
}

bool cBase_Spell::getIsActive()
{
	return m_bIsActive;
}

tFloat4 cBase_Spell::getPosition()
{
	return m_tPosition;
}

tFloat4 cBase_Spell::getHeading()
{
	return m_tHeading;
}

void cBase_Spell::setSpellId(int nSpellId)
{
	m_nSpell_Id = nSpellId;
}

void cBase_Spell::setIsActive(bool bActive)
{
	m_bIsActive = bActive;
}

void cBase_Spell::setPosition(tFloat4 tPosition)
{
	m_tPosition = tPosition;
}

void cBase_Spell::setHeading(tFloat4 tHeading)
{
	m_tHeading = tHeading;
}
