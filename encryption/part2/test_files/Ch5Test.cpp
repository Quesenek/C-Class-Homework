#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    const int SHIFTNUM = 3;
    
    string currentLine = "";
    string previousLine = "";

    char shiftedCurrentChar;

    char readInChar;
	ifstream inFile;

    inFile.open("file4.txt");

    getline(inFile, currentLine);
    while(currentLine != previousLine)
    {
        for(int i = 0; i < currentLine.length(); i++)
        {
            if (islower(currentLine.at(i)))
            {
                cout << currentLine.at(i) << " - ";

                shiftedCurrentChar = static_cast<int>(static_cast<char>(currentLine.at(i))) + SHIFTNUM;
                shiftedCurrentChar = ((shiftedCurrentChar - 'a') % 26) + 'a';

                cout << shiftedCurrentChar << endl;
            }
            else
            {
                cout << currentLine.at(i) << endl;
            }

        }
        cout << endl;

        previousLine = currentLine;
        getline(inFile, currentLine);
    }

    inFile.close();

    return 0;
}