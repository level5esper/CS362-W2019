/*************************************************
File name: cardtest4.c
Author: Chelsea Egan
Class: CS 362-400
Assignment: 3
Date: February 5, 2018
Description: This is a unit test for the
smithy card in dominion.c
*************************************************/

#include "dominion.h"
#include "testHelpers.h"
#include "dominion_helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUpBeforeEachTest(struct gameState *state) {
  int cards[5] = { smithy, treasure_map, copper, outpost, 27 };
  resetGameState(state);
  setPlayerHand(state, 0, cards, 5);
}

void playerDrawsThreeCards(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 1: player should have seven cards\n");
  printf("They draw three then discard the smithy card.\n");
  cardEffect(smithy, -1, -1, -1, state, 0, 0);
  assertTrueForIntComparison(testState, 7, state->handCount[0]);
  printf("---------------------------------------------\n\n");
}

//SMITHY IS TRASHED AND NOT ADDED TO PLAYED
void smithyAddedToPlayedPile(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 2: The Smithy card should be discarded and added to played pile\n");
  cardEffect(smithy, -1, -1, -1, state, 0, 0);
  printf("The smithy card should be removed from the hand\n");
  assertTrueForArrayNotHoldingCardValue(testState, state->hand[0], state->handCount[0], smithy);
  printf("Smithy should be in the played card pile.\n");
  assertTrueForArrayHoldingCardValue(testState, state->playedCards, state->playedCardCount, smithy);
  printf("---------------------------------------------\n\n");
}

int main() {
  printf("*********************************************\n");
  printf("cardtest4.c\n");
  printf("Testing smithy card from cardEffect function in dominion.c\n");
  printf("---------------------------------------------\n\n");

  struct gameState testGameState;
  struct TestState testState = *setUpTestSuite();

  setUpBeforeEachTest(&testGameState);
  playerDrawsThreeCards(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  smithyAddedToPlayedPile(&testGameState, &testState);

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");
  return 0;
}
