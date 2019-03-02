/*
 * Program to read in a file and encrypt the first character if it's lowercase.
 * Depending on what option is chosen the character can be:
 * - not encrypted and passed through to output.
 * - shifted forward 3 characters.
 * - shifted backward 3 characters.
 * - a hash number generated.
 *
 * Date: September 8, 2018
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

/*
 * main - asks for the encryption option the user wants to use then with the use of if statements the option chosen is output to the screen.
 *
 * Return:      status
 */

int main()
{
    // Variables that hold the alphabet and the alphabet after shifting it.
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string shiftedAlphabet = alphabet;
    string fileName = "";
    string charShifted;

    // Variables to create the hash.
    string hash;
    string charToHash;

    // Variable to hold the location of the char in the alphabet string.
    int charNumber = 0;
    
    // Variable to hold the type of encryption.
    int typeOfEncryption;

    // Variable to hold the value of the char from the file.
    char charEntered;

    // in file stream
    ifstream inFile;

    // Ask the user ? and the user enters the type of encryption and the file name.
    cout << "? ";
    cin >> typeOfEncryption >> fileName;
    cout << endl;

    // Open the file and grab the first char in the file.
    inFile.open(fileName);
    inFile.get(charEntered);
    inFile.close();
    // Check if the char grabbed is lowercase.
    // If it's lowercase it proceeds into the if statement.
    // Otherwise it just outputs the character.
    if (islower(charEntered))
    {
        // If statements for each of the encryption options.
        if (typeOfEncryption == 1)
        {
            // Option 1 just outputs the char to the screen unmodified.
            cout << charEntered << endl;
        }
        else if (typeOfEncryption == 2) 
        {
            // Option 2 uses the algorithm library to take the alphabet string and shifts everything + 3 characters.
            // Using rotate makes it so that the original spot that the character was on is now occupied by the character + 3 spaces.
            // Doing this prevents the need to use an if statement to roll back around the alphabet z -> a.
            rotate(shiftedAlphabet.begin(), shiftedAlphabet.begin() + 3, shiftedAlphabet.end());
        }
        else if (typeOfEncryption == 3) 
        {
            // Option 3 uses the algorithm library to take the alphabet string and shifts everything + 23 characters.
            // The only thing different about this and #2 is that rotate only works by shifting things to the left/forward.
            // So in order to shift things backward 3 spaces and output the correct character it is shifted forward 23 spaces.
            rotate(shiftedAlphabet.begin(), shiftedAlphabet.begin() + 23, shiftedAlphabet.end());
        }
        else if (typeOfEncryption == 4)
        {
            // Option 4 casts the int values of a char to a string and then the last two characters are appended to the hash string.
            charToHash = to_string(static_cast<int>(charEntered));

            hash += (charToHash.at((charToHash.length() - 2)));            
            hash += (charToHash.at((charToHash.length() - 1)));

            cout << hash << endl;
        }

        // This if statement checks if the encryption type is 2 or 3
        // and then grabs the correct character out of the shifted alphabet 
        // using the location of the original character in the unshifted alphabet.

        // the reason for the check is that 2 and 3 have an extra step for the output.
        if (typeOfEncryption == 2 || typeOfEncryption == 3)
        {
            charNumber = alphabet.find(charEntered);
            charShifted = shiftedAlphabet.at(charNumber);

            cout << charShifted << endl;
        }
    }
    else
    {
        // Output 0 for all non-lowercase characters if hash is being calculated.      
        if (typeOfEncryption == 4)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << charEntered << endl;
        }
        
    }

    // Pause output
    cin.ignore(100, '\n');
    cin.get();
    return 0;
}