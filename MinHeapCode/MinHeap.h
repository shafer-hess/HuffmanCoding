#ifndef MINHEAP_H
#define MINHEAP_H

#include "TreeNode.h"
#include <vector>

using namespace std;

class MinHeap
{
	private:
		vector<TreeNode*> * nodes = new vector<TreeNode*>();
		int size = 0;

	public:
		MinHeap();
		TreeNode * removeMin(); //returns root of heap
		void insert(TreeNode * val); //adds element to heap
		int getSize(); //returns size of heap
		~MinHeap();
};

#endif
