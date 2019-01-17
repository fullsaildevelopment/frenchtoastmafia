/************************************************************************
* Filename:  		Base_Spell.h
* Date:      		05/10/2018
* Mod. Date: 		12/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Base Spell Module to be inherit by various specific spell
*************************************************************************/
#pragma once
#include "basic_structs.h"
struct tNode
{
	int nData;
	tNode *tNext;
};

class cSpell_Book
{
private:
	bool m_bIsActive = false;
	int m_nSelections[4] = { 0, 1, 2, -1 };
	tNode *tNodeList[3] = { nullptr };
	tFloat4x4 m_tPosition;

public:
	cSpell_Book();
	~cSpell_Book();

	/***************
	* Accessors
	***************/
	/*****************************************************************
	* getPosition4x4():  Get the spell's current position
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
	* getPosition4x4():  Get the spell's current position
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
	tNode* getNodeList(int id);
	/***************
	* Mutators
	***************/
	/*****************************************************************
	* setPosition4x4():  Set the spell's current position
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

	void Build_Nodes(tNode *n, int a, int b, int c, int d);
};

