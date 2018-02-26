# Huffman Encoder and Decoder


This code allows you to use Huffman coding to encode and decode files.

The implementation uses a Node and Minheap implementation to generate the Huffman Codes needed to encode/decode a file.

Use the makefile to automatically compile all the necessary code, *Make sure all code is in the same directory*

Running this program in the command line requires 4 arguements:

# Encoding
`./huffman -e [fileInput] [fileOutput]`

# Decoding
`./huffman -d [fileInput] [fileOutput]`



***

NOTE: This program was created on a machine that stores bytes in Little Endian. Code may not work on machines that store in Big Endian

[Huffman Coding](https://en.wikipedia.org/wiki/Huffman_coding)
