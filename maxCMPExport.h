/**********************************************************************
 *<
	FILE: maxCMPExport.h

	DESCRIPTION:	Includes for Plugins

	CREATED BY:

	HISTORY:

 *>	Copyright (c) 2003, All Rights Reserved.
 **********************************************************************/

#ifndef __maxCMPExport__H
#define __maxCMPExport__H


#include "stdafx.h"


#if _MSC_VER > 1000


#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


#include "Max.h"
#include "resource.h"
#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include "stdmat.h"
#include "decomp.h"
#include "shape.h"
#include "interpik.h"
#include "bmmlib.h"	
#include "utilapi.h"
#include "igame.h"
#include "igameobject.h"
//SIMPLE TYPE

#define CFGFILENAME		_T("maxCMPExport.CFG")

typedef unsigned int uint;

struct FileName_
{
	const TCHAR * File_Name;
};

enum EXPORT_CMPNT_OPTION
{
	EXPORT_CMPNT_NONE = 0,
	EXPORT_CMPNT_RELOCATE = 1,
	EXPORT_CMPNT_NORELOCATE = 2		
};



unsigned int fl_crc32(char *);

struct VECTOR
{
	Point3 vec;
};

struct sObjInfo
{
	TCHAR *gName;
	TCHAR *parentName;
	int				objID;
	int				parentID;	
	//sPRS			prs;
	// initialize (assign) values from a IGameNode class
	void fromNode(IGameNode *pNode);
};
//-------------------------------------------------------------------------------------------
// VMeshData structures
struct VWireData
{
	uint StructSize;
	uint VWireDataID;
	unsigned short VertBase;
	unsigned short VertQuant;
	unsigned short RefVertQuant;
	unsigned short VertRabge;
};
struct VWireMesh {
	int start_vertex, end_vertex, num_triangles;
};
struct vmsVert
{
	Point3 vert;
	Point3 normal;
	Point2 uv;
};
struct gvmsVert
{
	Point3 gvert;
	Point3 gnormal;
	Point2 guv;
};
struct gvmsVertEnh
{
	Point3 gvert;
	Point3 gnormal;
	Point2 guv;
	Point3 gtangent;
	Point3 gbinormal;
};
struct vmsVertEnh
{
	Point3 vert;
	Point3 normal;
	Point2 uv;
	Point3 tangent;
	Point3 binormal;
};
struct StartVertArray
{
	short StartVertNumber;
	short EndVertNumber;
	short RefVertNum;
};
struct SplineVert
{
	Point3 SVert;
};
struct mSplineKnot
{
	unsigned short SVertice[3];
};
struct VMeshRefBounds
{
	uint Header_Size; // 0x0000003C
	uint VMesh_LibId; // crc of 3db name
	unsigned short Start_Vert;
	unsigned short Num_Vert;
	unsigned short Start_Index;
	unsigned short Num_Index;
	unsigned short Start_Mesh;
	unsigned short Num_Meshes;
	float bmaxx;
	float bminx;
	float bmaxy;
	float bminy;
	float bmaxz;
	float bminz;
	float Center_X;
    float Center_Y;
	float Center_Z;
 	//Point3 v_Center;
	float _Radius;

};

struct gvmsVertColor
{
 Point3 gvert;
 uint gdiffuse; // (4 bytes alpha-r-g-b or might be alpha-b-g-r)
 Point2 guv;
};
struct vmsVertColor
{
 Point3 vert;
 uint diffuse; // (4 bytes alpha-r-g-b or might be alpha-b-g-r)
 Point2 uv;
};
struct vmsTri
{
	unsigned short vertice[3];
};
struct gvmsTri
{
	unsigned short gvertice[3];
};
struct vmsHeader
{
	int unk1, unk2;
	unsigned short	nMeshes, nRefVertices, FVF, nVertices;
};

struct vmsMesh
{
	unsigned int material;	// material ID is a CRC32 (with mod table) of the material name
	short start_vert_number;
	short end_vert_number;
	short number_of_vert_references; // faces * 3;
	short padding;	// = 0xcc, for dword allignment, apparently
};

struct GLIST
{

	TCHAR * glname ;
	int NodeCount;
	IGameNode *GroupMesh;
};

struct GroupA
{
	int gChildren;
	Tab<IGameNode*> NodeInfo;
	TCHAR * gname;

	void fromNode(IGameNode *pNode);

};
struct ConsFix
{
	Point3 OriginXYZ;
	uint cfParent;
	uint cfChild;
	float OriginX;
	float OriginY;
	float OriginZ;
	Point3 RotationX;
	Point3 RotationY;
	Point3 RotationZ;
};
struct VMeshRef
{
	// Header - one per lod for each .3db section of cmp - 60 bytes
	uint HeaderSize; // 0x0000003C
	uint VMeshLibId; // crc of 3db name
	int StartVert;
	unsigned short NumVert;
	unsigned short StartIndex;
	unsigned short NumIndex;
	uint StartMesh;
	uint NumMeshes;
	float BoundingBoxMaxX;
	float BoundingBoxMinX;
	float BoundingBoxMaxY;
	float BoundingBoxMinY;
	float BoundingBoxMaxZ;
	float BoundingBoxMinZ;
    //float CenterX;
    //float CenterY;
	//float CenterZ;
 	Point3 vCenter;
	Point3 Radius;
};
struct sNodeInfo
{
	TCHAR *NodeName;
	TCHAR *parentName;
	int				objID;
	int				parentID;	
	// initialize (assign) values from a IGameNode class
	void fromNode(IGameNode *pNode);
};
struct MSpline
{
	SplineVert * sv;	// vmsVert array
	// vmsTri array
	mSplineKnot * spk;
	TCHAR* sname;
	int nSVerts;
	int Num_Splines;
	// mesh name

	//IGameMesh *pMesh; // 3ds max mesh object
};
struct GMMESH
{
	gvmsVertEnh * gv;	// vmsVert array
	gvmsTri * gt;		// vmsTri array
	VMeshRefBounds * gvmeshrefb;
	VMeshRef * vmeshre;
	gvmsVertColor * gvc;
	int gnVerts;
	int gnTris;
	uint gNum_Meshes;
	
	TCHAR *  gmaterial;	// material name
	TCHAR * gnname;	// mesh name
	bool ghardpoint;	
	VECTOR * gtri_normals;

	IGameMesh *gpMesh; // 3ds max mesh object
};
struct MMESH
{
	vmsVertEnh * v;	// vmsVert array
	vmsTri * t;		// vmsTri array
	VMeshRefBounds * vmeshrefb;
	VMeshRef * vmeshre;
	vmsVertColor * vc;
	int nVerts;
	int nTris;
	uint Num_Meshes;
	
	TCHAR *  material;	// material name
	TCHAR * nname;	// mesh name
	bool hardpoint;	
	VECTOR * tri_normals;

	IGameMesh *pMesh; // 3ds max mesh object
};


class CMaxPlugInApp : public CWinApp
{

public:
	CMaxPlugInApp();

	//{{AFX_VIRTUAL(CMsPlugInApp)
	//}}AFX_VIRTUAL
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	//{{AFX_MSG(CMsPlugInApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class PlugPanel : public UtilityObj {
	public:
		HINSTANCE		hInstance;
		IUtil*			iu;
		Interface*		ip;
		HWND			hPanel;

	public:
		// Constructor & Destructor
		PlugPanel();
		virtual ~PlugPanel();

		// Overides of the UtilityObj class
		void BeginEditParams(Interface* ip, IUtil* iu);
		void EndEditParams(Interface* ip, IUtil* iu);
		void DeleteThis()						{}
		void Init(HWND hWnd);
		void Destroy(HWND hWnd);

		//Specific Methods
		void Pick();
};

extern PlugPanel thePlugPanel;	

extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;



#endif
