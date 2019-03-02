/* 
 * Flash card program that reads in a file and asks the user to guess the answer.
 * If the answer is guessed correctly then it moves on to the next question and answer.
 * If the user guesses wrong 3 times then the question is guessed incorrectly and it will move
 * to the next question and answer. If the user doesn't answer all of the questions correctly the first time
 * the user is given a second chance to answer them, if the user still doesn't answer them correctly a reminder
 * to study the ones missed will be displayed.
 * 
 * Date:   October 20, 2018 
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// enum holding the states the user can be in.
enum UserState{ ANSWERING, CORRECT, INCORRECT };

const int ARRAYSIZE = 10;

// function prototype.
UserState getUserState(string guess, string answer, int &guessesIncorrect);

/*
 * main - main loop that reads in a file in sets of questions and answers
 * 
 * Return:     status 
 */

int main()
{
    // String variables
    string fileName = "";
    string currentLine = "";
    string guess = "";

    // temp variable to hold the number of questions.
    // Variable to hold the number of incorrect guesses.
    int numQuestions = 0;
    int guessesIncorrect = 0;

    // Create arrays to hold the questions and answers and also a boolean array to store what questions the user got wrong.
    string questionArray[ARRAYSIZE];
    string answerArray[ARRAYSIZE];
    bool correctAnswerArray[ARRAYSIZE];

    // Initialize the arrays.
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        questionArray[i] = "";
        answerArray[i] = "";
        correctAnswerArray[i] = false;
    }
    
    // Enum variable
    UserState uState;

    // file stream variable
    ifstream inFile;

    // Ask the user for the name of the file and gets the line.
    cout << "File? ";
    getline(cin, fileName);
    cout << endl;

    // Open file.
    inFile.open(fileName);

    // Get the first line of the file which is the number of questions and store it in numQuestions
    getline(inFile, currentLine);
    numQuestions = atoi(currentLine.c_str());

    // Get the questions and answers until the end of the file.
    int counter = 0;
    while (!inFile.eof())
    {
        getline(inFile, currentLine);
        questionArray[counter] = currentLine;
        getline(inFile, currentLine);
        answerArray[counter] = currentLine;

        counter++;
    }
    
    // set user state to ANSWERING to start.
    uState = ANSWERING;

    // Nested loop to run the game twice, once initially to ask the questions and once more to give the user a second try at them.
    for (int i = 0; i < 2; i++)
    {
        // The arrays have a size limit of 10 however since the file gives a number for how many questions are asked we don't need to
        // run over the spots in the array that are not occupied by anything so the numQuestions variable is used to limit the loop to that size.
        for (int j = 0; j < numQuestions; j++)
        {
            // If the question was answered correctly in the previous round there is no need to ask it again.
            if (!correctAnswerArray[j]) 
            {            
                // While the user state is not flagged as correct and the incorrect guesses are less than 3
                // the user is asked to give a guess and then the guess is sent to getUserState along with a pass by reference
                // to the guessesIncorrect so that it can increment it.
                while (uState != CORRECT && guessesIncorrect < 3)
                {
                    cout << questionArray[j] << "? ";
                    getline(cin, guess);
                    cout << endl;

                    uState = getUserState(guess, answerArray[j], guessesIncorrect);

                    if (uState == ANSWERING)
                    {
                        cout << "Try again" << endl;
                    }

                }

                // The loop has been exited so the guessesIncorrect variable needs to be reset for the next
                // question and answer.
                guessesIncorrect = 0;
            
                // Display the result of the guesses.
                switch (uState)
                {
                    case CORRECT:
                        cout << "Yay" << endl;
                        correctAnswerArray[j] = true;
                        break;
                    case INCORRECT:
                        cout << "Sorry, it's " << answerArray[j] << endl;
                        break;
                }
                // Set user state back to answering for a new question.
                uState = ANSWERING;
            }
        }
    }
    
    // Output at the end if the question was never answered correctly then it tells the user to study the answer for those questions.
    cout << "Study:" << endl;

    for (int i = 0; i < numQuestions; i++)
    {
        if (!correctAnswerArray[i]) 
        {
            cout << "- " << answerArray[i] << endl;
        }
    }
    
    // Close the file.
    inFile.close();
    
    cin.ignore(100, '\n');
    cin.get();
    return 0;
}

/*
 * getUserState - checks if the guess is the same as the answer.
 * 
 * Parameter:   guess   the user's guess
 * Parameter:   answer   the answer
 * Parameter:   guessesIncorrect    pass by reference to the guessesIncorrect variable
 * 
 * Return:     the state of UserState 
 */

UserState getUserState(string guess, string answer, int &guessesIncorrect)
{
    UserState uState;

    string formattedGuess = "";
    string formattedAnswer = "";

    // Parse through the guess and add everything that isn't a space to the formattedGuess variable
    // in the form of a lowercase char.
    for (int i = 0; i < guess.length(); i++)
    {
        if (!isspace(guess.at(i))) 
        {
            formattedGuess += tolower(guess.at(i));
        }
    }

    // Parse through the answer and add everything that isn't a space to the formattedAnswer variable
    // in the form of a lowercase char.
    for (int i = 0; i < answer.length(); i++)
    {
        if (!isspace(answer.at(i))) 
        {
            formattedAnswer += tolower(answer.at(i));
        }
    }

    // If logic to check if the guess is correct
    if (formattedGuess == formattedAnswer)
    {
        uState = CORRECT;
    }
    // If the guess was incorrect it increments the variable
    else if (formattedGuess != formattedAnswer)
    {
        guessesIncorrect++;
    }
    
    // This is a separate if so that the guessesIncorrect is checked every time the function is called.
    if (guessesIncorrect == 3)
    {
        uState = INCORRECT;
    }
    // The default user state is ANSWERING
    else if (uState != CORRECT)
    {
        uState = ANSWERING;
    }

    return uState;
}