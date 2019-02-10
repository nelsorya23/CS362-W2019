/***********************************************************************
*Author: Ryan Nelson
*
*Tests handCard function to see if it is working properly.
*
*Tests to run:
*Is a valid card value returned from the hand array for the current player.
*
*will the function return a card value from an invalid hand position.
*
*Will the function return an invalid card value from a valid hand position.
*
* Include in makefile:
*    gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
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

int main()
{
   struct gameState G, copyG;// declare a gameState struct
   int numPlayer = MAX_PLAYERS; //number of players playing game
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; //kingdom cards
   int seed = 1000;
   int result, flag = 0, currentPlayer = 0;

   memset(&G, 23, sizeof(struct gameState)); // clear the game state
   int r = initializeGame(numPlayer, k, seed, &G); //initialize a new game

   memcpy(&copyG, &G, sizeof(struct gameState));

   //set current player to player 0
   G.whoseTurn = 0;

   //set player's hand position 0 to the province card (3) and test if it's returned
   G.hand[currentPlayer][0] = province;
   result = handCard(0, &G);
   testResult(result, province, &flag, "hand position 0 is set to province (3)");

   //set player's hand position 4 to the smithy card (13) and test if it's returned
   G.hand[currentPlayer][4] = smithy;
   result = handCard(4, &G);
   testResult(result, smithy, &flag, "hand position 4 is set to smithy(13)");

   //set player's hand position of an invalid -1 to the smithy card (13) and test if an error is returned
   G.hand[currentPlayer][-1] = smithy;
   result = handCard(-1, &G);
   testResult(result, -9999, &flag, "Invalid hand position -1 is set to smithy(13)");

   //set player's hand position of an invalid 5 to the smithy card (13) and test if an error is returned
   G.hand[currentPlayer][5] = smithy;
   result = handCard(5, &G);
   testResult(result, -9999, &flag, "Invalid hand position 5 is set to smithy(13)");

   //set player's hand position of 3 to the an invalid card value of 250 and see if error is returned
   G.hand[currentPlayer][3] = 250;
   result = handCard(3, &G);
   testResult(result, -9999, &flag, "hand position 3 is set to an invalid card value of 250");

   //check if gameState variables changed for any of the other players
   testResult(playerState(&G, &copyG, currentPlayer + 1), 0, &flag, "Did Player 2 gameState change"); 

   //check if gameState variables changed for any of the other players
   testResult(playerState(&G, &copyG, currentPlayer + 2), 0, &flag, "Did Player 3 gameState change"); 

   //check if gameState variables changed for any of the other players
   testResult(playerState(&G, &copyG, currentPlayer + 3), 0, &flag, "Did Player 4 gameState change"); 

   
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

//handCard function being tested
/*************************************************************
int handCard(int handPos, struct gameState *state) {
  int currentPlayer = whoseTurn(state);
  return state->hand[currentPlayer][handPos];
}

***************************************************************/
