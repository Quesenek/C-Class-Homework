/*
 * This program is a game of hangman, using functions the user is asked to enter a number
 * the word corresponding to the number that is entered by the user is read in from a file and then the game starts.
 * Every loop the user is prompted to enter a character for a guess, if the guess is correct the word is updated to show where the guess fits in.
 * If the guess is wrong then the number of guesses is increased and the corresponding scene is drawn to the screen.
 * When the user has either guessed the word correctly or the user has entered too many wrong characters the loop exits and displays either
 * a won or loss message.
 *
 * Date: September 28, 2018
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Prototypes for the functions
int gameNumber();
string selectedGameWord(int gameNum);
string gameWordGuessCopy(string gameWord);
void gameGuess(string &gameWordCopy, string gameWord, int &wrongGuesses);
void hangmanScene(int wrongGuesses);
void endGame(int wrongGuesses, string word, bool won);
bool checkIfWordGuessed(string gameWordCopy, string gameWord);

/*
 * Main function initializes variables and runs the main game loop.
 * 
 * Return:  status
 */
int main()
{
    // Initialize the user input getting the game number and the game string based on the number and make a copy of the word using *'s.
    int gameNum = gameNumber();
    string selectedGame = selectedGameWord(gameNum);
    string gameWordCopy = gameWordGuessCopy(selectedGame);

    // Variable to end the loop
    bool endLoop = false;
    
    // Counter for the main game loop that holds the amound of wrong guesses.
    int wrongGuesses = 0;

    // Display the scene for the number of wrong guesses.
    hangmanScene(wrongGuesses);

    // Main game loop, 
    // currently the only exit condition is when the number of wrong guesses is greater then 6.
    while (wrongGuesses <= 5 && !(checkIfWordGuessed(gameWordCopy, selectedGame)))
    {
        gameGuess(gameWordCopy, selectedGame, wrongGuesses);
    }

    // When the game loop is done hasWon is used to display whether the user has won or loss. 
    endGame(wrongGuesses, selectedGame, checkIfWordGuessed(gameWordCopy, selectedGame));

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

    // If the user inputs 0 a random number is chosen.
    if (gameNum < 1)
    {
        // Seed rand()
        srand(static_cast<int>(time(0)));

        // Use rand() to get a number between 1 and 5.
        gameNum = (1 + rand() % 5);
    }

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
 * gameWordGuessCopy takes the original word and creates a new word that is the same length of the original word
 * but is all *'s
 *
 * Parameter:   gameWord          The original word that is being used to make a copy of.
 * 
 * Return:  copy.
 */
string gameWordGuessCopy(string gameWord)
{
    string wordCopy;

    // Make a string the same length as the original consisting only of *'s.
    for (int i = 0; i < gameWord.length(); i++)
    {
        wordCopy.append("*");
    }

    return wordCopy;
}

/*
 * gameGuess takes gameGuess and wrongGuesses using pass by reference and gameWord as pass by value
 * using these it promts the user to enter a guess and then it checks to see if the guess is correct
 * if it's wrong it increases the number of wrongGuesses.
 * 
 * Parameter:   &gameWordCopy     A copy of the original word that reflects the guesses the player has gotten correct.
 * Parameter:   gameWord          The word the user is trying to guess.
 * Parameter:   &wrongGuesses     the number of wrong guesses.
 * 
 * Return:  void.
 */
void gameGuess(string &gameWordCopy, string gameWord, int &wrongGuesses)
{
    // Variables to hold the guess and a bool used to check if a guess was correct
    char guess = 0;
    bool isRightGuess = false;

    cout << gameWordCopy << endl;

    cout << "? ";
    cin >> guess;
    cout << endl;

    // Loop through the word and if the guess is the same as a char in the word it adds
    // the char to the word at the same location in the copy and then sets isRightGuess 
    // to true meaning that the guess was correct and not wrong. 
    for (int i = 0; i < gameWord.length(); i++)
    {
        if (gameWord.at(i) == guess)
        {
            gameWordCopy.at(i) = guess;
            isRightGuess = true;
        }
    }

    // If the guess was incorrect and isRightGuess was never changed to true Oops is output and
    // wrongGuesses is increased.
    if (!isRightGuess)
    {
        cout << "Oops" << endl;
        wrongGuesses++;
    }
    // hangmanScene is called no matter what, but it will only show the scene that corresponds with the number of wrongGuesses.
    hangmanScene(wrongGuesses);
}

/*
 * checkIfWordGuessed returns whether gameWordCopy and gameWord are the same.
 * 
 * Parameter:   gameWordCopy     A copy of the original word that reflects the guesses the player has gotten correct.
 * Parameter:   gameWord         The word the user is trying to guess.
 *
 * 
 * Return:  true or false.
 */
bool checkIfWordGuessed(string gameWordCopy, string gameWord)
{
    return (gameWordCopy == gameWord);
}

/*
 * endGame uses the number of wrong guesses and the bool won to display if the user has won or loss.
 * 
 * Parameter:   wrongGuesses     Number of wrong guesses the user has made.
 * Parameter:   word             The original word.
 * Parameter:   won              true if the user guess the correct word.
 * 
 * Return:  void.
 */
void endGame(int wrongGuesses, string word, bool won)
{
    // If the number of wrong guesses is greater than 5 and won == false it means the user has lost.
    // If the user has less than 6 wrong guesses and won == true then the user has won.
    if (wrongGuesses > 5 && !won)
    {
        cout << "You lost" << endl << "Answer: " << word;
    }
    else if (wrongGuesses < 6 && won) 
    {
        cout << "Congrats!" << endl << "Answer: " << word;
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