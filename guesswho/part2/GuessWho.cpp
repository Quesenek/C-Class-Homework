/* 
 * This is a game of guess who.
 * The user enters a number for which game they want to play.
 * The user then has 5 guesses to find the correct person.
 * The game ends when the user has exhausted their 5 guesses or found the person. 
 * 
 * Date:   November 24, 2018 
 */ 

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Person.h"

using namespace std;

const int ARRAY_SIZE = 20;
const int NUM_GUESSES = 5;
const int NUM_FEATURES = 7;

// PlayerGuessList holds information about the game that we can send to functions easily.
struct PlayerGuessList
{
    Person gamePerson;

    string featureTypeList[NUM_GUESSES];
    string featureValueList[NUM_GUESSES];
    
    int guessesMade;
    bool rightAnswer[NUM_GUESSES];

    int numPeopleLeft;
};

// Function Prototypes
void makePeople(Person(&peopleArray)[ARRAY_SIZE]);
Person getGame(Person(&peopleArray)[ARRAY_SIZE]);
void makeGuess(PlayerGuessList &pgl);
void printPerson(Person(&peopleArray)[ARRAY_SIZE], PlayerGuessList &pgl);
void printHeader();

/*
 * main method runs the functions that make the guess who game.
 * 
 * Return:  0
 */
int main()
{
    // Array of persons and make a PlayerGuessList object to hold information
    Person peopleArray[ARRAY_SIZE];
    PlayerGuessList pgl;
    
    // Initialize the pgl object
    pgl.guessesMade = 0;
    pgl.numPeopleLeft = ARRAY_SIZE;
    for (int i = 0; i < NUM_GUESSES; i++)
    {
        pgl.featureTypeList[i] = "";
        pgl.featureValueList[i] = "";
        pgl.rightAnswer[i] = false;
    }

    // Populate the array of persons and get the game person
    makePeople(peopleArray);
    pgl.gamePerson = getGame(peopleArray);

    // Start game loop
    printPerson(peopleArray, pgl);
    while (pgl.guessesMade < 5 && pgl.numPeopleLeft > 1)
    {
        makeGuess(pgl);
        printPerson(peopleArray, pgl);
    }

    // Check if the user lost or won the game
    if (pgl.numPeopleLeft > 1 || pgl.guessesMade == 5)
    {
        cout << "You lost, it was " << pgl.gamePerson.getName() << endl;
    }
    else if (pgl.numPeopleLeft == 1)
    {
        cout << "Congrats" << endl;
    }

    cin.ignore(100, '\n');
    cin.get();
    return 0;
}

/*
 * makePeople reads in the people.txt and then it creates a Person object for each line of attributes in the file.
 * 
 * Parameter:   &peopleArray pass by reference of peopleArray
 * 
 * Return:  void
 */
void makePeople(Person(&peopleArray)[ARRAY_SIZE])
{
    ifstream inFile;
    string readTemp;

    inFile.open("people.txt");
    
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        inFile >> readTemp;
        peopleArray[i].setName(readTemp);
        inFile >> readTemp;
        peopleArray[i].setHairColor(readTemp);
        inFile >> readTemp;
        peopleArray[i].setHairType(readTemp);
        inFile >> readTemp;
        peopleArray[i].setGender(readTemp);
        inFile >> readTemp;
        peopleArray[i].setGlasses(readTemp);
        inFile >> readTemp;
        peopleArray[i].setEyeColor(readTemp);
        inFile >> readTemp;
        peopleArray[i].setHat(readTemp);
    }
    
    inFile.close();
}

/*
 * getGame asks the user for the game number, if the number is less than 1 or greater than 20 which is the size of the number of people to play with
 * then a random number is picked and used for the game number.
 * 
 * Parameter:   &peopleArray pass by reference of peopleArray
 * 
 * Return:  the person that matches the number picked.
 */
Person getGame(Person(&peopleArray)[ARRAY_SIZE])
{
    int personNumber = 0;
    cout << "Game? ";
    cin >> personNumber;
    cout << endl;

    if (personNumber < 1 || personNumber > 20)
    {
        srand(time(0));
        personNumber = (rand() % 20) + 1;
    }

    return peopleArray[personNumber - 1];
}

/*
 * makeGuess asks the user for input which it reads in and outputs a yes or a no based on if the input entered matches the feature of the game person at play.
 * If the guess is correct then a true is added to pgl.rightAnswer otherwise a false is added.
 * 
 * Parameter:   &pgl pass by reference of the PlayerGuessList struct
 * 
 * Return:  void
 */
void makeGuess(PlayerGuessList &pgl)
{
    
    cout << "Feature Value? ";
    cin >> pgl.featureTypeList[pgl.guessesMade] >> pgl.featureValueList[pgl.guessesMade];
    cout << endl;

    if (pgl.featureTypeList[pgl.guessesMade] == "name")
    {
        if (pgl.featureValueList[pgl.guessesMade] == pgl.gamePerson.getName())
        {
            cout << "Yes" << endl;
            pgl.rightAnswer[pgl.guessesMade] = true;
        }
        else 
        {
            cout << "No" << endl;
            pgl.rightAnswer[pgl.guessesMade] = false;
        }
    } 
    else if (pgl.featureTypeList[pgl.guessesMade] == "haircolor")
    {
        if (pgl.featureValueList[pgl.guessesMade] == pgl.gamePerson.getHairColor())
        {
            cout << "Yes" << endl;
            pgl.rightAnswer[pgl.guessesMade] = true;
        }
        else 
        {
            cout << "No" << endl;
            pgl.rightAnswer[pgl.guessesMade] = false;
        }
    }
    else if (pgl.featureTypeList[pgl.guessesMade] == "hairtype")
    {
        if (pgl.featureValueList[pgl.guessesMade] == pgl.gamePerson.getHairType())
        {
            cout << "Yes" << endl;
            pgl.rightAnswer[pgl.guessesMade] = true;
        }
        else 
        {
            cout << "No" << endl;
            pgl.rightAnswer[pgl.guessesMade] = false;
        }
    }
    else if (pgl.featureTypeList[pgl.guessesMade] == "gender")
    {
        if (pgl.featureValueList[pgl.guessesMade] == pgl.gamePerson.getGender())
        {
            cout << "Yes" << endl;
            pgl.rightAnswer[pgl.guessesMade] = true;
        }
        else 
        {
            cout << "No" << endl;
            pgl.rightAnswer[pgl.guessesMade] = false;
        }
    }
    else if (pgl.featureTypeList[pgl.guessesMade] == "glasses")
    {
        if ((pgl.featureValueList[pgl.guessesMade] == "yes") == pgl.gamePerson.getGlasses())
        {
            cout << "Yes" << endl;
            pgl.rightAnswer[pgl.guessesMade] = true;
        }
        else 
        {
            cout << "No" << endl;
            pgl.rightAnswer[pgl.guessesMade] = false;
        }
    }
    else if (pgl.featureTypeList[pgl.guessesMade] == "eyecolor")
    {
        if (pgl.featureValueList[pgl.guessesMade] == pgl.gamePerson.getEyeColor())
        {
            cout << "Yes" << endl;
            pgl.rightAnswer[pgl.guessesMade] = true;
        }
        else 
        {
            cout << "No" << endl;
            pgl.rightAnswer[pgl.guessesMade] = false;
        }
    }
    else if (pgl.featureTypeList[pgl.guessesMade] == "hat")
    {
        if ((pgl.featureValueList[pgl.guessesMade] == "yes") == pgl.gamePerson.getHat())
        {
            cout << "Yes" << endl;
            pgl.rightAnswer[pgl.guessesMade] = true;
        }
        else 
        {
            cout << "No" << endl;
            pgl.rightAnswer[pgl.guessesMade] = false;
        }
    }

    pgl.guessesMade++;
}

/*
 * printPerson takes the people array and the PlayerGuessList and then displays the correct output based on the guesses made
 * 
 * Parameter:   &peopleArray pass by reference of the people array
 * Parameter:   &pgl pass by reference of the PlayerGuessList struct
 * 
 * Return:  void
 */
void printPerson(Person(&peopleArray)[ARRAY_SIZE], PlayerGuessList &pgl)
{
    printHeader();

    // Size is + 1 because the first column is set true if the other options at that not set N/A are true
    string personValidity[ARRAY_SIZE][NUM_FEATURES + 1];
    
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        personValidity[i][0] = "true";
        for (int j = 1; j < NUM_FEATURES + 1; j++)
        {
            personValidity[i][j] = "N/A";
        }   
    }
    
    // The logic behind the way we are setting the values true and false is:
    // if the guess was correct then any person that matches the value is set to a "true" value otherwise "false"
    // if the guess was incorrect then anyone matching the value is set to a "false" value otherwise "true" 
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        for (int j = 0; j < pgl.guessesMade; j++)
        {
            if (pgl.featureTypeList[j] == "name")
            {
                if (pgl.rightAnswer[j])
                {
                    if (pgl.featureValueList[j] == peopleArray[i].getName())
                    {
                        personValidity[i][1] = "true";
                    }
                    else
                    {
                        personValidity[i][1] = "false";
                    }
                }
                if (!pgl.rightAnswer[j])
                {
                    if (pgl.featureValueList[j] == peopleArray[i].getName())
                    {
                        personValidity[i][1] = "false";
                    }
                    else
                    {
                        personValidity[i][1] = "true";
                    }
                }
            } 
            else if (pgl.featureTypeList[j] == "haircolor")
            {
                if (pgl.rightAnswer[j])
                {
                    if (pgl.featureValueList[j] == peopleArray[i].getHairColor())
                    {
                        personValidity[i][2] = "true";
                    }
                    else
                    {
                        personValidity[i][2] = "false";
                    }
                }
                else if (!pgl.rightAnswer[j])
                {
                    if (pgl.featureValueList[j] == peopleArray[i].getHairColor())
                    {
                        personValidity[i][2] = "false";
                    }
                    else
                    {
                        personValidity[i][2] = "true";
                    }
                }
            }
            else if (pgl.featureTypeList[j] == "hairtype")
            {
                if (pgl.rightAnswer[j])
                {
                    if (pgl.featureValueList[j] == peopleArray[i].getHairType())
                    {
                        personValidity[i][3] = "true";
                    }
                    else
                    {
                        personValidity[i][3] = "false";
                    }
                }
                else if (!pgl.rightAnswer[j])
                {
                    if (pgl.featureValueList[j] == peopleArray[i].getHairType())
                    {
                        personValidity[i][3] = "false";
                    }
                    else
                    {
                        personValidity[i][3] = "true";
                    }
                }
            }
            else if (pgl.featureTypeList[j] == "gender")
            {   
                if (pgl.rightAnswer[j])
                {
                    if (pgl.featureValueList[j] == peopleArray[i].getGender())
                    {
                        personValidity[i][4] = "true";
                    }
                    else
                    {
                        personValidity[i][4] = "false";
                    }
                }
                else if (!pgl.rightAnswer[j])
                {
                    if (pgl.featureValueList[j] == peopleArray[i].getGender())
                    {
                        personValidity[i][4] = "false";
                    }
                    else
                    {
                        personValidity[i][4] = "true";
                    }
                }
            }
            else if (pgl.featureTypeList[j] == "glasses")
            {
                if (pgl.rightAnswer[j])
                {
                    if ((pgl.featureValueList[j] == "yes"))
                    {
                        if (peopleArray[i].getGlasses())
                        {
                            personValidity[i][5] = "true";
                        }
                        else
                        {
                            personValidity[i][5] = "false";
                        }
                    }
                    else if ((pgl.featureValueList[j] == "no"))
                    {
                        if (!peopleArray[i].getGlasses())
                        {
                            personValidity[i][5] = "true";
                        }
                        else
                        {
                            personValidity[i][5] = "false";
                        }
                    }
                }
                else if (!pgl.rightAnswer[j])
                {
                    if ((pgl.featureValueList[j] == "yes"))
                    {
                        if (peopleArray[i].getGlasses())
                        {
                            personValidity[i][5] = "false";
                        }
                        else
                        {
                            personValidity[i][5] = "true";
                        }
                    }
                    else if ((pgl.featureValueList[j] == "no"))
                    {
                        if (!peopleArray[i].getGlasses())
                        {
                            personValidity[i][5] = "false";
                        }
                        else
                        {
                            personValidity[i][5] = "true";
                        }
                    }
                }
            }

            else if (pgl.featureTypeList[j] == "eyecolor")
            {
                if (pgl.rightAnswer[j])
                {
                    if (pgl.featureValueList[j] == peopleArray[i].getEyeColor())
                    {
                        personValidity[i][6] = "true";
                    }
                    else
                    {
                        personValidity[i][6] = "false";
                    }
                }
                else if (!pgl.rightAnswer[j])
                {
                    if (pgl.featureValueList[j] == peopleArray[i].getEyeColor())
                    {
                        personValidity[i][6] = "false";
                    }
                    else
                    {
                        personValidity[i][6] = "true";
                    }
                }
            }
            else if (pgl.featureTypeList[j] == "hat")
            {
                if (pgl.rightAnswer[j])
                {
                    if ((pgl.featureValueList[j] == "yes"))
                    {
                        if (peopleArray[i].getHat())
                        {
                            personValidity[i][7] = "true";
                        }
                        else
                        {
                            personValidity[i][7] = "false";
                        }
                    }
                    else if ((pgl.featureValueList[j] == "no"))
                    {
                        if (!peopleArray[i].getHat())
                        {
                            personValidity[i][7] = "true";
                        }
                        else
                        {
                            personValidity[i][7] = "false";
                        }
                    }
                }
                else if (!pgl.rightAnswer[j])
                {
                    if ((pgl.featureValueList[j] == "yes"))
                    {
                        if (peopleArray[i].getHat())
                        {
                            personValidity[i][7] = "false";
                        }
                        else
                        {
                            personValidity[i][7] = "true";
                        }
                    }
                    else if ((pgl.featureValueList[j] == "no"))
                    {
                        if (!peopleArray[i].getHat())
                        {
                            personValidity[i][7] = "false";
                        }
                        else
                        {
                            personValidity[i][7] = "true";
                        }
                    }
                }
            } 
        }
    }
    
    pgl.numPeopleLeft = 0;
    
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        for (int j = 1; j < NUM_FEATURES + 1; j++)
        {
            if (personValidity[i][j] == "false")
            {
                personValidity[i][0] = "false";
            }
        }
        if (personValidity[i][0] == "true")
        {
            pgl.numPeopleLeft++;
            peopleArray[i].printPerson();
        }
    }    
}

/*
 * printHeader header for the print function
 * 
 * Return:  void
 */
void printHeader()
{
    cout << "      name haircolor  hairtype    gender   glasses  eyecolor       hat" << endl;
    cout << "----------------------------------------------------------------------" << endl;
}