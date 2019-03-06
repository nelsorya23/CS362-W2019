/***********************************************************************
*Author: Ryan Nelson
*
*Tests smithyEffect function to see if it is working properly.
*
*Tests:
*Smithy effect function is tested when smithy card is located in a player's
*hand at first and last positions as well as a middle position.
*
*The objective of the test is to see if a net of two cards is added to the 
*player's hand after drawing three cards and discarding the smithy card. 
*
* Include in makefile:
*    gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
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
void runTests(struct gameState* G, struct gameState* testG, int* flag, int handPos, int currentPlayer)
{
   int card = smithy;
   int choice1, choice2, choice3;
   choice1 = choice2 = choice3 = 0;
   int* bonus = 0; 
   
   //run function with copied gameState
   int returnResult = cardEffect(card, choice1, choice2, choice3, testG, handPos, bonus);

   //test return value is 0 to ensure function ran without errors
   int expectedReturnResult = 0;
   testResult(returnResult, expectedReturnResult, flag, "Does returned result = 0");
   
   //test handCount variable to see if it increased by 2
   int expectedHandCount = G->handCount[currentPlayer] + 2;
   int actualHandCount = testG->handCount[currentPlayer];
   testResult(actualHandCount, expectedHandCount, flag, "Is new handCount two more than original handCount");
   
   //test deckCount variable to see if it decreased by 3
   int expectedDeckCount = G->deckCount[currentPlayer] - 3;
   int actualDeckCount = testG->deckCount[currentPlayer];
   testResult(actualDeckCount, expectedDeckCount, flag, "Is new deckCount three less than original deckCount");

   //check if gameState variables changed for any of the other players
   testResult(playerState(G, testG, currentPlayer + 1), 0, flag, "Did Player 2 gameState change"); 

   //check if gameState variables changed for any of the other players
   testResult(playerState(G, testG, currentPlayer + 2), 0, flag, "Did Player 3 gameState change"); 

   //check if gameState variables changed for any of the other players
   testResult(playerState(G, testG, currentPlayer + 3), 0, flag, "Did Player 4 gameState change"); 

   //test if supplyCount changed 
   int i; 
   int flag1 = 0;
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

   //test if card was discarded and is now in the played pile
   testResult(testG->playedCards[0], smithy, flag, "Is the card played in the played pile"); 

   //test if card was discarded and is now in the played pile
   testResult(testG->playedCardCount, 1, flag, "Is the playedCardCount equal to 1"); 

}

int main()
{
   struct gameState G, copyG, testG;// declare a gameState struct
   int numPlayer = 4; //number of players playing game
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
   copyG.playedCards[0] = -2;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   printf("\nRunning Test 1: Smithy card is last card in player's hand\n");
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
   copyG.playedCards[0] = -2;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   
   printf("\nRunning Test 2: Smithy card is first card in player's hand\n");
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
   copyG.playedCards[0] = -2;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   
   printf("\nRunning Test 3: Smithy card is 4th card in player's hand\n");
   runTests(&copyG, &testG, &flag, handPos, currentPlayer);

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


