#pragma once
#include "Base_Spell.h"
class cSpell_Shield : public cBase_Spell
{
private:
	int m_nHealth = 10;

public:
	cSpell_Shield();
	~cSpell_Shield();

	int getHealth();
	void setHealth(int change);
	void resetHealth();
};

