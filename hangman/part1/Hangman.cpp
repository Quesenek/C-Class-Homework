/*
 * This program is a game of hangman, using functions the user is asked to enter a number
 * the word corresponding to the number that is entered by the user is read in from a file and then the game starts.
 * Every loop the scene function is used to output the scene that corresponds with the number of wrong guesses.
 * When the number of wrong guesses equals 6 the loop is exited and a function is used to determine if the user has won or loss.
 *
 * Date: September 21, 2018
 */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Prototypes for the functions
int gameNumber();
string selectedGameWord(int gameNum);
bool gameWordGuessed(string gameWord, string userWord);
void hangmanScene(int wrongGuesses);
void hasWon(int wrongGuesses, string word);

/*
 * Main function initializes variables and runs the main game loop.
 * 
 * Return:  status
 */
int main()
{
    // Initialize the user input getting the game number and the game string based on the number.
    int gameNum = gameNumber();
    string selectedGame = selectedGameWord(gameNum);
    
    // Counter for the main game loop that holds the amound of wrong guesses.
    int wrongGuesses = 0;

    // Main game loop, 
    // currently the only exit condition is when the number of wrong guesses is greater then 6.
    while (wrongGuesses <= 6)
    {
        // Display the scene for the number of wrong guesses.
        hangmanScene(wrongGuesses);
        wrongGuesses++;
    }
    // When the game loop is done hasWon is used to display whether the user has won or loss. 
    hasWon(wrongGuesses, selectedGame);

    cin.ignore(100, '\n');
    cin.get();
    return 0;
}

/*
 * gameNumber asks the user for a game number and gets the user input.
 * 
 * Return:  number user inputs.
 */
int gameNumber()
{
    int gameNum;

    cout << "Game? ";
    cin >> gameNum;
    cout << endl;

    return gameNum;
}

/*
 * selectedGameWord opens the file word.txt and using the number entered in gameNumber
 * it reads in the words in the file until it gets to the word that corresponds with the number entered.
 * 
 * Parameter:   gameNum     the number entered by the user.
 * 
 * Return:  word read from file.
 */
string selectedGameWord(int gameNum)
{
    ifstream inFile;
    int count = 0;
    string word;

    inFile.open("word.txt");

    // Read in each word from the file until the loop exits on the number the user entered.
    // If the user enters a number that would go past the EOF the loop exits once the EOF is hit 
    // and the last word read is the value that is sent back as the game word.
    while (!inFile.eof() && count < gameNum)
    {
        inFile >> word;
        count++;
    }

    inFile.close();

    return word;
}

/*
 * hasWon uses the number of wrong guesses to display if the user has won or loss.
 * 
 * Parameter:   wrongGuesses     Number of wrong guesses the user has made.
 * Parameter:   word             The original word.
 * 
 * Return:  void.
 */
void hasWon(int wrongGuesses, string word)
{
    // If the number of wrong guesses is greater than 6 it means the user has lost.
    if (wrongGuesses > 6)
    {
        cout << "You lost" << endl << "Answer: " << word;
    } 
}

/*
 * hangmanScene uses the number of wrong guesses and displays a hangman scene that corresponds with the number.
 * 
 * Parameter:   wrongGuesses     Number of wrong guesses the user has made.
 * 
 * Return:  void.
 */
void hangmanScene(int wrongGuesses)
{
    switch (wrongGuesses)
    {
        case 0:
            cout << "L----+----" << endl
                 << "|"          << endl
                 << "|"          << endl
                 << "|"          << endl
                 << "X"          << endl 
                                 << endl;
            break;
        case 1:
            cout << "L----+----" << endl
                 << "|    O"     << endl
                 << "|"          << endl
                 << "|"          << endl
                 << "X"          << endl 
                                 << endl;
            break;
        case 2:
            cout << "L----+----" << endl
                 << "|    O"     << endl
                 << "|    |"     << endl
                 << "|"          << endl
                 << "X"          << endl 
                                 << endl;
            break;
        case 3:
            cout << "L----+----" << endl
                 << "|    O"     << endl
                 << "|   /|"     << endl
                 << "|"          << endl
                 << "X"          << endl 
                                 << endl;
            break;
        case 4:
            cout << "L----+----" << endl
                 << "|    O"     << endl
                 << "|   /|\\"   << endl
                 << "|"          << endl
                 << "X"          << endl 
                                 << endl;
            break;
        case 5:
            cout << "L----+----" << endl
                 << "|    O"     << endl
                 << "|   /|\\"   << endl
                 << "|   / "     << endl
                 << "X"          << endl 
                                 << endl;
            break;
        case 6:
            cout << "L----+----" << endl
                 << "|    O"     << endl
                 << "|   /|\\"   << endl
                 << "|   / \\"   << endl
                 << "X"          << endl 
                                 << endl;
            break;
    }
}