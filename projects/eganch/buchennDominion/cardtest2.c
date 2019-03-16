/*************************************************
File name: cardtest2.c
Author: Chelsea Egan
Class: CS 362-400
Assignment: 3
Date: February 5, 2018
Description: This is a unit test for the
village card in dominion.c
*************************************************/

#include "dominion.h"
#include "testHelpers.h"
#include "dominion_helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUpBeforeEachTest(struct gameState *state) {
  int cards[5] = { village, treasure_map, copper, outpost, 27 };
  resetGameState(state);
  setPlayerHand(state, 0, cards, 5);
}

void playerDrawsOneCard(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 1: player should have the same amount of cards as what they started with\n");
  printf("They draw one then discard the village card.\n");
  cardEffect(village, -1, -1, -1, state, 0, 0);
  assertTrueForIntComparison(testState, 5, state->handCount[0]);
  printf("---------------------------------------------\n\n");
}

void playerGetsTwoAction(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 2: Player gets two more actions resulting in three actions\n");
  cardEffect(village, -1, -1, -1, state, 0, 0);
  assertTrueForIntComparison(testState, 3, state->numActions);
  printf("---------------------------------------------\n\n");
}

void playerDiscardsVillage(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 4: The player should discard the village card\n");
  cardEffect(village, -1, -1, -1, state, 0, 0);
  printf("Village should not be in their hand.\n");
  assertTrueForArrayNotHoldingCardValue(testState, state->hand[0], state->handCount[0], 14);
  printf("Village should be in the played card pile.\n");
  assertTrueForArrayHoldingCardValue(testState, state->playedCards, state->playedCardCount, 14);
  printf("---------------------------------------------\n\n");
}

int main() {
  printf("*********************************************\n");
  printf("cardtest2.c\n");
  printf("Testing village card from cardEffect function in dominion.c\n");
  printf("---------------------------------------------\n\n");

  struct gameState testGameState;
  struct TestState testState = *setUpTestSuite();

  setUpBeforeEachTest(&testGameState);
  playerDrawsOneCard(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  playerGetsTwoAction(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  playerDiscardsVillage(&testGameState, &testState);

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");
  return 0;
}