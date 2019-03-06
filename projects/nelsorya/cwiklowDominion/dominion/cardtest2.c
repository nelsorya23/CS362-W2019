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
void runTests(struct gameState* G, struct gameState* testG, int* flag, int handPos, int currentPlayer, int expectedHandCount, int expectedCount, int expectedDiscardCount )
{
   int card = adventurer;
   int choice1, choice2, choice3;
   choice1 = choice2 = choice3 = 0;
   int* bonus = 0; 
   
   //run function with copied gameState
   int returnResult = cardEffect(card, choice1, choice2, choice3, testG, handPos, bonus);
   
   //test return value is 0 to ensure function ran without errors
   int expectedReturnResult = 0;
   testResult(returnResult, expectedReturnResult, flag, "Does returned result = 0");
   
   //test handCount variable to see if it increased by 1
   int actualHandCount = testG->handCount[currentPlayer];
   testResult(actualHandCount, expectedHandCount, flag, "Is new handCount one more than original handCount");
   
   //test if two treasure cards are now in the player's hand when there were none before
   int i, counter = 0;
   for(i = 0; i < testG->handCount[currentPlayer]; i++)
   {
      if(testG->hand[currentPlayer][i] == copper || testG->hand[currentPlayer][i] == silver || testG->hand[currentPlayer][i] == gold)   
      {
         counter++;
      }
   }
   testResult(counter, expectedCount, flag, "Do 2 treasure cards no exist in player's hand");

   //check if gameState variables changed for any of the other players
   testResult(playerState(G, testG, currentPlayer + 1), 0, flag, "Did Player 2 gameState change"); 

   //check if gameState variables changed for any of the other players
   testResult(playerState(G, testG, currentPlayer + 2), 0, flag, "Did Player 3 gameState change"); 

   //check if gameState variables changed for any of the other players
   testResult(playerState(G, testG, currentPlayer + 3), 0, flag, "Did Player 4 gameState change"); 

   //test if card was discarded and is now in the played pile
   testResult(testG->playedCards[0], adventurer, flag, "Is the card played in the played pile"); 

   //test if card was discarded and is now in the played pile
   testResult(testG->playedCardCount, 1, flag, "Is the playedCardCount equal to 1"); 

   //test if discardCount increased by proper amount
   int actualDiscardCount = testG->discardCount[currentPlayer];
   testResult(actualDiscardCount, expectedDiscardCount, flag, "Is new discardCount the correct number");

   //test if supplyCount changed 
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
   int expectedHandCount = copyG.handCount[currentPlayer] + 1;
   int expectedDiscardCount = copyG.discardCount[currentPlayer] + 1;
   int expectedCount = 2; //number of treasure cards in hand expected

   copyG.hand[currentPlayer][0] = estate;
   copyG.hand[currentPlayer][1] = estate;
   copyG.hand[currentPlayer][2] = estate;
   copyG.hand[currentPlayer][3] = estate;
   copyG.hand[currentPlayer][4] = adventurer;
   copyG.deck[currentPlayer][0] = silver;
   copyG.deck[currentPlayer][1] = estate;
   copyG.deck[currentPlayer][2] = copper;
   copyG.deck[currentPlayer][3] = copper;
   copyG.deck[currentPlayer][4] = estate;
   copyG.handCount[currentPlayer] = 5;
   copyG.deckCount[currentPlayer] = 5;
   copyG.playedCardCount = 0;
   copyG.playedCards[0] = -2;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   printf("\nRunning Test 1: Plenty of supply cards in player's deck and no treasure cards in player's hand\n");
   runTests(&copyG, &testG, &flag, handPos, currentPlayer, expectedHandCount, expectedCount, expectedDiscardCount);

   // Run test 2:
   
   memcpy(&copyG, &G, sizeof(struct gameState));

   //setup gameState variable values for testing purposes
   handPos = 0;
   expectedHandCount = copyG.handCount[currentPlayer] + 1;
   expectedCount = 2; //number of treasure cards in hand expected
   expectedDiscardCount = copyG.discardCount[currentPlayer] + 1;

   copyG.hand[currentPlayer][0] = adventurer;
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

   
   printf("\nRunning Test 2: Exactly two treasure cards in deck and none in player's hand\n");
   runTests(&copyG, &testG, &flag, handPos, currentPlayer, expectedHandCount, expectedCount, expectedDiscardCount);

   // Run test 3:
   
   memcpy(&copyG, &G, sizeof(struct gameState));

   //setup gameState variable values for testing purposes
   handPos = 3;
   expectedHandCount = copyG.handCount[currentPlayer] - 1;
   expectedDiscardCount = copyG.discardCount[currentPlayer] + 0;
   expectedCount = 0; //number of treasure cards in hand expected
   copyG.hand[currentPlayer][0] = estate;
   copyG.hand[currentPlayer][1] = estate;
   copyG.hand[currentPlayer][2] = estate;
   copyG.hand[currentPlayer][3] = adventurer;
   copyG.hand[currentPlayer][4] = estate;
   copyG.deck[currentPlayer][0] = estate;
   copyG.deck[currentPlayer][1] = estate;
   copyG.deck[currentPlayer][2] = estate;
   copyG.deck[currentPlayer][3] = estate;
   copyG.deck[currentPlayer][4] = estate;

   copyG.handCount[currentPlayer] = 5;
   copyG.deckCount[currentPlayer] = 5;
   copyG.playedCardCount = 0;
   copyG.playedCards[0] = -2;
 
   memcpy(&testG, &copyG, sizeof(struct gameState));

   
   printf("\nRunning Test 3: No treasure cards in deck and non in player's hand\n");
   runTests(&copyG, &testG, &flag, handPos, currentPlayer, expectedHandCount, expectedCount, expectedDiscardCount);

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
