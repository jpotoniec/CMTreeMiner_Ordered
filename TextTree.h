/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Header: TextTree.h
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TextTree_H
#define TextTree_H

#include "CMRmisc.h"

using namespace std;

struct TextTree {
	TextTree() : tid(-1), vNumber(0), vLabel(0), firstChild(0), nextSibling(0), parent(0) 
	{
	} 

	TextTree(int t) : tid(t), vNumber(0), vLabel(0), firstChild(0), nextSibling(0), parent(0) 
	{
	}

	TextTree(int t, int v) : tid(t), vNumber(v), 
		vLabel(v,-1), firstChild(v,-1), nextSibling(v,-1), parent(v,-1) 
	{
	}

	~TextTree()
	{
	}
	//assuming the copy constructor and operator= have default definition

	int tid;
	int vNumber;
	vector<int> vLabel;
	vector<int> firstChild;
	vector<int> nextSibling;
	vector<int> parent;
};

istream& operator>>(istream& in, TextTree& rhs);
ostream& operator<<(ostream& out, const TextTree& rhs);

#endif //TextTree_H
