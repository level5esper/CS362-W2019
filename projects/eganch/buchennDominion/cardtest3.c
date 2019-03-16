/*************************************************
File name: cardtest3.c
Author: Chelsea Egan
Class: CS 362-400
Assignment: 3
Date: February 5, 2018
Description: This is a unit test for the
adventurer card in dominion.c
*************************************************/

#include "dominion.h"
#include "testHelpers.h"
#include "dominion_helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUpBeforeEachTest(struct gameState *state) {
  int cards[5] = { adventurer, treasure_map, copper, outpost, 27 };
  resetGameState(state);
  setPlayerHand(state, 0, cards, 5);
}

//SHUFFLE RETURNS -1 WHEN DECK IS EMPTY
void ifDeckIsEmptyShuffleAndAddToDeck(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 1: If the deck is empty, cards should be shuffled and added back to deck\n");
  printf("The deck count should be greater than 0\n");
  emptyDeckIntoPlayedCards(state);
  cardEffect(adventurer, -1, -1, -1, state, 0, 0);
  assertTrueForGreaterThan(testState, state->deckCount[0], 0);
  printf("---------------------------------------------\n\n");
}

//CHECKING WRONG CARD FOR CARDDRAWN
//NOT DISCARDING ADVENTURER
//INFINITE LOOP DUE TO CHECKING WRONG CARD - NEVER DISCARDS
//WILL NEVER CHECK COPPER, SILVER, GOLD
void drawsTreasureCardTwice(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 2: If the player draws copper cards, they are added to their hand\n");
  setPlayerDeckToCard(state, copper);
  state->deck[0][1] = silver;
  state->deck[0][2] = gold;
  cardEffect(adventurer, -1, -1, -1, state, 0, 0);
  printf("Should discard adventurer, draw two treasures, resulting in 6 cards in hand\n");
  assertTrueForIntComparison(testState, 6, state->handCount[0]);
  printf("Should have treasure_map, copper, outpost, 27, copper, copper in hand\n");
  int expectedCards[6] = { treasure_map, copper, outpost, 27, copper, copper };
  assertTrueForIntArrayComparison(testState, expectedCards, 6, state->hand[0], state->handCount[0]);
  printf("Should only have discarded adventurer, no temp cards to discard\n");
  assertTrueForIntComparison(testState, 1, state->discardCount[0]);
  printf("Discard pile should hold adventurer\n");
  int expectedDiscard[1] = { adventurer };
  assertTrueForIntArrayComparison(testState, expectedDiscard, 1, state->discard[0], state->discardCount[0]);
  printf("---------------------------------------------\n\n");
}

//DOESN'T HANDLE IF ONLY ONE TREASURE
void onlyOneTreasureCardInDeck(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 3: If the deck only has one treasure then it should not shuffle again and only get one treasure\n");
  setPlayerDeckToCard(state, estate);
  state->deck[0][0] = copper;
  cardEffect(adventurer, -1, -1, -1, state, 0, 0);
  printf("Should stop searching after deck is empty and keep one treasure\n");
  printf("Should discard adventurer, draw one treasure, resulting in 5 cards\n");
  assertTrueForIntComparison(testState, 5, state->handCount[0]);
  printf("Should have treasure_map, copper, outpost, 27, copper in hand\n");
  int expectedCards[6] = { treasure_map, copper, outpost, 27, copper };
  assertTrueForIntArrayComparison(testState, expectedCards, 5, state->hand[0], state->handCount[0]);
  printf("---------------------------------------------\n\n");
}

void drawsNonTreasureCardsFirst(struct gameState *state, struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("TEST 4: If the player draws two non-treasure cards and then two treasure cards, the temp hand should discard twice\n");
  state->deckCount[0] = 10;
  setPlayerDeckToCard(state, estate);
  state->deck[0][0] = copper;
  state->deck[0][1] = copper;
  cardEffect(adventurer, -1, -1, -1, state, 0, 0);
  printf("Discard pile should have estate, estate, estate, estate, estate, estate, estate, estate, adventurer\n");
  int expectedCards[9] = { estate, estate, estate, estate, estate, estate, estate, estate, adventurer };
  assertTrueForIntArrayComparison(testState, expectedCards, 9, state->discard[0], state->discardCount[0]);
  printf("Discard pile should have 9 cards\n");
  assertTrueForIntComparison(testState, 9, state->discardCount[0]);
  printf("---------------------------------------------\n\n");
}

int main() {
  printf("*********************************************\n");
  printf("cardtest3.c\n");
  printf("Testing adventurer card from cardEffect function in dominion.c\n");
  printf("---------------------------------------------\n\n");

  struct gameState testGameState;
  struct TestState testState = *setUpTestSuite();

  setUpBeforeEachTest(&testGameState);
  ifDeckIsEmptyShuffleAndAddToDeck(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  drawsTreasureCardTwice(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  onlyOneTreasureCardInDeck(&testGameState, &testState);

  setUpBeforeEachTest(&testGameState);
  drawsNonTreasureCardsFirst(&testGameState, &testState);

  printTotalsOfPassFailTests(&testState);

  printf("*********************************************\n");
  return 0;
}