/*************************************************
File name: randomtestcard2.c
Author: Chelsea Egan
Class: CS 362-400
Assignment: 4
Date: February 26, 2018
Description: This is a random test for the
village card in dominion.c
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

void checkVillage(struct TestState *testState, struct gameState *post, int handPos) {
  int r;
  int bonus = 0;
  int playerNum = post->whoseTurn;
  int originalHandNum = post->handCount[playerNum];
  int originalDeckCount = post->deckCount[playerNum];
  int originalPlayedCount = post->playedCardCount;
  int originalNumActions = post->numActions;

  r = cardEffect(village, -1, -1, -1, post, handPos, &bonus);

  //returns 0
  if (!randomAssertTrueForIntComparison(testState, 0, r) && TEST_DEBUG) {
    printf("X - Test did not return 0\n");
  }

  //drew one card and discarded one card
  if (!randomAssertTrueForIntComparison(testState, originalHandNum, post->handCount[playerNum]) && TEST_DEBUG) {
    printf("X - Hand count incorrect\n");
  }

  //actions increased by two
  if (!randomAssertTrueForIntComparison(testState, originalNumActions + 2, post->numActions) && TEST_DEBUG) {
    printf("X - Number of actions incorrect\n");
  }

  //deck size has decreased by one
  if (!randomAssertTrueForIntComparison(testState, originalDeckCount - 1, post->deckCount[playerNum]) && TEST_DEBUG) {
    printf("X - Deck size incorrect\n");
  }

  //village should have been added to played cards
  if (!randomAssertTrueForArrayHoldingCardValue(testState, post->playedCards, post->playedCardCount, village) && TEST_DEBUG) {
    printf("X - played cards did not include village\n");
  }
  if (!randomAssertTrueForIntComparison(testState, originalPlayedCount + 1, post->playedCardCount) && TEST_DEBUG) {
    printf("X - played card count incorrect\n");
  }
}

int main() {
  printf("*********************************************\n");
  printf("randomtestcard2.c\n");
  printf("Random testing village card from cardEffect function in dominion.c\n");
  printf("---------------------------------------------\n\n");

  struct gameState gameState;
  struct TestState testState = *setUpTestSuite();

  SelectStream(2);
  PutSeed(3);


  for (int n = 0; n < 2000; n++) {
    int handPos = setUpRandomGameState(&gameState, village);
    checkVillage(&testState, &gameState, handPos);
  }

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");

  return 0;
}