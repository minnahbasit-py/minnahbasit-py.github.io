
// NxN tic-tac-toes
#include <iostream>
#include <cstdlib>
using namespace std;

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when you find yourself wanting to
// convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 * Use this function wherever you generate, row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);

/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToRow(int idx, int dim);

/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToCol(int idx, int dim);


/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/**
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 *
 */
int checkForWinner(char grid[], int dim);


/**
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 *
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);

/**
 * @brief Get the Ai Choice for the current player and update grid object
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If an error occurred or a choice was unable to be made
 * @return false If a play was successfully made
 */
bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player);

/**
 * @brief Picks a random location for the current player and update grid
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If no viable location to be played
 * @return false If a play was successfully made
 */
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player);


/**********************************************************
 *  Write your implementations for each function prototyped
 *  above in the space below
 **********************************************************/

char getEntryAtRC(char grid[], int dim, int r, int c)
{
    return grid[(dim*r)+c ];
}

int idxToRow(int idx, int dim)
{
    return (idx/dim );
}

int idxToCol(int idx, int dim)
{
    return (idx%dim);
}

void printTTT(char grid[], int dim)
{
  int line_width = 3 * dim + (dim - 1);
  for (int i = 0; i < (dim*dim); i++) {
    cout << " " << grid[i];
    if ((i + 1) % dim == 0) {
      cout << endl;
      if ((i+1) < dim * dim) {
        for (int j = 0; j < line_width; j++) {
          cout << "-";
        }
        cout << endl;
      }
    }
    else {
      cout << " |";
    }
  }
  // prints board
}

int checkForWinner(char grid[], int dim)
{
  /**
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 *
 */
 // check rows
 int x_cnt = 0;
 int o_cnt = 0;
 // i thought to have dim*dim
  for (int i = 0; i < dim; i++) {
    x_cnt = 0;
    o_cnt = 0;
    for (int j = 0; j < dim; j++){
      if (getEntryAtRC(grid,dim,i,j) == 'X') {
        x_cnt++;
      }
      if (getEntryAtRC(grid,dim,i,j) == 'O') {
        o_cnt++;
      }
    }
    if (x_cnt == dim) {
      return 1;
      // X has won
    }
    if (o_cnt == dim) {
      return 2;
      // O has won
    }
  }
  // check cols
  // reset counters
  x_cnt = 0;
  o_cnt = 0;
  for (int j = 0; j < dim; j++) {
    x_cnt = 0;
    o_cnt = 0;
    for (int i = 0; i < dim; i++){
      if (getEntryAtRC(grid,dim,i,j) == 'X') {
        x_cnt++;
      }
      if (getEntryAtRC(grid,dim,i,j) == 'O') {
        o_cnt++;
      }
    }
    if (x_cnt == dim) {
      return 1;
    }
    if (o_cnt == dim) {
      return 2;
    }
  }
  // reset counters
  x_cnt = 0;
  o_cnt = 0;
  // left diagonal
  for (int i = 0; i < dim; i++) {
    // x_cnt = 0;
    // o_cnt = 0;
    if (getEntryAtRC(grid,dim, i ,i) == 'X') {
      x_cnt++;
    }
    if (getEntryAtRC(grid,dim, i ,i) == 'O') {
      o_cnt++;
    }
  }
  if (x_cnt == dim) {
    return 1;
  }
  if (o_cnt == dim) {
    return 2;
  }
  // right diag
  x_cnt = 0;
  o_cnt = 0;
  for (int i = 0; i < dim; i++) {
  //   x_cnt = 0;
  // o_cnt = 0;
    if (getEntryAtRC(grid, dim, i, dim - 1 - i) == 'X') {
      x_cnt++;
    }
    if (getEntryAtRC(grid, dim, i, dim - 1 - i) == 'O') {
      o_cnt++;
    }
  }
  if (x_cnt == dim) {
    return 1;
  }
  if (o_cnt == dim) {
    return 2;
  }
  return 0;
}

bool checkForDraw(char grid[], int dim)
{
  // checking draw in rows
  int x_cnt = 0;
  int o_cnt = 0;
  int draw_row = 0;
  int draw_col = 0;
  int draw_r_l = 0;
  int draw_l_r = 0;
  int draw = 0;
  for (int i = 0; i < dim; i++) {
    x_cnt = 0;
    o_cnt = 0;
    for (int j = 0; j < dim; j++){
      if (getEntryAtRC(grid,dim,i,j) == 'X') {
        x_cnt++;
      }
      if (getEntryAtRC(grid,dim,i,j) == 'O') {
        o_cnt++;
        
      }
    }
    if ((x_cnt > 0) && (o_cnt > 0)) {
      // 3 from rows
      draw_row += 1;
    }
    if(draw_row == dim)
    {
      draw += 1;
      //cout << "drawRow" << draw << endl;
      break;
    }
  }
  // checking draw in cols
  // x_cnt = 0;
  // o_cnt = 0;
  for (int j = 0; j < dim; j++) {
    x_cnt = 0;
    o_cnt = 0;
    for (int i = 0; i < dim; i++){
      if (getEntryAtRC(grid,dim,i,j) == 'X') {
        x_cnt++;
      }
      if (getEntryAtRC(grid,dim,i,j) == 'O') {
        o_cnt++;
      }
    }
    if ((x_cnt > 0) && (o_cnt > 0)) {
      // 3 from cols
      draw_col += 1;
    }
    if(draw_col == dim)
    {
      draw += 1;
      //cout << "drawCol" << draw << endl;
      break;
    }
  }
  x_cnt = 0;
  o_cnt = 0;
  // left diagonal
  for (int i = 0; i < dim; i++) {
    // x_cnt = 0;
    // o_cnt = 0;
    if (getEntryAtRC(grid,dim, i ,i) == 'X') {
      x_cnt++;
    }
    if (getEntryAtRC(grid,dim, i ,i) == 'O') {
      o_cnt++;
    }
    if ((x_cnt > 0) && (o_cnt > 0)) {
      draw_l_r += 1;
    }
    if(draw_l_r == 1) {
      draw += 1;
      //cout << "drawLD" << draw << endl;
    }
  }
  
  // checking right diag
  x_cnt = 0;
  o_cnt = 0;
  for (int i = 0; i < dim; i++) {
    // x_cnt = 0;
    // o_cnt = 0;
    if (getEntryAtRC(grid, dim, i, dim - 1 - i) == 'X') {
      x_cnt++;
    }
    if (getEntryAtRC(grid, dim, i, dim - 1 - i) == 'O') {
      o_cnt++;
    }
  }
  if ((x_cnt > 0) && (o_cnt > 0)) {
    draw_r_l += 1;
    //cout << "draw_r_l" << draw_r_l << endl;
  }
  if (draw_r_l == 1) {
    draw += 1;
    //cout << "drawRD" << draw << endl;
  }
  
  if (draw == 4) {
    return true;
  }
  return false;
}

bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player)
{
  char player2;
  int dim_sq = dim*dim;
  if (player == 'X') {

    player2 = 'O';
  }
  else {
    player2 = 'X';
  }

  for (int i = 0; i < dim_sq; i++) {
    if (grid[i] == '?') {
      grid[i] = player;
      // set player to location
      // if player can win on this location checkwinner will b true
      if (checkForWinner(grid,dim)) {
        return true;
        // return so grid is updated in main
        // player can win on this move
      }
      grid[i] = '?';
      //cout << "i: " << grid[i] << endl;
    }
  }
  // player can't win on this move
  for (int i = 0; i < dim_sq; i++) {
    if (grid[i] == '?') {
      grid[i] = player2;
      if (checkForWinner(grid,dim)) {
        // other player can win on this move
        // need to block
        grid[i] = player;
        //grid[player2_loc] = player;
        return true;
      }
      grid[i] = '?';
    }
  }
  // neither player has a winning move
  //grid[player1_loc] = '?';
  // set rand choice
  getRandChoiceAndUpdateGrid(grid,dim,player);
  return false;
}


// Complete...Do not alter
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player)
{
    int start = rand()%(dim*dim);
    // look for an open location to play based on random starting location.
    // If that location is occupied, move on sequentially until wrapping and
    // trying all locations
    for(int i=0; i < dim*dim; i++) {
        int loc = (start + i) % (dim*dim);
        if(grid[ loc ] == '?') {
            grid[ loc ] = player;
            return false;
        }
    }
    // No viable location
    return true;
}

/**********************************************************
 *  Complete the indicated parts of main(), below.
 **********************************************************/
int main()
{
    // This array holds the actual board/grid of X and Os. It is sized
    // for the biggest possible case (11x11), but you should only
    // use dim^2 entries (i.e. if dim=3, only use 9 entries: 0 to 8)
    char tttdata[121];

    // dim stands for dimension and is the side length of the
    // tic-tac-toe board i.e. dim x dim (3x3 or 5x5).
    int dim;
    int seed;
    // Get the dimension from the user
    cin >> dim >> seed;
    srand(seed);

    int dim_sq = dim*dim;

    for(int i=0; i < dim_sq; i++) {
        tttdata[i] = '?';
    }

    // Print one of these messages when the game is over
    // and before you quit
    const char xwins_msg[] = "X player wins!";
    const char owins_msg[] = "O player wins!";
    const char draw_msg[] =  "Draw...game over!";

    bool done = false;
    char player = 'X';
    // Show the initial starting board
    printTTT(tttdata, dim);
    int counter = 2;
    bool player_x;
    string x_prompt = "Player X enter your square choice ";
    string o_prompt = "Player O enter your square choice ";
    string prompt2 = ", -1 (AI), or -2 (Random):";

    while(!done) {

        //**********************************************************
        // Get the current player's input (i.e. the location they want to
        // choose to place their mark [X or O]) or choice of AI or Random
        // location and update the tttdata array.
        // Be sure to follow the requirements defined in the guide/writeup
        // for quitting immediately if the user input is out-of-bounds
        // (i.e. not in the range 0 to dim_sq-1 nor -1 nor -2) as well as
        // continuing to prompt for an input if the user chooses locations
        // that have already been chosen (already marked with an X or O).
        //**********************************************************

        // Add your code here for getting input
        int choice;
        if (counter % 2 == 0) {
          player_x = true;
          // set player1
        }
        if (counter % 2 == 1) {
          player_x = false;
          // set player2
        }
        if (player_x) {
          player = 'X';
          cout << x_prompt;
          cout << "[0-" << (dim_sq) - 1 << "]";
          cout << prompt2 << endl;
        }
        if (!player_x) {
          player = 'O';
          cout << o_prompt;
          cout << "[0-" << (dim_sq) -1 << "]";
          cout << prompt2 << endl;
        }
        cin >> choice;
        // out of bounds checking
        if ((choice < -1)|| (choice > (dim_sq -1))) {
          return 0;
        }
        // reprompting if user chooses a square thats occupied
        while ((tttdata[choice] != '?') && (choice != -1)) {
          counter += 1;
          if (choice < -1) {
            return 0;
          }
          if (choice > (dim_sq-1)) {
            return 0;
          }
          if (player_x) {
            cout << x_prompt;
            cout << "[0-" << (dim_sq) -1 << "]";
            cout << prompt2 << endl;
            player = 'X';
            counter += 1;
          }
          if (!player_x) {
            cout << o_prompt;
            cout << "[0-" << (dim_sq) -1 << "]";
            cout << prompt2 << endl;
            player = 'O';
            counter += 1;
          }
          cin >> choice;
        }

        if (player_x) {
          if (choice == -1) {
            getAiChoiceAndUpdateGrid(tttdata,dim,player);
            // if user chooses AI
          }
          else {
            tttdata[choice] = player;
          }
        }
        if (!player_x) {
          if (choice == -1) {
            getAiChoiceAndUpdateGrid(tttdata,dim,player);
          }
          else {
            tttdata[choice] = player;
          }
        }

        // Show the updated board if the user eventually chose a valid location
        // (i.e. you should have quit the loop and program by now without any
        //  other output message if the user chosen an out-of-bounds input).
        printTTT(tttdata, dim);
        

        //**********************************************************
        // Complete the body of the while loop to process the input that was just
        //  received to check for a winner or draw and update other status, as
        //  needed.
        //
        // To match our automated checkers' expected output, you must output
        // one of the messages defined above using *one* of the cout commands
        // (under the appropriate condition) below:
        //   cout << xwins_msg << endl;  OR
        //   cout << owins_msg << endl;  OR
        //   cout << draw_msg << endl;
        //
        // Note: Our automated checkers will examine a specific number of lines
        //  at the end of the program's output and expect to see the updated board
        //  and game status message.  You may certainly add some debug print
        //  statements during development but they will need to be removed to
        //  pass the automated checks.
        //**********************************************************
        int check_win = checkForWinner(tttdata,dim);
        bool check_draw = checkForDraw(tttdata,dim);
        if ((check_win == 1) && (player_x)) {
          // users won
          cout << xwins_msg << endl;
          return 0;
        }
        if ((check_win == 2) && (!player_x)) {
          cout << owins_msg << endl;
          return 0;
        }
        if (check_draw) {
          cout << draw_msg << endl;
          return 0;
        }
        counter += 1;


    } // end while
    return 0;
}
