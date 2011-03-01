// About.cpp : implementation file
//

#include "stdafx.h"

#ifdef STRICT							// Already defined by stdafx,
#undef STRICT							// so we avoid warning linking msg
#endif
#ifdef _MBCS							// The same as above
#undef _MBCS
#endif

#include "Max.h"
#include "maxCMPExport.h"
#include "about.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbout dialog


ShowAbout::ShowAbout(CWnd* pParent /*=NULL*/)
	: CDialog(ShowAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAbout)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ShowAbout::DoDataExchange(CDataExchange* pDX)
{
	ShowAbout::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbout)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ShowAbout, CDialog)
	//{{AFX_MSG_MAP(CAbout)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbout message handlers
