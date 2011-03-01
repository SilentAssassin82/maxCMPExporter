// UniqueStringList.h: interface for the UniqueStringList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNIQUESTRINGLIST_H__DA72B9C5_9585_4D6D_8349_DF189453246A__INCLUDED_)
#define AFX_UNIQUESTRINGLIST_H__DA72B9C5_9585_4D6D_8349_DF189453246A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
using namespace std;

typedef struct
{
	int pos;
	CString * string;
} STRING_POS;

class UniqueStringList  
{
	list<STRING_POS *> * usl;
	int next_pos;

public:
	UniqueStringList();
	void Add (CString);
	int GetListSize(void);
	int GetOffset(CString);
	void ToBuffer(char *);
	virtual ~UniqueStringList();

};

#endif // !defined(AFX_UNIQUESTRINGLIST_H__DA72B9C5_9585_4D6D_8349_DF189453246A__INCLUDED_)
