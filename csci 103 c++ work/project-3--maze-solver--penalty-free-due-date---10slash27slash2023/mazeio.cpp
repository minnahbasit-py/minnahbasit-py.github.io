/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols)
{
    ifstream ifile(filename);
    // *** You complete **** CHECKPOINT 1
    // if file open fails return NULL
    if (ifile.fail()) {
        return NULL;
    }
    int f_row;
    int f_col;
    ifile >> f_row >> f_col;
    *rows = f_row;
    *cols = f_col;
    if (ifile.fail()) {
        return NULL;
        // means row and cols werent read in
    }
    
    // why do i need *rows = f_row? 
    //when it is already declared as pointer in parameters
    
    char** maze_arr = new char*[f_row];
    for (int i = 0; i < f_row; i++) {
        maze_arr[i] = new char[f_col];
        for (int j = 0; j < f_col; j++) {
            ifile >> maze_arr[i][j];
        }
    }
    ifile.close();
    return maze_arr;
    // if can't read 2 numbers from file return NULL
    // dynamically allocate 2d array -> char** = new *int[]
    // rows and cols are pointers
    // we will fill in dimensions by reading in from file








}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols)
{

    // *** You complete **** CHECKPOINT 1
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }


}

