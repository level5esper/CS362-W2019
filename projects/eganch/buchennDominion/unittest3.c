/*************************************************
File name: unittest3.c
Author: Chelsea Egan
Class: CS 362-400
Assignment: 3
Date: February 5, 2018
Description: This is a unit test for the handCard
function in dominion.c
*************************************************/

#include "dominion.h"
#include "testHelpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUpBeforeEachTest(struct gameState *state) {
  int firstPlayercards[5] = { council_room, treasure_map, copper, outpost, 27 };
  int secondPlayerCards[6] = { curse, gold, gardens, baron, cutpurse, smithy };
  resetGameState(state);
  setPlayerHand(state, 0, firstPlayercards, 5);
  setPlayerHand(state, 1, secondPlayerCards, 6);
}

// THIS FUNCTION NEEDS BETTER HANDLING FOR NONEXISTENT CARDS
void invalidHandPos(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 1: Calls handCard with a handPos that does not have a card\n");
  printf("handPos is an index higher than number of cards in hand\n");
  assertTrueForIntComparison(testState, -1, handCard(5, state));
  printf("handPos is an index lower than number of cards in hand\n");
  assertTrueForIntComparison(testState, -1, handCard(-1, state));
  printf("---------------------------------------------\n\n");
}

void handPosHigherThanStandardFour(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 2: Calls handCard with a handPos that is higher than four\n");
  printf("Hands start out with five, checking that handCard can return a sixth\n");
  state->whoseTurn = 1;
  assertTrueForIntComparison(testState, 13, handCard(5, state));
  printf("---------------------------------------------\n\n");
}

void getFirstCardForCurrentPlayer(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 3: Get the first card for player 1\n");
  assertTrueForIntComparison(testState, 8, handCard(0, state));
  printf("---------------------------------------------\n\n");
}

void getLastCardForCurrentPlayer(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 4: Get the last card for player 1\n");
  assertTrueForIntComparison(testState, 27, handCard(4, state));
  printf("---------------------------------------------\n\n");
}

void getAllCardsInHand(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 5: Can loop through all cards in hand correctly\n");
  int expectedHand[5] = { 8, 26, 4, 23, 27 };

  int actualHand[state->handCount[0]];

  for (int i = 0; i < state->handCount[0]; i++) {
    actualHand[i] = handCard(i, state);
  }

  assertTrueForIntArrayComparison(testState, expectedHand, 5, actualHand, state->handCount[0]);
  printf("---------------------------------------------\n\n");
}

int main() {
  printf("*********************************************\n");
  printf("unittest3.c\n");
  printf("Testing handCard function from dominion.c\n");
  printf("---------------------------------------------\n\n");

  struct gameState testGameState;
  struct TestState testState = *setUpTestSuite();

  setUpBeforeEachTest(&testGameState);
  invalidHandPos(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  handPosHigherThanStandardFour(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  getFirstCardForCurrentPlayer(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  getLastCardForCurrentPlayer(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  getAllCardsInHand(&testGameState, &testState);

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");
  return 0;
}