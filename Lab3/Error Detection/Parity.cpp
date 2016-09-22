#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

string input;

void getParity() {
	cout<<"Enter input :: \n";
	cin>>input;
	int numOfOnes = 0;
	for(int i = 0; i < input.length() ; i++ ) 
		if(input[i] == '1')		numOfOnes++;
	cout<<"Added Parity Bit to MSB of input ::\n";
	cout<<numOfOnes%2<<" "<<input<<"\n";
}

void checkParity() {
	cout<<"Enter input :: \n";
	cin>>input;
	int numOfOnes = 0;
	for(int i = 0; i < input.length() ; i++ ) 
		if(input[i] == '1')		numOfOnes++;
	cout<<"Parity Bit of string is :: "<<numOfOnes%2<<"\n";
}

int main(int argc,char *argv[]) {
	while(1) {
		cout<<"Note :: 0 is even parity and 1 is odd parity\n\n";
		cout<<"Select :: \n";
		cout<<"1. Generate Parity :: Press G/g.\n";
		cout<<"2. Check Parity    :: Press C/c.\n";
		cout<<"3. Exit            :: Press E/e.\n";
		char c;
		cin>>c;
		switch(c) {
			case 'g':
			case 'G':
				getParity();
				break;
			case 'c':
			case 'C':
				checkParity();
				break;
			case 'e':
			case 'E':
				return 0;
				break;
			default:
				cout<<"Enter a valid choice.\n";
		}
	}
	return 0;
}