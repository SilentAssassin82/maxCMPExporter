#if !defined(AFX_ABOUT_H__D8E04BE2_B88E_11D1_98AD_0040051EDCE7__INCLUDED_)
#define AFX_ABOUT_H__D8E04BE2_B88E_11D1_98AD_0040051EDCE7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// About.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbout dialog

class ShowAbout : public CDialog
{
// Construction
public:
	ShowAbout(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAbout)
	enum { IDD = IDD_ABOUTBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAbout)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUT_H__D8E04BE2_B88E_11D1_98AD_0040051EDCE7__INCLUDED_)
