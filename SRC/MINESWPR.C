#include <STDIO.H>
#include <DOS.H>
#include "SRC/MINESWPR.H"

int main(){
  unsigned int i, result;
  
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

  result = xorshift32(1);
  printf("\nResult 1: %d", result);
  result = xorshift32(result);
  printf("\nResult 2: %d", result);
  
  return 0;
}
