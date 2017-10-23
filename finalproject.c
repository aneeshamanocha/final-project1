#include <stdio.h>
#include <stdlib.h>

#define CARDS 52
#define SUITS 4
#define FACES 13
#define CAPACITY 1

//each card composes of a suit & face
typedef struct card {
  int cardNum; //0-51
  char *suit; //diamonds, clubs, hearts, spades
  int face; //2-14
} Card;

typedef struct vector {
  size_t size;
  size_t capacity;
  Card *cards;
} Vector;

void clear(Vector *vector);
void init(Vector *vector);
void resetDeck(Card * deck[], const char *suits[], int faces[]);
void shuffleDeck(Card deck[]);

int main(void){
  //start the game
  //srand(time(NULL));
  puts("Welcome to the Game of BS! Are you ready to play?");
  char str1;
  printf("y or n?\n");
  scanf("%c", &str1);
  if(str1 == 'n') {
    printf("Maybe next time!\n");
    return 0;
  }

  //5 arraylists: player, comp1, comp2, comp3, pile & initialize all of them
  //1 card deck - initalize it as well
  Vector player;
  Vector comp1;
  Vector comp2;
  Vector comp3;
  Vector pile;
  Card deck[CARDS];
  const char *suits[SUITS] = {"Diamonds", "Clubs", "Hearts", "Spades"};
  int faces[FACES] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  init(&player);
  init(&comp1);
  init(&comp2);
  init(&comp3);
  init(&pile);
  resetDeck(&deck, suits, faces);
  for(size_t i = 0; i < CARDS; i++) {
    printf("CardNum: %d Suit: %s Face: %d\n", deck[i].cardNum, deck[i].suit, deck[i].face);
  }
  puts("---------------");
  shuffleDeck(deck);
  for(size_t i = 0; i < CARDS; i++) {
    printf("CardNum: %d Suit: %s Face: %d\n", deck[i].cardNum, deck[i].suit, deck[i].face);
  }

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



  return 0;
}

void clear(Vector *vector) {
    free(vector->cards);
}

void init(Vector *vector) {
  vector->size = 0;
  vector->capacity = CAPACITY;
  vector->cards = calloc(CAPACITY, sizeof(char));
}

void resetDeck(Card * deck[], const char *suits[], int faces[]) {
  for(size_t i = 0; i < CARDS; ++i) {
    deck[i]->cardNum = i;
    deck[i]->suit = suits[i/SUITS];
    deck[i]->face = faces[i % FACES];
  }
}

void shuffleDeck(Card deck[]) {
  Card tmp;
  int randIndex;
  for(size_t i = 0; i < CARDS-1; ++i)
  {
    randIndex = rand() % (CARDS-i) + i;
    Card tmp = deck[i];
    deck[i] = deck[randIndex];
    deck[randIndex] = tmp;
  }
}
