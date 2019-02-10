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

void cmpStructs(struct gameState* a, struct gameState* b)
{
   int i, j, flag = 0;

   if (a->numPlayers != b->numPlayers)
   {
      flag = 1;
      printf("numPlayers, struct a = %d, struct b = %d\n", a->numPlayers, b->numPlayers);
   }
   
   for(i = 0; i < treasure_map + 1; i++) 
   {
      if(a->supplyCount[i] != b->supplyCount[i])
      {
         printf("supplyCount[%d], struct a = %d, struct b = %d\n", i, a->supplyCount[i], b->supplyCount[i]);
      }
   }

   for(i = 0; i < treasure_map + 1; i++) 
   {
      if(a->embargoTokens[i] != b->embargoTokens[i])
      {
         printf("embargoTokens[%d], struct a = %d, struct b = %d\n", i, a->embargoTokens[i], b->embargoTokens[i]);
      }
   }

   if (a->outpostPlayed != b->outpostPlayed)
   {
      flag = 1;
      printf("outpostPlayed, struct a = %d, struct b = %d\n", a->outpostPlayed, b->outpostPlayed);
   }
   if (a->outpostTurn != b->outpostTurn)
   {
      flag = 1;
      printf("outpostTurn, struct a = %d, struct b = %d\n", a->outpostTurn, b->outpostTurn);
   }
   if (a->whoseTurn != b->whoseTurn)
   {
      flag = 1;
      printf("whoseTurn, struct a = %d, struct b = %d\n", a->whoseTurn, b->whoseTurn);
   }
   if (a->phase != b->phase)
   {
      flag = 1;
      printf("phase, struct a = %d, struct b = %d\n", a->phase, b->phase);
   }
   if (a->numActions != b->numActions)
   {
      flag = 1;
      printf("numActions, struct a = %d, struct b = %d\n", a->numActions, b->numActions);
   }
   if (a->coins != b->coins)
   {
      flag = 1;
      printf("coins, struct a = %d, struct b = %d\n", a->coins, b->coins);
   }
   if (a->numBuys != b->numBuys)
   {
      flag = 1;
      printf("numBuys, struct a = %d, struct b = %d\n", a->numBuys, b->numBuys);
   }

   for(i = 0; i < MAX_PLAYERS; i++) 
   {
      for(j = 0; j < MAX_HAND; j++)
      {
         if(a->hand[i][j] != b->hand[i][j])
         {
            printf("hand[%d][%d], struct a = %d, struct b = %d\n", i, j, a->hand[i][j], b->hand[i][j]);
         }
      }
   }

   for(i = 0; i < MAX_PLAYERS; i++) 
   {
      if(a->handCount[i] != b->handCount[i])
      {
         printf("handCount[%d], struct a = %d, struct b = %d\n", i, a->handCount[i], b->handCount[i]);
      }
   }

   for(i = 0; i < MAX_PLAYERS; i++) 
   {
      for(j = 0; j < MAX_DECK; j++)
      {
         if(a->deck[i][j] != b->deck[i][j])
         {
            printf("deck[%d][%d], struct a = %d, struct b = %d\n", i, j, a->deck[i][j], b->deck[i][j]);
         }
      }
   }

   for(i = 0; i < MAX_PLAYERS; i++) 
   {
      if(a->deckCount[i] != b->deckCount[i])
      {
         printf("deckCount[%d], struct a = %d, struct b = %d\n", i, a->deckCount[i], b->deckCount[i]);
      }
   }

   for(i = 0; i < MAX_PLAYERS; i++) 
   {
      for(j = 0; j < MAX_DECK; j++)
      {
         if(a->discard[i][j] != b->discard[i][j])
         {
            printf("discard[%d][%d], struct a = %d, struct b = %d\n", i, j, a->discard[i][j], b->discard[i][j]);
         }
      }
   }

   for(i = 0; i < MAX_PLAYERS; i++) 
   {
      if(a->discardCount[i] != b->discardCount[i])
      {
         printf("discardCount[%d], struct a = %d, struct b = %d\n", i, a->discardCount[i], b->discardCount[i]);
      }
   }

   for(i = 0; i < MAX_DECK; i++) 
   {
      if(a->playedCards[i] != b->playedCards[i])
      {
         printf("playedCards[%d], struct a = %d, struct b = %d\n", i, a->playedCards[i], b->playedCards[i]);
      }
   }

   if (a->playedCardCount != b->playedCardCount)
   {
      flag = 1;
      printf("playedCardCount, struct a = %d, struct b = %d\n", a->playedCardCount, b->playedCardCount);
   }


   if(flag == 0)
   {
      printf("No Difference between both structs\n");
   }
}

void runTests(struct gameState* G, struct gameState* testG, int* flag, int handPos, int currentPlayer)
{
   //run function with copied gameState
   int returnResult = smithyEffect(handPos, currentPlayer, testG);

   //test return value is 0 to ensure function ran without errors
   int expectedReturnResult = 0;
   testResult(returnResult, expectedReturnResult, flag, "Does returned result = 0");
   
   //test handCount variable to see if it increased by 2
   int expectedHandCount = G->handCount[currentPlayer] + 2;
   int actualHandCount = testG->handCount[currentPlayer];
   testResult(actualHandCount, expectedHandCount, flag, "Is new handCount two more than original handCount");

   //test hand array value to see if card in handPos is no longer smithy and equals a copper
   testResult(testG->hand[currentPlayer][handPos], copper, flag, "Does new card in handPos of hand array equal copper");

   //test hand array value to see if card in position handCount - 2 is a copper
   int newCard = 5;
   testResult(testG->hand[currentPlayer][newCard], copper, flag, "Does new card in position 5 of hand array equal copper");

   //test hand array value to see if card in position handCount - 1 is a copper
   newCard = 6;
   testResult(testG->hand[currentPlayer][newCard], copper, flag, "Does new card in position 6 of hand array equal copper");

   //test hand array value to see if card in position handCount is a -1 which means its gone from hand
   newCard = 7;
   testResult(testG->hand[currentPlayer][newCard], -1, flag, "Does new card in position 7 of hand array equal -1");

   //test deckCount variable to see if it decreased by 3, which means only the first two cards in the deck are still active
   int expectedDeckCount = G->deckCount[currentPlayer] - 3;
   int actualDeckCount = testG->deckCount[currentPlayer];
   testResult(actualDeckCount, expectedDeckCount, flag, "Is new deckCount three less than original deckCount");

   //test playedCardCount variable to see if it increased by 1
   int expectedPlayedCardCount = G->playedCardCount + 1;
   int actualPlayedCardCount = testG->playedCardCount;
   testResult(actualPlayedCardCount, expectedPlayedCardCount, flag, "Is new playedCardCount one more than original playedCardCount");

   //test playedCards array to see if smithy card is in position 0 of playedCards array
   testResult(testG->playedCards[0], smithy, flag, "Does new card in position 0 of playedCards array equal smithy");

}

int main()
{
   struct gameState G, copyG, testG;// declare a gameState struct
   int numPlayer = 2; //number of players playing game
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; //kingdom cards
   int seed = 1000;
   int r, flag = 0;

   memset(&G, -4, sizeof(struct gameState)); // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); //initialize a new game
   
   // Run test 1:
   
   memcpy(&copyG, &G, sizeof(struct gameState));

   //setup gameState variable values for testing purposes
   int handPos = 4;
   int currentPlayer = 0;
   copyG.hand[currentPlayer][0] = copper;
   copyG.hand[currentPlayer][1] = copper;
   copyG.hand[currentPlayer][2] = estate;
   copyG.hand[currentPlayer][3] = copper;
   copyG.hand[currentPlayer][4] = smithy;
   copyG.deck[currentPlayer][0] = estate;
   copyG.deck[currentPlayer][1] = estate;
   copyG.deck[currentPlayer][2] = copper;
   copyG.deck[currentPlayer][3] = copper;
   copyG.deck[currentPlayer][4] = copper;
   copyG.handCount[currentPlayer] = 5;
   copyG.deckCount[currentPlayer] = 5;
   copyG.playedCardCount = 0;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   printf("Running Test 1:\n");
   runTests(&copyG, &testG, &flag, handPos, currentPlayer);

   // Run test 2:
   
   memcpy(&copyG, &G, sizeof(struct gameState));

   //setup gameState variable values for testing purposes
   handPos = 0;
   currentPlayer = 0;
   copyG.hand[currentPlayer][0] = smithy;
   copyG.hand[currentPlayer][1] = copper;
   copyG.hand[currentPlayer][2] = estate;
   copyG.hand[currentPlayer][3] = copper;
   copyG.hand[currentPlayer][4] = copper;
   copyG.deck[currentPlayer][0] = estate;
   copyG.deck[currentPlayer][1] = estate;
   copyG.deck[currentPlayer][2] = copper;
   copyG.deck[currentPlayer][3] = copper;
   copyG.deck[currentPlayer][4] = copper;
   copyG.handCount[currentPlayer] = 5;
   copyG.deckCount[currentPlayer] = 5;
   copyG.playedCardCount = 0;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   
   printf("Running Test 2:\n");
   runTests(&copyG, &testG, &flag, handPos, currentPlayer);

   // Run test 3:
   
   memcpy(&copyG, &G, sizeof(struct gameState));

   //setup gameState variable values for testing purposes
   handPos = 3;
   currentPlayer = 0;
   copyG.hand[currentPlayer][0] = copper;
   copyG.hand[currentPlayer][1] = copper;
   copyG.hand[currentPlayer][2] = estate;
   copyG.hand[currentPlayer][3] = smithy;
   copyG.hand[currentPlayer][4] = copper;
   copyG.deck[currentPlayer][0] = copper;
   copyG.deck[currentPlayer][1] = copper;
   copyG.deck[currentPlayer][2] = copper;
   copyG.deck[currentPlayer][3] = copper;
   copyG.deck[currentPlayer][4] = copper;

   copyG.handCount[currentPlayer] = 5;
   copyG.deckCount[currentPlayer] = 3;
   copyG.playedCardCount = 0;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   
   printf("Running Test 3:\n");
   runTests(&copyG, &testG, &flag, handPos, currentPlayer);

   //cmpStructs(&G, &H);
 
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


