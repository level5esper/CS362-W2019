/*************************************************
File name: unittest1.c
Author: Chelsea Egan
Class: CS 362-400
Assignment: 3
Date: February 5, 2018
Description: This is a unit test for the playCard
function in dominion.c
*************************************************/

#include "dominion.h"
#include "testHelpers.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int numHandCards(struct gameState *state) {
//  return state->handCount[whoseTurn(state)];
//}

void cardsInHandOfFirstPlayerAfterGameInitialized(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 1: numHandCards should return 5 for first player after game is initialized\n");
  assertTrueForIntComparison(testState, 5, numHandCards(state));
  printf("---------------------------------------------\n\n");
}

void cardsInHandOfSecondPlayerAfterGameInitialized(struct gameState *state, struct TestState *testState) {
  state->whoseTurn = 1;

  printf("---------------------------------------------\n");
  printf("TEST 2: numHandCards should return 0 for second player after game is initialized\n");
  assertTrueForIntComparison(testState, 0, numHandCards(state));
  printf("---------------------------------------------\n\n");
}

void returnsCorrectHandCountWhenManuallySet(struct gameState *state, struct TestState *testState) {
  state->whoseTurn = 0;
  state->handCount[0] = 15;

  printf("---------------------------------------------\n");
  printf("TEST 3: numHandCards should return 15 for first player when manually set\n");
  assertTrueForIntComparison(testState, 15, numHandCards(state));
  printf("---------------------------------------------\n\n");
}

int main() {
  printf("*********************************************\n");
  printf("unittest1.c\n");
  printf("Testing numHandCards function from dominion.c\n");
  printf("---------------------------------------------\n\n");

  // Set up the game with standard inputs and cards
  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens,  embargo, village, minion,
                          mine, cutpurse, sea_hag, tribute, smithy};
  int randomSeed = 1000;
  struct gameState testGameState;
  initializeGame(numPlayers, kingdomCards, randomSeed, &testGameState);

  struct TestState testState = *setUpTestSuite();

  cardsInHandOfFirstPlayerAfterGameInitialized(&testGameState, &testState);
  cardsInHandOfSecondPlayerAfterGameInitialized(&testGameState, &testState);
  returnsCorrectHandCountWhenManuallySet(&testGameState, &testState);

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");
  return 0;
}
