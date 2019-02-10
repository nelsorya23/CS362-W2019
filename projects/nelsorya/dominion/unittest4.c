/***********************************************************************
*Author: Ryan Nelson
*
*Tests fullDeckCount function to see if it is working properly.
*
*Tests to run:
*Is proper count returned when a card exists in all three decks. 
*
*Is proper count returned when a card doesn't exist in any of the three decks.
*
*Is proper count returned when a card only exists in one of the three decks.
*
* Include in makefile:
*    gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
***********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Prints to screen whether a test failed based on comaring test result to expected result
void testResult(int result, int expected, int player, char msg[], int* flag)
{
   if(result == expected)
   {
      printf("Player %d %s Result = %d, Expected = %d, Passed\n", player, msg, result, expected);
   }   
   else
   {
      *flag = 1;
      printf("Player %d %s Result = %d, Expected = %d, Failed\n", player, msg, result, expected);
   }
}

int main()
{
   struct gameState G;// declare a gameState struct
   int numPlayer = 4; //number of players playing game
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; //kingdom cards
   int seed = 1000;
   int result;

   memset(&G, 23, sizeof(struct gameState)); // clear the game state
   int r = initializeGame(numPlayer, k, seed, &G); //initialize a new game

   //load all three decks for all 4 players
   int i, j, flag = 0;
   for (i = 0; i < MAX_PLAYERS; i++)
   {
      //set deck counts to 0
      G.deckCount[i] = 0;
      G.handCount[i] = 0;
      G.discardCount[i] = 0;
      G.playedCardCount = 0;


      //fill decks with card value of 2
      for (j = 0; j < MAX_DECK; j++) 
      {
         G.deck[i][j] = 2;
         G.deckCount[i]++;
         G.hand[i][j] = 2;
         G.handCount[i]++;
         G.discard[i][j] = 2;
         G.discardCount[i]++;
         G.playedCards[j] = 2;
         G.playedCardCount++;

         //replace specific index with different card values
         G.deck[i][MAX_DECK - 1] = 8;
         G.hand[i][0] = -1;
         G.discard[i][150] = 0;
      }

   }

   //run tests on fullDeckCount function for card counts
   for (i = 0; i < MAX_PLAYERS; i++) 
   {
      result = fullDeckCount(i, 8, &G);
      testResult(result, 1, i, "Card 8 count", &flag); 
      result = fullDeckCount(i, -1, &G);
      testResult(result, 0, i, "Card -1 count", &flag); 
      result = fullDeckCount(i, 0, &G);
      testResult(result, 1, i, "Card 0 count", &flag); 
      result = fullDeckCount(i, 24, &G);
      testResult(result, 0, i, "Card 24 count", &flag); 
      result = fullDeckCount(i, 2, &G);
      testResult(result, 1997, i, "Card 2", &flag); 
   }

   if(flag == 0)
   {
      printf("\nAll tests passed successfully!\n"); 
   }
   else
   {
      printf("\nThere were problems with one or more tests!\n"); 
   }
   return 0;
}

//fullDeckCount function being tested
/*************************************************************
int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}
***************************************************************/
