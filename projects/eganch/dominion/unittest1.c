/*************************************************
File name: unittest1.c
Author: Chelsea Egan
Class: CS 362-400
Assignment: 3
Date: February 5, 2018
Description: This is a unit test for the 
numHandCards function in dominion.c
*************************************************/

#include "dominion.h"
#include "testHelpers.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cardsInHandOfFirstPlayerAfterGameInitialized(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 1: numHandCards should return 5 for first player after game is initialized\n");
  assertTrueForIntComparison(testState, 5, numHandCards(state));
  printf("---------------------------------------------\n\n");
}

void cardsInHandOfSecondPlayerAfterGameInitialized(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 2: numHandCards should return 0 for second player after game is initialized\n");
  state->whoseTurn = 1;
  assertTrueForIntComparison(testState, 0, numHandCards(state));
  printf("---------------------------------------------\n\n");
}

void returnsCorrectHandCountWhenManuallySet(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 3: numHandCards should return 15 for first player when manually set\n");
  state->handCount[0] = 15;
  assertTrueForIntComparison(testState, 15, numHandCards(state));
  printf("---------------------------------------------\n\n");
}

int main() {
  printf("*********************************************\n");
  printf("unittest1.c\n");
  printf("Testing numHandCards function from dominion.c\n");
  printf("---------------------------------------------\n\n");

  struct gameState testGameState;
  struct TestState testState = *setUpTestSuite();

  resetGameState(&testGameState);
  cardsInHandOfFirstPlayerAfterGameInitialized(&testGameState, &testState);
  
  resetGameState(&testGameState);
  cardsInHandOfSecondPlayerAfterGameInitialized(&testGameState, &testState);
  
  resetGameState(&testGameState);
  returnsCorrectHandCountWhenManuallySet(&testGameState, &testState);

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");
  return 0;
}
