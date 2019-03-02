#ifndef _TESTHELPERS_H
#define _TESTHELPERS_H

#include "dominion.h"
#include <stdbool.h>

#define TEST_DEBUG 0

struct TestState {
  int passedTests;
  int failedTests;
};

//Set up test suite
struct TestState *setUpTestSuite();

//Set up game state
int setUpGameState(struct gameState *gameState, int fixedCard);

//Set up first player's hand
void setPlayerHand(struct gameState *testGameState, int player, int cards[], int numCards);

//Returns true or false based on whether expected matches actual
bool assertTrueForIntComparison(struct TestState *testState, int expected, int actual);

//Returns true or false based on whether expected array matches actual
void assertTrueForIntArrayComparison(struct TestState *testState, int expected[], int expectedLength, int actual[], int actualLength);

//Return true or false based on whether the array does not hold a card value
void assertTrueForArrayNotHoldingCardValue(struct TestState *testState, int testArray[], int testArrayLength, int cardValue);

//Return true or false based on whether the array holds a card
bool assertTrueForArrayHoldingCardValue(struct TestState *testState, int testArray[], int testArrayLength, int cardValue);

//Tracks number of failed tests
void incrementFailedTests(struct TestState *testState);

//Tracks number of passed tests
void incrementPassedTests(struct TestState *testState);

//Prints number of tests that passed or failed
void printTotalsOfPassFailTests(struct TestState *testState);

//Reset counters for passed/failed tests
void resetTestCounters(struct TestState *testState);

//Empty the player's deck and move into played cards (used to test an empty deck)
void emptyDeckIntoPlayedCards(struct gameState *state);

//Set the player's deck to a certain card
void setPlayerDeckToCard(struct gameState *state, int card);

//Compare two values and return true if test value is greater than compare value
bool assertTrueForGreaterThan(struct TestState *testState, int testValue, int compareValue);

#endif // !_TESTHELPERS_H