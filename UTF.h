// UTF.h: interface for the UTF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTF_H__F01A949F_4253_4BC7_9F64_C584DF7FD257__INCLUDED_)
#define AFX_UTF_H__F01A949F_4253_4BC7_9F64_C584DF7FD257__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
using namespace std;

typedef struct
{
	int peer_next_offset;
	int string_offset;
	int flags;
	int zero;
	int child_offset;	// node segment if node, data segment if leaf
	int allocated_size;
	int size;
	int size2;
	int u1, u2, u3;
} NODE;


class UTF  
{
	list<HTREEITEM> * node_list;	// for convenience, list of all the tree nodes
	
	void insert_nodes(CTreeCtrl * tree, NODE * node, int node_size, char * string, char * data, HTREEITEM parent_item, int offset);

public:
	UTF();
	UTF(char *, CTreeCtrl * tree);
	void BuildTree (CTreeCtrl * tree, NODE * node, int node_size, char * string, char * data);
	void DestroyTree(CTreeCtrl * tree);
	bool Save(CTreeCtrl * tree, char *);
	void RemoveNode(CTreeCtrl * tree, HTREEITEM, bool remove_siblings);
	HTREEITEM AddNewNode(CTreeCtrl * tree, HTREEITEM parent, char * name);
	virtual ~UTF();

};

#endif // !defined(AFX_UTF_H__F01A949F_4253_4BC7_9F64_C584DF7FD257__INCLUDED_)
