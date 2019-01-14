/************************************************************************
* Filename:  		Base_Character.h
* Date:      		05/10/2018
* Mod. Date: 		12/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Base Character Module to be inherit by Player and AI
*************************************************************************/
#pragma once
#include "basic_structs.h"

class cBase_Character
{
private:
	// Game Data
	bool m_bIsAlive = true;
	int m_nHealth = 100;
	// int nPower = 0; unused placeholder

	// Movement
	bool m_bIsMovable = true;
	bool m_bIsGrounded = true;

	tFloat4x4 m_tPosition;
	tFloat4 m_tHeading;
	//float m_fVelocity;

	// TBD
	// int nStatus[3]; unused placeholder
	// int nSpellLists[5]; unused placeholder

	// Action
	bool m_bIsCasting = false;
	bool m_bIsCharging = false;

public:
	cBase_Character();
	~cBase_Character();

	/***************
	* Accessors
	***************/
	/*****************************************************************
	* getIsAlive():      Check is the character is alive
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     bool
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	bool getIsAlive();
	/*****************************************************************
	* getIsAlive():      Get the character's HP
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     int
	*
	* Mod. Date:		 12/12/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	int getHealth();
	/*****************************************************************
	* getIsMovable():    Check is the character is movable (Notes: gameplay as of current date character can't move while casting or charging)
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     bool
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	bool getIsMovable();
	/*****************************************************************
	* getIsGrounded():   Check is the character is on the ground
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     bool
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	bool getIsGrounded();
	/*****************************************************************
	* getIsCasting():    Check is the character is currently casting
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     bool
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	bool getIsCasting();
	/*****************************************************************
	* getIsCharging():   Check is the character is currently charging (power up?)
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     bool
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	bool getIsCharging();
	/*****************************************************************
	* getPosition4():    Get the character's current position
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     tFloat4 (float4 structure, see basic_structs.h for detail)
	*
	* Mod. Date:		 12/12/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	tFloat4 getPosition4();
	/*****************************************************************
	* getPosition4x4():  Get the character's current position
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     tFloat4x4 (float4 structure, see basic_structs.h for detail)
	*
	* Mod. Date:		 12/12/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	tFloat4x4 getPosition4x4();
	/*****************************************************************
	* getHeading():      Get the character's current heading
	*
	* Ins:			     none
	*
	* Outs:		         none
	*
	* Returns:		     tFloat4 (float4 structure, see basic_structs.h for detail)
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	tFloat4 getHeading();


	/***************
	* Mutators
	***************/
	/*****************************************************************
	* setIsAlive():      Set the character's alive state
	*
	* Ins:			     bAlive
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setIsAlive(bool bAlive);
	/*****************************************************************
	* getHeading():      Set the Character's HP
	*
	* Ins:			     int
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 12/12/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setHealth(int change);
	/*****************************************************************
	* setIsMovable():    Set the character's movable state (Notes: gameplay as of current date character can't move while casting or charging)
	*
	* Ins:			     bMovable
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setIsMovable(bool bMovable);
	/*****************************************************************
	* setIsGrounded():   Set the character's ground state.
	*
	* Ins:			     bGrounded
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setIsGrounded(bool bGrounded);
	/*****************************************************************
	* setIsCasting():    Set the character's casting state
	*
	* Ins:			     bCasting
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setIsCasting(bool bCasting);
	/*****************************************************************
	* setIsCharging():   Set the character's charging state.
	*
	* Ins:			     bCharging
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setIsCharging(bool bCharging);
	/*****************************************************************
	* setPosition4():    Set the character's current position
	*
	* Ins:			     tPosition
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 12/12/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setPosition4(tFloat4 tPosition);
	/*****************************************************************
	* setPosition4x4():  Set the character's current position
	*
	* Ins:			     tPosition
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 12/12/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setPosition4x4(tFloat4x4 tPosition);
	/*****************************************************************
	* setHeading():      Set the character's current heading
	*
	* Ins:			     tHeading
	*
	* Outs:		         none
	*
	* Returns:		     void
	*
	* Mod. Date:		 09/10/2018
	* Mod. Initials:	 WM
	*****************************************************************/
	void setHeading(tFloat4 tHeading);
};
