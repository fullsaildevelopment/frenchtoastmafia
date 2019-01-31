#include "Spell_Shield.h"

cSpell_Shield::cSpell_Shield()
{
}

cSpell_Shield::~cSpell_Shield()
{
}

int cSpell_Shield::getHealth()
{
	return m_nHealth;
}

void cSpell_Shield::setHealth(int change)
{
	m_nHealth += change;

	if (m_nHealth > 5)
		m_nHealth = 5;
}

void cSpell_Shield::resetHealth()
{
	m_nHealth = 6;
}
