#include <iostream>
#include "Encoder.h"
#include "TreeNode.h"
#include "MinHeap.h"
#include "HuffTree.h"

Encoder::Encoder(char * file_path) {
	this->file_path = file_path;	
	in.open(file_path, ios::in|ios::binary);

	mh = new MinHeap();
	ht = new HuffTree();

	for(int i = 0; i < 256; i++) {
		frequency_table[i] = 0;
	}
}

MinHeap * Encoder::getMinHeap() {
	return mh;
}


void Encoder::buildFrequencyTable() {
	unsigned char ch;

	while(in.read((char*)&ch , 1)) {
		frequency_table[ch] = frequency_table[ch] + 1;

	}

	for(int i = 0; i < 256; i++) {
		if(frequency_table[i] != 0) {
			uniqueChars++;
		}		
	}
	in.close();
}

void Encoder::printFrequencies() {
	for(int i = 0; i < 256; i++) {
		if(frequency_table[i] != 0) {
			char c = i;
			if(c == ' ') { std::cout << "Space: " << frequency_table[i] << std::endl;}
			if(c == '\n') { std::cout << "NewLine: " << frequency_table[i] << std::endl;}
			else if(c != ' ' && c != '\n') {
				std::cout << c << ": " << frequency_table[i] << std::endl;
			}
		}
	}
}

void Encoder::encode() {
	for(int i = 0; i < 256; i++) {
		if(frequency_table[i] != 0) {
			char c = i;
			int freq = frequency_table[i];

			//Enables printing of frequency table during creation of tree.
			//cout << "char: " << c << freq << endl;

			mh->insert(new TreeNode(c, freq));
		}
	}
}

void Encoder::writeBody() {
	unsigned char bit_buffer;
	unsigned char ch;
		
	ifstream in2;
	in2.open(file_path);
	
	int writtenBits = 0;
	
	while(in2.read((char*)&ch, 1)) {	
		string code = ht->getCharCode(ch);
		//cout << code << endl;
		for(int i = 0; i < code.length(); i++) {
			bit_buffer = bit_buffer << 1;
			bit_buffer = bit_buffer | (code[i] - '0');
			
			writtenBits++;
			if(writtenBits == 8) {
				out.write(reinterpret_cast<const char*> (&bit_buffer), sizeof(bit_buffer));
				writtenBits = 0;
				bit_buffer = 0;
			}
		}
	}

	if(writtenBits != 0) {
		int toAdd = 8 - writtenBits;
		for(int i = 0; i < toAdd; i++) {
			bit_buffer = bit_buffer << 1;
			bit_buffer = bit_buffer | 0;
		}
		out.write(reinterpret_cast<const char*> (&bit_buffer), sizeof(bit_buffer));
	}
	in2.close();
}

void Encoder::writeHeader() {	
	out.write(reinterpret_cast<const char*> (&uniqueChars),2); 
	for(int i = 0; i < 256; i++) {
		if(frequency_table[i] != 0) {
			out.write(reinterpret_cast<const char*> (&i), 1);
			out.write(reinterpret_cast<const char*> (&frequency_table[i]), 4);
		}
	}
}

void Encoder::writeEncodedFile(string output_file_path) {
        out.open(output_file_path, ios::out|ios::binary);
    	writeHeader();  
	writeBody();
	out.close(); 
}


Encoder::~Encoder() {
	delete mh;
	delete ht;
}
