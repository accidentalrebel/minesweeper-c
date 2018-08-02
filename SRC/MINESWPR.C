#include <STDIO.H>
#include <DOS.H>
#include "SRC/MINESWPR.H"

int main(){
  unsigned int i;
  unsigned int result;
  unsigned int currentSeed;
  
  unsigned int startX = (screenWidth / 2) - (boardWidth / 2);
  unsigned int startY = (screenHeight / 2) - (boardHeight / 2);

  /* Draw the back board */
  for ( i = 0 ; i < boardHeight + 2 ; i++ ) {
    placeCharAt(0xF0, 0x30, startX - 1, startY + i - 1, boardWidth + 2);
  }
  
  /* Draw the actual board */
  for ( i = 0 ; i < boardHeight ; i++ ) {
    placeCharAt(0xF9, 0x43, startX, startY + i, boardWidth);
  }

  currentSeed = 47776;
  for ( i = 0 ; i < 10 ; i++ ) {
    result = random(currentSeed);
    printf("\nResult %d: %u", i, result);
  }

  /* Generates 15008 */

  result = xorShift32(323232);
  printf("\nResult 1: %u", result);
  result = xorShift32(result);
  printf("\nResult 2: %u", result);
  result = xorShift32(result);
  printf("\nResult 3: %u", result);
  result = xorShift32(result);
  printf("\nResult 4: %u", result);
  result = xorShift32(result);
  printf("\nResult 5: %u", result);
  
  return 0;
}
