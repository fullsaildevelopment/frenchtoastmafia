/************************************************************************
* Filename:  		Base_Spell.h
* Date:      		05/10/2018
* Mod. Date: 		09/10/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Base Spell Module to be inherit by various specific spell
*************************************************************************/
#pragma once
#include "basic_structs.h"

class Base_Spell
{
private:
	// Gameplay Data
	int m_nSpell_Id;
	//int m_nSpell_Type;
	//int m_nSpell_Attributes;
	//int m_nPerfect_Count;

	// Core Game Data
	bool m_bIsActive = false;
	// bool m_bIsSpawning = false;
	// bool m_bIsRunning = false;
	// bool m_bIsDying = false;

	// Movement
	tFloat4 m_tPosition;
	tFloat4 m_tHeading;
	//float m_fVelocity;

public:
	Base_Spell();
	~Base_Spell();

	/***************
	* Accessors
	***************/
	/*****************************************************************
	* getIsAlive():      Get the spell's id
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     int
	*
	* Mod. Date:		 10/09/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	int getSpellId();
	/*****************************************************************
	* getIsActive():      Check is the spell is active
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     bool
	*
	* Mod. Date:		 10/09/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	bool getIsActive();
	/*****************************************************************
	* getPosition():     Get the spell's current position
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     tFloat4 (float4 structure, see basic_structs.h for detail)
	*
	* Mod. Date:		 10/09/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	tFloat4 getPosition();
	/*****************************************************************
	* getHeading():      Get the spell's current heading
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     tFloat4 (float4 structure, see basic_structs.h for detail)
	*
	* Mod. Date:		 10/09/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	tFloat4 getHeading();


	/***************
	* Mutators
	***************/
	/*****************************************************************
	* getPosition():     Set the spell's id
	*
	* Ins:			     nSpellId
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 10/09/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setSpellId(int nSpellId);
	/*****************************************************************
	* setIsAlive():      Set the spell's active state
	*
	* Ins:			     bActive
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 10/09/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setIsActive(bool bActive);
	/*****************************************************************
	* getPosition():     Set the spell's current position
	*
	* Ins:			     tPosition
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 10/09/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setPosition(tFloat4 tPosition);
	/*****************************************************************
	* getHeading():      Set the spell's current heading
	*
	* Ins:			     tHeading
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 10/09/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setHeading(tFloat4 tHeading);
};

