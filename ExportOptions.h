#pragma once
#include "afxwin.h"


// ExportOptions-Dialogfeld

class ExportOptions : public CDialog
{
	DECLARE_DYNAMIC(ExportOptions)

public:
	bool bDoExport;


public:
	ExportOptions(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~ExportOptions();

// Dialogfelddaten
	enum { IDD = IDD_EXPORTOPTIONS	};

	virtual BOOL OnInitDialog();
	virtual void OnCancel();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	BOOL bTangents;
	BOOL bVColor;
	BOOL bWireFrame;
	BOOL bVuvm2;
	BOOL bVColorEnh;
	EXPORT_CMPNT_OPTION eRadioCmpnts;
	int iLOD;
	afx_msg void OnBnClickedTangents();
	afx_msg void OnBnClickedVcolor();

};
