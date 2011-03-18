/**********************************************************************
*<
	FILE: maxCMPExport.cpp

	DESCRIPTION:	Appwizard generated plugin

	CREATED BY: 

	HISTORY: 

*>	Copyright (c) 2003, All Rights Reserved.
**********************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>

#include "3dsmaxport.h"
#include "maxCMPExport.h"
#include "inode.h"
#include "max.h"
#include "iparamb2.h"
#include "igame.h"
#include "igameobject.h"
//#include "forcelib.h"
#include "DlgOptions.h"
#include "ExportOptions.h"

#define CMPEXPORT_VERSION 0.1

static BOOL showPrompts;
static BOOL exportSelected;

#define maxCMPExport_CLASS_ID	Class_ID(0xaf82ab88, 0xadd6b246)
#define ID_GROUP				_T("*GROUP")



// FL CRC32 table
static unsigned int flcrc32tbl[] = {
	0x0,	0x9073096,	0x120E612C,	0x1B0951BA,	
	0xFF6DC419,	0xF66AF48F,	0xED63A535,	0xE46495A3,	
	0xFEDB8832,	0xF7DCB8A4,	0xECD5E91E,	0xE5D2D988,	
	0x1B64C2B,	0x8B17CBD,	0x13B82D07,	0x1ABF1D91,	
	0xFDB71064,	0xF4B020F2,	0xEFB97148,	0xE6BE41DE,	
	0x2DAD47D,	0xBDDE4EB,	0x10D4B551,	0x19D385C7,	
	0x36C9856,	0xA6BA8C0,	0x1162F97A,	0x1865C9EC,	
	0xFC015C4F,	0xF5066CD9,	0xEE0F3D63,	0xE7080DF5,	
	0xFB6E20C8,	0xF269105E,	0xE96041E4,	0xE0677172,	
	0x403E4D1,	0xD04D447,	0x160D85FD,	0x1F0AB56B,	
	0x5B5A8FA,	0xCB2986C,	0x17BBC9D6,	0x1EBCF940,	
	0xFAD86CE3,	0xF3DF5C75,	0xE8D60DCF,	0xE1D13D59,	
	0x6D930AC,	0xFDE003A,	0x14D75180,	0x1DD06116,	
	0xF9B4F4B5,	0xF0B3C423,	0xEBBA9599,	0xE2BDA50F,	
	0xF802B89E,	0xF1058808,	0xEA0CD9B2,	0xE30BE924,	
	0x76F7C87,	0xE684C11,	0x15611DAB,	0x1C662D3D,	
	0xF6DC4190,	0xFFDB7106,	0xE4D220BC,	0xEDD5102A,	
	0x9B18589,	0xB6B51F,	0x1BBFE4A5,	0x12B8D433,	
	0x807C9A2,	0x100F934,	0x1A09A88E,	0x130E9818,	
	0xF76A0DBB,	0xFE6D3D2D,	0xE5646C97,	0xEC635C01,	
	0xB6B51F4,	0x26C6162,	0x196530D8,	0x1062004E,	
	0xF40695ED,	0xFD01A57B,	0xE608F4C1,	0xEF0FC457,	
	0xF5B0D9C6,	0xFCB7E950,	0xE7BEB8EA,	0xEEB9887C,	
	0xADD1DDF,	0x3DA2D49,	0x18D37CF3,	0x11D44C65,	
	0xDB26158,	0x4B551CE,	0x1FBC0074,	0x16BB30E2,	
	0xF2DFA541,	0xFBD895D7,	0xE0D1C46D,	0xE9D6F4FB,	
	0xF369E96A,	0xFA6ED9FC,	0xE1678846,	0xE860B8D0,	
	0xC042D73,	0x5031DE5,	0x1E0A4C5F,	0x170D7CC9,	
	0xF005713C,	0xF90241AA,	0xE20B1010,	0xEB0C2086,	
	0xF68B525,	0x66F85B3,	0x1D66D409,	0x1461E49F,	
	0xEDEF90E,	0x7D9C998,	0x1CD09822,	0x15D7A8B4,	
	0xF1B33D17,	0xF8B40D81,	0xE3BD5C3B,	0xEABA6CAD,	
	0xEDB88320,	0xE4BFB3B6,	0xFFB6E20C,	0xF6B1D29A,	
	0x12D54739,	0x1BD277AF,	0xDB2615,	0x9DC1683,	
	0x13630B12,	0x1A643B84,	0x16D6A3E,	0x86A5AA8,	
	0xEC0ECF0B,	0xE509FF9D,	0xFE00AE27,	0xF7079EB1,	
	0x100F9344,	0x1908A3D2,	0x201F268,	0xB06C2FE,	
	0xEF62575D,	0xE66567CB,	0xFD6C3671,	0xF46B06E7,	
	0xEED41B76,	0xE7D32BE0,	0xFCDA7A5A,	0xF5DD4ACC,	
	0x11B9DF6F,	0x18BEEFF9,	0x3B7BE43,	0xAB08ED5,	
	0x16D6A3E8,	0x1FD1937E,	0x4D8C2C4,	0xDDFF252,	
	0xE9BB67F1,	0xE0BC5767,	0xFBB506DD,	0xF2B2364B,	
	0xE80D2BDA,	0xE10A1B4C,	0xFA034AF6,	0xF3047A60,	
	0x1760EFC3,	0x1E67DF55,	0x56E8EEF,	0xC69BE79,	
	0xEB61B38C,	0xE266831A,	0xF96FD2A0,	0xF068E236,	
	0x140C7795,	0x1D0B4703,	0x60216B9,	0xF05262F,	
	0x15BA3BBE,	0x1CBD0B28,	0x7B45A92,	0xEB36A04,	
	0xEAD7FFA7,	0xE3D0CF31,	0xF8D99E8B,	0xF1DEAE1D,	
	0x1B64C2B0,	0x1263F226,	0x96AA39C,	0x6D930A,	
	0xE40906A9,	0xED0E363F,	0xF6076785,	0xFF005713,	
	0xE5BF4A82,	0xECB87A14,	0xF7B12BAE,	0xFEB61B38,	
	0x1AD28E9B,	0x13D5BE0D,	0x8DCEFB7,	0x1DBDF21,	
	0xE6D3D2D4,	0xEFD4E242,	0xF4DDB3F8,	0xFDDA836E,	
	0x19BE16CD,	0x10B9265B,	0xBB077E1,	0x2B74777,	
	0x18085AE6,	0x110F6A70,	0xA063BCA,	0x3010B5C,	
	0xE7659EFF,	0xEE62AE69,	0xF56BFFD3,	0xFC6CCF45,	
	0xE00AE278,	0xE90DD2EE,	0xF2048354,	0xFB03B3C2,	
	0x1F672661,	0x166016F7,	0xD69474D,	0x46E77DB,	
	0x1ED16A4A,	0x17D65ADC,	0xCDF0B66,	0x5D83BF0,	
	0xE1BCAE53,	0xE8BB9EC5,	0xF3B2CF7F,	0xFAB5FFE9,	
	0x1DBDF21C,	0x14BAC28A,	0xFB39330,	0x6B4A3A6,	
	0xE2D03605,	0xEBD70693,	0xF0DE5729,	0xF9D967BF,	
	0xE3667A2E,	0xEA614AB8,	0xF1681B02,	0xF86F2B94,	
	0x1C0BBE37,	0x150C8EA1,	0xE05DF1B,	0x702EF8D,	
};

CMaxPlugInApp	theApp;
cDlgOptions     theDlgOptions;

BEGIN_MESSAGE_MAP(CMaxPlugInApp, CWinApp)
//{{AFX_MSG_MAP(CMsPlugInApp)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//-------------------------------------------------------------------------------------------

class maxCMPExport : public SceneExport {
public:

	IGameScene * nMeshes;

	static HWND hParams;

	//TSTR fileName;
	TSTR splitPath;

	IXMLDOMDocument * pXMLDoc;
	IXMLDOMNode * pRoot;		//this is our root node 	
	CComPtr<IXMLDOMNode> iGameNode;	//the IGame child - which is the main node
	CComPtr<IXMLDOMNode> rootNode;
	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
	const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box
	void			ShowOptions(HWND hWnd);

	void ExportNodeInfo(IGameNode * pMesh, const TCHAR *name);
	BOOL ExportGroup(IGameNode * pMesh, const TCHAR* name);
	BOOL ExportRootMesh(IGameNode * pMesh, const TCHAR *name);
	BOOL	nodeEnum(INode* node);
	void	PreProcess(INode* node, int& nodeCount);
	BOOL SupportsOptions(int ext, DWORD options);
	int				DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);
	int staticFrame;
	int cS;
	int Bounds(float);
	int			nTotalNodeCount;
	int			nCurNode;
	Tab<IGameNode*>Meshes;
	Tab<IGameNode*>gMeshes;

	maxCMPExport();
	~maxCMPExport();

	
	// Configuration methods
	TSTR	GetCfgFilename();
	BOOL	ReadConfig();
	void	WriteConfig();

	

private:
	Interface*	ip;
};

class maxCMPExportClassDesc : public ClassDesc2 
{
public:
	int 			IsPublic() { return TRUE; }
	void *			Create(BOOL loading = FALSE) { return new maxCMPExport(); }
	const TCHAR *	ClassName() { return GetString(IDS_CLASS_NAME); }
	SClass_ID		SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	Class_ID		ClassID() { return maxCMPExport_CLASS_ID; }
	const TCHAR* 	Category() { return GetString(IDS_CATEGORY); }

	const TCHAR*	InternalName() { return _T("maxCMPExport"); }	// returns fixed parsable name (scripter-visible name)
	HINSTANCE		HInstance() { return hInstance; }					// returns owning module handle
};

static maxCMPExportClassDesc maxCMPExportDesc;

ClassDesc2* GetmaxCMPExportDesc() 
{ 
	return &maxCMPExportDesc;
}
INT_PTR CALLBACK maxCMPExportOptionsDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	static maxCMPExport *imp = NULL;

	switch(message) {
	case WM_INITDIALOG:
		imp = (maxCMPExport *)lParam;
		CenterWindow(hWnd,GetParent(hWnd));
		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return 1;
	}
	return 0;
}
INT_PTR CALLBACK AboutBoxDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	switch (msg) {
	case WM_INITDIALOG:
		CenterWindow(hWnd, GetParent(hWnd)); 
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hWnd, 1);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
} 
INT_PTR CALLBACK OptionsBoxDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	switch (msg) {
	case WM_INITDIALOG:
		CenterWindow(hWnd, GetParent(hWnd)); 
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hWnd, 1);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
} 

void maxCMPExport::ShowAbout(HWND hWnd)
{	
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutBoxDlgProc, 0);

}void maxCMPExport::ShowOptions(HWND hWnd)
{	
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_OPTIONS), hWnd, OptionsBoxDlgProc, 0);
}
CMaxPlugInApp::CMaxPlugInApp()
{
}

//--- maxCMPExport -------------------------------------------------------
#include <list>
using namespace std;

list<MMESH *> * meshList;
list<GMMESH *> * groupList;
list<GLIST *> * nodeList;

std::list<string> lstNames;
std::list<string> MaterialNames;

int CMaxPlugInApp::ExitInstance() 
{	return CWinApp::ExitInstance();
}
maxCMPExport::maxCMPExport()
{}

maxCMPExport::~maxCMPExport() 
{}

int maxCMPExport::ExtCount()
{	//TODO: Returns the number of file name extensions supported by the plug-in.
	return 1;
}
const TCHAR *maxCMPExport::Ext(int n)
{		
	//TODO: Return the 'i-th' file name extension (i.e. "3DS").
	return _T("cmp");
}
const TCHAR *maxCMPExport::LongDesc()
{	//TODO: Return long ASCII description (i.e. "Targa 2.0 Image File")
	return _T("Freelancer CMP File Format");
}
const TCHAR *maxCMPExport::ShortDesc() 
{			
	return _T("cmp");
}
const TCHAR *maxCMPExport::AuthorName()
{			
	//TODO: Return ASCII Author name
	return _T("w0dk4 et al");
}
const TCHAR *maxCMPExport::CopyrightMessage() 
{	
	// Return ASCII Copyright message
	return _T("");
}
const TCHAR *maxCMPExport::OtherMessage1() 
{		
	//TODO: Return Other message #1 if any
	return _T("");
}
const TCHAR *maxCMPExport::OtherMessage2() 
{		
	//TODO: Return other message #2 in any
	return _T("");
}
unsigned int maxCMPExport::Version()
{				
	//TODO: Return Version number * 100 (i.e. v3.01 = 301)
	return (uint)(CMPEXPORT_VERSION * 100);
}
unsigned int fl_crc32 (char * string)
{	unsigned int crc;

	crc = 0xFFFFFFFFL;
	for (uint i = 0; i < strlen(string); i++)
	crc = ((crc>>8) & 0x00FFFFFFL) ^ flcrc32tbl[ (crc^ (tolower(string[i])) ) & 0xFF ];
	crc = crc^0xFFFFFFFFL;

	return crc;
}
void normalize (VECTOR * dest, VECTOR * src)
{	float len = sqrt(src->vec[0] * src->vec[0] +  src->vec[1] * src->vec[1] + src->vec[2] * src->vec[2]);
	dest->vec = src->vec / len;
}
IGameMaterial *pMaterial;
GroupA* gNode;
sNodeInfo nodeinfo;
GLIST *glist;
BOOL maxCMPExport::ExportGroup(IGameNode * pMesh, const TCHAR* name)
{	

	
	VMeshRef vmeshref;
	VMeshRefBounds vmeshrefb;
	IGameScene *nMeshes;
	nMeshes = GetIGameInterface();
	nMeshes->SetStaticFrame(0);

	ExportOptions OptionsDlgExport(NULL);
	
	OptionsDlgExport.DoModal();
	if(!OptionsDlgExport.bDoExport)
	return 1;


	meshList = new list<MMESH *>;
	nodeList = new list<GLIST *>;
	
	ConsFix cFix;
	MMESH *mesh;
	VMeshRef *VMBGroups;

	VMBGroups = new VMeshRef;	memset(VMBGroups, 0, sizeof(VMeshRef));
	
	char VMeshLibraryName[200];
	FILE *file2;
	FILE*file3;
	int start_vert = 0;
	int new_start_vert = 0;
	int new_Start_Mesh = 0;
	int new_Start_Index = 0;
	int startgvert = 0;

	char VWireOut2[200];
	strcpy(VWireOut2,gNode->gname);
	string sVWireOut2 = ".lod";
	sVWireOut2 += (char)(48+OptionsDlgExport.iLOD);
	sVWireOut2 += ".vwd";
	strcat (VWireOut2, sVWireOut2.c_str());

	Meshes = nMeshes->GetIGameNodeByType(IGameObject::IGAME_MESH);
	for(int nMesh = 0; nMesh < Meshes.Count(); nMesh++)
	{	

		mesh = new MMESH;	memset(mesh, 0, sizeof(MMESH));

		mesh->nname = gNode->gname;	  
		IGameObject *pModel;		
		pModel=pMesh->GetIGameObject();
		IGameMesh *gMesh =(IGameMesh*)Meshes[nMesh]->GetIGameObject();	

		if (gMesh->GetIGameType()==IGameObject::IGAME_MESH)		
		{	
			IGameNode *pMesh = (IGameNode*)gMesh;
			meshList->push_back(mesh);			
			gMesh->InitializeData();

			IGameMaterial *pMaterial=NULL;
			int faces = gMesh->GetNumberOfFaces();
			for(int i=0; i<faces; i++)
			{
				pMaterial=gMesh->GetMaterialFromFace(i);	
				int SubMat = pMaterial->GetSubMaterialCount();
				for(int i=0; i<SubMat;i++)
				{
					IGameMaterial * subMat;
					subMat = pMaterial->GetSubMaterial(i);
				}
				mesh->material = pMaterial->GetMaterialName();
				MaterialNames.push_back(pMaterial->GetMaterialName());
				IGameMesh *gMesh = (IGameMesh*)pMesh;			
				mesh->pMesh = gMesh;
			}
			int nTris = gMesh->GetNumberOfFaces();
			mesh->t = new vmsTri[nTris];
			int nVerts = nTris*3;
			mesh->v = new vmsVertEnh[nVerts];
			mesh->vc = new vmsVertColor[nVerts];
			
			uint iVertexDuplicates = 0;

			for (int nTri = 0; nTri < nTris; nTri++)
			{
				FaceEx * pTriangle = gMesh->GetFace(nTri);
				for(int i=0;i<3;i++)
				{
					int nVert = (nTri*3 + i) - iVertexDuplicates;
					
					Point3 vertice, normal, binormal, tangent, color, BoundingBoxMaxx, BoundingBoxMinx, BoundingBoxMaxy, BoundingBoxMiny, BoundingBoxMaxz, BoundingBoxMinz;
					Point2 uv, uvfl;
					Box3 Bounds;
					//float BoundingBoxMaxX = 1.0f;
					
					gMesh->GetVertex(pTriangle->vert[i], vertice);
					gMesh->GetTexVertex(pTriangle->texCoord[i], uv);
					gMesh->GetNormal(pTriangle->norm[i], normal);

					// before assigning the vert, check existing verts if there is a duplicate
					bool bDuplicate = false;
					for(int nVertB=0; nVertB < nVert; nVertB++)
					{
						if(mesh->v[nVertB].vert == vertice &&
								mesh->v[nVertB].normal == normal &&
								mesh->v[nVertB].uv == uv)
						{
							// match!
							// assign triangle corner to found vertex index
							mesh->t[pTriangle->meshFaceIndex].vertice[i] = nVertB;
							iVertexDuplicates++;
							bDuplicate = true;
							break;
						}
					}
					if(bDuplicate)
					continue;
					

					mesh->t[pTriangle->meshFaceIndex].vertice[i] = nVert;

					mesh->v[nVert].vert = vertice;
					mesh->v[nVert].normal = normal;
					mesh->v[nVert].uv = uv;
					
					int iTBindex = gMesh->GetFaceVertexTangentBinormal(pTriangle->meshFaceIndex, i);
					if(iTBindex != -1)
					{
						tangent = gMesh->GetTangent(iTBindex);
						binormal = gMesh->GetBinormal(iTBindex);
						mesh->v[nVert].tangent = tangent;
						mesh->v[nVert].binormal = binormal;
					}
					float alpha = 1.0f;
					int iVCindex = gMesh->GetFaceVertex(pTriangle->meshFaceIndex, i);		
					if(iVCindex != -1)
					{
						alpha = gMesh->GetAlphaVertex(pTriangle->alpha[i]);
						color = gMesh->GetColorVertex(pTriangle->color[i]);
						mesh->vc[nVert].vert = vertice;
						mesh->vc[nVert].diffuse = (DWORD)(alpha * 255)<<24 | (DWORD)(color.x * 255)<<16 | (DWORD)(color.y *255)<<8 | (DWORD)(color.z * 255);
						mesh->vc[nVert].uv = uv;
					}
					else
					{
						mesh->v[nVert].tangent = Point3(0,0,1);
						mesh->v[nVert].binormal = Point3(1,0,0);
					}
				}
				mesh->nVerts = nVerts - iVertexDuplicates;
				mesh->nTris = nTris;
			}
		}
	}
	Point3 BoundingBoxMaxx, BoundingBoxMinx, BoundingBoxMaxy, BoundingBoxMiny, BoundingBoxMaxz, BoundingBoxMinz;
	Box3 Bounds;


	int bmaxx = 0;
	list<MMESH *>::iterator j;
	list<GMMESH *>::iterator G;
	list<GLIST *>::iterator GL;
	list<MMESH *>::iterator i = meshList->begin();

	GMMESH * gmesh;
	MMESH * mmesh = *i;

	list<VMeshRef *>::iterator I;
	int NewStartVert = 0;
	int NewVert = 0;
	int NewVertWire =0;

	char VMeshRefFile[200];
	char VWireOut[200];
	strcpy (VMeshLibraryName, pMesh->GetName());
	string sLod = ".lod";
	sLod += (char)(48 +  OptionsDlgExport.iLOD);
	sLod += ".vms";
	strcat (VMeshLibraryName, sLod.c_str());
	int ngNodes= nMeshes->GetTopLevelNodeCount();
	file3 = _tfopen ("___temp.verts", "wb");

	
	for( int nNodes=0; nNodes<ngNodes; nNodes++)
	{
		IGameNode * pMesh = nMeshes->GetTopLevelNode(nNodes);
		{
			{
				IGameObject *pModel;		
				pModel=pMesh->GetIGameObject();
				
				IGameMesh *gMesh = (IGameMesh*)pMesh;			
				mesh->pMesh = gMesh;
				gMesh->InitializeData();
				
				strcpy(VMeshRefFile, pMesh->GetName());
				string sVMeshRef = ".lod";
				sVMeshRef += (char)(48+OptionsDlgExport.iLOD);
				sVMeshRef += ".vmr";
				strcat (VMeshRefFile, sVMeshRef.c_str());


				//If it's in a group, then the group owner will be IGAME_HELPER
				//store it's name for our group name and VWireData
				if(pModel->GetIGameType()==IGameObject::IGAME_HELPER)
				{
					groupList = new list<GMMESH*>;
					lstNames.push_back(pMesh->GetName());

					strcpy(VWireOut, pMesh->GetName());
					string sVWireOut = ".lod";
					sVWireOut += (char)(48+OptionsDlgExport.iLOD);
					sVWireOut += ".vwd";
					strcat (VWireOut, sVWireOut.c_str());
					
					for( int nChilds=0; nChilds<pMesh->GetChildCount(); nChilds++)
					{
						
						IGameNode * pChild = pMesh->GetNodeChild(nChilds);
						IGameObject *gModel;		
						gModel=pChild->GetIGameObject();

						//After we find the group owner we access the mesh
						if(gModel->GetIGameType()==IGameObject::IGAME_MESH)
						{
							gmesh = new GMMESH;	memset(gmesh, 0, sizeof(GMMESH));
							
							gModel->InitializeData();

							groupList->push_back(gmesh);			
							IGameMesh *pChild = (IGameMesh*)gModel;


							int gnTris = pChild->GetNumberOfFaces();
							gmesh->gt = new gvmsTri[gnTris];
							int gnVerts = gnTris*3;
							gmesh->gv = new gvmsVertEnh[gnVerts];
							gmesh->gvc = new gvmsVertColor[gnVerts];
							
							uint iVertexDuplicates = 0;

							
							for (int gnTri = 0; gnTri < gnTris; gnTri++)
							{
								FaceEx * pTriangle = pChild->GetFace(gnTri);
								for(int i=0;i<3;i++)
								{
									int gnVert = (gnTri*3 + i) - iVertexDuplicates;
									
									Point3 vertice, normal, binormal, tangent, color, BoundingBoxMaxx, BoundingBoxMinx, BoundingBoxMaxy, BoundingBoxMiny, BoundingBoxMaxz, BoundingBoxMinz;
									Point2 uv, uvfl;
									Box3 Bounds;
									
									pChild->GetVertex(pTriangle->vert[i], vertice);
									pChild->GetTexVertex(pTriangle->texCoord[i], uv);
									pChild->GetNormal(pTriangle->norm[i], normal);

									// before assigning the vert, check existing verts if there is a duplicate
									bool bDuplicate = false;
									for(int gnVertB=0; gnVertB < gnVert; gnVertB++)
									{
										if(gmesh->gv[gnVertB].gvert == vertice &&
												gmesh->gv[gnVertB].gnormal == normal &&
												gmesh->gv[gnVertB].guv == uv)
										{
											// match!
											// assign triangle corner to found vertex index
											gmesh->gt[pTriangle->meshFaceIndex].gvertice[i] = gnVertB;
											iVertexDuplicates++;
											bDuplicate = true;
											break;
										}
									}
									if(bDuplicate)
									continue;
									
									gmesh->gt[pTriangle->meshFaceIndex].gvertice[i] = gnVert;

									gmesh->gv[gnVert].gvert = vertice;
									gmesh->gv[gnVert].gnormal = normal;
									gmesh->gv[gnVert].guv = uv;
									
									int iTBindex = pChild->GetFaceVertexTangentBinormal(pTriangle->meshFaceIndex, i);
									if(iTBindex != -1)
									{
										tangent = pChild->GetTangent(iTBindex);
										binormal = pChild->GetBinormal(iTBindex);
										gmesh->gv[gnVert].gtangent = tangent;
										gmesh->gv[gnVert].gbinormal = binormal;
									}
									float alpha = 1.0f;
									int iVCindex = pChild->GetFaceVertex(pTriangle->meshFaceIndex, i);		
									if(iVCindex != -1)
									{
										alpha = pChild->GetAlphaVertex(pTriangle->alpha[i]);
										color = pChild->GetColorVertex(pTriangle->color[i]);
										gmesh->gvc[gnVert].gvert = vertice;
										gmesh->gvc[gnVert].gdiffuse = (DWORD)(alpha * 255)<<24 | (DWORD)(color.x * 255)<<16 | (DWORD)(color.y *255)<<8 | (DWORD)(color.z * 255);
										gmesh->gvc[gnVert].guv = uv;
									}
									else
									{
										gmesh->gv[gnVert].gtangent = Point3(0,0,1);
										gmesh->gv[gnVert].gbinormal = Point3(1,0,0);
									}
								}
								gmesh->gnVerts = gnVerts - iVertexDuplicates;
								gmesh->gnTris = gnTris;
							}

							int nMesh=0;
							memset(&vmeshrefb, 0,sizeof(vmeshrefb));
							for (G = groupList->begin(); G != groupList->end(); G++)
							{
								GMMESH * gm = *G;

								vmeshref.NumMeshes = nChilds+1;
							}
							
							Point3 vCenter;
							
							pModel->GetBoundingBox(Bounds);
							BoundingBoxMaxx = Bounds.pmax;
							vmeshrefb.bmaxx = BoundingBoxMaxx.x;
							vmeshref.BoundingBoxMaxX  = vmeshrefb.bmaxx;
							BoundingBoxMinx = Bounds.pmin;
							vmeshrefb.bminx = BoundingBoxMinx.x;
							vmeshref.BoundingBoxMinX  = vmeshrefb.bminx;
							BoundingBoxMaxy = Bounds.pmax;
							vmeshrefb.bmaxy = BoundingBoxMaxy.y;
							vmeshref.BoundingBoxMaxY  = vmeshrefb.bmaxy;
							BoundingBoxMiny = Bounds.pmin;
							vmeshrefb.bminy = BoundingBoxMiny.y;
							vmeshref.BoundingBoxMinY  = vmeshrefb.bminy;
							BoundingBoxMaxz = Bounds.pmax;
							vmeshrefb.bmaxz = BoundingBoxMaxz.z;
							vmeshref.BoundingBoxMaxZ  = vmeshrefb.bmaxz;
							BoundingBoxMinz = Bounds.pmin;
							vmeshrefb.bminz = BoundingBoxMinz.z;
							vmeshref.BoundingBoxMinZ  = vmeshrefb.bminz;
							vCenter = Bounds.Center();
							vmeshrefb.Center_X = vCenter.x;
							vmeshrefb.Center_Y = vCenter.y;
							vmeshrefb.Center_Z = vCenter.z;
							Point3 BRadius = Bounds.Width();
							vmeshrefb._Radius = BRadius.FLength();
						}
					}
				}
				else
				{
					// If it's not in a group, export as a single mesh
					//on it's own
					if(pModel->GetIGameType()==IGameObject::IGAME_MESH)
					{
						groupList = new list<GMMESH*>;
						gmesh = new GMMESH;	memset(gmesh, 0, sizeof(GMMESH));
						pModel->InitializeData();
						groupList->push_back(gmesh);			
						IGameMesh *pChild = (IGameMesh*)pModel;

						lstNames.push_back(pMesh->GetName());
						int gnTris = pChild->GetNumberOfFaces();
						gmesh->gt = new gvmsTri[gnTris];
						int gnVerts = gnTris*3;
						gmesh->gv = new gvmsVertEnh[gnVerts];
						gmesh->gvc = new gvmsVertColor[gnVerts];

						strcpy(VWireOut, pMesh->GetName());
						string sVWireOut = ".lod";
						sVWireOut += (char)(48+OptionsDlgExport.iLOD);
						sVWireOut += ".vwd";
						strcat (VWireOut, sVWireOut.c_str());
						
						uint iVertexDuplicates = 0;

						for (int gnTri = 0; gnTri < gnTris; gnTri++)
						{
							FaceEx * pTriangle = pChild->GetFace(gnTri);
							for(int i=0;i<3;i++)
							{
								int gnVert = (gnTri*3 + i) - iVertexDuplicates;
								
								Point3 vertice, normal, binormal, tangent, color, BoundingBoxMaxx, BoundingBoxMinx, BoundingBoxMaxy, BoundingBoxMiny, BoundingBoxMaxz, BoundingBoxMinz;
								Point2 uv, uvfl;
								Box3 Bounds;
								
								pChild->GetVertex(pTriangle->vert[i], vertice);
								pChild->GetTexVertex(pTriangle->texCoord[i], uv);
								pChild->GetNormal(pTriangle->norm[i], normal);

								// before assigning the vert, check existing verts if there is a duplicate
								bool bDuplicate = false;
								for(int gnVertB=0; gnVertB < gnVert; gnVertB++)
								{
									if(gmesh->gv[gnVertB].gvert == vertice &&
											gmesh->gv[gnVertB].gnormal == normal &&
											gmesh->gv[gnVertB].guv == uv)
									{
										// match!
										// assign triangle corner to found vertex index
										gmesh->gt[pTriangle->meshFaceIndex].gvertice[i] = gnVertB;
										iVertexDuplicates++;
										bDuplicate = true;
										break;
									}
								}
								if(bDuplicate)
								continue;
								
								gmesh->gt[pTriangle->meshFaceIndex].gvertice[i] = gnVert;

								gmesh->gv[gnVert].gvert = vertice;
								gmesh->gv[gnVert].gnormal = normal;
								gmesh->gv[gnVert].guv = uv;
								
								int iTBindex = pChild->GetFaceVertexTangentBinormal(pTriangle->meshFaceIndex, i);
								if(iTBindex != -1)
								{
									tangent = pChild->GetTangent(iTBindex);
									binormal = pChild->GetBinormal(iTBindex);
									gmesh->gv[gnVert].gtangent = tangent;
									gmesh->gv[gnVert].gbinormal = binormal;
								}
								float alpha = 1.0f;
								int iVCindex = pChild->GetFaceVertex(pTriangle->meshFaceIndex, i);		
								if(iVCindex != -1)
								{
									alpha = pChild->GetAlphaVertex(pTriangle->alpha[i]);
									color = pChild->GetColorVertex(pTriangle->color[i]);
									gmesh->gvc[gnVert].gvert = vertice;
									gmesh->gvc[gnVert].gdiffuse = (DWORD)(alpha * 255)<<24 | (DWORD)(color.x * 255)<<16 | (DWORD)(color.y *255)<<8 | (DWORD)(color.z * 255);
									gmesh->gvc[gnVert].guv = uv;
								}
								else
								{
									gmesh->gv[gnVert].gtangent = Point3(0,0,1);
									gmesh->gv[gnVert].gbinormal = Point3(1,0,0);
								}
							}
							gmesh->gnVerts = gnVerts - iVertexDuplicates;
							gmesh->gnTris = gnTris;
						}

						int nMesh=0;
						memset(&vmeshrefb, 0,sizeof(vmeshrefb));
						for (G = groupList->begin(); G != groupList->end(); G++)
						{
							GMMESH * gm = *G;

							vmeshref.NumMeshes = 1;
						}
						
						Point3 vCenter;
						
						pChild->GetBoundingBox(Bounds);
						BoundingBoxMaxx = Bounds.pmax;
						vmeshrefb.bmaxx = BoundingBoxMaxx.x;
						vmeshref.BoundingBoxMaxX  = vmeshrefb.bmaxx;
						BoundingBoxMinx = Bounds.pmin;
						vmeshrefb.bminx = BoundingBoxMinx.x;
						vmeshref.BoundingBoxMinX  = vmeshrefb.bminx;
						BoundingBoxMaxy = Bounds.pmax;
						vmeshrefb.bmaxy = BoundingBoxMaxy.y;
						vmeshref.BoundingBoxMaxY  = vmeshrefb.bmaxy;
						BoundingBoxMiny = Bounds.pmin;
						vmeshrefb.bminy = BoundingBoxMiny.y;
						vmeshref.BoundingBoxMinY  = vmeshrefb.bminy;
						BoundingBoxMaxz = Bounds.pmax;
						vmeshrefb.bmaxz = BoundingBoxMaxz.z;
						vmeshref.BoundingBoxMaxZ  = vmeshrefb.bmaxz;
						BoundingBoxMinz = Bounds.pmin;
						vmeshrefb.bminz = BoundingBoxMinz.z;
						vmeshref.BoundingBoxMinZ  = vmeshrefb.bminz;
						vCenter = Bounds.Center();
						vmeshrefb.Center_X = vCenter.x;
						vmeshrefb.Center_Y = vCenter.y;
						vmeshrefb.Center_Z = vCenter.z;
						Point3 BRadius = Bounds.Width();
						vmeshrefb._Radius = BRadius.FLength();
					}
				}
			}
			StartVertArray SVarray; memset(&SVarray, 0, sizeof(SVarray));

			int vertnum = 0;
			file2 = _tfopen (VMeshRefFile, "wb");

			//Create a VMeshRef for each part and store start/end vert for each
			//part aswell in an array to update original .vms file
			vmsMesh vmesh;	memset(&vmesh, 0, sizeof(vmesh));
			int hStartVert = 0;
			for (G = groupList->begin(); G != groupList->end(); G++)
			{
				vmeshrefb.Num_Vert  += (*G)->gnVerts;
				vmeshrefb.Start_Index = new_Start_Index;
				vmeshrefb.Num_Index += (*G)->gnTris * 3;
				SVarray.StartVertNumber = hStartVert;
				SVarray.EndVertNumber = hStartVert += (*G)->gnVerts-1;
				SVarray.RefVertNum = (*G)->gnTris * 3;
				fwrite(&SVarray, sizeof(SVarray), 1, file3);
				hStartVert += +1;
				startgvert += (*G)->gnVerts;
			}
			vmeshrefb.Start_Vert = new_start_vert;
			vmeshrefb.Header_Size = 60;
			vmeshrefb.VMesh_LibId = fl_crc32(VMeshLibraryName);
			vmeshrefb.Start_Mesh = new_Start_Mesh;
			vmeshrefb.Num_Meshes = vmeshref.NumMeshes;
			vmeshref.StartMesh = new_Start_Mesh += vmeshref.NumMeshes;

			// Create a dummy one piece .vms to make wireframe
			if(OptionsDlgExport.bWireFrame)
			{
				FILE *file4;
				file4 = _tfopen (VWireOut, "wb");
				if (!file4)
				{
					MessageBox(0,"Could not open export file for some reason, check if it's not being used by another application!","Error exporting VMS file",MB_ICONERROR);
					return -1;
				}
				if( file3 == NULL )
				exit( 0 );
				// save header
				vmsHeader header;	memset(&header, 0, sizeof(header));
				header.unk1 = 1;
				header.unk2 = 4;
				//header.nMeshes = nMeshes;
				header.nMeshes = 0;
				for (G = groupList->begin(); G != groupList->end(); G++)
				header.nMeshes = 1;

				if(OptionsDlgExport.bTangents)
				header.FVF = 0x412;
				else if(OptionsDlgExport.bVColor)
				header.FVF = 0x142;
				else
				header.FVF = 0x112;
				for (G = groupList->begin(); G != groupList->end(); G++)
				{
					header.nRefVertices += (*G)->gnTris * 3;
					header.nVertices += (*G)->gnVerts;
				}
				fwrite (&header, sizeof(header), 1, file4);

				
				// save each mesh entry
				for (G = groupList->begin(); G != groupList->end(); G++)
				{
					vmesh.material = fl_crc32(VWireOut);
					vmesh.start_vert_number = NewVertWire;
					vmesh.end_vert_number = NewStartVert + (*G)->gnVerts - 1;
					vmesh.number_of_vert_references += (*G)->gnTris * 3;
					vmesh.padding = 0xcc;
					
					NewStartVert += (*G)->gnVerts;
				}
				fwrite(&vmesh, sizeof(vmesh), 1, file4);
				NewVertWire = NewStartVert;
				// save triangles
				for (G = groupList->begin(); G != groupList->end(); G++)
				fwrite((*G)->gt, sizeof(vmsTri) * (*G)->gnTris, 1, file4);

				// save vertices
				for (G = groupList->begin(); G != groupList->end(); G++)
				{
					if(OptionsDlgExport.bTangents)
					fwrite((*G)->gv, sizeof(vmsVertEnh) * (*G)->gnVerts, 1, file4);
					else if(OptionsDlgExport.bVColor)
					fwrite((*G)->gvc, sizeof(vmsVertColor) * (*G)->gnVerts, 1, file4);
					else
					for(int p=0;p<(*G)->gnVerts;p++)
					fwrite((*G)->gv + p, sizeof(vmsVert), 1, file4);		
				}
				NewVert = NewStartVert;
				fclose (file4);
			}
		}
		fwrite(&vmeshrefb, sizeof(vmeshrefb), 1, file2);
		fclose (file2);
		for (G = groupList->begin(); G != groupList->end(); G++)
		{
			new_Start_Mesh = vmeshref.StartMesh;
			new_start_vert += (*G)->gnVerts;
			new_Start_Index += (*G)->gnTris * 3;
		}
	}
	nMeshes->ReleaseIGame();
	fclose (file3);

	char buffer[200];
	int *temp_int = (int *)buffer;

	FILE *file;

	file = _tfopen ("___temp.vms", "wb");
	if (!file)
	{
		MessageBox(0,"Could not open export file for some reason, check if it's not being used by another application!","Error exporting VMS file",MB_ICONERROR);
		return -1;
	}
	fopen_s( &file3,"___temp.verts","rb");
	if( file3 == NULL )
	exit( 0 );

	// save header
	vmsHeader header;	memset(&header, 0, sizeof(header));
	header.unk1 = 1;
	header.unk2 = 4;

	//header.nMeshes = nMeshes;
	header.nMeshes = 0;
	for (j = meshList->begin(); j != meshList->end(); j++)
	header.nMeshes++;

	if(OptionsDlgExport.bTangents)
	header.FVF = 0x412;
	else if(OptionsDlgExport.bVColor)
	header.FVF = 0x142;
	else
	header.FVF = 0x112;
	for (j = meshList->begin(); j != meshList->end(); j++)
	{
		header.nRefVertices += (*j)->nTris * 3;
		header.nVertices += (*j)->nVerts;
	}
	fwrite (&header, sizeof(header), 1, file);

	// save each mesh entry
	for (j = meshList->begin(); j != meshList->end(); j++)
	{
		vmsMesh vmesh;	memset(&vmesh, 0, sizeof(vmesh));
		vmesh.material = fl_crc32( (*j)->material );
		fread(buffer,1,2,file3);
		vmesh.start_vert_number = *temp_int;
		fread(buffer,1,2,file3);
		vmesh.end_vert_number = *temp_int;
		fread(buffer,1,2,file3);
		vmesh.number_of_vert_references = *temp_int;//(*j)->nTris * 3;
		vmesh.padding = 0xcc;
		fwrite(&vmesh, sizeof(vmesh), 1, file);

		start_vert += (*j)->nVerts;
	}
	// save triangles
	for (j = meshList->begin(); j != meshList->end(); j++)
	fwrite((*j)->t, sizeof(vmsTri) * (*j)->nTris, 1, file);

	// save vertices
	for (j = meshList->begin(); j != meshList->end(); j++)
	{
		if(OptionsDlgExport.bTangents)
		fwrite((*j)->v, sizeof(vmsVertEnh) * (*j)->nVerts, 1, file);
		else if(OptionsDlgExport.bVColor)
		fwrite((*j)->vc, sizeof(vmsVertColor) * (*j)->nVerts, 1, file);
		else
		for(int p=0;p<(*j)->nVerts;p++)
		fwrite((*j)->v + p, sizeof(vmsVert), 1, file);		
	}
	// fclose
	fclose (file);
	fclose (file3);
	mesh = new MMESH;	memset(mesh, 0, sizeof(MMESH));
	memset(&vmeshrefb, 0,sizeof(vmeshrefb));

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	cDlgOptions dlgOptions (NULL);
	dlgOptions.SetLODs(OptionsDlgExport.iLOD);
	dlgOptions.SetMesh(meshList);
	dlgOptions.SetWire(OptionsDlgExport.bWireFrame);
	dlgOptions.SetFileName((char*)name);
	dlgOptions.SetComponentMode(OptionsDlgExport.eRadioCmpnts);
	dlgOptions.DoModal();

	return 0;

}
BOOL maxCMPExport::ExportRootMesh(IGameNode * pMesh,  const TCHAR *name)
{	
	
	lstNames.push_back( pMesh->GetName());
	
	ExportOptions OptionsDlgExport(NULL);

	OptionsDlgExport.DoModal();
	if(!OptionsDlgExport.bDoExport)
	return 1;

	char VMeshRefFile[200];
	strcpy(VMeshRefFile, pMesh->GetName());
	string sVMeshRef = ".lod";
	sVMeshRef += (char)(48+OptionsDlgExport.iLOD);
	sVMeshRef += ".vmr";
	strcat (VMeshRefFile, sVMeshRef.c_str());

	char VWireOut[200];
	strcpy(VWireOut, pMesh->GetName());
	string sVWireOut = ".lod";
	sVWireOut += (char)(48+OptionsDlgExport.iLOD);
	sVWireOut += ".vwd";
	strcat (VWireOut, sVWireOut.c_str());

	gNode = new GroupA;	memset(gNode, 0, sizeof(GroupA));
	IGameScene *nMeshes;
	VMeshRef vmeshref;
	VMeshRefBounds vmeshrefb;
	nMeshes = GetIGameInterface();

	nMeshes->SetStaticFrame(0);
	meshList = new list<MMESH *>;
	MMESH * mesh;
	FILE *file2;
	char VMeshLibraryName[200];
	int start_vert = 0;
	int NewStartVert = 0;
	int NewVert = 0;
	int NewVertWire =0;

	for(int nMesh = 0; nMesh < nMeshes->GetTopLevelNodeCount(); nMesh++)
	{
		mesh = new MMESH;	memset(mesh, 0, sizeof(MMESH));

		IGameNode *pMesh = nMeshes->GetTopLevelNode(nMesh);
		IGameObject *pModel;
		pModel=pMesh->GetIGameObject();
		if (pModel->GetIGameType()==IGameObject::IGAME_MESH)
		{
			meshList->push_back(mesh);

			pModel->InitializeData();
			IGameMaterial *pMaterial=NULL;
			pMaterial=pMesh->GetNodeMaterial();
			IGameTextureMap *pTexMap=NULL;
			if (pMaterial!=NULL) pTexMap=pMaterial->GetIGameTextureMap(0);
			mesh->material = pMaterial->GetMaterialName(); 
			MaterialNames.push_back(pMaterial->GetMaterialName());
			mesh->nname = pMesh->GetName();


			IGameMesh *pMesh = (IGameMesh*)pModel;

			mesh->pMesh = pMesh;
			
			// triangles
			int nTris = pMesh->GetNumberOfFaces();
			mesh->t = new vmsTri[nTris];
			int nVerts = nTris*3;
			mesh->v = new vmsVertEnh[nVerts];
			mesh->vc = new vmsVertColor[nVerts];
			
			uint iVertexDuplicates = 0;

			for (int nTri = 0; nTri < nTris; nTri++)
			{
				FaceEx * pTriangle = pMesh->GetFace(nTri);
				
				for(int i=0;i<3;i++)
				{
					int nVert = (nTri*3 + i) - iVertexDuplicates;
					
					Point3 vertice, normal, binormal, tangent, color, BoundingBoxMaxx, BoundingBoxMinx, BoundingBoxMaxy, BoundingBoxMiny, BoundingBoxMaxz, BoundingBoxMinz;
					Point2 uv, uvfl;
					Box3 Bounds;
					//float BoundingBoxMaxX = 1.0f;
					
					pMesh->GetVertex(pTriangle->vert[i], vertice);
					pMesh->GetTexVertex(pTriangle->texCoord[i], uv);
					pMesh->GetNormal(pTriangle->norm[i], normal);

					// before assigning the vert, check existing verts if there is a duplicate
					bool bDuplicate = false;
					for(int nVertB=0; nVertB < nVert; nVertB++)
					{
						if(mesh->v[nVertB].vert == vertice &&
								mesh->v[nVertB].normal == normal &&
								mesh->v[nVertB].uv == uv)
						{
							// match!
							// assign triangle corner to found vertex index
							mesh->t[pTriangle->meshFaceIndex].vertice[i] = nVertB;
							iVertexDuplicates++;
							bDuplicate = true;
							break;
						}
					}
					if(bDuplicate)
					continue;
					
					mesh->t[pTriangle->meshFaceIndex].vertice[i] = nVert;

					mesh->v[nVert].vert = vertice;
					mesh->v[nVert].normal = normal;
					mesh->v[nVert].uv = uv;
					
					int iTBindex = pMesh->GetFaceVertexTangentBinormal(pTriangle->meshFaceIndex, i);
					if(iTBindex != -1)
					{
						tangent = pMesh->GetTangent(iTBindex);
						binormal = pMesh->GetBinormal(iTBindex);
						mesh->v[nVert].tangent = tangent;
						mesh->v[nVert].binormal = binormal;
					}
					float alpha = 1.0f;
					int iVCindex = pMesh->GetFaceVertex(pTriangle->meshFaceIndex, i);		
					if(iVCindex != -1)
					{
						alpha = pMesh->GetAlphaVertex(pTriangle->alpha[i]);
						color = pMesh->GetColorVertex(pTriangle->color[i]);
						mesh->vc[nVert].vert = vertice;
						mesh->vc[nVert].diffuse = (DWORD)(alpha * 255)<<24 | (DWORD)(color.x * 255)<<16 | (DWORD)(color.y *255)<<8 | (DWORD)(color.z * 255);
						mesh->vc[nVert].uv = uv;
					}
					else
					{
						mesh->v[nVert].tangent = Point3(0,0,1);
						mesh->v[nVert].binormal = Point3(1,0,0);
					}
				}
				mesh->nVerts = nVerts - iVertexDuplicates;
				mesh->nTris = nTris;
			}
			Point3 BoundingBoxMaxx, BoundingBoxMinx, BoundingBoxMaxy, BoundingBoxMiny, BoundingBoxMaxz, BoundingBoxMinz;
			Box3 Bounds;

			int bmaxx = 0;
			list<MMESH *>::iterator j;

			list<MMESH *>::iterator i = meshList->begin();
			MMESH * mesh = *i;
			
			strcpy (VMeshLibraryName, mesh->nname);
			string sLod = ".lod";
			sLod += (char)(48 + OptionsDlgExport.iLOD);
			sLod += ".vms";
			strcat (VMeshLibraryName, sLod.c_str());
			
			memset(&vmeshrefb, 0,sizeof(vmeshrefb));
			for (j = meshList->begin(); j != meshList->end(); j++)
			{
				vmeshref.NumMeshes = nMesh+1;
			}
			Point3 vCenter;
			
			pMesh->GetBoundingBox(Bounds);
			BoundingBoxMaxx = Bounds.pmax;
			vmeshrefb.bmaxx = BoundingBoxMaxx.x;
			vmeshref.BoundingBoxMaxX  = vmeshrefb.bmaxx;
			BoundingBoxMinx = Bounds.pmin;
			vmeshrefb.bminx = BoundingBoxMinx.x;
			vmeshref.BoundingBoxMinX  = vmeshrefb.bminx;
			BoundingBoxMaxy = Bounds.pmax;
			vmeshrefb.bmaxy = BoundingBoxMaxy.y;
			vmeshref.BoundingBoxMaxY  = vmeshrefb.bmaxy;
			BoundingBoxMiny = Bounds.pmin;
			vmeshrefb.bminy = BoundingBoxMiny.y;
			vmeshref.BoundingBoxMinY  = vmeshrefb.bminy;
			BoundingBoxMaxz = Bounds.pmax;
			vmeshrefb.bmaxz = BoundingBoxMaxz.z;
			vmeshref.BoundingBoxMaxZ  = vmeshrefb.bmaxz;
			BoundingBoxMinz = Bounds.pmin;
			vmeshrefb.bminz = BoundingBoxMinz.z;
			vmeshref.BoundingBoxMinZ  = vmeshrefb.bminz;
			vCenter = Bounds.Center();
			vmeshrefb.Center_X = vCenter.x;
			vmeshrefb.Center_Y = vCenter.y;
			vmeshrefb.Center_Z = vCenter.z;
			Point3 BRadius = Bounds.Width();
			vmeshrefb._Radius = BRadius.FLength();
		}
	}
	nMeshes->ReleaseIGame();
	file2 = _tfopen (VMeshRefFile, "wb");

	list<MMESH *>::iterator j;
	for (j = meshList->begin(); j != meshList->end(); j++)
	{
		vmeshrefb.Start_Index = start_vert;
		vmeshrefb.Num_Index += (*j)->nTris * 3;
		vmeshrefb.Num_Vert  += (*j)->nVerts;
	}
	vmeshrefb.Header_Size = 60;
	vmeshrefb.VMesh_LibId = fl_crc32(VMeshLibraryName);
	vmeshrefb.Num_Meshes = vmeshref.NumMeshes;

	fwrite(&vmeshrefb, sizeof(vmeshrefb), 1, file2);
	fclose (file2);

	if(OptionsDlgExport.bWireFrame)
	{
		FILE *file4;
		file4 = _tfopen (VWireOut, "wb");
		if (!file4)
		{
			MessageBox(0,"Could not open export file for some reason, check if it's not being used by another application!","Error exporting VMS file",MB_ICONERROR);
			return -1;
		}
		if( file4 == NULL )
		exit( 0 );
		// save header
		vmsHeader header;	memset(&header, 0, sizeof(header));
		header.unk1 = 1;
		header.unk2 = 4;
		//header.nMeshes = nMeshes;
		header.nMeshes = 0;
		for (j = meshList->begin(); j != meshList->end(); j++)
		header.nMeshes = 1;

		if(OptionsDlgExport.bTangents)
		header.FVF = 0x412;
		else if(OptionsDlgExport.bVColor)
		header.FVF = 0x142;
		else
		header.FVF = 0x112;
		for (j = meshList->begin(); j != meshList->end(); j++)
		{
			header.nRefVertices += (*j)->nTris * 3;
			header.nVertices += (*j)->nVerts;
		}
		fwrite (&header, sizeof(header), 1, file4);

		vmsMesh vmesh;	memset(&vmesh, 0, sizeof(vmesh));
		// save each mesh entry
		for (j = meshList->begin(); j != meshList->end(); j++)
		{
			
			vmesh.material = fl_crc32(VWireOut);
			vmesh.start_vert_number = NewVertWire;
			vmesh.end_vert_number = NewStartVert + (*j)->nVerts - 1;
			vmesh.number_of_vert_references += (*j)->nTris * 3;
			vmesh.padding = 0xcc;
			
			NewStartVert += (*j)->nVerts;
		}
		
		fwrite(&vmesh, sizeof(vmesh), 1, file4);
		NewVertWire = NewStartVert;
		// save triangles
		for (j = meshList->begin(); j != meshList->end(); j++)
		fwrite((*j)->t, sizeof(vmsTri) * (*j)->nTris, 1, file4);

		// save vertices
		for (j = meshList->begin(); j != meshList->end(); j++)
		{
			if(OptionsDlgExport.bTangents)
			fwrite((*j)->v, sizeof(vmsVertEnh) * (*j)->nVerts, 1, file4);
			else if(OptionsDlgExport.bVColor)
			fwrite((*j)->vc, sizeof(vmsVertColor) * (*j)->nVerts, 1, file4);
			else
			for(int p=0;p<(*j)->nVerts;p++)
			fwrite((*j)->v + p, sizeof(vmsVert), 1, file4);		
		}
		NewVert = NewStartVert;
		fclose (file4);
	}
	FILE *file;

	file = _tfopen ("___temp.vms", "wb");
	if (!file)
	{
		MessageBox(0,"Could not open export file for some reason, check if it's not being used by another application!","Error exporting VMS file",MB_ICONERROR);
		return -1;
	}
	// save header
	vmsHeader header;	memset(&header, 0, sizeof(header));
	header.unk1 = 1;
	header.unk2 = 4;
	//header.nMeshes = nMeshes;
	header.nMeshes = 0;
	for (j = meshList->begin(); j != meshList->end(); j++)
	header.nMeshes++;

	if(OptionsDlgExport.bTangents)
	header.FVF = 0x412;
	else if(OptionsDlgExport.bVColor)
	header.FVF = 0x142;
	else
	header.FVF = 0x112;
	for (j = meshList->begin(); j != meshList->end(); j++)
	{
		header.nRefVertices += (*j)->nTris * 3;
		header.nVertices += (*j)->nVerts;
	}
	fwrite (&header, sizeof(header), 1, file);

	// save each mesh entry
	for (j = meshList->begin(); j != meshList->end(); j++)
	{
		vmsMesh vmesh;	memset(&vmesh, 0, sizeof(vmesh));
		vmesh.material = fl_crc32( (*j)->material );
		vmesh.start_vert_number = start_vert;
		vmesh.end_vert_number = start_vert + (*j)->nVerts - 1;
		vmesh.number_of_vert_references = (*j)->nTris * 3;
		vmesh.padding = 0xcc;
		fwrite(&vmesh, sizeof(vmesh), 1, file);

		start_vert += (*j)->nVerts;
	}
	// save triangles
	for (j = meshList->begin(); j != meshList->end(); j++)
	fwrite((*j)->t, sizeof(vmsTri) * (*j)->nTris, 1, file);

	// save vertices
	for (j = meshList->begin(); j != meshList->end(); j++)
	{
		if(OptionsDlgExport.bTangents)
		fwrite((*j)->v, sizeof(vmsVertEnh) * (*j)->nVerts, 1, file);
		else if(OptionsDlgExport.bVColor)
		fwrite((*j)->vc, sizeof(vmsVertColor) * (*j)->nVerts, 1, file);
		else
		for(int p=0;p<(*j)->nVerts;p++)
		fwrite((*j)->v + p, sizeof(vmsVert), 1, file);		
	}
	// fclose
	fclose (file);

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	cDlgOptions dlgOptions (NULL);
	dlgOptions.SetLODs(OptionsDlgExport.iLOD);
	dlgOptions.SetMesh(meshList);
	dlgOptions.SetWire(OptionsDlgExport.bWireFrame);
	dlgOptions.SetFileName((char*)name);
	dlgOptions.SetComponentMode(OptionsDlgExport.eRadioCmpnts);
	dlgOptions.DoModal();

	return 0;
}

void maxCMPExport::ExportNodeInfo(IGameNode * pMesh, const TCHAR *name)
{	if(pMesh->IsGroupOwner())
	ExportGroup(pMesh, name);
	else
	ExportRootMesh(pMesh, name);
}

IGameMesh * gMesh;
char VMeshLibraryName[200];
FILE *file2;

int	maxCMPExport::DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options)
{	
	
	VMeshRef vmeshref;
	GroupA mGroup;

	// Set a global prompt display switch
	exportSelected = (options & SCENE_EXPORT_SELECTED) ? TRUE : FALSE;

	// Grab the interface pointer.
	ip = i;

	// Get the options the user selected the last time
	ReadConfig();

	
	//ExportOptions OptionsDlgExport(NULL);
	

	//OptionsDlgExport.DoModal();
	//if(!OptionsDlgExport.bDoExport)
	//return 1; // abort by user

	gNode = new GroupA;	memset(gNode, 0, sizeof(GroupA));
	IGameScene *nMeshes;
	
	nMeshes = GetIGameInterface();

	IGameConversionManager * cm = GetConversionManager();
	cm->SetCoordSystem(IGameConversionManager::IGAME_D3D);
	nMeshes->InitialiseIGame(false); // true- we want selected only - false we want all!

	nMeshes->SetStaticFrame(0);
	meshList = new list<MMESH *>;
	MMESH * mesh;
	groupList = new list<GMMESH *>;

	int start_vert = 0;

	Point3 vcenter;	
	for(int nMesh = 0; nMesh < nMeshes->GetTopLevelNodeCount(); nMesh++)	
	{		
		mesh = new MMESH;	memset(mesh, 0, sizeof(MMESH));

		IGameNode *pMesh = nMeshes->GetTopLevelNode(nMesh);	

		mesh->nname = nMeshes->GetTopLevelNode(nMesh)->GetName();
		gNode->gname = mesh->nname;

		
		if(pMesh->IsTarget())
		continue;
		ExportNodeInfo(pMesh, name);
	}

	// -----------------------------------------------------------------------------------------
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	list<MMESH *>::iterator j;
	list<GMMESH *>::iterator G;
	//
	// dialog

	/*cDlgOptions dlgOptions (NULL);
	dlgOptions.SetLODs(OptionsDlgExport.iLOD);
	dlgOptions.SetMesh(meshList);
	dlgOptions.SetFileName((char*)name);
	dlgOptions.SetComponentMode(OptionsDlgExport.eRadioCmpnts);
	dlgOptions.DoModal();*/

	// destroy list
	for (j = meshList->begin(); j != meshList->end(); j++)
	{
		MMESH * m = *j;
		delete [] m->t;
		delete [] m->v;
		delete m;
	}
	delete meshList;
	for (G = groupList->begin(); G != groupList->end(); G++)
	{
		GMMESH * gmesh = *G;
		delete [] gmesh->gt;
		delete [] gmesh->gv;
		delete gmesh;
	}
	delete groupList;

	// Write the current options to be used next time around.
	WriteConfig();

	return 1;
}

BOOL maxCMPExport::nodeEnum(INode* node) 
{	if(exportSelected && node->Selected() == FALSE)
	return TREE_CONTINUE;

	nCurNode++;

	if (ip->GetCancel())
	return FALSE;

	if (node->IsGroupHead())
	{
	}
	if(!exportSelected || node->Selected()) 
	{
		ObjectState os = node->EvalWorldState(0); 
		if (os.obj) 
		{
			// We look at the super class ID to determine the type of the object.
			switch(os.obj->SuperClassID()) {
			case GEOMOBJECT_CLASS_ID: 
				if (os.obj->SuperClassID()==GEOMOBJECT_CLASS_ID); 
				break;
			}
		}
	}
	for (int c = 0; c < node->NumberOfChildren(); c++) {
		if (!nodeEnum(node->GetChildNode(c)))
		return FALSE;
	}
	if (node->IsGroupHead()) {
	}
	return TRUE;
}
void maxCMPExport::PreProcess(INode* node, int& nodeCount)
{	nodeCount++;
	// Add the nodes material to out material list
	// Null entries are ignored when added...
	//mtlList.AddMtl(node->GetMtl());

	// For each child of this node, we recurse into ourselves 
	// and increment the counter until no more children are found.
	for (int c = 0; c < node->NumberOfChildren(); c++) {
		PreProcess(node->GetChildNode(c), nodeCount);
	}

}
BOOL maxCMPExport::SupportsOptions(int ext, DWORD options) {
	assert(ext == 0);	// We only support one extension
	return(options == SCENE_EXPORT_SELECTED) ? TRUE : FALSE;
}
TSTR maxCMPExport::GetCfgFilename()
{	TSTR filename;
	filename += ip->GetDir(APP_PLUGCFG_DIR);
	filename += "\\";
	filename += CFGFILENAME;

	return filename;
}// NOTE: Update anytime the CFG file changes
#define CFG_VERSION 0x03

BOOL maxCMPExport::ReadConfig()
{	TSTR filename = GetCfgFilename();
	FILE* cfgStream;

	cfgStream = fopen(filename, "rb");
	if (!cfgStream)
	return FALSE;

	// First item is a file version
	int fileVersion = _getw(cfgStream);

	if (fileVersion > CFG_VERSION) {
		// Unknown version
		fclose(cfgStream);
		return FALSE;
	}

	fclose(cfgStream);

	return TRUE;
}
void maxCMPExport::WriteConfig()
{	TSTR filename = GetCfgFilename();
	FILE* cfgStream;

	cfgStream = fopen(filename, "wb");
	if (!cfgStream)
	return;

	// Write CFG version
	_putw(CFG_VERSION,				cfgStream);

	fclose(cfgStream);
}