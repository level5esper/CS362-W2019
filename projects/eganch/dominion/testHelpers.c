#include "testHelpers.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

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

//Set up first player's hand
void setFirstPlayerHand(struct gameState *testGameState, int cards[]) {
  for (int i = 0; i < 5; i++) {
    testGameState->hand[0][i] = cards[i];
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