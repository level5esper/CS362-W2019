/*************************************************
File name: unittest2.c
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

void wrongPhaseReturnsNegativeOne(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 1: playCard should return -1 if the phase is not 0\n");
  state->phase = 1;
  int result = playCard(0, -1, -1, -1, state);
  assertTrueForIntComparison(testState, -1, result);
  printf("---------------------------------------------\n\n");
}

void notEnoughActionsReturnsNegativeOne(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 2: playCard should return -1 if the player has less than 1 actions\n");
  state->numActions = 0;
  state->phase = 0;
  int result = playCard(0, -1, -1, -1, state);
  assertTrueForIntComparison(testState, -1, result);
  printf("---------------------------------------------\n\n");
}

void cardIsBasicCardReturnsNegativeOne(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 3: playCard should return -1 if the card played is a basic card\n");
  state->numActions = 1;
  int result = playCard(2, -1, -1, -1, state);
  assertTrueForIntComparison(testState, -1, result);
  printf("---------------------------------------------\n\n");
}

void cardIsGreaterThanTreasureMapReturnsNegativeOne(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 4: playCard should return -1 if the card played is greater than treasure_map in enum\n");
  int result = playCard(4, -1, -1, -1, state);
  assertTrueForIntComparison(testState, -1, result);
  printf("---------------------------------------------\n\n");
}

void cardPlayedHasAnEffectThatReturnsNegativeOne(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 5: playCard should return -1 if the card played has an effect that returns -1\n");
  int result = playCard(1, -1, -1, -1, state);
  assertTrueForIntComparison(testState, -1, result);
  printf("---------------------------------------------\n\n");
}

void cardPlayedReturnsZeroReducesNumActions(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 6: playCard should reduce the number of actions if the card played does not return -1\n");
  state->numActions = 1;
  playCard(0, -1, -1, -1, state);
  assertTrueForIntComparison(testState, 0, state->numActions);
  printf("---------------------------------------------\n\n");
}

//TODO: Test update coins

int main() {
  printf("*********************************************\n");
  printf("unittest2.c\n");
  printf("Testing playCard function from dominion.c\n");
  printf("---------------------------------------------\n\n");

  int cards[5] = { council_room, treasure_map, copper, estate, 27 };
  struct TestState testState = *setUpTestSuite();
  struct gameState testGameState;

  setUpGameState(&testGameState);
  setFirstPlayerHand(&testGameState, cards);

  wrongPhaseReturnsNegativeOne(&testGameState, &testState);
  notEnoughActionsReturnsNegativeOne(&testGameState, &testState);
  cardIsBasicCardReturnsNegativeOne(&testGameState, &testState);
  cardIsGreaterThanTreasureMapReturnsNegativeOne(&testGameState, &testState);
  cardPlayedHasAnEffectThatReturnsNegativeOne(&testGameState, &testState);
  cardPlayedReturnsZeroReducesNumActions(&testGameState, &testState);

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");
  return 0;
}
