#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CARDS 52
#define SUITS 4
#define FACES 13
#define CAPACITY 52

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
int computerFunction(Vector *vector, Vector *vector2, Vector *pile, Vector *player, int currentCard, int numComputer);
int playerFunction(Vector *vector, Vector *comp1, Vector *comp2, Vector *comp3, Vector *pile, int currentCard);

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

  puts("Type y when you are finished reading the rules.");
  scanf(" %c", &str1);
  while(str1 != 'y') {
    puts("Please type y when you are finished reading the rules");
    scanf(" %c", &str1);
  }
  printf("\e[1;1H\e[2J");

  //player1 assigned cards
  puts("YOUR CARDS");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&player, deck[i]);
    //printf("CardNum: %d Suit: %s Face: %s\n", (player.cards[i]).cardNum, (player.cards[i]).suit, (player.cards[i]).face);
  }
  printVector(&player);


  //comp1 assigned cards
  //puts("FOR COMP 1");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp1, deck[i+13]);
    //printf("CardNum: %d Suit: %s Face: %d\n", (comp1.cards[i]).cardNum, (comp1.cards[i]).suit, (comp1.cards[i]).face);
  }

  //comp2 assigned cards
  //puts("FOR COMP 2");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp2, deck[i+26]);
    //printf("CardNum: %d Suit: %s Face: %d\n", (comp2.cards[i]).cardNum, (comp2.cards[i]).suit, (comp2.cards[i]).face);
  }

  //comp3 assigned cards
  //puts("FOR COMP 3");
  for(size_t i = 0; i < 13; ++i) {
    insertCard(&comp3, deck[i+39]);
    //printf("CardNum: %d Suit: %s Face: %d\n", (comp3.cards[i]).cardNum, (comp3.cards[i]).suit, (comp3.cards[i]).face);
  }

  Vector tmp;
  //find ace of spades and add to pile
  if(findAceOfSpades(&player) == 1) {
    for(size_t i = 0; i <= player.size; ++i) {
      if((player.cards[i]).cardNum == 51) {
        insertCard(&pile, player.cards[i]);
        deleteCard(&player, (player.cards[i]).cardNum);
        puts("The Ace of Spades is in your hand, so you have to place it down.");
        break;
      }
    }
    tmp = comp1;
  } else if(findAceOfSpades(&comp1) == 1) {
    for(size_t i = 0; i <= comp1.size; ++i) {
      if((comp1.cards[i]).cardNum == 51) {
        insertCard(&pile, comp1.cards[i]);
        deleteCard(&comp1, (comp1.cards[i]).cardNum);
        puts("The Ace of Spades is in Computer 1.");
        break;
      }
    }
    tmp = comp2;
  } else if(findAceOfSpades(&comp2) == 1) {
    for(size_t i = 0; i <= comp2.size; ++i) {
      if((comp2.cards[i]).cardNum == 51) {
        insertCard(&pile, comp2.cards[i]);
        deleteCard(&comp2, (comp2.cards[i]).cardNum);
        puts("The Ace of Spades is in Computer 2.");
        break;
      }
    }
    tmp = comp3;
  } else {
    for(size_t i = 0; i <= comp3.size; ++i) {
      if((comp3.cards[i]).cardNum == 51) {
        insertCard(&pile, comp3.cards[i]);
        deleteCard(&comp3, (comp3.cards[i]).cardNum);
        puts("The Ace of Spades is in Computer 3.");
        break;
      }
    }
    tmp = player;
  }

  puts("Type y when you're ready to play");
  scanf(" %c", &str1);
  while(str1 != 'y') {
    puts("Please type y when you are finished reading the rules");
    scanf(" %c", &str1);
  }

  int currentCard = 2;   //current card player is looking for

  while((player.size != 0) && (comp1.size != 0) && (comp2.size != 0) && (comp3.size != 0)) {
    //find next player
    if((tmp.cards[0]).cardNum == (comp1.cards[0]).cardNum) {
      computerFunction(&comp1, &comp2, &pile, &player, currentCard, 1);
      tmp = comp2;
    } else if((tmp.cards[0]).cardNum == (comp2.cards[0]).cardNum) {
      computerFunction(&comp2, &comp3, &pile, &player, currentCard, 2);
      tmp = comp3;
    } else if((tmp.cards[0]).cardNum == (comp3.cards[0]).cardNum) {
      computerFunction(&comp3, &comp1, &pile, &player, currentCard, 3);
      tmp = player;
    } else {
      playerFunction(&player, &comp1, &comp2, &comp3, &pile, currentCard);
      tmp = comp1;
    }


    //changes the current card in play
    if(currentCard == 14) {
      currentCard = 2;
    } else {
      currentCard++;
    }

    //whoever wins the game
    if(comp1.size == 0) {
      puts("Sorry! Comp1 won the game! Maybe next time!");
      return 0;
    } else if(comp2.size == 0) {
      puts("Sorry! Comp2 won the game! Maybe next time!");
      return 0;
    } else if(comp3.size == 0) {
      puts("Sorry! Comp3 won the game! Maybe next time!");
      return 0;
    } else if (player.size == 0){
      puts("Congrats on winning the game!");
      return 0;
    }

  }

  return 0;

}

void clear(Vector *vector) {
    free(vector->cards);
}

void init(Vector *vector) {
  vector->size = 0;
  vector->capacity = CAPACITY;
  vector->cards = calloc(CAPACITY, sizeof(Card));
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

int computerFunction(Vector *vector, Vector *vector2, Vector *pile, Vector *player, int currentCard, int numComputer) {
  //initializing variables
  int counter = 0; //how many of that type of card the player has
  char str2; //scanf
  int alternative = 0; //bs card placed if player doesn't have the card asked for
  int numOfCardsPlacedDown = 0; //if player wants to place down less/more cards than they have
  int additionalCard = 0; //if player wants to place down more cards than they have
  int counter1 = 0;
  int counter2 = 0;
  int counter3 = 0; //counter for placing cards in pile
  int randPercent = 0; //random percent for calling BS
  int testBs = 0; //tests whether to break loop or not
  int callingBS = 0; //callingBS = 2 not callingBS = 1

  //introduction to make sure player is ready to play
  printf("\e[1;1H\e[2J");
  printf("It is now Computer %d's turn.\n", numComputer);
  printf("The card that computer %d must place down is %d.\n", numComputer, currentCard);
  puts("Type y if you have received this notification.");
  scanf(" %c", &str2);
  while(str2 != 'y'){
       puts("Please type y to confirm you have received this message.");
       scanf(" %c", &str2);
  }

  //counter for how many cards
  for(size_t i = 0; i < vector->size; i++) {
    if((vector->cards[i]).face == currentCard)
      counter++;
  }

  //if they have the card(s), play all of them & delete them from pile
  if(counter > 0){
    //insert cards computer has into pile
    for(size_t i = 0; i < vector->size; i++) {
        if((vector->cards[i]).face == currentCard) {
          insertCard(pile, vector->cards[i]);
        }
    }

    //delete cards from computer
    for(int i = vector->size-1; i >= 0; i--) {
        if((vector->cards[i]).face == currentCard) {
          deleteCard(vector, (vector->cards[i]).cardNum);
        }
    }

    //asking user if they want to call BS
    printf("\e[1;1H\e[2J");
    printf("Computer %d has placed %d of %d. Would you like to call BS?\nType y or n.\n", numComputer, counter, currentCard);
    scanf(" %c", &str2);
    if(str2 == 'y') {
      printf("Oops! Computer %d wasn't lying! Type y to understand you are getting all the cards added to your pile.\n", numComputer);
      puts("Pile: 0");
      scanf(" %c", &str2);
      while(str2 != 'y') {
        puts("Try again & type y.");
        scanf(" %c", &str2);
      }
      printf("\e[1;1H\e[2J");

      for(size_t i = 0; i < pile->size; i++) {
          insertCard(player, pile->cards[i]);
          printf("Cardnum of card added: %d\n", pile->cards[i].cardNum);
      }
      for(int i = pile->size-1; i >= 0; i--) {
        deleteCard(pile, pile->cards[i].cardNum);
      }
      puts("PILE");
      printVector(pile);

      puts("YOUR CARDS");
      printVector(player);
      puts("Type y when you're ready to continue.");
      scanf(" %c", &str2);
      while(str2 != 'y') {
        puts("Try again & type y.");
        scanf(" %c", &str2);
      }
    }

    /*computers have a 20% chance of calling BS if they don't have the card themsevles
    *computers have a 50% chance of calling BS if they have one card themsevles
    *computers have a 70% chance of calling BS if they have two cards themselves
    *computers have a 90% chance of calling BS if they have three cards themselves
    *computers have a 100% chance of calling BS if they have all of the cards themselves*/

    //compute chance of other computer calling BS
    else {
      randPercent = rand() % 100 + 1;
      if(findNumOfCards(vector2, currentCard) == 0) {
        if(randPercent <= 20) {
          callingBS = 2;
        } else {
          callingBS = 1;
        }
      } else if(findNumOfCards(vector2, currentCard) == 1) {
        if(randPercent <= 50) {
          callingBS = 2;
        } else {
          callingBS = 1;
        }
      } else if(findNumOfCards(vector2, currentCard) == 2) {
        if(randPercent <= 70) {
          callingBS = 2;
        } else {
          callingBS = 1;
        }
      } else if(findNumOfCards(vector2, currentCard) == 3) {
        if(randPercent <= 90) {
          callingBS = 2;
        } else {
          callingBS = 1;
        }
      } else {
        callingBS = 2;
      }

      if(callingBS == 2) {
        printf("\e[1;1H\e[2J");
        printf("A computer wants to call BS on computer %d. Please type y to confirm that you got this message.\n", numComputer);
        scanf(" %c", &str2);
        while(str2 != 'y') {
          puts("Please try again & type y.");
          scanf(" %c", &str2);
        }
        sleep(1);

        printf("\e[1;1H\e[2J");
        puts("A computer was wrong when it called BS! All of the cards from the pile will be added to the computer's hand now!");
        puts("Pile: 0 cards");
        puts("PILE");
        printVector(pile);
        //insert cards into comp2 & delete from pile
        for(size_t i = 0; i < pile->size; i++){
            insertCard(vector2, pile->cards[i]);
        }
        for(int i = pile->size-1; i >= 0; i--) {
            deleteCard(pile, (pile->cards[i]).cardNum);
        }
        puts("PILE");
        printVector(pile);

        puts("Type y when you have received this message.");
        scanf(" %c", &str2);
        while(str2 != 'y') {
          puts("Please try again & type y.");
          scanf(" %c", &str2);
        }
      } else {
        printf("\e[1;1H\e[2J");
        puts("Nobody wanted to call BS, so we are moving on to the next player.");
      }
    }
  } else { //picks random cards because computer doesn't have the card requested
    insertCard(pile, vector->cards[0]);
    deleteCard(vector, (vector->cards[0].cardNum));
    printf("\e[1;1H\e[2J");
    printf("Computer %d has placed 1 of %d. Would you like to call BS?\n", numComputer, currentCard);
    scanf(" %c", &str2);
    if(str2 == 'y') {
      printf("\e[1;1H\e[2J");
      printf("You got it! Computer %d was lying!! All of the cards will be added to Computer %d's pile!\n", numComputer, numComputer);
      for(size_t i = 0; i < pile->size; i++) {
        insertCard(vector, pile->cards[i]);
      }

      //delete cards from pile to restart pile
     for(int i = pile->size-1; i >= 0; i--) {
       deleteCard(pile, (pile->cards[i]).cardNum);
     }

     puts("Type y to confirm you have gotten the message.");
     scanf(" %c", &str2);
     while(str2 != 'y') {
       puts("Please try again.");
       scanf(" %c", &str2);
     }

   } else {
     /*computers have a 20% chance of calling BS if they don't have the card themsevles
     *computers have a 50% chance of calling BS if they have one card themsevles
     *computers have a 70% chance of calling BS if they have two cards themselves
     *computers have a 90% chance of calling BS if they have three cards themselves
     *computers have a 100% chance of calling BS if they have all of the cards themselves*/

     //compute chance of other computer calling BS
     randPercent = rand() % 100 + 1;
     if(findNumOfCards(vector2, currentCard) == 0) {
       if(randPercent <= 20) {
         callingBS = 2;
       } else {
         callingBS = 1;
       }
     } else if(findNumOfCards(vector2, currentCard) == 1) {
       if(randPercent <= 50) {
         callingBS = 2;
       } else {
         callingBS = 1;
       }
     } else if(findNumOfCards(vector2, currentCard) == 2) {
       if(randPercent <= 70) {
         callingBS = 2;
       } else {
         callingBS = 1;
       }
     } else if(findNumOfCards(vector2, currentCard) == 3) {
       if(randPercent <= 90) {
         callingBS = 2;
       } else {
         callingBS = 1;
       }
     } else {
       callingBS = 2;
     }

     if(callingBS == 2) {
       printf("\e[1;1H\e[2J");
       printf("A computer wants to call BS on computer %d. Please type y to confirm that you got this message.\n", numComputer);
       scanf(" %c", &str2);
       while(str2 != 'y') {
         puts("Please try again & type y.");
         scanf(" %c", &str2);
       }

       printf("\e[1;1H\e[2J");
       printf("A computer was right when it called BS! All of the cards from the pile will be added to computer %d now!", numComputer);
       puts("Pile: 0 cards");
       sleep(2);
       //insert cards into comp1 & delete from pile
       for(int i = 0; i < pile->size; i++){
           insertCard(vector, pile->cards[i]);
       }
       for(int i = pile->size-1; i >= 0; i--) {
           deleteCard(pile, (pile->cards[i]).cardNum);
       }

     } else {
       printf("\e[1;1H\e[2J");
       puts("Nobody wanted to call BS, so we are moving on to the next player");
     }
   }
  }
  return 0;
}

int playerFunction(Vector *player, Vector *comp1, Vector *comp2, Vector *comp3, Vector *pile, int currentCard) {
  //initializing variables
  int counter = 0; //how many of that type of card the player has
  char str2; //scanf
  int alternative = 0; //bs card placed if player doesn't have the card asked for
  int numOfCardsPlacedDown = 0; //if player wants to place down less/more cards than they have
  int additionalCard = 0; //if player wants to place down more cards than they have
  int counter1 = 0;
  int counter2 = 0;
  int counter3 = 0; //counter for placing cards in pile
  int randPercent = 0; //random percent for calling BS
  int testBs = 0; //tests whether to break loop or not
  int callingBS = 0; //callingBS = 2 not callingBS = 1
  Vector *tmp2 = comp1;

  //check player is ready to play
  printf("\e[1;1H\e[2J");
  puts("It's your turn. Are you ready to play?");
  printf("y or n?\n");
  scanf(" %c", &str2);
  while(str2 == 'n') {
    puts("Do you want to stop the game?");
    printf("y or n?\n");
    scanf(" %c", &str2);
    if(str2 == 'y') {
      puts("Play again sometime!");
      return 0;
    }
    puts("Let's try again. It's your turn. Are you ready to play?");
    printf("y or n?\n");
    scanf(" %c", &str2);
  }

  //find the current card
  puts("Here's your deck of cards");
  sleep(2);
  printf("\e[1;1H\e[2J");
  printVector(player);
  printf("Your card to place down is %d.\n", currentCard);
  for(size_t i = 0; i < player->size; i++) {
    if((player->cards[i]).face == currentCard) {
      counter++;
    }
  }

  //if the player has the card
  if(counter > 0) {
    printf("You have %d of %d. Would you like to place them down?\n y or n?\n", counter, currentCard);
    scanf(" %c", &str2);
    //if they don't want to place down all of their cards
    if(str2 == 'n') {
      printf("How many would you like to place down?\n");
      scanf(" %d", &numOfCardsPlacedDown);
      //if they try to place down too many cards
      //if they try to place down too little cards
      //if they are trying to place down more cards than they have
      while(numOfCardsPlacedDown > 4 || numOfCardsPlacedDown <= 0 || player->size < numOfCardsPlacedDown) {
        printf("You can't place down that amount of cards. Try again.\n");
        scanf(" %d", &numOfCardsPlacedDown);
      }

      //if they want to place down one more than the cards they have
      if(numOfCardsPlacedDown > counter) {
        printf("You can only take in one more card along with the %d cards you will be placing down. Which card would you like that to be? Type the card from the range 1-however many cards you have.\n", counter);
        scanf(" %d", &additionalCard);
        for(size_t i = 0; i < player->size; i++) {
          if((player->cards[i]).face == currentCard) {
            insertCard(pile, player->cards[i]);
            counter1++;
          }
        }
        insertCard(pile, player->cards[additionalCard-1]);

        for(int i = player->size-1; i >= 0; i--) {
          if((player->cards[counter2]).face == currentCard) {
            deleteCard(player, player->cards[counter2].cardNum);
          }
        }
        deleteCard(player, player->cards[additionalCard-1].cardNum);

      } else if(numOfCardsPlacedDown < counter){ //if they want to place down less cards than they have
        //finds the number of whatever cards and places them into pile
        for(size_t i = 0; i < player->size; i++) {
          if(counter1 == numOfCardsPlacedDown) {
            break;
          }
          if((player->cards[i]).face == currentCard) {
            insertCard(pile, player->cards[i]);
            counter1++;
          }
        }

        //delete the cards from the person's pile
        counter1 = 0;
        for(int i = player->size-1; i >= 0; i--) {
          if(counter1 == numOfCardsPlacedDown) {
            break;
          }
          if((player->cards[i]).face == currentCard) {
            deleteCard(player, (player->cards[i]).cardNum);
            counter1++;
          }
        }

      } else { //if they said no but placed down the same number of cards as they have anyways
        //insert every card into the pile
        for(size_t i = 0; i < player->size; i++) {
          if((player->cards[i]).face == currentCard) {
            insertCard(pile, player->cards[i]);
          }
        }

        //take every card away from the player's pile
        for(int i = player->size-1; i >= 0; i--) {
          if((player->cards[i]).face == currentCard) {
            deleteCard(player, (player->cards[i]).cardNum);
          }
        }
      }

    }
    else { //if the person does want to place down every card in pile
      //insert every card into the pile
      for(size_t i = 0; i < player->size; i++) {
        if((player->cards[i]).face == currentCard) {
          insertCard(pile, player->cards[i]);
        }
      }

      //take every card away from the player's pile
      for(int i = player->size-1; i >= 0; i--) {
        if((player->cards[i]).face == currentCard) {
          deleteCard(player, (player->cards[i]).cardNum);
        }
      }

    }
  }

  //if the player does not have the card
  else {
    printf("You do not have any %ds. Choose which card you want to place down.\n", currentCard);
    scanf(" %d", &alternative);
    while(alternative >= player->size) {
      puts("You cannot place that card down. Please try again.");
      scanf(" %d", &alternative);
    }
    insertCard(pile, player->cards[alternative-1]);
    deleteCard(player, (player->cards[alternative-1]).cardNum);
  }

  //for calling BS
  /*computers have a 20% chance of calling BS if they don't have the card themsevles
  *computers have a 50% chance of calling BS if they have one card themsevles
  *computers have a 70% chance of calling BS if they have two cards themselves
  *computers have a 90% chance of calling BS if they have three cards themselves
  *computers have a 100% chance of calling BS if they have all of the cards themselves*/

  while((tmp2->cards[0]).cardNum != (player->cards[0]).cardNum) {
    randPercent = rand() % 100 + 1; //establishes random percentage

    //determining whether or not to call BS
    if(findNumOfCards(tmp2, currentCard) == 0) {
      if(randPercent <= 20) {
        callingBS = 2;
      } else {
        callingBS = 1;
      }
    } else if(findNumOfCards(tmp2, currentCard) == 1) {
      if(randPercent <= 50) {
        callingBS = 2;
      } else {
        callingBS = 1;
      }
    } else if(findNumOfCards(tmp2, currentCard) == 2) {
      if(randPercent <= 70) {
        callingBS = 2;
      } else {
        callingBS = 1;
      }
    } else if(findNumOfCards(tmp2, currentCard) == 3) {
      if(randPercent <= 90) {
        callingBS = 2;
      } else {
        callingBS = 1;
      }
    } else {
      callingBS = 2;
    }

    //if somebody does call bs, notify player
    if(callingBS == 2) {
      printf("\e[1;1H\e[2J");
      puts("One of the computer users has called BS on you. Type y when you have received this message.");
      scanf(" %c", &str2);
      while(str2 != 'y') {
        puts("Please type y to confirm you have received this message");
        scanf(" %c", &str2);
      }

      //if player played multiple cards
      if(numOfCardsPlacedDown > 0) {
        for(int i = 0; i < numOfCardsPlacedDown; i++) {
          if((pile->cards[pile->size-1-i]).face != currentCard) {
            puts("The computer's attempt to call BS was correct! All of the cards in the pile will be added to your hand.");
            puts("Please type y to confirm you have received the message.");
            scanf(" %c", &str2);
            while(str2 != 'y') {
              puts("Please type y to confirm you have received this message");
              scanf(" %c", &str2);
            }

            //insert cards into players hand
            for(int i = 0; i < pile->size; i++) {
              insertCard(player, pile->cards[i]);
            }

            //delete cards from pile to restart game
            for(int i = pile->size-1; i >= 0; i--) {
              deleteCard(pile, (pile->cards[i]).cardNum);
            }

            printf("\e[1;1H\e[2J");
            puts("YOUR CARDS");
            printVector(player);
            puts("Here is your new list. Ready to continue? Please type y to continue.");
            scanf(" %c", &str2);
            while(str2 != 'y') {
              puts("Please type y to confirm you have received this message");
              scanf(" %c", &str2);
            }
            testBs = 1;
            break;
          }
        }
        if(testBs == 1) {
          break;
        }

        //if loop isn't broken, player is correct
        puts("You were right & put down the correct cards! The computer was wrong when it called BS. The computer will now take all of the cards.");
        puts("Pile: 0 Cards");
        if((tmp2->cards[0]).cardNum == (comp1->cards[0]).cardNum) {
          //insert cards into comp1 hand
          for(int i = 0; i < pile->size; i++) {
            insertCard(comp1, pile->cards[i]);
          }

          //delete cards from pile to restart game
          for(int i = pile->size-1; i >= 0; i--) {
            deleteCard(pile, (pile->cards[i]).cardNum);
          }
        } else if((tmp2->cards[0]).cardNum != (comp2->cards[0]).cardNum) {
          //insert cards into comp2 hand
          for(int i = 0; i < pile->size; i++) {
            insertCard(comp2, pile->cards[i]);
          }

          //delete cards from pile to restart game
          for(int i = pile->size-1; i >= 0; i--) {
            deleteCard(pile, (pile->cards[i]).cardNum);
          }
        } else if((tmp2->cards[0]).cardNum != (comp3->cards[0]).cardNum) {
          //insert cards into comp3 hand
          for(size_t i = 0; i < pile->size; i++) {
            insertCard(comp3, pile->cards[i]);
          }

          //delete cards from pile to restart game
          for(int i = pile->size-1; i >= 0; i--) {
            deleteCard(pile, (pile->cards[i]).cardNum);
          }
        }
        puts("Type y to confirm that you have received this message");
        scanf(" %c", &str2);
        while(str2 != 'y') {
          puts("Please type y to confirm you have received this message");
          scanf(" %c", &str2);
        }
        printf("\e[1;1H\e[2J");

      } else {
        if((pile->cards[pile->size-1]).face != currentCard) {
            puts("The computer's attempt to call BS was correct! All of the cards in the pile will be added to your hand.");
            puts("Please type y to confirm you have received the message.");
            scanf(" %c", &str2);
            while(str2 != 'y') {
              puts("Please type y to confirm you have received this message");
              scanf(" %c", &str2);
            }

            //insert cards into players hand
            for(int i = 0; i < pile->size; i++) {
              insertCard(player, pile->cards[i]);
            }

            //delete cards from pile to restart game
            for(int i = pile->size-1; i >= 0; i--) {
              deleteCard(pile, (pile->cards[i]).cardNum);
            }

            printf("\e[1;1H\e[2J");
            puts("YOUR CARDS");
            printVector(player);
            puts("Here is your new list. Ready to continue? Please type y to continue.");
            scanf(" %c", &str2);
            while(str2 != 'y') {
              puts("Please type y to confirm you have received this message");
              scanf(" %c", &str2);
            }
            break;
        } else {
            //if player had correct cards and was not lying
            //printf("\e[1;1H\e[2J");
            puts("You were right & put down the correct cards! The computer was wrong when it called BS. The computer will now take all of the cards.");
            puts("Pile: 0 Cards");
            puts("Type y to confirm that you have received this message");
            scanf(" %c", &str2);
            while(str2 != 'y') {
              puts("Please type y to confirm you have received this message");
              scanf(" %c", &str2);
            }

            if((tmp2->cards[0]).cardNum == (comp1->cards[0]).cardNum) {
              //insert cards into comp1 hand
              for(int i = 0; i < pile->size; i++) {
                insertCard(comp1, pile->cards[i]);
              }

              //delete cards from pile to restart game
              for(int i = pile->size-1; i >= 0; i--) {
                deleteCard(pile, (pile->cards[i]).cardNum);
              }
            } else if((tmp2->cards[0]).cardNum != (comp2->cards[0]).cardNum) {
              //insert cards into comp2 hand
              for(int i = 0; i < pile->size; i++) {
                insertCard(comp2, pile->cards[i]);
              }

              //delete cards from pile to restart game
              for(int i = pile->size-1; i >= 0; i--) {
                deleteCard(pile, (pile->cards[i]).cardNum);
              }
            } else if((tmp2->cards[0]).cardNum != (comp3->cards[0]).cardNum) {
              //insert cards into comp3 hand
              for(size_t i = 0; i < pile->size; i++) {
                insertCard(comp3, pile->cards[i]);
              }

              //delete cards from pile to restart game
              for(int i = pile->size-1; i >= 0; i--) {
                deleteCard(pile, (pile->cards[i]).cardNum);
              }
            }

            printf("\e[1;1H\e[2J");

            puts("YOUR CARDS");
            printVector(player);

            puts("Please confirm you are ready to move on by typing y.");
            scanf(" %c", &str2);
            while(str2 != 'y') {
              puts("Please type y to confirm you have received this message");
              scanf(" %c", &str2);
            }
          }
        }

        break;
      } else {
        //changes computer to determine who is calling BS next
        if((tmp2->cards[0]).cardNum == (comp1->cards[0]).cardNum) {
          tmp2 = comp2;
        } else if((tmp2->cards[0]).cardNum != (comp2->cards[0]).cardNum) {
          tmp2 = comp3;
        } else if((tmp2->cards[0]).cardNum != (comp3->cards[0]).cardNum) {
          tmp2 = player;
          puts("Nobody called BS on you. We are moving on.");
          break;
        }
      }
    }

  return 0;
}
