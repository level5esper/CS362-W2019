/*************************************************
File name: unittest4.c
Author: Chelsea Egan
Class: CS 362-400
Assignment: 3
Date: February 5, 2018
Description: This is a unit test for the endTurn
function in dominion.c
*************************************************/

#include "dominion.h"
#include "testHelpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void currentPlayerHandEmptied(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 1: The player whose turn is ending should have an empty hand\n");
  endTurn(state); 
  assertTrueForIntComparison(testState, 0, state->handCount[0]);
  printf("---------------------------------------------\n\n");
}

void currentPlayerHandSetToNegativeOne(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 2: All cards in the current player's hand should be set to -1\n");
  int handCount = state->handCount[0];
  int expectedHand[handCount];
  for (int i = 0; i < handCount; i++) {
    expectedHand[i] = -1;
  }
  endTurn(state);
  assertTrueForIntArrayComparison(testState, expectedHand, handCount, state->hand[0], handCount);
  printf("---------------------------------------------\n\n");
}

void afterPlayerOneTurnChangesToPlayerTwo(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 3: When the first player ends their turn, it is the second player's turn\n");
  endTurn(state);
  assertTrueForIntComparison(testState, 1, state->whoseTurn);
  printf("---------------------------------------------\n\n");
}

void afterPlayerTwoTurnChangesToPlayerOne(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 4: When the second player ends their turn, it is the first player's turn\n");
  state->whoseTurn = 1;
  endTurn(state);
  assertTrueForIntComparison(testState, 0, state->whoseTurn);
  printf("---------------------------------------------\n\n");
}

void stateVariablesAreReset(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 5: The following variables are reset\n");
  endTurn(state);
  printf("outpostPlayed\n");
  assertTrueForIntComparison(testState, 0, state->outpostPlayed);
  printf("phase\n");
  assertTrueForIntComparison(testState, 0, state->phase);
  printf("numActions\n");
  assertTrueForIntComparison(testState, 1, state->numActions);
  printf("numBuys\n");
  assertTrueForIntComparison(testState, 1, state->numBuys);
  printf("playedCardCount\n");
  assertTrueForIntComparison(testState, 0, state->playedCardCount);
  
  //Can't test these because they get changed immediately after
  //Also - why set them then? And it seems risky to set handCount to 0 without verifying that their hand is empty
  //printf("handCount for next player\n");
  //assertTrueForIntComparison(testState, 0, state->handCount[1]);
  //printf("coins\n");
  //assertTrueForIntComparison(testState, 0, state->coins);
  printf("---------------------------------------------\n\n");
}

void nextPlayerDrawsFiveCards(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 6: The next player draws five cards\n");
  endTurn(state);
  printf("The player should have a hand count of 5\n");
  assertTrueForIntComparison(testState, 5, state->handCount[1]);
  printf("The player's hand should not hold any set to -1\n");
  assertTrueForArrayNotHoldingCardValue(testState, state->hand[1], state->handCount[1], -1);
  printf("---------------------------------------------\n\n");
}

//Not sure how to test this because the cards drawn get set in the function
//I can't control how many coins they get
//void coinsOfNextPlayerGetSet(struct gameState *state, struct TestState *testState) {
//  printf("---------------------------------------------\n");
//  printf("TEST 7: The next player has coins updated\n");
//  endTurn(state);
//  printf("---------------------------------------------\n\n");
//}

void currentPlayerHandDiscarded(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 8: All cards in the current player's hand should be discarded\n");
  int expectedDiscardCount = state->handCount[0];
  int cards[5] = { curse, estate, duchy, province, copper };
  setPlayerHand(state, 0, cards, 5);
  endTurn(state);
  printf("Discard count should equal the player's hand count\n");
  assertTrueForIntComparison(testState, expectedDiscardCount, state->discardCount[0]);
  printf("Discard pile should hold curse, estate, duchy, province, copper\n");
  assertTrueForIntArrayComparison(testState, cards, 5, state->discard[0], state->discardCount[0]);
  printf("---------------------------------------------\n\n");
}

void playedCardsShouldBeEmptied(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 9: Any cards added to playedCards should be emptied\n");
  state->playedCardCount = 1;
  state->playedCards[0] = copper;
  endTurn(state);
  printf("No cards in playedCardCount\n");
  assertTrueForIntComparison(testState, -1, state->playedCards[0]);
  printf("---------------------------------------------\n\n");
}

int main() {
  printf("*********************************************\n");
  printf("unittest4.c\n");
  printf("Testing endTurn function from dominion.c\n");
  printf("---------------------------------------------\n\n");

  struct gameState testGameState;
  struct TestState testState = *setUpTestSuite();

  resetGameState(&testGameState);
  currentPlayerHandEmptied(&testGameState, &testState);

  resetGameState(&testGameState);
  currentPlayerHandSetToNegativeOne(&testGameState, &testState);

  resetGameState(&testGameState);
  afterPlayerOneTurnChangesToPlayerTwo(&testGameState, &testState);

  resetGameState(&testGameState);
  afterPlayerTwoTurnChangesToPlayerOne(&testGameState, &testState);

  resetGameState(&testGameState);
  stateVariablesAreReset(&testGameState, &testState);

  resetGameState(&testGameState);
  nextPlayerDrawsFiveCards(&testGameState, &testState);

  //resetGameState(&testGameState);
  //coinsOfNextPlayerGetSet(&testGameState, &testState);

  resetGameState(&testGameState);
  currentPlayerHandDiscarded(&testGameState, &testState);

  resetGameState(&testGameState);
  playedCardsShouldBeEmptied(&testGameState, &testState);

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");
  return 0;
}
