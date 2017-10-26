#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
void insertCard(Vector *vector, Card card); //insert cards for each player
void resizeIfFull(Vector *vector); //resize vector if full
void deleteCard(Vector *vector, int cardNum); //deletes card
Vector * findAceOfSpades(Vector *vector); //find ace of spades

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

  //explaining rules of BS
  puts("Here are the rules for BS: The cards are distributed evenly between three computers players and you. The ace of spades will be placed down first and then following the placement, the next player will check their deck for the number two. If they have any twos, they will place all of them down and say they have an amount of twos. If they do not have a two, they will place down one random card and claim they placed down a two. Each player then has a chance of calling BS on them. If somebody gets called for BS, the last card placed on the pile will be shown to the players. If the person who placed down the last card lied and the card wasn't the number they stated it was, the whole pile gets added to their deck. If the person who called BS is wrong and the person does have that card, they will get the whole pile added to their deck. The game will circle through the players, and the next player will place down threes. The same procedure will continue to occur until somebody runs out of cards.");
  puts("");

  sleep(5);

  //player1 assigned cards
  puts("YOUR CARDS");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&player, deck[i]);
    //printf("CardNum: %d Suit: %s Face: %s\n", (player.cards[i]).cardNum, (player.cards[i]).suit, (player.cards[i]).face);
  }
  printVector(&player);


  //comp1 assigned cards
  puts("FOR COMP 1");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp1, deck[i+13]);
    printf("CardNum: %d Suit: %s Face: %s\n", (comp1.cards[i]).cardNum, (comp1.cards[i]).suit, (comp1.cards[i]).face);
  }

  //comp2 assigned cards
  puts("FOR COMP 2");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp2, deck[i+26]);
    printf("CardNum: %d Suit: %s Face: %s\n", (comp2.cards[i]).cardNum, (comp2.cards[i]).suit, (comp2.cards[i]).face);
  }

  //comp3 assigned cards
  puts("FOR COMP 3");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp3, deck[i+39]);
    printf("CardNum: %d Suit: %s Face: %s\n", (comp3.cards[i]).cardNum, (comp3.cards[i]).suit, (comp3.cards[i]).face);
  }

  /*Vector tmp;
  for(size_t i = 0; i < player.size; ++i) {
    if((player.cards[i]).cardNum == 51) {
      insertCard(&pile, player.cards[i]);
      tmp = player;
      puts("in player 1");
      break;
    }
  }
  for(size_t i = 0; i < comp1.size; ++i) {
    if((comp1.cards[i]).cardNum == 51) {
      insertCard(&pile, comp1.cards[i]);
      tmp = comp1;
      puts("in comp 1");
      break;
    }
  }
  for(size_t i = 0; i < comp2.size; ++i) {
    if((comp2.cards[i]).cardNum == 51) {
      insertCard(&pile, comp2.cards[i]);
      tmp = comp2;
      puts("in comp 2");
      break;
    }
  }
  for(size_t i = 0; i < comp2.size; ++i) {
    if((comp2.cards[i]).cardNum == 51) {
      tmp = comp2;
      insertCard(&pile, comp2.cards[i]);
      puts("in comp 2");
      break;
    }
  }*/

  //find ace of spades and add to pile
  if(findAceOfSpades(&player) != NULL) {
    puts("hello1");
    for(size_t i = 0; i <= player.size; ++i) {
      puts("??");
      if((player.cards[i]).cardNum == 51) {
        insertCard(&pile, player.cards[i]);
        deleteCard(&player, (player.cards[i]).cardNum);
        puts("in player 1");
        break;
      }
    }
  } else if(findAceOfSpades(&comp1) != NULL) {
    puts("hello3");
    for(size_t i = 0; i <= comp1.size; ++i) {
      puts("??");
      if((comp1.cards[i]).cardNum == 51) {
        puts("hello4");
        insertCard(&pile, comp1.cards[i]);
        deleteCard(&comp1, (comp1.cards[i]).cardNum);
        puts("in comp 1");
        break;
      }
    }
  } else if(findAceOfSpades(&comp2) != NULL) {
    puts("hello5");
    for(size_t i = 0; i <= comp2.size; ++i) {
      puts("??");
      if((comp2.cards[i]).cardNum == 51) {
        puts("hello6");
        insertCard(&pile, comp2.cards[i]);
        deleteCard(&comp2, (comp2.cards[i]).cardNum);
        puts("in comp 2");
        break;
      }
    }
  } else {
    for(size_t i = 0; i <= comp3.size; ++i) {
      if((comp3.cards[i]).cardNum == 51) {
        insertCard(&pile, comp3.cards[i]);
        deleteCard(&comp3, (comp3.cards[i]).cardNum);
        puts("in comp 3");
        break;
      }
    }
  }


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
  for(size_t i = 0; i < CARDS-1; ++i){
    randIndex = rand() % (CARDS-i) + i;
    Card tmp = deck[i];
    deck[i] = deck[randIndex];
    deck[randIndex] = tmp;
  }
}

void printVector(Vector *vector) {
  for(size_t i = 0; i < vector->size; ++i) {
    printf("Card %lu: %s of %s\n", (i+1), (vector->cards[i]).face, (vector->cards[i]).suit);
  }
}

void printDeck(Card deck[]) {
  for(size_t i = 0; i < CARDS; i++) {
    printf("CardNum: %d Suit: %s Face: %s\n", deck[i].cardNum, deck[i].suit, deck[i].face);
  }
}

void insertCard(Vector *vector, Card card){
  resizeIfFull(vector);
  vector->cards[vector->size] = card;
  vector->size++;
}

void resizeIfFull(Vector *vector) {
  if(vector->size >= vector->capacity) {
    vector->capacity *= 2;
    vector->cards = realloc(vector->cards, sizeof(char) * vector->capacity);
  }
}

Vector * findAceOfSpades(Vector *vector){
  for(size_t i = 0; i < vector->size; ++i) {
    if((vector->cards[i]).cardNum == 51) {
      return vector;
    }
  }
  return NULL;
}

void deleteCard(Vector *vector, int cardNum){
  int index;
  for(size_t i = 0; i < vector->size; ++i) {
    if((vector->cards[i]).cardNum == cardNum) {
      index = i;
      break;
    }
  }

  for(size_t i = index; i < vector->size-1; ++i) {
    vector->cards[i] = vector->cards[i+1];
  }
  vector->size -= 1;

}
