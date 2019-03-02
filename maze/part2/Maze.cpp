/*
 * This application reads in a 10x20 character maze from a text file
 * and then lets the player traverse the maze until either the user quits or wins
 * by reaching the bottom rightmost open character.
 * 
 * Date:    November 3, 2018 
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int ARRAY_ROWS = 10;
const int ARRAY_COLS = ARRAY_ROWS * 2;

const int WIN_CONDITION_ROW = ARRAY_ROWS - 2;
const int WIN_CONDITION_COL = ARRAY_COLS - 1;

// Player struct this holds all the variables for the player object.
struct Player
{
    bool initialized = false;

    int x;
    int y;
    
    char character = '*';
};

// User struct this holds all the variables for the user object such as 
// the move the user makes and if they have won or quit.
struct User
{
    bool quit = false;
    bool won = false;
    char move;
};

// Maze struct this holds all of the information about the maze such as
// the maze itself and the player and user objects.
struct Maze
{
    char mazeArray[ARRAY_ROWS][ARRAY_COLS];

    Player player;
    User user;
};

// Function prototypes
void mazeBuilder(Maze &maze);
void displayMaze(const Maze &maze);
void updateMaze(Maze &maze);
bool hasWon(int row, int col, const Maze &maze);
void queryUser(Maze &maze);
void checkMove(Maze &maze);
void translateMove(char &move, int &x, int &y);

/*
 * main - initialize variables and calls functions.
 * 
 * Return:  0
 */
int main()
{
    // Create a maze instance
    Maze maze;

    // Build the maze from the file.
    mazeBuilder(maze);
    
    // main game loop
    // The loop runs until the player either quits or has won the game.
    while (!maze.user.quit && !maze.user.won)
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
            if (hasWon(WIN_CONDITION_ROW, WIN_CONDITION_COL, maze))
            {
                maze.user.won = true;
            }
        }
    }

    // If the user beat the maze then it's updated and drawn once more and the user is congratulated.
    if (maze.user.won)
    {
        updateMaze(maze);
        displayMaze(maze);
        cout << "Congrats!" << endl;
    }
    
    cin.ignore(100, '\n');
    cin.get();
    return 0;
}

/*
 * mazeBuilder asks the user for the filename and then reads in the maze from the file into the 2D array in the maze struct.
 * 
 * Parameter: Maze &maze  Pass by reference of a maze instance.
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
 * displayMaze iterates over the 2D array in the maze struct and displays it.
 * 
 * Parameter: Maze &maze  Pass by constant reference of a maze instance.
 * Return:  void
 */
void displayMaze(const Maze &maze)
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
 * updateMaze initializes the player object if the player object hasn't been initialized.
 * The function then moves over the array looking to find a player in the maze, once found that
 * location is converted into a space and then the player is updated to the new location in the array. 
 * 
 * Parameter: Maze &maze  Pass by reference of a maze instance.
 * Return:  void
 */
void updateMaze(Maze &maze)
{
    if (!maze.player.initialized)
    {
        maze.player.y = 1;
        maze.player.x = 0;
        maze.player.initialized = true;
    }
    else
    {
        for (int i = 0; i < ARRAY_ROWS; i++)
        {
            for (int j = 0; j < ARRAY_COLS; j++)
            {
                if (maze.mazeArray[i][j] == maze.player.character)
                {
                    maze.mazeArray[i][j] = 32;
                }
            }
        }
    }
    
    maze.mazeArray[maze.player.y][maze.player.x] = maze.player.character;
}

/*
 * hasWon takes the win condition row and col and the player location in the maze
 * and then checks to see if they are the same.
 * if yes the function returns true that the player has won
 * otherwise the function returns false that the player has not won.
 * 
 * Parameter: int row   WIN_CONDITION_ROW
 * Parameter: int col   WIN_CONDITION_COL
 * Parameter: Maze &maze  Pass by reference of a maze instance.
 * 
 * Return:  bool    true/false
 */
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
 * queryUser asks the user which direction to go and then updates the maze.user.move with the new move.
 * 
 * Parameter: Maze &maze  Pass by reference of a maze instance.
 *  
 * Return:  void.
 */
void queryUser(Maze &maze)
{
    char userInput;

    cout << "Move (udrlq)? ";
    cin >> userInput;
    cout << endl;

    maze.user.move = userInput;
}

/*
 * checkMove works with translateMove to check if the move is legal
 * if yes then the temp x and y are then applied to the player object.
 * Otherwise the user is told the move is illegal and nothing is changed.
 * 
 * Parameter: Maze &maze  Pass by reference of a maze instance.
 * Return:  void
 */

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
 * translateMove takes the current x and y from the player object and then using the move from the user object
 * they are tested to see if the move is even valid.
 * If the move is valid then x and y are sent back to checkMove where the location is checked to see if the move is legal.
 * If the move is invalid then a message is displayed saying it's illegal.
 * 
 * Parameter:   &x   the x coordinate that the user is currently at.
 * Parameter:   &y   the y coordinate that the user is currently at.
 * Parameter:   move   the user input.
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