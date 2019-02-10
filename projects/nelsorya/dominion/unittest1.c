/***********************************************************************
*Author: Ryan Nelson
*
*Tests whoseTurn function to see if it is working properly.
*
*Tests to run:
*Does function return player number stored in whosTurn variable. 
*
*Will function return the player number stored in whosTurn variable even if the
*the value is invalid.
*
* Include in makefile:
*    gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
***********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Prints to screen whether a test failed based on comaring test result to expected result
void testResult(int result, int expected, int* flag, char msg[])
{
   if(result == expected)
   {
      printf("Test: %s, Result = %d, Expected = %d, Passed\n", msg, result, expected);
   }   
   else
   {
      *flag = 1;
      printf("Test: %s, Result = %d, Expected = %d, Failed\n", msg, result, expected);
   }
}


int main()
{
   struct gameState G;// declare a gameState struct
   int numPlayer = MAX_PLAYERS; //number of players playing game
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; //kingdom cards
   int seed = 1000;
   int result, flag = 0;

   memset(&G, 23, sizeof(struct gameState)); // clear the game state
   int r = initializeGame(numPlayer, k, seed, &G); //initialize a new game

   //test if whoseTurn returns a valid player number
   G.whoseTurn = 1;
   result = whoseTurn(&G);
   testResult(result, 1, &flag, "whoseTurn is set to 1");

   //test if whoseTurn returns an error value of some sort if player number is invalid (negative)
   G.whoseTurn = -1;
   result = whoseTurn(&G);
   testResult(result, -9999, &flag, "whoseTurn is set to -1");

   //test if whoseTurn returns an error value of some sort if player number is invalid (exceeds max number of players)
   G.whoseTurn = 4;
   result = whoseTurn(&G);
   testResult(result, -9999, &flag, "whoseTurn is set to 4");

   
   if(flag == 0)
   {
      printf("All tests passed successfully!\n"); 
   }
   else
   {
      printf("There were problems with one or more tests!\n"); 
   }
   return 0;
}

//whoseTurn function being tested
/*************************************************************
int whoseTurn(struct gameState *state) {
  return state->whoseTurn;
}
***************************************************************/
