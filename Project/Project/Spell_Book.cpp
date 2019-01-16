#include "Spell_Book.h"



cSpell_Book::cSpell_Book()
{
	//Build_Nodes(tNodeList[0], 0, 1, 2, 3);
	//Build_Nodes(tNodeList[1], 1, 3, 0, 2);
	//Build_Nodes(tNodeList[2], 2, 1, 3, 0);
}


cSpell_Book::~cSpell_Book()
{
}

tFloat4x4 cSpell_Book::getPosition4x4()
{
	return m_tPosition;
}

tNode* cSpell_Book::getNodeList(int id)
{
	return tNodeList[id];
}

void cSpell_Book::setPosition4x4(tFloat4x4 tPosition)
{
	m_tPosition = tPosition;
}

void cSpell_Book::Build_Nodes(tNode* n, int a, int b, int c, int d)
{
	tNode *newNode1 = new tNode;
	tNode *newNode2 = new tNode;
	tNode *newNode3 = new tNode;

	n->nData = a;
	n->tNext = newNode1;
	newNode1->nData = b;
	newNode1->tNext = newNode2;
	newNode2->nData = c;
	newNode2->tNext = newNode3;
	newNode3->nData = d;
}

