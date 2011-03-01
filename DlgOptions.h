#ifndef __DLG_OPTIONS_H__
#define __DLG_OPTIONS_H__



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "maxCMPExport.h"

#include <list>
using namespace std;

//
// option flags
//
enum {
    eMeshes         = 1,
    eMaterials      = 2
};

#include "UTF.h"

class cDlgOptions : public CDialog
{
private:
    int     m_nFlags;
    CString m_sPathName;

	CTreeCtrl * tree;
	UTF * utf;
	list<MMESH *> * meshList;
	char fileName[1000];
	
	void create_hardpoints(HTREEITEM);
	void calculate_position( float * pos, MMESH * mesh);
	void calculate_orientation( float * matrix, float * pos, char * name);
	int num_meshes();
	int VertQuantity();
	
	

	EXPORT_CMPNT_OPTION cmpnt_mode;

public:
	cDlgOptions(CWnd* pParent = NULL);
	int iLODs;

public:
    CString GetPathName ();
    int GetOptionFlags ();
	void SetMesh(list<MMESH *> *);
	void SetFileName(char * fileName);
	void SetComponentMode(EXPORT_CMPNT_OPTION);
	void SetLODs(int);
	
	//{{AFX_VIRTUAL(cDlgOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(cDlgOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // __DLG_OPTIONS_H__
