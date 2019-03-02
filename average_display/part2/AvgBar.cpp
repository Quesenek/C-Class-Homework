/*
 * This program reads in 4 test scores and outputs the average of them.
 * It then outputs a bar chart to visualize the scores.
 * 
 * Date: August 30, 2018
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

/*
 * main - Asks the user for the test scores and takes the average between 4 of them.
 *
 * Return:      status
 */

int main()
{

    // Variables for the scores the user is asked to enter.
    int score1 = 0;
    int score2 = 0;
    int score3 = 0;
    int score4 = 0;

    // Variables to hold the number without the ones place of it's corresponding test score.
    int score1wo1s = 0;
    int score2wo1s = 0;
    int score3wo1s = 0;
    int score4wo1s = 0;

    // Variable to hold the total average between the 4 test scores.
    double totalAvg = 0.0;

    // Variables for reading in a file

    string inFileName = "";
    ifstream inFile;

    // Ask the user for the test scores and then read them into their variables.
    cout << "File? ";
    cin >> inFileName;
    cout << endl;

    // Read in the file and get the scores

    inFile.open(inFileName);

    inFile >> score1 >> score2 >> score3 >> score4;

    inFile.close();
    
    // Calculation to get the score without its ones place.
    score1wo1s = score1 / 10;
    score2wo1s = score2 / 10;
    score3wo1s = score3 / 10;
    score4wo1s = score4 / 10;

    // Code that displays the Barchart.
    cout << right << setw(3) << setfill(' ') << score1 << ": " << setw(score1wo1s) << setfill('*') << "*" << endl;
    cout << right << setw(3) << setfill(' ') << score2 << ": " << setw(score2wo1s) << setfill('*') << "*" << endl;
    cout << right << setw(3) << setfill(' ') << score3 << ": " << setw(score3wo1s) << setfill('*') << "*" << endl;
    cout << right << setw(3) << setfill(' ') << score4 << ": " << setw(score4wo1s) << setfill('*') << "*" << endl << endl;

    // Get the total average of the 4 test scores.
    totalAvg = (static_cast<double>(score1) + 
                static_cast<double>(score2) + 
                static_cast<double>(score3) + 
                static_cast<double>(score4)) / 4;

    // Output the average of the 4 test scores.
    cout << fixed << showpoint << setprecision(1);
    cout << "Avg = " << totalAvg << endl;

    cin.ignore(100, '\n');
    cin.get();
    return 0;
}