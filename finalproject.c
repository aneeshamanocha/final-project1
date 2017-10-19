#include <stdio.h>
#include <stdlib.h>

#define CARDS 52
#define SUITS 4
#define FACES 13

typedef struct card {
  int cardNum;
  char *suit;
  char *face;
} Card;

typedef struct vector {
  size_t size;
  size_t capacity;
  Card *cards;
}


void printCard(const int card, const char *suits[], const char *faces[]);
void resetDeck(int deck[]);
void shuffleDeck(int deck[]);
/*
* functions:
* shuffle (Fisher Yates)
*/

int main(void){
  
  //5 arraylists: player, comp1, comp2, comp3, pile
  puts("Welcome to the Game of BS! Are you ready to play?");
  //shuffle
  //assign cards to three computers and player
  //show card to player & ask when ready to start Game
  //user with ace of spades puts it down and next user goes
  //function to check if user has next card
    //if does, place down those card(s)
    //else place random card down
    //each user has random chance to call BS
      //if BS is called, check the last card
        //if last card is the incorrect card, add all the cards from pile into arraylist & reset pile to 0
    
  //if comp1/comp2/comp3/player size == 0, print ("comp/player won the game!")
  srand(time(NULL));
  
  int deck[CARDS] = {0};
  const char *suits[SUITS] = {"Diamonds", "Clubs", "Hearts", "Spades"};
  const char *faces[FACES] = {"Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
  
  resetDeck(deck);
  shuffleDeck(deck);
  
  return 0;
}

void printCard(const int card, const int char *suits[], const char *faces[])
{
  printf("%s of %s\n", faces[card%FACES], suits[card/FACES]);
}

void resetDeck(int deck[])
{
  for(size_t i =0; i < CARDS; ++i)
  deck[i] = (int)i;
}

void shuffleDeck(int deck[])
{
  int randIndex, tmp;
  for(size_t i =0; i < CARDS-1; ++i)
  {
    randIndex = rand() % (CARDS-i) + i;
    int tmp = deck[i];
    deck[i] = deck[randIndex];
    deck[randIndex] = tmp;
  }
}
