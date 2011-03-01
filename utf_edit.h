// utf_edit.h : main header file for the UTF_EDIT application
//

#if !defined(AFX_UTF_EDIT_H__0F4F8DD2_AC2E_4371_896D_D36BCFDAE1A8__INCLUDED_)
#define AFX_UTF_EDIT_H__0F4F8DD2_AC2E_4371_896D_D36BCFDAE1A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUtf_editApp:
// See utf_edit.cpp for the implementation of this class
//

class CUtf_editApp : public CWinApp
{
public:
	CUtf_editApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUtf_editApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUtf_editApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UTF_EDIT_H__0F4F8DD2_AC2E_4371_896D_D36BCFDAE1A8__INCLUDED_)
