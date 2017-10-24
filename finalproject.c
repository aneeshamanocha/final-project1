#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARDS 52
#define SUITS 4
#define FACES 13
#define CAPACITY 1

//each card composes of a suit & face
typedef struct card {
  int cardNum; //0-51
  char *suit; //diamonds, clubs, hearts, spades
  char *face; //2-14
} Card;

typedef struct vector {
  size_t size; //size of specific vector
  size_t capacity; //capacity of vector
  Card *cards; //cards
} Vector;

void clear(Vector *vector); //free vector
void init(Vector *vector); //initialize vector
void resetDeck(Card deck[], char *suits[], char *faces[]); //reset deck of cards
void shuffleDeck(Card deck[]); //shuffle deck of cards
void printDeck(Card deck[]); //print deck
void printVector(Vector *vector);
int insertCard(Vector *vector, Card card, int index); //insert cards for each player
void resizeIfFull(Vector *vector); //resize vector if full


int main(void){
  //start the game
  srand(time(NULL));
  puts("Welcome to the Game of BS! Are you ready to play?");
  char str1;
  printf("y or n?\n");
  scanf("%c", &str1);
  if(str1 == 'n') {
    printf("Maybe next time!\n");
    return 0;
  }

  //clears command line
  printf("\e[1;1H\e[2J");

  //5 arraylists: player, comp1, comp2, comp3, pile & initialize all of them
  //1 card deck - initalize it as well
  Vector player;
  Vector comp1;
  Vector comp2;
  Vector comp3;
  Vector pile;
  Card deck[CARDS];
  char *suits[SUITS] = {"Diamonds", "Clubs", "Hearts", "Spades"};
  char *faces[FACES] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
  "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
  init(&player);
  init(&comp1);
  init(&comp2);
  init(&comp3);
  init(&pile);
  resetDeck(deck, suits, faces);
  shuffleDeck(deck);

  //player1 assigned cards
  puts("YOUR CARDS");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&player, deck[i], i);
    printf("CardNum: %d Suit: %s Face: %s\n", (player.cards[i]).cardNum, (player.cards[i]).suit, (player.cards[i]).face);
  }

  //comp1 assigned cards
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp1, deck[i+13], i);
    //puts("FOR COMP 1");
    //printf("CardNum: %d Suit: %s Face: %s\n", (comp1.cards[i]).cardNum, (comp1.cards[i]).suit, (comp1.cards[i]).face);
  }

  //comp2 assigned cards
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp2, deck[i+26], i);
    //puts("FOR COMP 2");
    //printf("CardNum: %d Suit: %s Face: %s\n", (comp2.cards[i]).cardNum, (comp2.cards[i]).suit, (comp2.cards[i]).face);
  }

  //comp3 assigned cards
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp3, deck[i+39], i);
    //puts("FOR COMP 3");
    //printf("CardNum: %d Suit: %s Face: %s\n", (comp3.cards[i]).cardNum, (comp3.cards[i]).suit, (comp3.cards[i]).face);
  }

  /*puts("FOR PLAYER");
  printVector(&player);*/

  

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

void resetDeck(Card deck[], char *suits[], char *faces[]) {
  for(size_t i = 0; i < CARDS; ++i) {
    deck[i].cardNum = i;
    deck[i].suit = suits[i/FACES];
    deck[i].face = faces[i % FACES];
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

void printVector(Vector *vector) {
  for(size_t i = 0; i < vector->size; ++i) {
    printf("For %zu card:\n", i);
    printf("CardNum: %d Suit: %s Face: %s\n", (vector->cards[i]).cardNum, (vector->cards[i]).suit, (vector->cards[i]).face);
  }
}

void printDeck(Card deck[]) {
  for(size_t i = 0; i < CARDS; i++) {
    printf("CardNum: %d Suit: %s Face: %s\n", deck[i].cardNum, deck[i].suit, deck[i].face);
  }
}

int insertCard(Vector *vector, Card card, int index){
  resizeIfFull(vector);
  vector->cards[index] = card;
  vector->size++;
}

void resizeIfFull(Vector *vector) {
  if(vector->size >= vector->capacity) {
    vector->capacity *= 2;
    vector->cards = realloc(vector->cards, sizeof(char) * vector->capacity);
  }
}
