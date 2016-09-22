#include <bits/stdc++.h>
using namespace std;

string getRem(string input, string divisor) {
    string res = input;

    for (int i = 0; i < divisor.length() - 1; i++) {
        res += "0";
    }

    for (int p2 = 0; p2 < res.length() - divisor.length() + 1; p2++) {
        if (res[p2] == '0') {
            continue;
        }
        for (int j = 0; j < divisor.length(); j++) {
            res[p2+j] = '0' + ((res[p2+j] - '0') ^ (divisor[j] - '0'));
        }
    }
    string remain;
    for (int i = res.length() - divisor.length() + 1; i < res.length(); i++) {
        remain += res[i];
    }
    return remain;
}

string checkRem(string input, string divisor) {
    string res = input;
    for (int p2 = 0; p2 < input.length() - divisor.length() + 1; p2++) {
        if (res[p2] == '0') {
            continue;
        }
        for (int j = 0; j < divisor.length(); j++) {
            res[p2+j] = '0' + ((res[p2+j] - '0') ^ (divisor[j] - '0'));
        }
    }
    return res;
}

void genCRC() {
    cout << "input: ";
    string input;
    cin >> input;

    string divisor = "1010";

    string remain = getRem(input, divisor);
    cout << "Remainder: " << remain << endl;
    cout << "CRC: " << input + remain << endl;
}

void checkCRC() {
    cout << "CRC: ";
    string crc;
    cin >> crc;

    string divisor = "1010";

    string remain = checkRem(crc, divisor);
    cout << "Remainder: " << remain << endl;
}

int main() {
    while (1) {
        cout<<"Select ::\n";
        cout<<"1.Enter 'g' to generate a CRC.\n2.Enter 'c' to check CRC.\n3.Enter 'e' to exit \n";
        char ch;
        cin >> ch;
        switch(ch) {
            case 'g':
                genCRC();
                break;
            case 'c':
                checkCRC();
                break;
            case 'e':
                return 0;
            default:
                cout<<"Enter valid choice\n";
        }
    }
    return 0;
}
