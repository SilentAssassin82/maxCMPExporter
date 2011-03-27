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
	, bWireFrame(FALSE)
	, bVColor(FALSE)
	, bVuvm2(FALSE)
	, bVColorEnh(FALSE)
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
	DDX_Check(pDX, IDC_WIREFRAME, bWireFrame);
	DDX_Check(pDX, IDC_VUVM2, bVuvm2);
	DDX_Check(pDX, IDC_VCOLORENH, bVColorEnh);
	DDX_Radio(pDX, IDC_CMPNT_NONE, (int&)eRadioCmpnts);
	DDX_CBIndex(pDX, IDC_COMBO1, iLOD);
	DDV_MinMaxInt(pDX, iLOD, 0, 5);
}


BEGIN_MESSAGE_MAP(ExportOptions, CDialog)
	ON_BN_CLICKED(IDC_TANGENTS, &ExportOptions::OnBnClickedTangents)
	ON_BN_CLICKED(IDC_VCOLOR, &ExportOptions::OnBnClickedVcolor)
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

void ExportOptions::OnBnClickedTangents()
{
	// TODO: Add your control notification handler code here
}

void ExportOptions::OnBnClickedVcolor()
{
	// TODO: Add your control notification handler code here
}
