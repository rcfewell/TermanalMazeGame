/*
  Title : Proj3app.cpp
  File id : Maze Generator
  Author : Riley Fewell
  Description : This program calls all the functions needed in
  class to display, generate and run the Maze. This will output
  the instructions, determine whether or not the user wins. 
  When the user does win with will ask whether or not they
  want to play again.
 */

#include <iostream>
#include "Maze.h"
using namespace std;

int main ()
{
    char play = 'y';
    Maze maze;
    // Calls the functioin to output the instructions
    maze.Instructions (cout, cin);
    // does this only if the user wants to play again.
    while (tolower (play) == 'y')
    {
      // displays the maze.
	maze.Init();
	maze.Display (cout);
	bool finished = false, quitting = false;
	while (!finished && !quitting)
	{
	  // Displays instructions at the bottom of the screen
		char key;
		cout << "\nEnter move (a = left, w = up, d = right, s = down,\n\tq = quit, i = instructions): ";
		cin >> key;
		// if the user wants to quit the program will
		// stop
		if (key == 'q')
			quitting = true;
		// if the user wants to see the instructions
		// it will call the instruction function
		else if (key == 'i')
			maze.Instructions (cout, cin);
		// or else it waits for the user to move the 
		// character
		else
			maze.Move(key);
		finished = maze.Done();
		maze.Display (cout);
	}
	// when they winn it will ask if they want to play again
	maze.Message (finished, cout);
	cout << "Would you like to play again (y/n)? ";
	cin >> play;
	cin.clear ();;
    }
    cout << endl;
    return 0;
}
