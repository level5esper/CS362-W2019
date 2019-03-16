/*************************************************
File name: cardtest1.c
Author: Chelsea Egan
Class: CS 362-400
Assignment: 3
Date: February 5, 2018
Description: This is a unit test for the
council_room card in dominion.c
*************************************************/

#include "dominion.h"
#include "testHelpers.h"
#include "dominion_helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUpBeforeEachTest(struct gameState *state) {
  int cards[5] = { council_room, treasure_map, copper, outpost, 27 };
  resetGameState(state);
  setPlayerHand(state, 0, cards, 5);
}

void playerDrawsFourCards(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 1: player should have three additional cards in hand\n");
  printf("They draw four then discard the council_room card.\n");
  cardEffect(council_room, -1, -1, -1, state, 0, 0);
  assertTrueForIntComparison(testState, 8, state->handCount[0]);
  printf("---------------------------------------------\n\n");
}

void playerGetsAnotherBuy(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 2: Player gets another buy resulting in two buys\n");
  cardEffect(council_room, -1, -1, -1, state, 0, 0);
  assertTrueForIntComparison(testState, 2, state->numBuys);
  printf("---------------------------------------------\n\n");
}

void otherPlayerDrawsACard(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 3: The second player should draw a card\n");
  cardEffect(council_room, -1, -1, -1, state, 0, 0);
  assertTrueForIntComparison(testState, 1, state->handCount[1]);
  printf("---------------------------------------------\n\n");
}

void playerDiscardsCouncilRoom(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 4: The player should discard the council room card\n");
  cardEffect(council_room, -1, -1, -1, state, 0, 0);
  printf("Council room should not be in their hand.\n");
  assertTrueForArrayNotHoldingCardValue(testState, state->hand[0], state->handCount[0], 8);
  printf("Council room should be in the played card pile.\n");
  assertTrueForArrayHoldingCardValue(testState, state->playedCards, state->playedCardCount, 8);
  printf("---------------------------------------------\n\n");
}

int main() {
  printf("*********************************************\n");
  printf("cardtest1.c\n");
  printf("Testing council_room card from cardEffect function in dominion.c\n");
  printf("---------------------------------------------\n\n");

  struct gameState testGameState;
  struct TestState testState = *setUpTestSuite();

  setUpBeforeEachTest(&testGameState);
  playerDrawsFourCards(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  playerGetsAnotherBuy(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  otherPlayerDrawsACard(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  playerDiscardsCouncilRoom(&testGameState, &testState);

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");
  return 0;
}