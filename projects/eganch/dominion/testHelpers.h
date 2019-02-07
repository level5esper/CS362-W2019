#ifndef _TESTHELPERS_H
#define _TESTHELPERS_H

#include "dominion.h"

struct TestState {
  int passedTests;
  int failedTests;
};

//Set up test suite
struct TestState *setUpTestSuite();

//Set up game state
void setUpGameState(struct gameState *testGameState);

//Clear game state for reset
void resetGameState(struct gameState *testGameState);

//Set up first player's hand
void setPlayerHand(struct gameState *testGameState, int player, int cards[], int numCards);

//Returns true or false based on whether expected matches actual
void assertTrueForIntComparison(struct TestState *testState, int expected, int actual);

//Returns true or false based on whether expected array matches actual
void assertTrueForIntArrayComparison(struct TestState *testState, int expected[], int expectedLength, int actual[], int actualLength);

//Tracks number of failed tests
void incrementFailedTests(struct TestState *testState);

//Tracks number of passed tests
void incrementPassedTests(struct TestState *testState);

//Prints number of tests that passed or failed
void printTotalsOfPassFailTests(struct TestState *testState);

//Reset counters for passed/failed tests
void resetTestCounters(struct TestState *testState);


#endif // !_TESTHELPERS_H
