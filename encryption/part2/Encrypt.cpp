/*
 * Program to read in a file and encrypt each of the characters if the character is lowercase.
 * Depending on what option is chosen the character can be:
 * - not encrypted and passed through to output.
 * - shifted forward 3 characters.
 * - shifted backward 3 characters.
 * - a hash number generated.
 * - every other character is duplicated.
 * - if there are duplicate characters next to eachother one is removed. 
 *
 * Date: September 15, 2018
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
 * main - asks for the encryption option the user wants to use, then with the use of if statements the option chosen is output to the screen.
 *
 * Return:      status
 */

int main()
{
    // Const to hold the amount to shift the characters.
    const int SHIFTNUM = 3;
    
    // String variables to control the loops and the output
    string currentLine = "";
    string previousLine = "";
    string finalOutput = "";

    string fileName;

    // Variables to compare whether a character is repeated
    string currentChar;
    string previousChar;

    // Variable to hold the new shifted characater value
    int shiftedCurrentChar;

    int hash = 0;

    // Counter for option 5
    int counter = 0;
    
    // Variable to hold the type of encryption.
    int typeOfEncryption;

    // in file stream
    ifstream inFile;

    // Ask the user ? and the user enters the type of encryption and the file name.
    cout << "? ";
    cin >> typeOfEncryption >> fileName;
    cout << endl;

    // Open the file and grab the first char in the file.
    inFile.open(fileName);

    // Get first line of file
    getline(inFile, currentLine);
    
    // Through testing I found that no matter how many times getline is called
    // once it gets the last line it keeps getting the same last line so the loop runs until a duplicate is found.
    while (currentLine != previousLine)
    {
        // Nested loop that parses through each line.
        for (int i = 0; i < currentLine.length(); i++)
        {
            // If the character is lowercase it runs the type of encryption the user specifies.
            if (islower(currentLine.at(i)))
            {
                
                if (typeOfEncryption == 1)
                {
                    // Option 1 just outputs the char to the screen unmodified.
                    finalOutput += currentLine.at(i);
                }
                else if (typeOfEncryption == 2) 
                {
                    // Shifts a char 3 values to the right
                    shiftedCurrentChar = static_cast<char>(currentLine.at(i)) +  SHIFTNUM;
                    shiftedCurrentChar = ((shiftedCurrentChar - 'a') % 26) + 'a';

                    // Adds the value to the output string.
                    finalOutput += static_cast<char>(shiftedCurrentChar);
                }
                else if (typeOfEncryption == 3) 
                {
                    // Shifts a char 23 values to the right which results in being the same as what a user would expect -3 to do.
                    shiftedCurrentChar = static_cast<char>(currentLine.at(i)) + (26 - SHIFTNUM);
                    shiftedCurrentChar = ((shiftedCurrentChar - 'a') % 26) + 'a';

                    // Adds the value to the output string.
                    finalOutput += static_cast<char>(shiftedCurrentChar);
                }
                else if (typeOfEncryption == 4)
                {
                    // Here the current parsed value is turned into a character and added to the hash.
                    hash += static_cast<char>(currentLine.at(i));
                }
                else if (typeOfEncryption == 5)
                {
                    // To get every other character a counter is used to increase every loop and when the counter
                    // is divisible by 2 it means the counter is even and a duplicate character is added on.
                    if ((counter % 2) == 0)
                    {
                        finalOutput += currentLine.at(i);
                    }

                    // Adds the value to the output string.
                    finalOutput += currentLine.at(i);

                    counter++;
                }
                else if (typeOfEncryption == 6)
                {
                    // Starts off by adding the currently parsed value to the first comparison variable
                    currentChar = currentLine.at(i);

                    // Checks if the current value is equal to the one behind it in the list
                    // if it's not equal the currently parsed value is added to the final output.
                    // Otherwise the character is passed on and not added to the final output.
                    if (currentChar != previousChar)
                    {
                        finalOutput += currentLine.at(i);
                    }

                    previousChar = currentChar;

                }
            }
            else
            {
                // This catches all of the values that are not lowercase.
                // Since the hash encryption type is a different type of output
                // this checks what type of encryption the user is using to output the correct values.
                if (typeOfEncryption == 4) 
                {
                    hash += 0;
                }
                else
                {
                    finalOutput += currentLine.at(i);
                }
            }
        }

        previousLine = currentLine;
        getline(inFile, currentLine);

        if (currentLine != previousLine)
        {
            // Output a new line character to style the output the same as the input.
            finalOutput += '\n';
        }
    }

    // close the file when done.
    inFile.close();

    // This is where things are output
    // Since the hash is a different type of output
    // this checks what type of encryption is used before moving further.
    if (typeOfEncryption == 4)
    {
        // Variables for the first and second output values.
        int hash1;
        int hash2;

        // Get second output value and then cut that off the end to get the first output value.
        hash2 = hash % 10;
        hash /= 10;
        hash1 = hash % 10;

        cout << hash1 << hash2 << endl;
    }
    else
    {
        // Output the string that was built in the loop.
        cout << finalOutput << endl;
    }

    //Pause output
    cin.ignore(100, '\n');
    cin.get();
    return 0;
}