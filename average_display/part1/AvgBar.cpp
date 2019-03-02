/*
 * This program takes in 4 test scores from the user
 * and outputs the total average for the student.
 * 
 * Date: August 23, 2018
 */

#include <iostream>

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

    // Ask the user for the test scores and then read them into their variables.
    cout << "Scores? ";
    cin >> score1 >> score2 >> score3 >> score4;
    cout << endl;
    
    // Calculation to get the score without its ones place.
    score1wo1s = score1 / 10;
    score2wo1s = score2 / 10;
    score3wo1s = score3 / 10;
    score4wo1s = score4 / 10;

    // Output the score and the score without its ones place.
    cout << score1 << ": " << score1wo1s << endl;
    cout << score2 << ": " << score2wo1s << endl;
    cout << score3 << ": " << score3wo1s << endl;
    cout << score4 << ": " << score4wo1s << endl << endl;

    // Get the total average of the 4 test scores.
    totalAvg = (static_cast<double>(score1) + 
                static_cast<double>(score2) + 
                static_cast<double>(score3) + 
                static_cast<double>(score4)) / 4;

    // Output the average of the 4 test scores.
    cout << "Avg = " << totalAvg << endl;

    cin.ignore(100, '\n');
    cin.get();
    return 0;
}