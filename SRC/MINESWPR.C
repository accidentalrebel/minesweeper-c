#include <STDIO.H>
#include <DOS.H>
#include "SRC/MINESWPR.H"
#include "LIB/TXTGFX.H"
#include "LIB/RANDOM.H"

int main() {
  unsigned int i, col, row;
  unsigned long *currentSeed = 0;
  unsigned long longSeed = 0;
  
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

  *currentSeed = 3232326542301;
  for ( i = 0 ; i < 10 ; i++ ) {
    col = randomRange(currentSeed, 0, boardWidth);
    row = randomRange(currentSeed, 0, boardHeight);

    printf("\nCol: %u, Row: %u", col, row);

    placeCharAt('0', 0x03, startX + col, startY + row, 1);
    
    /*printf("%u, ", result);*/
  }

  /* Generates 15008 */

  /*
  result = xorShift(323232);
  printf("\nResult 1: %u", result);
  result = xorShift(result);
  printf("\nResult 2: %u", result);
  result = xorShift(result);
  printf("\nResult 3: %u", result);
  result = xorShift(result);
  printf("\nResult 4: %u", result);
  result = xorShift(result);
  printf("\nResult 5: %u", result);
  */
  
  return 0;
}
