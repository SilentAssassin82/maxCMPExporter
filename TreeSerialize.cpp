// TreeSerialize.cpp: implementation of the TreeSerialize class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "utf_edit.h"
#include "TreeSerialize.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void TreeSerialize::StringToBuffer(char * string)
{
	memcpy (string, string_buffer, string_size);
}

void TreeSerialize::DataToBuffer(char * data)
{
	memcpy (data, data_buffer, data_size);
}

void TreeSerialize::NodeToBuffer(NODE * node)
{
	memcpy (node, node_buffer, node_size);
}

int TreeSerialize::GetStringSize()
{
	return string_size;
}

int TreeSerialize::GetDataSize()
{
	return data_size;
}

int TreeSerialize::GetNodeSize()
{
	return node_size;
}

int TreeSerialize::build_data_and_nodes(CTreeCtrl * tree, HTREEITEM self)
{

	int node_ptr = next_node_ptr++;

	node_buffer[node_ptr].string_offset = usl->GetOffset( tree->GetItemText(self) );
	node_buffer[node_ptr].u1 = 0;
	node_buffer[node_ptr].u2 = 0;
	node_buffer[node_ptr].u3 = 0;
	
	HTREEITEM child = tree->GetChildItem(self);
	if (child == NULL)
	{
		int size;
		int * psize = (int *) tree->GetItemData(self);
		if (psize == 0) size = 0;
		else size = *psize;

		node_buffer[node_ptr].size = size;
		node_buffer[node_ptr].size2 = size;
		node_buffer[node_ptr].allocated_size = size;
		node_buffer[node_ptr].child_offset = next_data_ptr;
		node_buffer[node_ptr].flags = 0x80;

		// put data
		if (size > 0)
		{
			char * node_data = (char *) (psize + 1);
			memcpy (data_buffer + next_data_ptr, node_data, size);
			next_data_ptr += size;
		}
	}
	else
	{
		node_buffer[node_ptr].size = 0;
		node_buffer[node_ptr].size2 = 0;
		node_buffer[node_ptr].allocated_size = 0;
		node_buffer[node_ptr].child_offset = build_data_and_nodes (tree, child) * sizeof(NODE);
		node_buffer[node_ptr].flags= 0x10;
	}

	HTREEITEM sibling = tree->GetNextSiblingItem(self);

	if (sibling == 0)
		node_buffer[node_ptr].peer_next_offset = 0;
	else
		node_buffer[node_ptr].peer_next_offset = build_data_and_nodes (tree, sibling) * sizeof(NODE);

	return node_ptr;
}

TreeSerialize::TreeSerialize(CTreeCtrl * tree, list<HTREEITEM> * node_list)
{
	data_size = 0;
	node_size = 0;
	string_size = 0;

	next_node_ptr = 0;
	next_data_ptr = 0;

	// build strings
	usl = new UniqueStringList();

	list<HTREEITEM>::iterator i;
	for (i = node_list->begin(); i != node_list->end(); i++)
	{
		HTREEITEM item = *i;
		usl->Add(tree->GetItemText(item));

		// Since we're iterating the list, let's take the chance to count number of nodes
		// and size of data
		node_size += sizeof(NODE);
		int * node_data = (int *)tree->GetItemData(item);
		if (node_data != 0)	data_size += *node_data;
	}

	string_size = usl->GetListSize();
	string_buffer = (char *) malloc (string_size);
	memset(string_buffer, 0, string_size);
	usl->ToBuffer(string_buffer);

	// build data + nodes
	data_buffer = (char *) malloc (data_size);	memset(data_buffer, 0, data_size);
	node_buffer = (NODE *) malloc (node_size);	memset(node_buffer, 0, node_size);

	HTREEITEM root_item = tree->GetRootItem();
	build_data_and_nodes(tree, root_item);	
}

TreeSerialize::TreeSerialize()
{
	data_buffer = 0;
	node_buffer = 0;
	string_buffer = 0;

	data_size = 0;
	node_size = 0;
	string_size = 0;

	next_node_ptr = 0;
	next_data_ptr = 0;
}

TreeSerialize::~TreeSerialize()
{
	if (string_buffer) free (string_buffer);
	if (data_buffer) free (data_buffer);
	if (node_buffer) free (node_buffer);
	if (usl) delete usl;
}
