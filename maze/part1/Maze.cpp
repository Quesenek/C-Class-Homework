/*
 * This application asks the user to enter a filename of a text file that contains a maze.
 * it then places the user in an open space to the left of the maze and asks what direction
 * the user wants to move.
 * If the direction would move the user off the map the command is ignored and the user is told
 * the action is invalid.
 * 
 * Date:    October 28, 2018 
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int ARRAY_ROWS = 4;
const int ARRAY_COLS = ARRAY_ROWS * 2;

const int WIN_CONDITION_ROW = ARRAY_ROWS-2;
const int WIN_CONDITION_COL = ARRAY_COLS-1;

struct Player
{
    bool initialized = false;

    int x;
    int y;
    
    char character = '*';
};

struct User
{
    char quit = false;
    char won = false;
    char move;
};

struct Maze
{
    char mazeArray[ARRAY_ROWS][ARRAY_COLS];

    Player player;
    User user;
};

// Function prototypes, the maze array is passed by reference because we need to edit it using the functions
// and with c++ we cannot return an array so we just edit the array itself.
void mazeBuilder(Maze &maze);
void displayMaze(Maze &maze);
void updateMaze(Maze &maze);
void queryUser(Maze &maze);
void translateMove(char &move, int &x, int &y);
void checkMove(Maze &maze);
bool hasWon(int row, int col, const Maze &maze);
void parseThroughArray (Maze &maze);

/*
 * main - initialize variables and calls functions.
 * 
 * Return:  0
 */
int main()
{
    Maze maze;

    // We don't need a loop yet, but dividing thing up into functions will make the jump to a loop easier and less cluttered.

    mazeBuilder(maze);
    
    while (maze.user.quit != true && maze.user.won != true)
    {
        updateMaze(maze);
        displayMaze(maze);
        queryUser(maze);
        if (maze.user.move == 'q')
        {
            cout << "You lost" << endl;
            maze.user.quit = true;
        }
        else
        {
            checkMove(maze);
            if(hasWon(WIN_CONDITION_ROW, WIN_CONDITION_COL, maze))
            {
                cout << "Congrats!" << endl;
                maze.user.won = true;
            }
        }
    }
        
    
    // cin.ignore(100, '\n');
    // cin.get();
    return 0;
}

/*
 * mazeBuilder asks the user for the filename and then reads in the maze from the file into the 2D array.
 * 
 * Parameter: (&mazeArray)[ARRAY_ROWS][ARRAY_COLS]  Passes the mazeArray by reference so that we can edit it.
 * Return:  void
 */
void mazeBuilder(Maze &maze)
{
    char nextChar;
    string fileName = "";
    ifstream inFile;

    cout << "File? ";
    cin >> fileName;
    cout << endl;

    inFile.open(fileName);

    for (int i = 0; i < ARRAY_ROWS; i++)
    {
        for (int j = 0; j < ARRAY_COLS; j++)
        {
            inFile.get(nextChar);
            maze.mazeArray[i][j] = nextChar;
        }
        // Read in the new line which gets discarded.
        inFile.get(nextChar);
    }

    inFile.close();
}

/*
 * initMaze places the player object into the maze.
 * 
 * Parameter:   (&mazeArray)[ARRAY_ROWS][ARRAY_COLS]    Passes the mazeArray by reference so that we can edit it.
 * Parameter:   x   the x coordinate that we use to place the object.
 * Parameter:   y   the y coordinate that we use to place the object.
 * Return:  void
 */
void updateMaze(Maze &maze)
{
    if (maze.player.initialized == false)
    {
        maze.player.y = 1;
        maze.player.x = 0;
        maze.player.initialized = true;
    }
    
    for(int i = 0; i < ARRAY_ROWS; i++)
    {
        for(int j = 0; j < ARRAY_COLS; j++)
        {
            if (maze.mazeArray[i][j] == maze.player.character)
            {
                maze.mazeArray[i][j] = 32;
            }
        }
    }
    
    maze.mazeArray[maze.player.y][maze.player.x] = maze.player.character;
}

bool hasWon(int row, int col, const Maze &maze)
{
    if (maze.player.x == col && maze.player.y == row)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

/*
 * displayMaze iterates over the 2D array and displays it.
 * 
 * Parameter: (&mazeArray)[ARRAY_ROWS][ARRAY_COLS]  Passes the mazeArray by reference so that we can edit it.
 * Return:  void
 */
void displayMaze(Maze &maze)
{
    for (int i = 0; i < ARRAY_ROWS; i++)
    {
        for (int j = 0; j < ARRAY_COLS; j++)
        {
            cout << maze.mazeArray[i][j];
        }
        cout << endl;
    }
}

/*
 * queryUser asks the user which direction to go and then returns the input.
 * 
 * Return:  char    returns the value the user entered.
 */
void queryUser(Maze &maze)
{
    char userInput;

    cout << "Move (udrlq)? ";
    cin >> userInput;
    cout << endl;

    maze.user.move = userInput;
}

void checkMove(Maze &maze)
{
    char move = maze.user.move;
    char wall = '|';
    char openSpace = 32;
    char charInArray = 32;

    int xTemp = maze.player.x;
    int yTemp = maze.player.y;

    translateMove(move, xTemp, yTemp);

    charInArray = maze.mazeArray[yTemp][xTemp];

    if (charInArray != wall)
    {
        maze.player.x = xTemp;
        maze.player.y = yTemp;
    }
    else
    {
        cout << "Illegal move" << endl;
    }
}

/*
 * translateMove takes the value that the user entered in queryUser and translates it into x/y values.
 * 
 * Parameter:   &x   the x coordinate that the user is currently at.
 * Parameter:   &y   the y coordinate that the user is currently at.
 * Parameter:   move   the user input from queryUser.
 * Return:  void
 */
void translateMove(char &move, int &x, int &y)
{
    // If the user picks u and is not already at the top of the maze the user is moved up one space.
    if (move == 'u' && y > 0)
    {
        // cout << "(" << x << "," << y << ")"
        //      << " to "
        //      << "(" << x << "," << (y - 1) << ")" << endl;
        y -= 1;
    }
    // If the user picks d and is not already at the bottom of the maze the user is moved down one space.
    else if (move == 'd' && y < ARRAY_ROWS - 1)
    {
        // cout << "(" << x << "," << y << ")"
        //      << " to "
        //      << "(" << x << "," << (y + 1) << ")" << endl;
        y += 1;
    }
    // If the user picks r and is not already at the right side of the maze the user is moved one space to the right.
    else if (move == 'r' && x < ARRAY_COLS - 1)
    {
        // cout << "(" << x << "," << y << ")"
        //      << " to "
        //      << "(" << (x + 1) << "," << y << ")" << endl;
        x += 1;
    }
    // If the user picks l and is not already at the left side of the maze the user is moved one space to the left.
    else if (move == 'l' && x > 0)
    {
        // cout << "(" << x << "," << y << ")"
        //      << " to "
        //      << "(" << x << "," << y << ")" << endl;
        x -= 1;
    }
    // If the user uses an input that would result in them going out of the bounds of the array, or if the user inputs something that isn't valid.
    // a message is output telling the user that something isn't valid.
    else
    {
        cout << "Illegal move" << endl;
    }
}