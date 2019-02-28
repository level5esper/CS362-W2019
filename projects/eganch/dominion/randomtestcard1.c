/*************************************************
File name: randomtestcard1.c
Author: Chelsea Egan
Class: CS 362-400
Assignment: 4
Date: February 26, 2018
Description: This is a random test for the
smithy card in dominion.c
*************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include "rngs.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


/*** SET TEST_DEBUG TO 1 IN TESTHELPERS.H TO PRINT ERRORS ***/

void checkSmithy(struct TestState *testState, struct gameState *post, int handPos) {
  int r;
  int bonus = 0;
  int playerNum = post->whoseTurn;
  int originalHandNum = post->handCount[playerNum];
  int originalDeckCount = post->deckCount[playerNum];
  int originalPlayedCount = post->playedCardCount;

  r = cardEffect(smithy, -1, -1, -1, post, handPos, &bonus);

  //returns 0
  if (!assertTrueForIntComparison(testState, 0, r) && TEST_DEBUG) {
    printf("X - Test did not return 0\n");
  }

  //drew three cards and discarded one card
  if (!assertTrueForIntComparison(testState, originalHandNum + 2, post->handCount[playerNum]) && TEST_DEBUG) {
    printf("X - Hand count incorrect\n");
  }

  //deck size has decreased by three
  if (!assertTrueForIntComparison(testState, originalDeckCount - 3, post->deckCount[playerNum]) && TEST_DEBUG) {
    printf("X - Deck size incorrect\n");
  }

  //smithy should have been added to played cards
  if (!assertTrueForArrayHoldingCardValue(testState, post->playedCards, post->playedCardCount, adventurer) && TEST_DEBUG) {
    printf("X - played cards did not include smithy\n");
  }
  if (!assertTrueForIntComparison(testState, originalPlayedCount + 1, post->playedCardCount) && TEST_DEBUG) {
    printf("X - played card count incorrect\n");
  }
}

int main() {
  printf("*********************************************\n");
  printf("randomtestcard1.c\n");
  printf("Random testing smithy card from cardEffect function in dominion.c\n");
  printf("---------------------------------------------\n\n");

  struct gameState gameState;
  struct TestState testState = *setUpTestSuite();

  SelectStream(2);
  PutSeed(3);


  for (int n = 0; n < 2000; n++) {
    int handPos = setUpGameState(&gameState, smithy);
    checkSmithy(&testState, &gameState, handPos);
  }

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");

  return 0;
}
