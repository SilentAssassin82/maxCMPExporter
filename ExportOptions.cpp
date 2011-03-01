// ExportOptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "maxCMPExport.h"
#include "ExportOptions.h"


// ExportOptions-Dialogfeld

IMPLEMENT_DYNAMIC(ExportOptions, CDialog)

ExportOptions::ExportOptions(CWnd* pParent /*=NULL*/)
	: CDialog(ExportOptions::IDD, pParent)
	, bTangents(FALSE)
	, bVColor(FALSE)
	, eRadioCmpnts(EXPORT_CMPNT_NONE)
	, iLOD(0)
{
	bDoExport = true;
}

ExportOptions::~ExportOptions()
{
}

void ExportOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_TANGENTS, bTangents);
	DDX_Check(pDX, IDC_VCOLOR, bVColor);
	DDX_Radio(pDX, IDC_CMPNT_NONE, (int&)eRadioCmpnts);
	DDX_CBIndex(pDX, IDC_COMBO1, iLOD);
	DDV_MinMaxInt(pDX, iLOD, 0, 5);
}


BEGIN_MESSAGE_MAP(ExportOptions, CDialog)
END_MESSAGE_MAP()

// ExportOptions-Meldungshandler

BOOL ExportOptions::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return false;

	return true;
}

void ExportOptions::OnCancel()
{
	CDialog::OnCancel();

	bDoExport = false;
}
