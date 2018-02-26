#include <iostream>
#include <climits>
//#include <assert.h>

#include "MinHeap.h"

#define ileft(p) (2*(p)+1)
#define iright(p) (2*(p)+2)
#define iparent(ch) (((ch)-1)/2)

MinHeap::MinHeap() {
	size = 0;
}

MinHeap::~MinHeap() {
	delete nodes;
}

void MinHeap::insert(TreeNode * val) {
	
	////////////////VECTOR IMPLEMENTATION////////////////	
	//insert node to heap
	
	nodes->push_back(val);

	size++;	
	
	//apply upheap
	int child = size - 1;
	int parent = iparent(child);
	
	while(child > 0) {
		if(nodes->at(child)->getFrequency() >= nodes->at(parent)->getFrequency()) {
			//No need to swap
			break;
		}
		swap(nodes->at(child), nodes->at(parent));
		
		child = parent;
		parent = iparent(child);
	}
}

int MinHeap::getSize() {
	return size;
}

TreeNode * MinHeap::removeMin() {
	
	//////////////VECTOR IMPLEMENTATION////////////
	if(size == 0) { return NULL; }	


	TreeNode * min = nodes->at(0);
	size--;
	//if heap is empty, nothing to fix
	if(size == 0) {
		return min;
	}

	//move last element to top
	TreeNode * rearNode = nodes->at(size);
	nodes->at(0) = rearNode;
	nodes->erase(nodes->begin() + size);	

	//fix heap using down heap
	int parent = 0;
	int left = ileft(parent);
	int right = iright(parent);
	
	while(left < size) {
		//determine smallest child
		int minchild = left;
		if(right < size && nodes->at(right)->getFrequency() < nodes->at(left)->getFrequency()) {
			minchild = right;
		}
	
		//check if we need to swap
		if(nodes->at(parent)->getFrequency() <= nodes->at(minchild)->getFrequency()) {
			//no need
			break;
		} 

		swap(nodes->at(minchild), nodes->at(parent));

		//continue downheap
		parent = minchild;
		left = ileft(parent);
		right = iright(parent);
	}
	return min;
}

