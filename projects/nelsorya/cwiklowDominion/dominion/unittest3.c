/***********************************************************************
*Author: Ryan Nelson
*
*Tests isGameOver function to see if it is working properly.
*
*Tests:
*Province card is tested when it is zero and when it is not zero. isGameOver
*should return 1 when the province card supply is 0, otherwise returns 0.
*
*isGameOver should also return a 1 if at least three supply piles are at 0.
*Otherwise it returns 0, indicating game is not over. Four tests are run 
*where no card piles are 0, 2 card piles are 0, 3 card piles are 0, and  
*4 card piles are 0. This tests domains of where less than 3 piles are 0,
*exactly 3 piles are 0, and greater than 3 piles are 0.
*
* Include in makefile:
*    gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
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

//Tests result of isGameOver when setting province pile count to the set value
void testProvince(int expected, int set, struct gameState* G, int* flag) 
{
   char msg[35];
   sprintf(msg, "province card count is set to %d", set);
   
   int temp = G->supplyCount[province];
   G->supplyCount[province] = set;

   int result = isGameOver(G);
   testResult(result, expected, flag, msg);
   
   G->supplyCount[province] = temp;
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
   int numPlayer = 4; //number of players playing game
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; //kingdom cards
   int seed = 1000;
   int result, r, flag = 0, currentPlayer = 0;
   const int max = treasure_map; 

   memset(&G, 23, sizeof(struct gameState)); // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); //initialize a new game

   memcpy(&copyG, &G, sizeof(struct gameState));

   //test province count when it is 0
   testProvince(1, 0, &G, &flag);
   
   //test province count when it is 8
   testProvince(0, 8, &G, &flag);

   //test province count when it is -2
   testProvince(1, -2, &G, &flag);

   //test result when no card piles equal 0
   result = isGameOver(&G);
   testResult(result, 0, &flag, "No card piles = 0");

   //test result when 2 card piles equal 0
   G.supplyCount[0] = 0;
   G.supplyCount[7] = 0;
   result = isGameOver(&G);
   testResult(result, 0, &flag, "2 card piles equal 0");

   //test result when 3 card piles equal 0, use the max card which is 26
   G.supplyCount[max] = 0;
   result = isGameOver(&G);
   testResult(result, 1, &flag, "3 card piles = 0");

   //test result when 4 card piles equal 0
   G.supplyCount[24] = 0;
   result = isGameOver(&G);
   testResult(result, 1, &flag, "4 card piles = 0");

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

//isGameOver function being tested
/**************************************************
int isGameOver(struct gameState *state) {
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
}
*************************************************************/

