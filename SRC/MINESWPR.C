#include <STDIO.H>
#include <DOS.H>
#include "SRC/MINESWPR.H"
#include "LIB/TXTGFX.H"
#include "LIB/RANDOM.H"

int main() {
  unsigned int i, col, row, currentChar;
  unsigned long *currentSeed = 0;
  unsigned long longSeed = 0;
  
  unsigned int startX = (screenWidth / 2) - (boardWidth / 2);
  unsigned int startY = (screenHeight / 2) - (boardHeight / 2);

  /* Flushes the background to black */
  placeCharAt(0x0, 0x0F, 0, 0, screenWidth * screenHeight);

  /* Draw the back board */
  for ( i = 0 ; i < boardHeight + 2 ; i++ ) {
    placeCharAt(0xF0, 0x30, startX - 1, startY + i - 1, boardWidth + 2);
  }

  /* Draw the actual board */
  for ( i = 0 ; i < boardHeight ; i++ ){ 
    placeCharAt(0xF9, 0x43, startX, startY + i, boardWidth);
  }

  *currentSeed = getInitialSeed();
  for ( i = 0 ; i < (boardWidth * boardHeight) ; i++ ) {

    while ( 1 ) {
      col = randomRange(currentSeed, 0, boardWidth);
      row = randomRange(currentSeed, 0, boardHeight);

      currentChar = getCharAt(startX + col, startY + row);
      if ( currentChar != '0' ) {
	placeCharAt('0', 0x03, startX + col, startY + row, 1);
	break;
      }
    }
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
