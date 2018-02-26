#include <iostream>
#include "HuffTree.h"
#include "TreeNode.h"
#include "MinHeap.h"

HuffTree::HuffTree() {
	for(int i = 0; i < 256; i++) {
		bitcode_table[i] = "";
	}
}

HuffTree::~HuffTree() {
	delete root;
}

TreeNode * HuffTree::getRoot() {
	return root;
}

void HuffTree::printBitCodes() {
	for(int i = 0; i < 256; i++) {
		if(bitcode_table[i] != "") {
			char c = i;
			string bitCode = bitcode_table[i];
			if(c == '\n') { std::cout << "NewLine: " << bitCode << std::endl; }
			else if(c == ' ') { std::cout << "Space: " << bitCode << std::endl; }
			else if(c == 0) { std::cout << "NULL: " << bitCode << std::endl; }
			else {
				std::cout << c << ": " << bitCode << std::endl;
			}
		}
	}
}

void HuffTree::buildTree(MinHeap * mh) {
	while(mh->getSize() > 1) {
		TreeNode * n1 = mh->removeMin();
		TreeNode * n2 = mh->removeMin();
			
		char ch = n1->getVal();
		char ch2 = n2->getVal();	

		//Optional printing of node values and frequencies pulled from MinHeap
		/*	
		cout << "n1 Val: " << ch << endl << "n1 Freq: " << n1->getFrequency() << endl;
		cout << "n2 Val: " << ch2 << endl << "n2 Freq: " << n2->getFrequency() << endl;
		//cout << endl; 
		*/	


		//Frequency calculated in join function
		TreeNode * n3 = new TreeNode('*', 0);	
		n3->join(n1, n2);

		//Optional printing of a succeful join and its frequency
		/*
		cout << "JOINED" << endl << endl;
		cout << "JOINED FREQ: " << n3->getFrequency() << endl;		
		*/

		
		if(mh->getSize() == 0) { 
			root = n3;
			//delete n3;
			break;
		}
		
		mh->insert(n3);		
	}

	//Optional print value of Root
	/*		
	cout << "-------ROOT------" << endl;
	char cl = root->getLeft()->getVal();
	cout << "ROOT LEFT: " << cl << endl;
	cout << "ROOT LEFT FREQ: " << root->getLeft()->getFrequency() << endl << endl;

	char cr = root->getRight()->getVal();
	cout << "ROOT RIGHT: " << cr << endl;
	cout << "ROOT RIGHT FREQ: " << root->getRight()->getFrequency() << endl;
	cout << endl;
	
	char rv = root->getVal();
	cout << "ROOT VAL: " << rv << endl;
	cout << "ROOT FREQ: " << root->getFrequency() << endl << endl;
	*/	

}


void HuffTree::generateCodes(TreeNode * root, string code) {
	
	if(root->isLeafNode()) {
		bitcode_table[root->getVal()] = code;
	}
	
	if(root->getLeft() != NULL) {
		generateCodes(root->getLeft(), code + "1");
	}

	if(root->getRight() != NULL) {
		generateCodes(root->getRight(), code + "0");
	}
}

string HuffTree::getCharCode(int c) {
	return bitcode_table[c];

}
