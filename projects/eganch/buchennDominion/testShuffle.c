#include "dominion.h"
#include "myTestSuite.h"
#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <stdlib.h>

//int compare(const int* a, const int* b);

int main () {
  struct gameState G;
  struct gameState G2;

  // Initialize G.
  int k[10] = {adventurer, gardens, embargo, village, minion, salvager, cutpurse,
               sea_hag, tribute, smithy};

  //Intialize unmutable gamestate
  memset(&G, 'z', sizeof(struct gameState));
  initializeGame(2, k, 30, &G);
  memcpy (&G2, &G, sizeof(struct gameState));

  int ret = shuffle(0,&G);

  if (G.deckCount[0] > 0) {
    asserttrue((ret != -1));
    
    qsort ((void*)(G.deck[0]), G.deckCount[0], sizeof(int), compare);
    qsort ((void*)(G2.deck[0]), G2.deckCount[0], sizeof(int), compare);    
  } else
    asserttrue(ret == -1);
  int result = memcmp(&G, &G2, sizeof(struct gameState));
  printf("memcmp results = %d", result);

  asserttrue((memcmp(&G, &G2, sizeof(struct gameState)) == 0));

}
