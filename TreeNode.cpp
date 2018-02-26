#include <iostream>
#include "TreeNode.h"
#include <string>

TreeNode::TreeNode(unsigned char val, unsigned frequency) {
	this->val = val;
	this->frequency = frequency;

	left = NULL;
	right = NULL;
	huffCode = "";
}

void TreeNode::deleteNodes(TreeNode * node) {
	if(node) {
		deleteNodes(node->left);
		deleteNodes(node->right);
		delete node;
	}
}

TreeNode::~TreeNode() {
	delete left;
	delete right;
	//deleteNodes(this);
}


unsigned TreeNode::getFrequency() {
	return frequency;
}
unsigned TreeNode::getVal() {
	return val;
}

bool TreeNode::isLeafNode() {
	if(this->left == NULL && this->right == NULL) { return true; }
	return false;
}

TreeNode * TreeNode::getLeft() {
	return left; 
}

TreeNode * TreeNode::getRight() {
	return right; 
}

void TreeNode::join(TreeNode * leftVal, TreeNode * rightVal) {
	this->left = leftVal;
	this->right = rightVal;
	
	this->frequency = leftVal->getFrequency() + rightVal->getFrequency();

}

