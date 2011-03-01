#include "stdafx.h"
#include "resource.h"
#include "DlgOptions.h"

#include "maxCMPExport.h"
#include "UTF.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void cDlgOptions::calculate_position( float * pos, MMESH * mesh)
{
	pos[0] = (mesh->v[0].vert[0] + mesh->v[1].vert[0] + mesh->v[2].vert[0]) / 3.0f;
	pos[1] = (mesh->v[0].vert[1] + mesh->v[1].vert[1] + mesh->v[2].vert[1]) / 3.0f;
	pos[2] = (mesh->v[0].vert[2] + mesh->v[1].vert[2] + mesh->v[2].vert[2]) / 3.0f;
}


void cDlgOptions::calculate_orientation( float * matrix, float * pos, char * name)
{
	// check special cases:
	// Put identity matrix if:
	if ( !_strnicmp(name,"HpEngine",8) || 
		 !_strnicmp(name,"HpMount",7) ||
		 !_strnicmp(name,"HpThruster",10)
		 )
	{
		matrix[0] = 1.0f;
		matrix[1] = 0.0f;
		matrix[2] = 0.0f;

		matrix[3] = 0.0f;
		matrix[4] = 1.0f;
		matrix[5] = 0.0f;

		matrix[6] = 0.0f;
		matrix[7] = 0.0f;
		matrix[8] = 1.0f;

		return;
	}

	// determine closest vertex and take note of vertex normal (will be used as Y vector later)
	float normal[3];
	float distance = 999999.0f;
	list<MMESH *>::iterator i;
	for (i = meshList->begin(); i != meshList->end(); i++)
	{
		MMESH * m = *i;
	
		// we don't care about hardpoint meshes (they are ficticious meshes, as far as we're concerned)
		if (m->hardpoint) continue;

/*
		for (int j = 0; j < m->nVerts; j++)
		{

			float d1 = pos[0] - m->v[j].vert[0];
			float d2 = pos[1] - m->v[j].vert[1];
			float d3 = pos[2] - m->v[j].vert[2];

			float d = d1 * d1 + d2 * d2 + d3 * d3;
			d = sqrt (d);

			if (d < distance)
			{
				distance = d;

				normal[0] = m->v[j].normal[0];
				normal[1] = m->v[j].normal[1];
				normal[2] = m->v[j].normal[2];
			}
		}
	}
*/

		for (int j = 0; j < m->nTris; j++)
		{
			float tri_center[3];
			tri_center[0] = ( m->v[ m->t[j].vertice[0] ].vert[0] + m->v[ m->t[j].vertice[1] ].vert[0] + m->v[ m->t[j].vertice[2] ].vert[0] ) / 3;
			tri_center[1] = ( m->v[ m->t[j].vertice[0] ].vert[1] + m->v[ m->t[j].vertice[1] ].vert[1] + m->v[ m->t[j].vertice[2] ].vert[1] ) / 3;
			tri_center[2] = ( m->v[ m->t[j].vertice[0] ].vert[2] + m->v[ m->t[j].vertice[1] ].vert[2] + m->v[ m->t[j].vertice[2] ].vert[2] ) / 3;

			float d1 = pos[0] - tri_center[0];
			float d2 = pos[1] - tri_center[1];
			float d3 = pos[2] - tri_center[2];

			float d = d1 * d1 + d2 * d2 + d3 * d3;
			d = sqrt (d);

			if (d < distance)
			{
				distance = d;

				normal[0] = m->tri_normals[j].vec[0];
				normal[1] = m->tri_normals[j].vec[1];
				normal[2] = m->tri_normals[j].vec[2];
			}
		}
	}

	normal[0] = -normal[0];

	// calculate orientation matrix
	if (normal[2] > -0.99999 && normal[2] < 0.99999)
		{
		// get Y vector
		matrix[3] = normal[0];
		matrix[4] = normal[1];
		matrix[5] = normal[2];

		// get X vector
		matrix[0] = normal[1];
		matrix[1] = -normal[0];
		matrix[2] = 0;

		// calculate Z vector
		matrix[6] = matrix[1] * matrix[5] - matrix[2] * matrix[4];
		matrix[7] = matrix[2] * matrix[3] - matrix[0] * matrix[5];
		matrix[8] = matrix[0] * matrix[4] - matrix[1] * matrix[3];
		}
	else
		{
		// get Y vector
		matrix[3] = normal[0];
		matrix[4] = normal[1];
		matrix[5] = normal[2];

		// get Z vector
		matrix[6] = 0;
		matrix[7] = - normal[2];
		matrix[8] = normal[1];

		// calculate X vector
		matrix[0] = matrix[4] * matrix[8] - matrix[5] * matrix[7];
		matrix[1] = matrix[5] * matrix[6] - matrix[3] * matrix[8];
		matrix[2] = matrix[3] * matrix[7] - matrix[4] * matrix[6];	
		}
}
void cDlgOptions::create_hardpoints(HTREEITEM item)
{
	HTREEITEM fixed = utf->AddNewNode(tree, item, "Fixed");
	HTREEITEM revolute = utf->AddNewNode(tree, item, "Revolute");

	// iterate mesh list and create hardpoints
	list<MMESH *>::iterator i;
	for (i = meshList->begin(); i != meshList->end(); i ++)
	{
		MMESH * m = *i;
		char * hp_name = 0;

		// Hardpoint|Fixed|blah or Hardpoint|Revolute|blah
		if ( !_strnicmp(m->nname, "Hp", 2) )
		{
			HTREEITEM parent = 0;
			if ( !_strnicmp (m->nname + 3, "Fixed", 5) )
			{
				parent = fixed;
				hp_name = m->nname + 9;	// pointer to name Hp|Fixed|name
			}
			else if ( !_strnicmp (m->nname + 3, "Revolute", 8) )
			{
				parent = revolute;
				hp_name = m->nname + 12;	// pointer to name Hp|Revolute|name
			}
			else 
				continue;

 			HTREEITEM new_hp = utf->AddNewNode(tree, parent, hp_name);

				// only revolute hardpoints have these
				if (parent == revolute)
				{
					HTREEITEM axis = utf->AddNewNode(tree, new_hp, "Axis");
						float * axis_data = (float *) malloc (12 + 4);
						*(int *) axis_data = 12;
						axis_data[1] = 0.0f;
						axis_data[2] = 1.0f;
						axis_data[3] = 0.0f;
						tree->SetItemData(axis, (DWORD_PTR)axis_data);

					HTREEITEM max = utf->AddNewNode(tree, new_hp, "Max");
						float * max_data = (float *) malloc (8 + 4);
						*(int *) max_data = 8;
						max_data[1] = 0.785380f;
						max_data[2] = 0.0f;
						tree->SetItemData(max, (DWORD_PTR)max_data);

					HTREEITEM min = utf->AddNewNode(tree, new_hp, "Min");
						float * min_data = (float *) malloc (8 + 4);
						*(int *) min_data = 8;
						min_data[1] = -0.785400f;
						min_data[2] = 0.0f;
						tree->SetItemData(min, (DWORD_PTR)min_data);
				}

				// both fixed and revolute hardpoints have Orientation and Position
						float * position_data = (float *) malloc (12 + 4);
						*(int *) position_data = 12;
						calculate_position( position_data + 1, m);

						float * orientation_data = (float *) malloc (36 + 4);
						*(int *) orientation_data = 36;
						calculate_orientation( orientation_data + 1, position_data + 1, hp_name);

					HTREEITEM orientation = utf->AddNewNode(tree, new_hp, "Orientation");
						tree->SetItemData(orientation, (DWORD_PTR) orientation_data);

					HTREEITEM position = utf->AddNewNode(tree, new_hp, "Position");
						tree->SetItemData(position, (DWORD_PTR) position_data);
		}
	}
}

int cDlgOptions::num_meshes()
{
	// iterate mesh list, calculate number of meshes
	int nMesh = 0;

	list<MMESH *>::iterator i;
	for (i = meshList->begin(); i != meshList->end(); i ++)
	{
		MMESH * m = *i;

		if ( _strnicmp(m->nname, "Hp", 2) )
			nMesh ++;
	}

	return nMesh;
}


//======================================================================
// constructor
//======================================================================
cDlgOptions::cDlgOptions(CWnd* pParent /*=NULL*/)
: CDialog(IDD_OPTIONS, pParent)
{
	//{{AFX_DATA_INIT(cDlgOptions)
	//}}AFX_DATA_INIT
}
//======================================================================
// DoDataExchange
//======================================================================
void cDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cDlgOptions)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(cDlgOptions, CDialog)
	//{{AFX_MSG_MAP(cDlgOptions)
	//ON_BN_CLICKED(IDC_BTBROWSE,     OnBrowse)
	//ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//======================================================================
// OnInitDialog
//======================================================================
BOOL cDlgOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
    CDialog::CenterWindow();

/*    m_nFlags = eMeshes | eMaterials;
    m_sPathName.Empty();

    CheckDlgButton (IDC_BTMESHES, TRUE);
    CheckDlgButton (IDC_BTMATERIALS, TRUE);
*/	

	tree = (CTreeCtrl *) GetDlgItem(IDC_TREE);
	utf = new UTF();

	// first mesh
	list<MMESH *>::iterator i = meshList->begin();
	MMESH * mesh = *i;

	// -------------------------------------
	char VMeshLibraryName[200];
	strcpy (VMeshLibraryName, mesh->nname);
	string sLod = ".lod";
	sLod += (char)(48 + iLODs);
	sLod += ".vms";
	strcat (VMeshLibraryName, sLod.c_str());

	HTREEITEM root = utf->AddNewNode(tree, NULL, "\\");
		HTREEITEM VMeshLibrary = utf->AddNewNode(tree, root, "VMeshLibrary");
			HTREEITEM meshdata = utf->AddNewNode(tree, VMeshLibrary, VMeshLibraryName);
				HTREEITEM VMeshData = utf->AddNewNode(tree, meshdata, "VMeshData");
					// attach temporary vms file to this node
					FILE * VMeshData_file = fopen ("___temp.vms","rb");
					fseek (VMeshData_file, 0, SEEK_END);
					int VMeshData_file_size = ftell(VMeshData_file);
					fseek (VMeshData_file, 0, SEEK_SET);
					char * VMeshData_file_data = (char *)malloc (VMeshData_file_size + 4);
					fread (VMeshData_file_data + 4, VMeshData_file_size, 1, VMeshData_file);
					*(int *)VMeshData_file_data = VMeshData_file_size;	// first 4 bytes is the size, data comes afterwards
					tree->SetItemData(VMeshData, (DWORD_PTR)VMeshData_file_data);
					fclose(VMeshData_file);

					unlink ("___temp.vms");

		HTREEITEM Cmpnd = utf->AddNewNode(tree, root, "Cmpnd");
			HTREEITEM Cmpnd_root = utf->AddNewNode(tree, Cmpnd, "Root");
				HTREEITEM CR_filename = utf->AddNewNode(tree, Cmpnd_root, "File name");
					// set data entry for "File name"
					char * CR_filename_data = (char *) malloc ( strlen(mesh->nname) + strlen (".3db") + 1 + 4);
					strcpy (CR_filename_data + 4, mesh->nname);	// 4 = int position at beginning
					strcat (CR_filename_data + 4, ".3db");
					*(size_t *)CR_filename_data = strlen(mesh->nname) + 4 + 1;	// 4 = strlen(".3db") 1 = '\0'
					tree->SetItemData(CR_filename, (DWORD_PTR)CR_filename_data);
				HTREEITEM CR_index = utf->AddNewNode(tree, Cmpnd_root, "Index");
					// set data entry for "Index"
					int * CR_index_data = (int *)malloc (2*sizeof(int) + 4);
					CR_index_data[0] = 8;	// size = 8 (2 integers)
					CR_index_data[1] = 0;
					CR_index_data[2] = 0;
					tree->SetItemData(CR_index, (DWORD_PTR)CR_index_data);
				HTREEITEM CR_objname = utf->AddNewNode(tree, Cmpnd_root, "Object name");
					// set data entry for "Object name"
					char * CR_objname_data = (char *) malloc ( strlen("Root") + 1 + 4 );
					strcpy (CR_objname_data + 4, "Root");
					*(size_t *)CR_objname_data = strlen("Root") + 1;
					tree->SetItemData(CR_objname, (DWORD_PTR)CR_objname_data);

		char objName[200];
		strcpy (objName, mesh->nname);
		strcat (objName, ".3db");
		HTREEITEM obj1 = utf->AddNewNode(tree, root, objName);
			HTREEITEM hardpoints = utf->AddNewNode(tree, obj1, "Hardpoints");
			create_hardpoints (hardpoints);
			HTREEITEM multilevel = utf->AddNewNode(tree, obj1, "MultiLevel");
				string sLevel = "Level";
				sLevel += (char)(48 + iLODs);
				HTREEITEM level0 = utf->AddNewNode(tree, multilevel, (char*)sLevel.c_str());
					HTREEITEM VMeshPart = utf->AddNewNode(tree, level0, "VMeshPart");
						HTREEITEM VMeshRef = utf->AddNewNode(tree, VMeshPart, "VMeshRef");

						FILE * VMeshRef_file = fopen ("___temp.vmref","rb");
						fseek (VMeshRef_file, 0, SEEK_END);
						int VMeshRef_file_size = ftell(VMeshRef_file);
						fseek (VMeshRef_file, 0, SEEK_SET);
						char * VMeshRef_file_data = (char *)malloc (VMeshRef_file_size + 4);
						fread (VMeshRef_file_data + 4, VMeshRef_file_size, 1, VMeshRef_file);
						*(int *)VMeshRef_file_data = VMeshRef_file_size;	// first 4 bytes is the size, data comes afterwards
						tree->SetItemData(VMeshRef, (DWORD_PTR)VMeshRef_file_data);
						fclose(VMeshRef_file);

						unlink ("___temp.vmref");
							// basic VMeshRef (single component with multiple meshes)
							//int * VMeshRef_data = (int *) malloc (60 + 4);
							//VMeshRef_data[0] = 60;
							//tree->SetItemData(VMeshRef, (DWORD_PTR)VMeshRef_data);
							//memset (VMeshRef_data + 1, 0, 60);
							//VMeshRef_data[1] = 60;
							//VMeshRef_data[2] = fl_crc32(VMeshLibraryName);
							//VMeshRef_data[3] = 0;
							//VMeshRef_data[4] = 0;
							//VMeshRef_data[5] = num_meshes() << 16;


	
	utf->Save(tree, fileName);
	// -------------------------------------

	return TRUE;
}

//======================================================================
// OnClose
//======================================================================
void cDlgOptions::OnClose() 
{
	OnCancel ();
}

//======================================================================
// OnCancel
//======================================================================

void cDlgOptions::OnCancel()
{
//	utf->DestroyTree(tree);
//	delete utf;

	CDialog::OnCancel();
}

// CMP exporter methods here

void cDlgOptions::SetMesh(list<MMESH *> * meshList)
{
	this->meshList = meshList;
}

void cDlgOptions::SetFileName(char * fileName)
{
	strcpy (this->fileName, fileName);
}

void cDlgOptions::SetComponentMode(EXPORT_CMPNT_OPTION mode)
{
	cmpnt_mode = mode;
}

void cDlgOptions::SetLODs(int lod_setting)
{
	iLODs = lod_setting;
}

//======================================================================
// OnOK
//======================================================================
void cDlgOptions::OnOK() 
{
	CDialog::OnOK();
}

//======================================================================
// GetPathName
//======================================================================
CString cDlgOptions::GetPathName() 
{
    return m_sPathName;
}

//======================================================================
// GetPathName
//======================================================================
int cDlgOptions::GetOptionFlags() 
{
    return m_nFlags;
}
