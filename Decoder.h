#ifndef DECODER_H
#define DECODER_H

#include <string>
#include "HuffTree.h"
#include "TreeNode.h"
#include "MinHeap.h"
#include <fstream>
#include <vector>

using namespace std;



class Decoder
{
	private:
		unsigned frequency_table[256];
		// You need to add more class memeber and methods
		string huff_file_path;		
		string out_file_path;

		ifstream in;
		ofstream out;

		int uniqueChars;
		int frequenciesSum;
		
		MinHeap * mh;
		HuffTree * ht;
		
		vector<int> * bits;
		
		TreeNode * seed;		


	public:
		//huff_file_path is the input (encoded) file that we 
		//want to decode
		Decoder(string huff_file_path, string out_file_path);
		
		bool tableEmpty();
		void tableAdd(unsigned char character, int frequency);
		void tableSum();
		void printFrequencies();

		//Fills up the frequency_table array where frequency_table[i] 
		//will contain the frequency of char with ASCII code i			
		//This method will read the header of the encoded file to 
		//extract the chars and their frequency
		void buildFrequencyTableFromFile();

		//Creates a min-heap and builds the Huffman tree
		void decode();

		//Writes the uncompressed file and save it as file_path
		void writeUncompressedFile(string file_path);

		~Decoder();

};

#endif
