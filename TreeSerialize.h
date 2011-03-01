// TreeSerialize.h: interface for the TreeSerialize class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREESERIALIZE_H__40187C00_6556_48D7_A231_795AE4A937F4__INCLUDED_)
#define AFX_TREESERIALIZE_H__40187C00_6556_48D7_A231_795AE4A937F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UTF.h"
#include "UniqueStringList.h"


class TreeSerialize  
{
	NODE * node_buffer;	int node_size;
	char * data_buffer;	int data_size;

	char * string_buffer;	int string_size;

	int next_node_ptr, next_data_ptr;

	UniqueStringList * usl;
	int build_data_and_nodes(CTreeCtrl * tree, HTREEITEM self);
public:
	TreeSerialize();
	TreeSerialize(CTreeCtrl *, list<HTREEITEM> *);
	void DataToBuffer(char *);
	void NodeToBuffer(NODE *);
	void StringToBuffer(char *);
	int GetDataSize();
	int GetNodeSize();
	int GetStringSize();
	virtual ~TreeSerialize();

};

#endif // !defined(AFX_TREESERIALIZE_H__40187C00_6556_48D7_A231_795AE4A937F4__INCLUDED_)
