#include "testHelpers.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Set up test suite
struct TestState *setUpTestSuite() {
  struct TestState *testState = malloc(sizeof(struct TestState));
  testState->passedTests = 0;
  testState->failedTests = 0;
  return testState;
}

//Set up game state
void setUpGameState(struct gameState *testGameState) {
  // Set up the game with standard inputs and cards
  int numPlayers = 2;
  int kingdomCards[10] = { adventurer, gardens,  embargo, village, minion,
    mine, cutpurse, sea_hag, tribute, smithy };
  int randomSeed = 1000;
  initializeGame(numPlayers, kingdomCards, randomSeed, testGameState);
}

//Clear game state and reinitialize
void resetGameState(struct gameState *testGameState) {
  memset(testGameState, 23, sizeof(struct gameState));
  setUpGameState(testGameState);
}

//Set up player's hand
void setPlayerHand(struct gameState *testGameState, int player, int cards[], int numCards) {
  for (int i = 0; i < numCards; i++) {
    testGameState->hand[player][i] = cards[i];
  }
}

//Returns true or false based on whether expected matches actual
void assertTrueForIntComparison(struct TestState *testState, int expected, int actual) {
  printf("Expected: %d          Actual: %d\n", expected, actual);
  if (expected == actual) {
    printf("TEST PASSED\n\n");
    incrementPassedTests(testState);
  } else {
    printf("TEST FAILED\n\n");
    incrementFailedTests(testState);
  }
}

//Returns true or false based on whether expected array matches actual
void assertTrueForIntArrayComparison(struct TestState *testState, int expected[], int expectedLength, int actual[], int actualLength) {
  printf("Expected: ");
  for (int i = 0; i < expectedLength; i++) {
    printf("%d, ", expected[i]);
  }
  printf("Actual: ");
  for (int i = 0; i < actualLength; i++) {
    printf("%d, ", actual[i]);
  }
  printf("\n");

  bool arraysMatch = true;

  if (expectedLength != actualLength) {
    arraysMatch = false;
  } else {
    for (int i = 0; i < expectedLength; i++) {
      if (expected[i] != actual[i]) {
        arraysMatch = false;
      }
    }
  }
  if (arraysMatch == true) {
    printf("TEST PASSED\n\n");
    incrementPassedTests(testState);
  } else {
    printf("TEST FAILED\n\n");
    incrementFailedTests(testState);
  }
}

//Return true or false based on whether the array holds a card
void assertTrueForArrayHoldingCardValue(struct TestState *testState, int testArray[], int testArrayLength, int cardValue) {
  bool cardValueFound = false;

  printf("CARDS:\n");
  for (int i = 0; i < testArrayLength; i++) {
    printf("%d\n", testArray[i]);
    if (testArray[i] == cardValue) {
      cardValueFound = true;
    }
  }

  if (cardValueFound == true) {
    printf("TEST PASSED\n\n");
    incrementPassedTests(testState);
  }
  else {
    printf("TEST FAILED\n\n");
    incrementFailedTests(testState);
  }
}

//Return true or false based on whether the array does not hold any card value
void assertTrueForArrayNotHoldingCardValue(struct TestState *testState, int testArray[], int testArrayLength, int cardValue) {
  bool cardValueFound = false;

  printf("CARDS:\n");
  for (int i = 0; i < testArrayLength; i++) {
    printf("%d\n", testArray[i]);
    if (testArray[i] == cardValue) {
      cardValueFound = true;
    }
  }

  if (cardValueFound == false) {
    printf("TEST PASSED\n\n");
    incrementPassedTests(testState);
  } else {
    printf("TEST FAILED\n\n");
    incrementFailedTests(testState);
  }
}

//Tracks number of failed tests
void incrementFailedTests(struct TestState *testState) {
  testState->failedTests++;
}

//Tracks number of passed tests
void incrementPassedTests(struct TestState *testState) {
  testState->passedTests++;
}

//Prints number of tests that passed or failed
void printTotalsOfPassFailTests(struct TestState *testState) {
  printf("---------------------------------------------\n");
  printf("STATUS OF TESTS\n");
  printf("Total passing tests: %d\n", testState->passedTests);
  printf("Total failing tests: %d\n", testState->failedTests);
  printf("---------------------------------------------\n");
}

//Reset counters for passed/failed tests
void resetTestCounters(struct TestState *testState) {
  testState->failedTests = 0;
  testState->passedTests = 0;
}

//Empty the player's deck and move into played cards (used to test an empty deck)
void emptyDeckIntoPlayedCards(struct gameState *state) {
  int deckSize = state->deckCount[0];
  for (int i = 0; i < deckSize; i++) {
    state->playedCards[i] = state->deck[0][state->deckCount[0]];
    state->deck[0][state->deckCount[0]] = -1;
    state->deckCount[0]--;
    state->playedCardCount++;
  }
}

//Set the player's deck to a certain card
void setPlayerDeckToCard(struct gameState *state, int card) {
  for (int i = 0; i < state->deckCount[0]; i++) {
    state->deck[0][i] = card;
  }
}

//Compare two values and return true if test value is greater than compare value
void assertTrueForGreaterThan(struct TestState *testState, int testValue, int compareValue) {
  printf("%d > %d\n", testValue, compareValue);
  if (testValue > compareValue) {
    printf("TEST PASSED\n\n");
    incrementPassedTests(testState);
  }
  else {
    printf("TEST FAILED\n\n");
    incrementFailedTests(testState);
  }
}