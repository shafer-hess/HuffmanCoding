#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include "MinHeap.h"
#include "Encoder.h"
#include "Decoder.h"
#include "HuffTree.h"
using namespace std;

void printHelp(){
	cout << "Invalid arguments." << endl;
	cout << "Type \"huffman [mode] [arguments]\" where mode and its arguments are one of the following:" << endl;
	cout << "-e [src] [dest]: encode the source file and place the result into the specified destination" << endl;
	cout << "-d [src] [dest]: decode the source file and place the result into the specified destination" << endl;
	exit(1);
}

int main (int argc, char** argv){

	if(argc < 4) {
		printHelp();
	}
	
	Encoder * encoder;
	Decoder * decoder;

	if(strcmp(argv[1], "-e") == 0) {
		char * filePath = argv[2];
		char * fileOut = argv[3];
		
		encoder = new Encoder(filePath);
		encoder->buildFrequencyTable();
		//encoder->printFrequencies();		

		encoder->encode();
		encoder->ht->buildTree(encoder->getMinHeap());
		encoder->ht->generateCodes(encoder->ht->getRoot(), "");
		//encoder->ht->printBitCodes();
		encoder->writeEncodedFile(fileOut);
		delete encoder;
			
	}

	if(strcmp(argv[1], "-d") == 0) {
		char * fileIn = argv[2];
		char * fileOut = argv[3];

		decoder = new Decoder(fileIn, fileOut);
		decoder->buildFrequencyTableFromFile();
		decoder->decode();
		delete decoder;
		
	}

	//delete decoder;

	return 0;
}
