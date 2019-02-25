/***********************************************************************
*Author: Ryan Nelson
*
*Tests adventurerEffect function to see if it is working properly.
*
*Tests:
*This function is tested when the adventurer card is played with  
*several treasure cards in the draw pile, exactly two treasure cards
*in the draw pile, and no treasure cards in the draw pile.
i*
*The objective of the test is to see if a net of one card is added to the 
*player's hand after drawing looking for two treasure cards and discarding
*the adventurer card.
* Include in makefile:
*    gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
***********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "rngs.h"

struct testValues {
   int handTreasureCount;
   int deckTreasureCount;
   int discardTreasureCount;
   int handPos;
};


volatile sig_atomic_t HAS_SIGSEGV = 0;

//function taken from Piazza post @120  
void catch_alarm(int sig_num)
{
   //char* message = "caught SIGSEGV\n";
   //write(STDOUT_FILENO, message, 15); 
   HAS_SIGSEGV = 1;
}

//Outputs whether a test failed based on comaring test result to expected result
void testResult(int result, int expected, int* flag, char msg[])
{
   //if(result == expected)
   //{
      //printf("Test: %s, Result = %d, Expected = %d, Passed\n", msg, result, expected);
   //}   
   if(result != expected)
   {
      *flag = 1;
      printf("Test: %s, Result = %d, Expected = %d, Failed\n", msg, result, expected);
   }
}


//compares values of two structs for a player
int playerState(struct gameState* a, struct gameState* b, int player)
{
   int i, j, flag = 0;

   
   for(j = 0; j < MAX_HAND; j++)
   {
      if(a->hand[player][j] != b->hand[player][j])
      {
         flag = 1;
      }
   }

   if(a->handCount[player] != b->handCount[player])
   {
      flag = 1;
   }

   for(j = 0; j < MAX_DECK; j++)
   {
      if(a->deck[player][j] != b->deck[player][j])
      {
         flag = 1;
      }
   }

   if(a->deckCount[player] != b->deckCount[player])
   {
      flag = 1;
   }

   for(j = 0; j < MAX_DECK; j++)
   {
      if(a->discard[player][j] != b->discard[player][j])
      {
         flag = 1;
      }
   }

   if(a->discardCount[player] != b->discardCount[player])
   {
      flag = 1;
   }


   if(flag == 0)
   {
      return 0;
   }
   else
   {
      return 1;
   }
}


int randomNum(min, max)
{
   return (rand() % (max - min + 1)) + min;
}

void runTest(struct gameState* G, struct gameState* testG, struct testValues* tv)
{
   int currentPlayer = G->whoseTurn;
   int flag = 0;
   
   //set expected results

   //show games state before running test
   printf("Games State variables are set to the following:\n\n");
   printf("numPlayer = %d\n", G->numPlayers);
   printf("currentPlayer = %d\n", currentPlayer);
   printf("Player hand count = %d\n", G->handCount[currentPlayer]);
   printf("Village card hand pos = %d\n", tv->handPos);
   printf("Player deck count = %d\n", G->deckCount[currentPlayer]);
   printf("Player discard count = %d\n", G->discardCount[currentPlayer]);
   printf("Played cards count = %d\n\n", G->playedCardCount);

   //run test with random game state
   int card = great_hall;
   int choice1, choice2, choice3;
   choice1 = choice2 = choice3 = 0;
   int* bonus = 0; 
   
   //run function with copied gameState
   int returnResult = 1;

   returnResult = cardEffect(card, choice1, choice2, choice3, testG, tv->handPos, bonus);
   
    
   //see if return result is correct
   testResult(returnResult, 0, &flag, "Does returned result = 0"); 

   //see if handcount is correct
   testResult(testG->handCount[currentPlayer], G->handCount[currentPlayer], &flag, "Is hand count correct");

   //see if playedcardCount is correct
   testResult(testG->playedCardCount, G->playedCardCount + 1, &flag, "Is played Card Count correct");

   //see if numActions is correct
   testResult(testG->numActions, G->numActions, &flag, "Is numActions Count correct");

   //is played card in played card pile
   testResult(testG->playedCards[testG->playedCardCount - 1], great_hall, &flag, "Is great_hall card in played card pile");

   //see if supplyCount stayed the same
   int i, indicator = 0;
   for(i = 0; i < 26; i++)
   {
      if(testG->supplyCount[i] != G->supplyCount[i])
         indicator = 1;
   }
   testResult(indicator, 0, &flag, "Is supplyCount unchanged");

   //test if other player's hands changed at all
   for (i = 0; i < G->numPlayers; i++)
   {
      if(i != currentPlayer)
         testResult(playerState(G, testG, i), 0, &flag, "Did Player gameState change"); 
   }

   if(flag == 0)
   {
      printf("\nAll tests passed successfully!\n"); 
   }
   else
   {
      printf("\nThere were problems with one or more tests!\n"); 
   }

   printf("-----------------------------------------------------------------------------\n");

}

void setGame(struct gameState* G, int currentPlayer, struct testValues* tv)
{

   //set hand of current player randomly
   G->handCount[currentPlayer] = randomNum(0, MAX_HAND);
   int i;
   for(i = 0; i < G->handCount[currentPlayer]; i++)
   {
      G->hand[currentPlayer][i] = randomNum(0, 26);
   }

   //make sure great hall card is in player's hand at a random place
   int randMax;
   if(G->handCount[currentPlayer] < 1)
      randMax = 0;
   else
      randMax = G->handCount[currentPlayer] - 1;

   tv->handPos = randomNum(0, randMax);
   G->hand[currentPlayer][tv->handPos] = village;

   
   //set deck of current player randomly
   int tempNum = randomNum(0, 3);
   if(tempNum < 3)
      G->deckCount[currentPlayer] = randomNum(0, 5);
   else 
      G->deckCount[currentPlayer] = randomNum(0, MAX_DECK);

   for(i = 0; i < G->deckCount[currentPlayer]; i++)
   {
      G->deck[currentPlayer][i] = randomNum(0, 26);
   }

   //set discard of current player randomly
   G->discardCount[currentPlayer] = randomNum(0, MAX_DECK);
   for(i = 0; i < G->discardCount[currentPlayer]; i++)
   {
      G->discard[currentPlayer][i] = randomNum(0, 26);
   }

}

int main()
{
   //register handlers for SIGSEGV
   //struct sigaction SIGSEGV_action = {0}, ignore_action = {0};
   
   //SIGSEGV_action.sa_handler = catch_alarm;
   //sigfillset(&SIGSEGV_action.sa_mask);
   //SIGSEGV_action.sa_flags = 0;

   //ignore_action.sa_handler = SIG_IGN;

   //sigaction(SIGSEGV, &SIGSEGV_action, NULL);

   int seed = time(0);
   srand(seed);
   int* flag = 0;
   int i = 0;

   struct gameState G, testG;// declare a gameState struct
   struct testValues tv; //holds test values calculated when randomly setting game state

   for (i = 0; i < 1000; i++)
   {
      int numPlayer = randomNum(2, 4); //initialize number of players playing game
      int currentPlayer = randomNum(0, numPlayer - 1);; //initialize current player
      int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; //kingdom cards

      memset(&G, -4, sizeof(struct gameState)); // clear the game state
      int r = initializeGame(numPlayer, k, seed, &G); //initialize a new game

      G.whoseTurn = currentPlayer; //set current player in game state 
      setGame(&G, currentPlayer, &tv);
      memcpy(&testG, &G, sizeof(struct gameState));
      
      printf("-----------------------------------------------------------------------------\n");
      printf("Test %d\n", i+1);
      runTest(&G, &testG, &tv);
   }

   return 0;
}
/**********************
int adventurerEffect (int drawntreasure, int currentPlayer, int cardDrawn, int z, int* temphand, struct gameState *state)
{
   while(drawntreasure<2){
	if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	  shuffle(currentPlayer, state);
	}
	drawCard(currentPlayer, state);
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]+1];//top card of hand is most recently drawn card. // I changed -1 to +1
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  drawntreasure++;
	else{
	  temphand[z]=cardDrawn;
	  state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	  z++;
	}
   }
   while(z-1>=0){
	state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	z=z-1;
   }
   
   return 0;
}
**************************/
