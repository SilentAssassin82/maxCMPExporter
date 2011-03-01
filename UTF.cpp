// UTF.cpp: implementation of the UTF class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "utf_edit.h"
#include "UTF.h"
#include "UniqueStringList.h"
#include "TreeSerialize.h"
#include "3dsmaxport.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HTREEITEM UTF::AddNewNode(CTreeCtrl * tree, HTREEITEM parent, char * name)
{
	HTREEITEM self = tree->InsertItem(name, 0, 0, parent);
	tree->SetItemData(self, 0);
	node_list->push_back( self );
	return self;
}

void UTF::RemoveNode(CTreeCtrl * tree, HTREEITEM item,  bool remove_siblings)
{
	void * ndata = (void *)tree->GetItemData(item);
	if (ndata) free(ndata);
	
	node_list->remove(item);

	HTREEITEM sibling = tree->GetNextSiblingItem(item);
	HTREEITEM child = tree->GetChildItem(item);

	if (child) RemoveNode(tree, child, true);
	if (sibling != NULL && remove_siblings) RemoveNode (tree, sibling, true);

	tree->DeleteItem(item);
}

bool UTF::Save(CTreeCtrl * tree, char * fileName)
{

	FILE * f = _tfopen (fileName, "wb");
	if (f)
	{
		int sig=' FTU';	int ver=0x101; int temp = 0;
		NODE * node;		int node_size=0;	int node_offset;
		char * string;		int string_size=0;	int string_offset;
		char * data;		int data_size=0;	int data_offset;

		fwrite (&sig, 4, 1, f);
		fwrite (&ver, 4, 1, f);

		// build strings, nodes and data
		TreeSerialize * tl = new TreeSerialize(tree, node_list);
		data_size = tl->GetDataSize();
		node_size = tl->GetNodeSize();
		string_size = tl->GetStringSize();
		data = (char *) malloc (data_size);	memset (data, 0, data_size);
		node = (NODE *) malloc (node_size);	memset (node, 0, node_size);
		string = (char *) malloc (string_size);	memset(string, 0, string_size);
		tl->DataToBuffer(data);
		tl->NodeToBuffer(node);
		tl->StringToBuffer(string);

		// now we can setup offsets...
		node_offset = 0x38;			// right after the header
		string_offset = node_offset + node_size;
		data_offset = string_offset + string_size;

		// ... so let's write the header...
		fwrite (&node_offset, 4, 1, f);
		fwrite (&node_size, 4, 1, f);
		temp = 0;	fwrite (&temp, 4, 1, f);
		temp = 0x2c;fwrite (&temp, 4, 1, f);
		fwrite (&string_offset, 4, 1, f);
		fwrite (&string_size, 4, 1, f);
		fwrite (&string_size, 4, 1, f);
		fwrite (&data_offset, 4, 1, f);
		temp = 0;	fwrite (&temp, 4, 1, f);
					fwrite (&temp, 4, 1, f);
					fwrite (&temp, 4, 1, f);
					fwrite (&temp, 4, 1, f);

		// ...and data.
		fwrite (node, node_size, 1, f);
		fwrite (string, string_size, 1, f);
		fwrite (data, data_size, 1, f);

		delete tl;
		free(node);
		free(data);
		free(string);
		fclose(f);
		return true;	
	}
	else
		return false;
}

void UTF::DestroyTree(CTreeCtrl * tree)
{
	list<HTREEITEM>::iterator i;
	for (i = node_list->begin(); i != node_list->end(); i++)
	{
		HTREEITEM node = *i;
		void * data = (void *)tree->GetItemData(node);
		if (data)	free(data);
	}
	delete node_list;

	tree->DeleteAllItems();
}

void UTF::insert_nodes(CTreeCtrl * tree, NODE * node, int node_size, char * string, char * data, HTREEITEM parent_item, int offset)
{
	NODE * aux_node = node + offset/sizeof(NODE);

	while (aux_node != node)
	{
		HTREEITEM self = tree->InsertItem( aux_node->string_offset + string ,0, 0, parent_item);
		node_list->push_back( self );
		
		// if this node has children, let's add them!
		if ( (aux_node->flags & 0x80) == 0)
		{
			insert_nodes(tree, node, node_size, string, data, self, aux_node->child_offset);
			tree->SetItemData(self, 0);
		}
		else
		{
			// otherwise, let's add the node data
			if (aux_node->allocated_size > 0)
			{
				// check for possible compression
				if (aux_node->size != aux_node->size2)
					MessageBox(0,"Possible compression being used on this chunk",string + aux_node->string_offset,0);

				char * node_data = (char *)malloc (aux_node->allocated_size + 4);
				memcpy (node_data + 4, aux_node->child_offset + data, aux_node->allocated_size);
				*(int *)node_data = aux_node->allocated_size;
				tree->SetItemData(self, (DWORD_PTR)node_data);
			}
			else
				tree->SetItemData(self, 0);
		}

		// next node on the same depth level
		aux_node = node + aux_node->peer_next_offset/sizeof(NODE);
	}
}

void UTF::BuildTree (CTreeCtrl * tree, NODE * node, int node_size, char * string, char * data)
{
	HTREEITEM root_item = tree->InsertItem(string + node->string_offset, 0,0);
	node_list->push_back( root_item );
	insert_nodes(tree, node, node_size, string, data, root_item, node->child_offset);
}

UTF::UTF()
{
	node_list = new list<HTREEITEM>;
}

UTF::UTF(char * fileName, CTreeCtrl * tree)
{
	node_list = new list<HTREEITEM>;

	FILE * f = fopen (fileName, "rb");
	if (f)
	{
		int sig;	int ver;
		NODE * node;		int node_size;	int node_offset;
		char * string;		int string_size;	int string_offset;
		char * data;		int data_size;	int data_offset;

		fread (&sig, 4, 1, f);
		fread (&ver, 4, 1, f);

		// check if it's UTF, otherwise abort
		if (sig != ' FTU' || ver != 0x101)
		{
			fclose(f);
			return;
		}

		// load chunks
		fread (&node_offset, 4, 1, f);			// get node chunk info
		fread (&node_size, 4, 1, f);
		fseek (f, 8, SEEK_CUR);
		fread (&string_offset, 4, 1, f);		// get string chunk info
		fread (&string_size, 4, 1, f);
		fseek (f, 4, SEEK_CUR);
		fread (&data_offset, 4, 1, f);			// get data chunk info
		data_size = -data_offset;
		fseek (f, 0, SEEK_END);
		data_size += ftell(f);


		fseek (f, node_offset, SEEK_SET);					// load nodes
		node = (NODE *) malloc (node_size);
		fread (node, node_size, 1, f);
		fseek (f, string_offset, SEEK_SET);					// load strings
		string = (char *) malloc (string_size);
		fread (string, string_size, 1, f);
		fseek (f, data_offset, SEEK_SET);					// load data
		data = (char *) malloc (data_size);
		fread (data, data_size, 1, f);

		BuildTree (tree, node, node_size, string, data);
		
		fclose(f);
		free(data);
		free(string);
		free(node);
	}
}

UTF::~UTF()
{

}
