/***********************************************************************
*Author: Ryan Nelson
*
*Tests greatHallEffect function to see if it is working properly.
*
**Tests:
*This function is tested when the great_hall card is played when in the
*player's hand position of 0, 4, and 3.
*
*The objective of the test is to see if the players hand count stays the  
*same and the player's action count is 1 after the card is played, and.
*to ensure it was discarded to the played pile.
* Include in makefile:
*    gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
***********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Outputs whether a test failed based on comaring test result to expected result
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

//compares values of two structs and prints any difference found
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

//runs all tests on a card effect function
void runTests(struct gameState* G, struct gameState* testG, int* flag, int handPos, int currentPlayer, int expectedHandCount, int expectedActionCount )
{
   int card = great_hall;
   int choice1, choice2, choice3;
   choice1 = choice2 = choice3 = 0;
   int* bonus = 0; 
   
   //run function with copied gameState
   int returnResult = cardEffect(card, choice1, choice2, choice3, testG, handPos, bonus);
   
   //test return value is 0 to ensure function ran without errors
   int expectedReturnResult = 0;
   testResult(returnResult, expectedReturnResult, flag, "Does returned result = 0");
   
   //test handCount variable to see if it remained the same
   int actualHandCount = testG->handCount[currentPlayer];
   testResult(actualHandCount, expectedHandCount, flag, "Is new handCount same as the original handCount");
   
   //test if the number of actions is 1
   testResult(testG->numActions, expectedActionCount, flag, "Is the number of actions 1");

   //test if card was discarded and is now in the played pile
   testResult(testG->playedCards[0], great_hall, flag, "Is the card played in the played pile"); 

   //test if card was discarded and is now in the played pile
   testResult(testG->playedCardCount, 1, flag, "Is the playedCardCount equal to 1"); 

   //check if gameState variables changed for any of the other players
   testResult(playerState(G, testG, currentPlayer + 1), 0, flag, "Did Player 2 gameState change"); 

   //check if gameState variables changed for any of the other players
   testResult(playerState(G, testG, currentPlayer + 2), 0, flag, "Did Player 3 gameState change"); 

   //check if gameState variables changed for any of the other players
   testResult(playerState(G, testG, currentPlayer + 3), 0, flag, "Did Player 4 gameState change"); 

   //test if supplyCount changed 
   int i, flag1 = 0;
   for(i = 0; i < treasure_map + 1; i++) 
   {
      if(G->supplyCount[i] != testG->supplyCount[i])
      {
         flag1 = 1;
      }
   }
   if(flag1 == 1)
   {
      testResult(1, 0, flag, "Did supplyCount of cards change" );
   }
   else
   {
      testResult(0, 0, flag, "Did supplyCount of cards change" );
   }

}

int main()
{
   struct gameState G, copyG, testG;// declare a gameState struct
   int numPlayer = 4; //number of players playing game
   int currentPlayer = 0;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; //kingdom cards
   int seed = 1000;
   int r, flag = 0;

   memset(&G, -4, sizeof(struct gameState)); // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); //initialize a new game
   G.whoseTurn = currentPlayer; 

   // Run test 1:
   
   memcpy(&copyG, &G, sizeof(struct gameState));

   //setup gameState variable values for testing purposes
   int handPos = 4;
   int expectedHandCount = copyG.handCount[currentPlayer];
   int expectedActionCount = 1; //number of actions left after gaining 1 actions

   copyG.hand[currentPlayer][0] = estate;
   copyG.hand[currentPlayer][1] = estate;
   copyG.hand[currentPlayer][2] = estate;
   copyG.hand[currentPlayer][3] = estate;
   copyG.hand[currentPlayer][4] = great_hall;
   copyG.deck[currentPlayer][0] = silver;
   copyG.deck[currentPlayer][1] = estate;
   copyG.deck[currentPlayer][2] = copper;
   copyG.deck[currentPlayer][3] = copper;
   copyG.deck[currentPlayer][4] = copper;
   copyG.handCount[currentPlayer] = 5;
   copyG.deckCount[currentPlayer] = 5;
   copyG.playedCardCount = 0;
   copyG.playedCards[0] = -2;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   printf("\nRunning Test 1: Check if number of cards in player's hand stays the same with great_hall card in hand position 4\n");
   runTests(&copyG, &testG, &flag, handPos, currentPlayer, expectedHandCount, expectedActionCount);

   // Run test 2:
   
   memcpy(&copyG, &G, sizeof(struct gameState));

   //setup gameState variable values for testing purposes
   handPos = 0;
   expectedHandCount = copyG.handCount[currentPlayer];
   expectedActionCount = 1; //number of actions left after gaining 1 actions
   copyG.hand[currentPlayer][0] = great_hall;
   copyG.hand[currentPlayer][1] = estate;
   copyG.hand[currentPlayer][2] = estate;
   copyG.hand[currentPlayer][3] = estate;
   copyG.hand[currentPlayer][4] = estate;
   copyG.deck[currentPlayer][0] = estate;
   copyG.deck[currentPlayer][1] = estate;
   copyG.deck[currentPlayer][2] = copper;
   copyG.deck[currentPlayer][3] = silver;
   copyG.deck[currentPlayer][4] = estate;
   copyG.handCount[currentPlayer] = 5;
   copyG.deckCount[currentPlayer] = 5;
   copyG.playedCardCount = 0;
   copyG.playedCards[0] = -2;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   
   printf("\nRunning Test 2: Check if number of cards in player's hand stays the same with great_hall card in hand position 0\n");
   runTests(&copyG, &testG, &flag, handPos, currentPlayer, expectedHandCount, expectedActionCount);

   // Run test 3:
   
   memcpy(&copyG, &G, sizeof(struct gameState));

   //setup gameState variable values for testing purposes
   handPos = 3;
   expectedHandCount = copyG.handCount[currentPlayer];
   expectedActionCount = 1; //number of actions left after gaining 1 actions
   copyG.hand[currentPlayer][0] = estate;
   copyG.hand[currentPlayer][1] = estate;
   copyG.hand[currentPlayer][2] = estate;
   copyG.hand[currentPlayer][3] = village;
   copyG.hand[currentPlayer][4] = estate;
   copyG.deck[currentPlayer][0] = estate;
   copyG.deck[currentPlayer][1] = estate;
   copyG.deck[currentPlayer][2] = estate;
   copyG.deck[currentPlayer][3] = estate;
   copyG.deck[currentPlayer][4] = estate;

   copyG.handCount[currentPlayer] = 5;
   copyG.deckCount[currentPlayer] = 3;
   copyG.playedCardCount = 0;
   copyG.playedCards[0] = -2;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   
   printf("\nRunning Test 3: Check if number cards in player's hand stays the same with great_hall card in hand position 3\n");
   runTests(&copyG, &testG, &flag, handPos, currentPlayer, expectedHandCount, expectedActionCount);

   //cmpStructs(&G, &H);
 
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


