#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "Maze.h"
using namespace std;

Maze::Maze ()
// This is a default constructor.
// This initiates all the values in the class
// and sets them to zero and the grid size to NULL
// until they are changed later in the program.
{
  numRows = numCols = 0;
  grid = NULL;
  startRow = startCol = 0;
  endRow = endCol = 0;
  currentRow = currentCol = 0;
}

Maze::Maze (const Maze & other)
// Copy constructor stub
{
}

Maze::~Maze ()
// Destructor stub
{
}

Maze & Maze::operator = (const Maze & other)
// Assignment operator stub
{
}

void Maze::Init ()
// This functions declares and sets all the variables
// that are going to be inside the grid.
// It forms the skeleton for the maze and declares the size
// of the maze. It also places the character that will be moved
// and the ending character in the correct spots.
{
  numRows = 21;// declares the value of rows
  numCols = 31;// declares the value of columns
  grid = new char * [numRows];
  for (int r = 0; r < numRows; r++)
    {
      grid[r] = new char [numCols+1];
    }
  // makes the outside border of the maze.
  strcpy (grid[0], "*******************************");
  strcpy (grid[1], "*                             *");
  //This is my manually inputted maze.
  //strcpy (grid[1], "*   *       *   *     * *     *");
  //strcpy (grid[2], "* ******* * *** * ***** * * ***");
  //strcpy (grid[3], "*         *     *     * * *   *");
  //strcpy (grid[4], "******* ***** *** *** * * *** *");
  //strcpy (grid[5], "*         * *   * *     * *   *");
  //strcpy (grid[6], "***** ******* * *** ******* ***");
  //strcpy (grid[7], "*         *   *     *         *");
  //strcpy (grid[8], "* * ***** *** *** ***** * *** *");
  //strcpy (grid[9], "* *     * *     *       *   * *");
  //strcpy (grid[10], "***** *************************");
  //strcpy (grid[11], "*  *    *   *   *             *");
  //strcpy (grid[12], "* ***** * ***** ************* *");
  //strcpy (grid[13], "*  *        *     * * *       *");
  //strcpy (grid[14], "* *** ***** *** * * * *** *****");
  //strcpy (grid[15], "*       *       *   * *       *");
  //strcpy (grid[16], "*********** ***** * * * *******");
  //strcpy (grid[17], "*     * *       * * *       * *");
  //strcpy (grid[18], "* ***** ******* * * * * *** * *");
  //strcpy (grid[19], "*               * *   *   *   *");
  for (int i = 2; i < numRows - 1; ++i)
    strcpy (grid[i], grid[1]);
  strcpy (grid[numRows-1], "*******************************");
  //where the moving character will be placed to start
  startRow = 1;
  startCol = 1;
  grid [startRow][startCol] = 'O';
  // where the ending character will be placed
  endRow = numRows-2;
  endCol = numCols-2;
  grid [endRow][endCol] = '$';
  currentRow = startRow;
  currentCol = startCol;
  // Starts the recurrsive function to start making the maze
  Generate (0, 0, numCols - 1, numRows - 1);
}

void Maze::Instructions (ostream & outs, istream & ins)
// This function declares and outputs the instructions for the
// maze. It needs the variables outs and ins to be able to 
//intake what the user wants to do and also output the 
// instructions
{
  system ("clear");
  // Moving instructions
  outs << "\nUse the a, w, d, and s keys to move yourself (O) through the\n";
  // basic concept of what needs to ne done
  outs << "maze to find the treasure ($)!\n\n";
  // letting you know what each moving key represents
  // and additional information such as quit
  outs << "\ta = left\n\tw = up\n\td = right\n\ts = down\n\tq = quit\n\ti = instructions\n\n";
  // information on how to start the game
  outs << "Press any key and enter to start.\n";
  char c;
  ins >> c;
}

void Maze::Display (ostream & outs)
// This funciton draws the display on the screen. it needs
// the ostream and outs to be able to output the display
{
  char esc = 0x1B;
  system ("clear");
  // Draws the skeleton of the grid
  for (int r = 0; r < numRows; r++)
    {
      for (int c = 0; c < numCols; c++)
	outs << grid[r][c] << ' ';
      outs << endl;
    }
}

bool Maze::Done () const
// This function determines whether the game is still running
// or not.
{
  // a boolean equation to determine whether the game has ended
  // or not.
  if (currentRow == endRow && currentCol == endCol)
    {
      grid[currentRow][currentCol] = '#';
      return true;
    }
  return false;
}

void Maze::Move (char direction)
// This function intakes a characte, either a (left), s (down),
// d (right), and w (up). Depending on the character, this function
// checks to see if that move is possible and then performs the
// move passed on the instructions.
{
  switch (tolower(direction))
    {
    case 'a': // moves character left
      //checks to see if there is a wall to the left
      // of the character.
      if (grid[currentRow][currentCol - 1] != '*')
	{
	  // if there isn't a wall to the left of the character
	  // the character is swapped from the current position
	  // to one position to the left
	  swap (grid[currentRow][currentCol],
		grid[currentRow][currentCol - 1]);
	  //updates the column to the new value.
	  --currentCol;
	}
      break;
    case 'w': // moves character up
      //checks to see if there is a wall above the character
      if (grid[currentRow - 1][currentCol] != '*')
	{
	  // if there isn't a wall above the character
	  // the character is swapped from the current position
	  // to one position above it
	  swap (grid[currentRow][currentCol],
		grid[currentRow - 1][currentCol]);
	  --currentRow;
	}
      break;
    case 'd': // moves character right
      //checks to see if there is a wall to the right of the character
      if (grid[currentRow][currentCol + 1] != '*')
	{
	  // if there isn't a wall to the right of the character
	  // the character is swapped from the current position
	  // to one position to the right
	  swap (grid[currentRow][currentCol],
		grid[currentRow][currentCol + 1]);
	  ++currentCol;
	}
      break;
    case 's': // moves character down
      //checks to see if there is a wall below the character
      if (grid[currentRow + 1][currentCol] != '*')
	{
	  // if there isn't a wall below the character
	  // the character is swapped from the current position
	  // to one position below
	  swap (grid[currentRow][currentCol],
		grid[currentRow + 1][currentCol]);
	  ++currentRow;
	}
      break;
    }
}

void Maze::Message (bool completed, ostream & outs)
//This function displays a message if the user has won or lost
// It needs a true or false from the boolean function completed
// and also the ostream and outs to be able to display the 
// message.
{
  // If completed returned true determining that the user won
  // the user is given a congrats. Otherwise they lost
  // and given a sorry message
  if (completed)
    outs << "\nCongratulations! You found the treasure!\n\n";
  else
    outs << "\nSorry! You did not find the treasure!\n\n";
}

void Maze::Generate (int left, int top, int right, int bottom)
// For Recursive Division. It needs the variable left, top, 
// right, bottom inorder to know where to draw the new lines in
// the maze.
{
  // creates a random number based on the time
  // numbers are completely random everytime
  srand (time(NULL));

  // This stops the recursion if the maze is small enough
  // so no new lines can be drawn anymore
  if (right - left <= 3 || bottom - top <= 3)
    return;

  // variables used to draw the lines
  int vert = 0;
  int horiz = 0;
  // an equation that will pick random even numbers between
  // the walls. This is where the walls will be drawn
  vert = 2 * (rand () % ((right - left - 2) / 2)) + 2 + left;
  horiz = 2 * (rand () % ((bottom - top - 2) / 2 )) + top + 2;

  // Once the values for vert and horiz are found. These loops
  // actually draw the lines at the spots found by the equation
  for (int i = top; i < bottom; ++i)
    grid[i][vert] = '*';
  for (int i = left; i < right; ++i)
    grid[horiz][i] = '*';
  
  // equations to find odd numbers in the vert and horiz
  // lines that will be used to draw doors for the maze.
  int door1 = 2 * (rand () % ((horiz  - top) / 2)) + 1 + top;
  int door2 = 2 * (rand () % ((vert  - left) / 2)) + 1 + left;
  int door3 = 2 * (rand () % ((bottom - horiz) / 2)) + 1 + horiz;
  int door4 = 2 * (rand () % ((right - vert) / 2)) + 1 + vert;

  // picks a random number between 0 and 3 so it can be used
  // to skip a random door so only 3 doors are drawn.
  int skip = rand () % 4;
  
  // If statements to draw the doors if the skip variable
  // doesn't equal the doors certain value.
  if (skip != 0)
    grid[door1][vert] = ' ';
  if (skip != 1)
    grid[horiz][door2] = ' ';
  if (skip != 2)
    grid[door3][vert] = ' ';
  if (skip != 3)
    grid[horiz][door4] = ' ';
  
  // Starts the recursive steps over and over again until
  // no more lines can be drawn.
  Generate (left, top, vert, horiz);
  Generate (vert, top, right, horiz);
  Generate (left, horiz, vert, bottom);
  Generate (vert, horiz, right, bottom);
  
}

void Generate (int row, int col) // For Depth First
{
}


