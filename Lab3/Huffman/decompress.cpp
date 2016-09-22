#include <bits/stdc++.h>
#define LENGTH 1000000

using namespace std;

int output_buffer_size = 0;
unsigned char buffer[LENGTH];
unsigned char output_buffer[LENGTH];

map < string , unsigned char > decoded;

void readFile( char inputFileName[] ) {
	int i;
	FILE *input = fopen(inputFileName, "rb");
	if (input == NULL) {
		cout << "Error opening file";
		return;
	}

	//creating decoding map
	while(1) {
		int inp;
        unsigned char y;
        char arr[300];
        fscanf(input, "%d %s\n", &inp, arr);
        string str (arr);
        y = inp;
        if (y == 0 && str == "0") {
            break;
        }
		decoded.insert(make_pair(str,y));
	}

	//taking the binary encoded input into buffer
	size_t bytes_read = fread(buffer,sizeof(unsigned char),sizeof(buffer),input);
	if(bytes_read==0) {
		printf("Error!");
		return;
	}
	fclose(input);

	//Creating the bin-encoded input file from the buffer(basically decoding the binary string to an integer value between 0-255)
	string currstr = "";
	for (i=0 ; i < bytes_read ; i++) {
	    for (int pos = 7; pos >= 0; pos--) {
	        unsigned char res = buffer[i] & (1 << pos);
	        if (res == 0) {
	            currstr += "0";
	        } else {
	            currstr += "1";
	        }
	        if (decoded.find(currstr) != decoded.end()) {
	            //cout << decoded[currstr] << endl;
	            output_buffer[output_buffer_size] = decoded[currstr];
	            output_buffer_size++;
	            currstr = "";
	        }
	    }
	} 
}

void writeFile( char outputFileName[] ) {
	FILE *out = fopen(outputFileName, "wb");
	if (out == NULL) {
		cout << "Error writing to file";
		return;
	}
	fwrite(output_buffer, sizeof(unsigned char), output_buffer_size, out);                //finally puts in the output binary data
	fclose(out);
}

int main( int argc, char *argv[] ) {
	if( argc != 3 ) {
		cout << "Error in input. Format :- compress <inputfilename> <outputfilename>";
		return 0;
	}
	readFile(argv[1]);
	writeFile( argv[2] );	

	return 0;
}
