/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// Add other prototypes here for any functions you wish to use
bool isValid(int r, int c, int rows, int cols);
bool isAvailable(char** maze, int row, int col, Location loc);
int invalid_maze(char** maze_arr, int rows, int cols);
int invalid_char(char** maze_arr, int rows, int cols);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, retval;
    char** mymaze=NULL;
    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }

    mymaze = read_maze(argv[1],&rows,&cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1

    // For checkpoint 2 you should check the validity of the maze
    // You may do so anywhere you please and can abstract that
    // operation with a function or however you like.
    retval = maze_search(mymaze, rows, cols);
    // ask about parameters


    //================================
    // When working on Checkpoint 4, you will need to call maze_search
    // and output the appropriate message or, if successful, print
    // the maze.  But for Checkpoint 1, we print the maze, regardless.
    // cout << rows << " " << cols << endl;
    // print_maze(mymaze, rows, cols);

    //================================
    // ADD CODE BELOW 
    if (invalid_maze(mymaze,rows,cols)) {
      // invalid maze
      cout << invalid_maze_message << endl;
    }
    if (invalid_char(mymaze,rows,cols)) {
      // invalid char
      cout << invalid_char_message << endl;
    }
    if (retval < 1) {
      // no apth found
      cout << no_path_message << endl;
    }
    if (retval == 1) {
      cout << rows << " " << cols << endl;
      print_maze(mymaze, rows, cols);
    }
    // to delete all memory that read_maze allocated: CHECKPOINT 2
    for (int i = 0; i < rows; i++) {
        delete [] mymaze[i];
    }
    delete [] mymaze;



    return 0;
}

bool isValid(int r, int c, int rows, int cols) {
  if ((r >= 0) && (r < rows) && (c >= 0) && (c < cols)) {
    return true;
  }
  else {
    return false;
  }
}

bool isAvailable(char** maze, int row, int col, Location loc) {
  if (isValid(loc.row, loc.col, row, col) && ((maze[loc.row][loc.col] == '.') || (maze[loc.row][loc.col] == 'S') || (maze[loc.row][loc.col] == 'F'))) {
    return true;
  } 
  else {
    return false;
  }
}
int invalid_maze(char** maze_arr, int rows, int cols) {
  Queue queue(rows*cols);
  int s_count = 0;
  int f_count = 0;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (maze_arr[i][j] == 'S') {
          Location loc;
          loc.row = i;
          loc.col = j;
          queue.add_to_back(loc);
          // add the starting location to the queue
          // ADD BACK LATER explored_arr[i][j] = true;
          // marked starting loc to queue
          s_count++;
        }
        if (maze_arr[i][j] == 'F') {
          f_count++;
        }
      }
    }
    if (s_count != 1 || f_count != 1) {
      return 1;
    }
    return 0;
}
int invalid_char(char** maze_arr, int rows, int cols) {
  Queue queue(rows*cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if ((maze_arr[i][j] != '.') && (maze_arr[i][j] != '#') && 
        (maze_arr[i][j] != 'S') && (maze_arr[i][j] != 'F') && (maze_arr[i][j] != '*')) {
          return 1;
        }
      }
    }
    return 0;
}
/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
    // *** You complete **** CHECKPOINT 4
    bool start_found = false;
    bool finish_found = false;
    //bool path_found = false;
    //bool invalid_char = false;
    int result = 0;
    Queue queue(rows*cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (maze[i][j] == 'S') {
          start_found = true;
          Location start_loc;
          start_loc.row = i;
          start_loc.col = j;
          queue.add_to_back(start_loc);
          // add the starting location to the queue
          // ADD BACK LATER explored_arr[i][j] = true;
          // marked starting loc to queue
        }
      }
    }
    if (start_found == false) {
      return -1;
    }
    Location** predecessor = new Location*[rows];
    bool** explored_arr = new bool*[rows];
    // remember to deallocate later using 2 for loops
    for (int i = 0; i < rows; i++) {
      predecessor[i] = new Location[cols];
      explored_arr[i] = new bool[cols];
      for (int j = 0; j < cols; j++) {
        explored_arr[i][j] = false;
      }
    }

    // BFS algorithm
    Location curr;
    while (!queue.is_empty()) {
      curr = queue.remove_from_front();
      // loc is starting location on first iteration
      // on next it is whatecer is in the front of the queue
      if (maze[curr.row][curr.col] == 'F') {
        finish_found = true;
        break;
      }
      for (int i = 0; i < 4; i++) {
        // explore nswe
        Location neighbor;
        if (i == 0) {
          neighbor.row = curr.row - 1;
          neighbor.col = curr.col;
        }
        if (i == 1) {
          neighbor.row = curr.row;
          neighbor.col = curr.col-1;
        }
        if (i == 2) {
          neighbor.row = curr.row + 1;
          neighbor.col = curr.col;
        }
        if (i == 3) {
          neighbor.row = curr.row;
          neighbor.col = curr.col + 1;
        }
          if ((isValid(neighbor.row,neighbor.col,rows,cols)) && (explored_arr[neighbor.row][neighbor.col] == false) 
        && (isAvailable(maze, rows, cols, neighbor))) {
          //char** maze, int row, int col, Location loc
          // check if neighbor is valid, available, and not marked as explored
          predecessor[neighbor.row][neighbor.col] = curr;
          queue.add_to_back(neighbor);
          explored_arr[neighbor.row][neighbor.col] = true;
        }
      }
    }
      // check if having isvalid && is necessary
    if (finish_found == false) {
      result = -1;
      // no path found
    }
    if (finish_found == true) {
      result = 1;
    }
      // until start cell found
    while (maze[curr.row][curr.col] != 'S') {
      if (maze[curr.row][curr.col] != 'F') {
        maze[curr.row][curr.col] = '*';
      }
      curr = predecessor[curr.row][curr.col];
    }
      // walk pred array backwards from finish loc to start loc
      // fill maze with *
    for (int i = 0; i < rows; i++) {
      delete [] predecessor[i];
      delete [] explored_arr[i];
    }
    delete [] predecessor;
    delete [] explored_arr;
    if (result == -1) {
      return result;
    }
    else {
      result = 1;
      return result;
    }
}

