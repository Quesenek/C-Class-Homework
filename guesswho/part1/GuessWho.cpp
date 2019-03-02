/* 
 * This application is a guess who game where people and their attributes are read in from a file
 * and then the user asks about the different attributes to gather clues about who the person is.
 * 
 * Date:   November 11, 2018 
 */ 

#include <iostream>
#include <string>
#include <fstream>
#include "Person.h"

using namespace std;

void makePerson(Person &person);
void printPerson(const Person &person);
void questionUser(const Person &person);

/*
 * main method runs the functions that make the guess who game.
 * 
 * Return:  0
 */
int main()
{
    Person person;

    makePerson(person);
    printPerson(person);
    questionUser(person);

    cin.ignore(100, '\n');
    cin.get();
    return 0;
}

/*
 * makePerson reads in the people.txt and then it creates a Person object for the attributes in the first line of the file.
 * 
 * Parameter:   &person is a pass by reference to the person object created in main. Passing by reference saves on memory.
 * 
 * Return:  void
 */
void makePerson(Person &person)
{
    ifstream inFile;
    string readTemp;

    inFile.open("people.txt");
    
    inFile >> readTemp;
    person.setName(readTemp);
    inFile >> readTemp;
    person.setHairColor(readTemp);
    inFile >> readTemp;
    person.setHairType(readTemp);
    inFile >> readTemp;
    person.setGender(readTemp);
    inFile >> readTemp;
    person.setGlasses(readTemp);
    inFile >> readTemp;
    person.setEyeColor(readTemp);
    inFile >> readTemp;
    person.setHat(readTemp);

    inFile.close();
}

/*
 * printPerson takes the person object created in main and prints out the attributes
 * 
 * Parameter:   &person is a pass by reference to the person object created in main. 
 *              This is a pass by const reference meaning it is immutable and wont be changed by a print function, but we are still saving on memory by using pass by reference.
 * 
 * Return:  void
 */
void printPerson(const Person &person)
{

    cout << "      name haircolor  hairtype    gender   glasses  eyecolor       hat" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << "      " << person.getName() << "     ";
    cout << person.getHairColor() << "  ";
    cout << person.getHairType() << "    ";
    cout << person.getGender() << "       ";
    cout << ((person.getGlasses() == 1) ? "yes" : "no") << "     ";
    cout << person.getEyeColor() << "        " ;
    cout << ((person.getHat() == 1) ? "yes" : "no") << endl;
}

/*
 * questionUser is a function that asks the user for an attribute/feature and then based on the user input an answer is given.
 * The true/false booleans are changed to yes/no for readability.
 * 
 * Parameter:   &person is a pass by reference to the person object created in main. 
 *              This is a pass by const reference meaning it is immutable and wont be changed by a print function, but we are still saving on memory by using pass by reference.
 * 
 * Return:  void
 */
void questionUser(const Person &person)
{
    string userInput = "";

    cout << "Feature? ";
    cin >> userInput;
    cout << endl;

    if (userInput == "name")
    {
        cout << person.getName();
    }
    else if (userInput == "haircolor")
    {
        cout << person.getHairColor();
    }
    else if (userInput == "hairtype")
    {
        cout << person.getHairType();
    }
    else if (userInput == "gender")
    {
        cout << person.getGender();
    }
    else if (userInput == "glasses")
    {
        cout << ((person.getGlasses() == 1) ? "yes" : "no");
    }
    else if (userInput == "eyecolor")
    {
        cout << person.getEyeColor();
    }
    else if (userInput == "hat")
    {
        cout << ((person.getHat() == 1) ? "yes" : "no");
    }
}
