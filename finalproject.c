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
  int face; //2-14
} Card;

//arraylist
typedef struct vector {
  size_t size; //size of specific vector
  size_t capacity; //capacity of vector
  Card *cards; //cards
} Vector;

void clear(Vector *vector); //free vector
void init(Vector *vector); //initialize vector
void resetDeck(Card deck[], char *suits[], int faces[]); //reset deck of cards
void shuffleDeck(Card deck[]); //shuffle deck of cards
void printDeck(Card deck[]); //print deck
void printVector(Vector *vector); //print vector
void insertCard(Vector *vector, Card card); //insert cards for each player
void resizeIfFull(Vector *vector); //resize vector if full
void deleteCard(Vector *vector, int cardNum); //deletes card
int findAceOfSpades(Vector *vector); //find ace of spades
int findNumOfCards(Vector *vector, int current); //finds the number of those cards in vector

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
  int faces[FACES] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  init(&player);
  init(&comp1);
  init(&comp2);
  init(&comp3);
  init(&pile);
  resetDeck(deck, suits, faces);
  shuffleDeck(deck);

  //explaining rules of BS
  puts("Here are the rules for BS: The cards are distributed evenly between three computers players and you. The ace of spades will be placed down first and then following the placement, the next player will check their deck for the number two. If they have any twos, they will place all of them down and say they have an amount of twos. If they do not have a two, they will place down one random card and claim they placed down a two. Each player then has a chance of calling BS on them. If somebody gets called for BS, the last card placed on the pile will be shown to the players. If the person who placed down the last card lied and the card wasn't the number they stated it was, the whole pile gets added to their hand. If the person who called BS is wrong and the person does have that card, they will get the whole pile added to their deck. The game will circle through the players, and the next player will place down threes. The same procedure will continue to occur until somebody runs out of cards.");
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
    printf("CardNum: %d Suit: %s Face: %d\n", (comp1.cards[i]).cardNum, (comp1.cards[i]).suit, (comp1.cards[i]).face);
  }

  //comp2 assigned cards
  puts("FOR COMP 2");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp2, deck[i+26]);
    printf("CardNum: %d Suit: %s Face: %d\n", (comp2.cards[i]).cardNum, (comp2.cards[i]).suit, (comp2.cards[i]).face);
  }

  //comp3 assigned cards
  puts("FOR COMP 3");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp3, deck[i+39]);
    printf("CardNum: %d Suit: %s Face: %d\n", (comp3.cards[i]).cardNum, (comp3.cards[i]).suit, (comp3.cards[i]).face);
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

  Vector tmp;
  //find ace of spades and add to pile
  if(findAceOfSpades(&player) == 1) {
    puts("hello1");
    for(size_t i = 0; i <= player.size; ++i) {
      if((player.cards[i]).cardNum == 51) {
        insertCard(&pile, player.cards[i]);
        deleteCard(&player, (player.cards[i]).cardNum);
        puts("in player 1");
        break;
      }
    }
    tmp = player;
  } else if(findAceOfSpades(&comp1) == 1) {
    puts("hello2");
    for(size_t i = 0; i <= comp1.size; ++i) {
      if((comp1.cards[i]).cardNum == 51) {
        insertCard(&pile, comp1.cards[i]);
        deleteCard(&comp1, (comp1.cards[i]).cardNum);
        puts("in comp 1");
        break;
      }
    }
    tmp = comp1;
  } else if(findAceOfSpades(&comp2) == 1) {
    puts("hello3");
    for(size_t i = 0; i <= comp2.size; ++i) {
      if((comp2.cards[i]).cardNum == 51) {
        insertCard(&pile, comp2.cards[i]);
        deleteCard(&comp2, (comp2.cards[i]).cardNum);
        puts("in comp 2");
        break;
      }
    }
    tmp = comp2;
  } else {
    for(size_t i = 0; i <= comp3.size; ++i) {
      puts("hello4");
      if((comp3.cards[i]).cardNum == 51) {
        insertCard(&pile, comp3.cards[i]);
        deleteCard(&comp3, (comp3.cards[i]).cardNum);
        puts("in comp 3");
        break;
      }
    }
    tmp = comp3;
  }

  int currentCard = 2;   //current card player is looking for
  int counter = 0; //how many of that type of card the player has
  int alternative = 0; //bs card placed if player doesn't have the card asked for
  int numOfCardsPlacedDown; //if player wants to place down less/more cards than they have
  int additionalCard; //if player wants to place down more cards than they have
  int counter1, counter2, counter3; //counter for placing cards in pile
  char str2; //for scanf
  char str3; //for scanf
  char str4; //for scanf

  while((player.size != 0) && (comp1.size != 0) && (comp2.size != 0) && (comp3.size != 0)) {
    //find next player
    if((tmp.cards[0]).cardNum == (player.cards[0]).cardNum) {
      tmp = comp1;
    } else if((tmp.cards[0]).cardNum == (comp1.cards[0]).cardNum) {
      tmp = comp2;
    } else if((tmp.cards[0]).cardNum == (comp2.cards[0]).cardNum) {
      tmp = comp3;
    } else {
      tmp = player;

      //check player is ready to play
      puts("It's your turn. Are you ready to play?");
      printf("y or n?\n");
      scanf("%c", &str2);
      while(str2 == 'n') {
        puts("Do you want to stop the game?");
        printf("y or n?\n");
        scanf("%c", &str3);
        if(str3 == 'y') {
          puts("Play again sometime!");
          return 0;
        }
        puts("Let's try again. It's your turn. Are you ready to play?");
        printf("y or n?\n");
        scanf("%c", &str2);
      }

      //find the current card
      puts("Here's your deck of cards");
      sleep(1);
      printf("\e[1;1H\e[2J");
      printVector(&player);
      printf("Your card to place down is %d.\n", currentCard);
      for(size_t i = 0; i < player.size; i++) {
        if((player.cards[i]).face == currentCard) {
          counter++;
        }
      }

      //if the player has the card
      if(counter > 0) {
        printf("You have %d of %d. Would you like to place them down?\n y or n?", counter, currentCard);
        scanf("%c", &str4);
        //if they don't want to place down all of their cards
        if(str4 == 'n') {
          printf("How many would you like to place down?\n");
          scanf("%d", &numOfCardsPlacedDown);
          //if they try to place down too many cards
          while(numOfCardsPlacedDown > 4) {
            printf("You're trying to place too many cards. There are only four %ds Try again.\n", currentCard);
            scanf("%d", &numOfCardsPlacedDown);
          }

          //if they try to place down too little cards
          while (numOfCardsPlacedDown <= 0) {
            printf("You're trying to place too few cards. You have to place down at least one card.\n");
            scanf("%d", &numOfCardsPlacedDown);
          }

          //if they want to place down more than the cards they have
          if(numOfCardsPlacedDown < counter) {
            printf("You can only take in one more card along with the %d cards you will be placing down. Which card would you like that to be? Type the card from the range 1-however many cards you have.\n", counter);
            scanf("%d", &additionalCard);
            for(size_t i = 0; i < player.size; i++) {
              if((player.cards[i]).face == currentCard) {
                insertCard(&pile, player.cards[i]);
                counter1++;
              }
            }
            insertCard(&pile, player.cards[additionalCard-1]);

            while(counter2 < player.size) {
              if((player.cards[counter2]).face == currentCard) {
                deleteCard(&player, player.cards[counter2].cardNum);
              } else {
                counter2++;
              }
            }
            deleteCard(&player, player.cards[additionalCard-1].cardNum);

          } else if(numOfCardsPlacedDown > counter){ //if they want to place down less cards than they have
            for(size_t i = 0; i < player.size; i++) {
              if(counter1 == numOfCardsPlacedDown) {
                break;
              }
              if((player.cards[i]).face == currentCard) {
                insertCard(&pile, player.cards[i]);
                counter1++;
              }
            }

            counter1 = 0;
            while(counter1 <= numOfCardsPlacedDown) {
              if((player.cards[counter3]).face == currentCard) {
                insertCard(&pile, player.cards[counter3]);
                counter1++;
              }
              counter3++;
            }
          } else { //if they said no but placed down the same number of cards as they have anyways
            //insert every card into the pile
            for(size_t i = 0; i < player.size; i++) {
              if((player.cards[i]).face == currentCard) {
                insertCard(&pile, player.cards[i]);
              }
            }

            //take every card away from the player's pile
            while(counter2 < player.size) {
              if((player.cards[counter2]).face == currentCard) {
                deleteCard(&player, player.cards[counter2].cardNum);
              } else {
                counter2++;
              }
            }
          }

        } else {
          //insert every card into the pile
          for(size_t i = 0; i < player.size; i++) {
            if((player.cards[i]).face == currentCard) {
              insertCard(&pile, player.cards[i]);
            }
          }

          //take every card away from the player's pile
          while(counter2 < player.size) {
            if((player.cards[counter2]).face == currentCard) {
              deleteCard(&player, player.cards[counter2].cardNum);
            } else {
              counter2++;
            }
          }

        }
      }
      //if the player does not have the card
      else {
        printf("You do not have any %ds. Choose which card you want to place down.\n", currentCard);
        scanf("%d", &alternative);
        insertCard(&pile, player.cards[alternative]);
        deleteCard(&player, (player.cards[alternative]).cardNum);
      }

      /*computers have a 20% chance of calling BS if they don't have the card themsevles
      *computers have a 50% chance of calling BS if they have one card themsevles
      *computers have a 70% chance of calling BS if they have two cards themselves
      *computers have a 90% chance of calling BS if they have three cards themselves*/
      if(findNumOfCards(&comp1, currentCard) > 0) {

      } else if(findNumOfCards(&comp1, currentCard) == 0) {

      

    }

    break;

    //find the next person to put down the card
    //check their pile of cards for that face
    //if they don't have those card, place down a random card (remove random card from hand)
    //if they do have the card(s), place all of them down (remove card(s) from hand)
    //each player afterwards has a random chance of calling BS

    //changes the current card in play
    if(currentCard == 14) {
      currentCard = 2;
    } else {
      currentCard++;
    }
    counter = 0;
    alternative = 0;
    numOfCardsPlacedDown = 0;
    counter1 = 0;
    counter2 = 0;
    counter3 = 0;
    additionalCard = 0;
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
  vector->cards = calloc(FACES, sizeof(Card));
}

void resetDeck(Card deck[], char *suits[], int faces[]) {
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
    printf("Card %lu: %d of %s\n", (i+1), (vector->cards[i]).face, (vector->cards[i]).suit);
  }
}

void printDeck(Card deck[]) {
  for(size_t i = 0; i < CARDS; i++) {
    printf("CardNum: %d Suit: %s Face: %d\n", deck[i].cardNum, deck[i].suit, deck[i].face);
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
    vector->cards = realloc(vector->cards, sizeof(Card) * vector->capacity);
  }
}

int findAceOfSpades(Vector *vector){
  for(size_t i = 0; i < vector->size; ++i) {
      //printf("findAceOfSpades: cardNum =   %d \n",(vector->cards[i]).cardNum);
    if((vector->cards[i]).cardNum == 51) {
        //printf("found card 51 in %d \n", vector->cards[i].face);
      return 1;
    }
  }
  return 0;
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

int findNumOfCards(Vector *vector, int current) {
  int counter;
  for(size_t i = 0; i < vector->size; ++i) {
    if((vector->cards[i]).face == current) {
      counter++;
    }
  }
  return counter;
}
