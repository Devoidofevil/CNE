#include <bits/stdc++.h>
#define LENGTH 1000000

using namespace std;

class Huffnode{
	public:
		unsigned char c;
		int freq;
		Huffnode *left = NULL;
		Huffnode *right = NULL;
		Huffnode( unsigned char ci , int freqi , Huffnode *lefti , Huffnode *righti ) {
			c = ci;
			freq = freqi;
			left = lefti;
			right = righti;
		}
};

int outbufIndex = 0;
typedef pair< int, Huffnode* > pqnode;
unsigned char buffer[LENGTH];
unsigned char outbuf[LENGTH];
map < unsigned char, string > encoded;

Huffnode *createHuffTree( priority_queue < pqnode , vector < pqnode > , greater < pqnode > > huffmanHeap ) {
	while( huffmanHeap.size() != 1 ) {
		// Extract nodes with minimum node, create a new node with frequence as their sum, push it into the p-queue while updating its left and right child
		int charFreq1 = huffmanHeap.top().first;
		Huffnode *huffnode1 = huffmanHeap.top().second;
		huffmanHeap.pop();

		int charFreq2 = huffmanHeap.top().first;
		Huffnode *huffnode2 = huffmanHeap.top().second;
		huffmanHeap.pop();

		huffmanHeap.push( make_pair( charFreq1 + charFreq2 , new Huffnode( 0 , charFreq1 + charFreq2 , huffnode1 , huffnode2 ) ) );

	}
	return huffmanHeap.top().second;
}

void encodeChar( Huffnode *root, string Code ) {
	if( !root )
		return;
	if( !root->left && !root->right ) {
		encoded[ root->c ] = Code;
		return;
	}
	encodeChar( root->left , Code + "0" );
	encodeChar( root->right , Code + "1" );
}

void createOutBuffer( size_t fileLengthInBytes ) {
	int count = 0;
	//0 is 00000000 in binary. So |'ing with that bit by bit will give us the same string in binary.
	outbuf[ 0 ] = 0;
	for ( int bytenum = 0 ; bytenum < fileLengthInBytes ; bytenum++ ) {
		string currEncodedByte = encoded[ buffer[ bytenum ] ];
		for( int bitpos = 0; bitpos < currEncodedByte.length() ; bitpos++ ) {
			int shift = 7 - count;
			outbuf[ outbufIndex ] = outbuf[ outbufIndex ] | ( currEncodedByte[bitpos] - '0' ) << shift ;
			count++;
			if( count == 8 ) {
				count = 0;
				outbufIndex++;
				outbuf[outbufIndex] = 0;
			}
		}
	}
	if( count != 0 )
		outbufIndex++;
}

size_t readFile( char inputFileName[] ) {
	FILE *input = fopen(inputFileName, "rb");
	if (input == NULL) {
		cout << "Error opening file";
		return 0;
	}

	size_t bytes_read;
	bytes_read = fread(buffer, sizeof(unsigned char), sizeof(buffer), input);
	if (bytes_read == 0) {
		cout << "Error reading file";
		return 0;
	}
	fclose(input);
	return bytes_read-1;
}

void write_tree(FILE *out) {			//writes all encoded stuff into the file
    for (int i = 0; i < 256; i++) {
        unsigned char x = i;
        if (encoded.find(x) != encoded.end()) {
            fprintf(out, "%d %s\n", i, encoded[x].c_str());
        }
    }
    fprintf(out, "%d %c\n",0,'0');
}

void writeFile( char outputFileName[] ) {
	FILE *out = fopen(outputFileName, "wb");
	if (out == NULL) {
		cout << "Error writing to file";
		return;
	}
	write_tree(out);
	fwrite(outbuf, sizeof(unsigned char), outbufIndex, out);                //finally puts in the output binary data
	fclose(out);
}

int main( int argc, char *argv[] ) {
	if( argc != 3 ) {
		cout << "Error in input. Format :- compress <inputfilename> <outputfilename>";
		return 0;
	}
	size_t fileLengthInBytes = readFile(argv[1]);
	map <unsigned char, int> charFreq;

	// Now calculating the frequency of characters
	for( int i = 0; i < fileLengthInBytes ; i++ )
		charFreq[buffer[i]]++;
	
	priority_queue < pqnode , vector < pqnode > , greater < pqnode > > huffmanHeap;

	// Creating Huffman priority queue (least frequent character at top)
	for( int i = 0; i < 256 ; i++ ) {
		if( charFreq[i] != 0 ) {
			char c = i;
			Huffnode *huffnode = new Huffnode( c , charFreq[i] , NULL , NULL );
			huffmanHeap.push( make_pair( charFreq[i] , huffnode) );
		}
	}

	// Creating Huffman tree
	Huffnode *root = createHuffTree( huffmanHeap );	
	
	// Mapping each character to encoded string
	encodeChar( root , "" );
	//Writing output to file argv[2]	
	createOutBuffer( fileLengthInBytes );
	outbuf[outbufIndex]='\0';
	writeFile( argv[2] );	

	return 0;
}
