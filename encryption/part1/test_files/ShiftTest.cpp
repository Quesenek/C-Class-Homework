#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    // string alphabet = "abcdefghijklmnopqrstuvwxyz";
    // string shiftedAlphabet = alphabet;

    // int charNumber = 0;
    // char charEntered = 'y';
    // char charShifted;

    // cout << alphabet.length() << endl;
        
    // int typeOfEncryption = 3;

    // if (typeOfEncryption == 2) {
    //     rotate(shiftedAlphabet.begin(), shiftedAlphabet.begin() + 3, shiftedAlphabet.end());
    // }
    // else if (typeOfEncryption == 3) { 
    //     rotate(shiftedAlphabet.begin(), shiftedAlphabet.begin() + 23, shiftedAlphabet.end());
    // }

    // charNumber = alphabet.find(charEntered);
    // charShifted = shiftedAlphabet.at(charNumber);


    // cout << charEntered << " | " << alphabet << endl << charShifted << " | " << shiftedAlphabet << endl << endl;

    char char1 = 'y';
    int newChar;

    cout << char1 << endl;
    
    newChar = static_cast<int>(char1) + 3;

    cout << "newChar after + 3: \t" << newChar << endl
         << "'a' \t" << static_cast<int>('a') << endl 
         << "newChar - 'a': \t" << static_cast<int>((newChar - 'a')) << endl
         << "(newChar - 'a') mod 26: \t" << static_cast<int>(((newChar - 'a') % 26)) << endl
         << "((newChar - 'a') mod 26) + 'a': \t" << static_cast<char>((((newChar - 'a') % 26) + 'a')) << endl;

    newChar = ((newChar - 'a') % 26) + 'a';

    return 0;
}