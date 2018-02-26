#ifndef ENCODER_H
#define ENCODER_H


#include <string>
#include "MinHeap.h"
#include "HuffTree.h"
#include <fstream>
using namespace std;

class Encoder
{
	private:
		unsigned frequency_table[256];
		int uniqueChars;

		char * file_path;
		
		ifstream in;
		ofstream out;
		
		MinHeap * mh;

	public:

		HuffTree * ht;

		//test_file_path is the input (decoded) file
		Encoder(char * file_path); 
		
		//Fills up the frequency_table array where frequency_table[i] 
		//will contain the frequency of char with ASCII code i		
		void buildFrequencyTable(); 

		//Builds the min heap  and run the encoding algorithm
		void encode();

		//Generates the encoded file and save it as output_file_path
		void writeEncodedFile(string output_file_path);
	
		void writeHeader();
		void writeBody();	

		~Encoder();

		void printFrequencies();
		MinHeap * getMinHeap();
};

#endif
