
// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
bool playAgain();
void winMessage(int* phand,int pcount, int* dhand, int dcount);
void loseMessage(int* phand,int pcount, int* dhand, int dcount);
void userPrompt();
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);
bool checkBust(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

bool playAgain() {
  // asks user if they want to play again and returns bool val
  cout << endl;
  char choice;
  cout << "Play again? [y/n]" << endl;
  cin >> choice;
  if (choice == 'n') {
    return false;
  }
  else {
    return true;
  }
}
void userPrompt() {
  // function for repetitive question of hitting or staying
  cout << "Type 'h' to hit and 's' to stay:" << endl;
}
/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */

void shuffle(int cards[])
{
  // used fisher yates algorithm to shuffle
  for (int i = 0; i < NUM_CARDS; i++) {
    cards[i] = i;
  }
  for (int i = NUM_CARDS-1; i >= 1; i--) {
    int j = rand() % (i+1);
    int temp_val = cards[i];
    cards[i] = cards[j];
    cards[j] = temp_val;
  }
  // To shuffle an array a of n elements (indices 0..n-1):
  // for i from n - 1 downto 1 do
  // j = random integer with 0 <= j <= i
  // exchange a[j] and a[i]

}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Must use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id)
{

  /******** You complete ****************/
  // outputs suit and value of cards dealt
  char suit_ = suit[id/13];
  const char* val = type[id % 13];
  cout << val << "-" << suit_ << " ";

}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Must use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  //const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};
  // just gives the value of the card for total score purposes
  return value[id % 13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  // prints all cards a player/dealer has
  for (int i = 0; i < numCards; i++) {
    printCard(hand[i]);
    cout << " ";
  }
  cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  int total_score = 0;
  int ace_count = 0;
  /******** You complete ****************/
  // first count how many aces and see the total score bare
  for (int i = 0; i < numCards; i++) {
    if (cardValue(hand[i]) == 11) {
      ace_count++;
    }
    total_score += cardValue(hand[i]);
  }
  // if the player is going to bust because of their score, subtract as many
  // aces needed to get player/dealer back down to a number where they wont bust
  while (total_score > 21 && ace_count > 0) {
    total_score -= 10;
    ace_count--;
  }
  return total_score;
}
bool checkBust(int hand[], int numCards) {
  // bool function that returns if they have busted or not
  return getBestScore(hand, numCards) > 21;
}
void winMessage(int* phand,int pcount, int* dhand, int dcount) {
  // repetitive message displayed if player won
  cout << "Win " << getBestScore(phand, pcount) << " " << getBestScore(dhand, dcount) << endl;
}
void loseMessage(int* phand,int pcount, int* dhand, int dcount) {
  // repetitive message displayed if player lost
  cout << "Lose " << getBestScore(phand, pcount) << " " << getBestScore(dhand, dcount)  << endl;
}
/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    //return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  bool end_game = false;
  int pcard_count;
  int dcard_count;
  char player_choice;
  
  //bool test = true;
  
  // while loop will end when player wants to end the game
  while(!end_game) {
    int top_card = 4;
    //int turn = 0;
    bool play_again = false;
    shuffle(cards);
    // for (int i = 0; i < 52; i++) {
    //   cout << cards[i] << " ";
    // }
    phand[0] = cards[0];
    dhand[0] = cards[1];
    phand[1] = cards[2];
    dhand[1] = cards[3];
    // shuffle and dealt cards
    pcard_count = 2;
    dcard_count = 2;
    cout << "Dealer: ? ";
    printCard(dhand[1]);
    cout << " " << endl; 
    cout << "Player: ";
    printHand(phand, pcard_count);
    // cout << "Dealer: ? ";
    // printCard(dhand[1]);
    //   cout << " " << endl; 
    // cout << "Player: ";
    // printHand(phand, pcard_count);
    // checks if player has already hit blackjack, if so give dealer turn
    if (getBestScore(phand, pcard_count) == 21) {
      while (getBestScore(dhand, dcard_count) < 17) {
        dhand[dcard_count] = cards[top_card];
        top_card++;
        dcard_count++;
      }
      // if player has still won aka dealer hasn't hit blackjack, automatic win for player
      if (getBestScore(phand,pcard_count) == 21) {
        if ((getBestScore(phand,pcard_count)) > getBestScore(dhand,dcard_count)) {
          cout << "Dealer: ";
          printHand(dhand, dcard_count);
          winMessage(phand, pcard_count, dhand, dcard_count);
        }
      }
      // ask if they want to play again
      if (!playAgain()) {
            return 0;
        }
      else {
          play_again = true;
      }
      // continue back up to the beginning of while loop
      if (play_again == true) {
        continue;
      } 
    }
    // check if player has busted
    else {
      if (checkBust(phand,pcard_count)) {
        loseMessage(phand, pcard_count, dhand, dcard_count);
        if (!playAgain()) {
            return 0;
          }
          else {
            play_again = true;
          }
        }
        if (play_again == true) {
            continue;
        } 
      userPrompt();
      cin >> player_choice;
      // input validation
      if (player_choice != 'h' && player_choice != 's') {
        //cout << "Incorrect choice" << endl;
        return 0;
      }
      // if player has chose to hit they can keep hitting UNTIL they hit s
      while (player_choice == 'h') {
        // deal additional card
        phand[pcard_count] = cards[top_card];
        pcard_count++;
        top_card++;
        cout << "Player: ";
        printHand(phand, pcard_count);
        //cout << "Dealer: ";
        //printHand(dhand, dcard_count);
        // check if hitting has made player bust
        if (checkBust(phand,pcard_count)) {
          cout << "Player busts" << endl;
          loseMessage(phand, pcard_count, dhand, dcard_count);
          if (!playAgain()) {
            return 0;
          }
          else {
            play_again = true;
          }
        }
        if (play_again == true) {
          // if they do want to play again break out of hit while loop and go to
          // main game while loop
          break;
        } 
        // if players hit blackjack give dealer turn
        if (getBestScore(phand,pcard_count) == 21) {
          while (getBestScore(dhand, dcard_count) < 17) {
            dhand[dcard_count] = cards[top_card];
            // keep dealing cards to dealer
                  top_card++;
                  dcard_count++;
          }
        }
        // check if players still at blackjack and dealer hasn't hit blacjack either
        // so player wins
        if (getBestScore(phand,pcard_count) == 21) {
          if ((getBestScore(phand,pcard_count)) > getBestScore(dhand,dcard_count)) {
          cout << "Dealer: ";
          printHand(dhand, dcard_count);
          winMessage(phand, pcard_count, dhand, dcard_count);
          }
          if (!playAgain()) {
            return 0;
          }
          else {
            play_again = true;
          }
        }
        if (play_again == true) {
          break;
        } 
        // if they have reached here ask them if they want to hit or stay as they havent
        // won or lost yet
        userPrompt();
        cin >> player_choice;
      } // hit
      
      if (play_again == true) {
        continue;
      }
      // player has decided to stay 
      if (player_choice == 's') {
        // userPrompt();
        // cin >> player_choice;
        // deal cards to dealer and try not to go over 17
        if (getBestScore(dhand, dcard_count) < 17) {
          while (getBestScore(dhand, dcard_count) < 17) {
            dhand[dcard_count] = cards[top_card];
            top_card++;
            dcard_count++;
          }
        }
        // if thye have equal scores, tie
        if (getBestScore(dhand, dcard_count) == getBestScore(phand,pcard_count)) {
          cout << "Dealer: ";
          printHand(dhand,dcard_count);
          cout << "Tie " << getBestScore(phand, pcard_count) << " " << getBestScore(dhand, dcard_count) << endl;
          if (!playAgain()) {
            return 0;
          }
          else {
            play_again = true;
          }
        }
        if (play_again == true) {
            continue;
        } 
        // if dealer still hasn't gotten more total score then players won
        if (getBestScore(phand, pcard_count) > getBestScore(dhand,dcard_count)) {
          cout << "Dealer: ";
          printHand(dhand, dcard_count);
          winMessage(phand, pcard_count, dhand, dcard_count);
          if (!playAgain()) {
            return 0;
          }
          else {
            play_again = true;
          }
        }
        if (play_again == true) {
            continue;
        }
        // dealers total is over 21, so they bust 
        if (getBestScore(phand, pcard_count) < getBestScore(dhand, dcard_count)) {
          if (checkBust(dhand, dcard_count)) {
            cout << "Dealer: ";
            printHand(dhand,dcard_count);
            cout << "Dealer busts" << endl;
            winMessage(phand, pcard_count, dhand, dcard_count);
          }
          else {
            cout << "Dealer: ";
            printHand(dhand,dcard_count);
            loseMessage(phand, pcard_count, dhand, dcard_count);
          }
          if (!playAgain()) {
            return 0;
          }
          else {
            play_again = true;
          }
        }
        if (play_again == true) {
            continue;
        } 
        // why are we checking again if they have busted
        if (checkBust(dhand, dcard_count)) {
          cout << "Dealer: ";
          printHand(dhand,dcard_count);
          cout << "Dealer busts" << endl;
          if (!playAgain()) {
            return 0;
          }
          else {
            play_again = true;
          }
        }
        if (play_again == true) {
            continue;
        } 
      } // s
    } // else
  } // while loop
  return 0;
}
