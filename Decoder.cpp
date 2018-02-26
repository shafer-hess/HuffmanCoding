#include <iostream>
#include "Decoder.h"

Decoder::Decoder(string huff_file_path, string out_file_path) {
	this->huff_file_path = huff_file_path;
	this->out_file_path = out_file_path;	

	in.open(huff_file_path, ios::in|ios::binary);

	mh = new MinHeap();
	ht = new HuffTree();

	bits = new vector<int>();
	frequenciesSum = 0;

	for(int i = 0; i < 256; i++) {
		frequency_table[i] = 0;
	}

}

void Decoder::buildFrequencyTableFromFile() {
		int x = 0;		
		
		in.read(reinterpret_cast<char*> (&x),2); 	
		uniqueChars = x;
		

		unsigned character;
		int frequency;		
		for(int i = 0; i < uniqueChars; i++) {
			in.read(reinterpret_cast<char*>(&character), 1);	
			in.read(reinterpret_cast<char*>(&frequency), 4);
			tableAdd(character, frequency);
		}
}

char ch;
void Decoder::decode() {
	//Build MinHeap
	for(int i = 0; i < 256; i++) {
		if(frequency_table[i] != 0) {
			mh->insert(new TreeNode((char) i, frequency_table[i]));
		}
	}
	
	//Build HuffTree and get Root
	ht->buildTree(mh);
	ht->generateCodes(ht->getRoot(), "");
	//ht->printBitCodes();
	
	//Loop to gather bits and store in vector	
	while(in.good()) {
		unsigned char input;
		in.read(reinterpret_cast<char*>(&input), 1);
			
		for(int i = 7; i >= 0; i--) {
			int mask = 1 << i;
			if(input & mask) { bits->push_back(1); }
			else { bits->push_back(0); }
		}
	
	}
	seed = ht->getRoot();
	tableSum();	

	/*
	//Optional printing of Remaining Bytes separated by newlines
	int count = 0;	
	for(vector<int>::iterator it = bits->begin(); it != bits->end() - 8; ++it) {
		cout << *it;
		count++;
		if(count % 8 == 0) { cout << endl; }
	}	
	cout << endl;				
	*/

	/*
	//Optional printing of all bytes in a single line
	for(vector<int>::iterator it = bits->begin(); it != bits->end() - 8; it++) {
		//cout << *it;
	}
	cout << endl;
	*/
	
	FILE * fd = fopen(out_file_path.c_str(), "w");	
	
	for(vector<int>::iterator it = bits->begin(); it != bits->end(); ++it) { 	
		if(frequenciesSum == 0) { 
			fclose(fd);
			in.close();
			return;
		}		
	
		if(seed->getLeft() == NULL && seed->getRight() == NULL) {
			//cout << (char) seed->getVal();
			ch = seed->getVal();
			putc(ch, fd);
			frequenciesSum--;
			seed = ht->getRoot();	
		}
			
		if(*it == 1) {
			seed = seed->getLeft();
		}		
			
		if(*it == 0) {
			seed = seed->getRight();
		}	
	}			
	cout << endl;
}

bool Decoder::tableEmpty() {
	int flag = 1;
	for(int i = 0; i < 256; i++) {
		if(frequency_table[i] != 0) {
			flag = 0; 
		}	
	}
	return flag;
}

void Decoder::tableAdd(unsigned char character, int frequency) {
	frequency_table[character] = frequency;
}

void Decoder::tableSum() {
	frequenciesSum = 0;
	for(int i = 0; i < 256; i++) {
		if(frequency_table[i] != 0) {
			frequenciesSum += frequency_table[i];
		}
	}
}

/*
void Decoder::printFrequencies() {
	for(int i = 0; i < 256; i++) {
		if(frequency_table[i] != 0) {
			char c = i;
			cout << c << ": " << frequency_table[i] << endl;
		}
	}
}
*/

Decoder::~Decoder() {
	delete mh;
	delete ht;
	delete bits;
}

