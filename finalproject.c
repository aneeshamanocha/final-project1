#include <stdio.h>
#include <stdlib.h>

#define CARDS 52
#define SUITS 4
#define FACES 13

/*
* create struct for each card
* holds: cardnum (2-ace), suit, face
* arraylist struct
*/

typedef struct card {
  int cardNum;
  char *suit;
  char *face;
} Card;


/*
* functions:
* shuffle (Fisher Yates)
*/

int main(void){
  puts("Welcome to the Game of BS!");
  //shuffle
  //assign cards to three computers and player
  //show card to player & ask when ready to start Game
  //user with ace of spades puts it down and next user goes
  //function to check if user has next card
    //if does, place down those card(s)
    //else place random card down
    //each user has random chance to call BS
    //add cards to arraylist if necessary
  
}
