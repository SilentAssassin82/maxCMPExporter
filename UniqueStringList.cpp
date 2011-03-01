// UniqueStringList.cpp: implementation of the UniqueStringList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "utf_edit.h"
#include "UniqueStringList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void UniqueStringList::Add (CString s)
{
	if (GetOffset(s) != -1)
		return;

	STRING_POS * p = (STRING_POS *) malloc (sizeof(STRING_POS));
	p->string = new CString(s);
	p->pos = next_pos;
	next_pos = next_pos + 1 + s.GetLength();

	usl->push_back(p);
}

int UniqueStringList::GetListSize(void)
{
	return next_pos;
}

int UniqueStringList::GetOffset(CString s)
{
	list<STRING_POS *>::iterator i;
	for (i = usl->begin(); i != usl->end(); i ++)
	{
		STRING_POS * sp = *i;
	
		if (sp->string->Compare(s.GetBuffer(0)) == 0)
			return sp->pos;
	}

	return -1;
}

void UniqueStringList::ToBuffer(char * st)
{
	list<STRING_POS *>::iterator i;
	for (i = usl->begin(); i != usl->end(); i++)
	{
		STRING_POS * p = *i;
		strcpy (st + p->pos, p->string->GetBuffer(0));
	}
}

UniqueStringList::UniqueStringList()
{
	usl = new list<STRING_POS *>;
	next_pos = 1;
}

UniqueStringList::~UniqueStringList()
{
	delete usl;
}
