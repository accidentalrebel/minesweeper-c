#include <STDIO.H>
#include <DOS.H>
#include "SRC/MINESWPR.H"

int main(){
  unsigned int i;
  
  unsigned int startX = (screenWidth / 2) - (boardWidth / 2);
  unsigned int startY = (screenHeight / 2) - (boardHeight / 2);

  /* Draw the back board */
  for ( i = 0 ; i < boardHeight ; i++ ) {
    placeCharAt('=', startX - 1, startY + i, boardWidth + 2);
  }
  
  /* Draw the actual board */
  for ( i = 0 ; i < boardHeight ; i++ ) {
    placeCharAt('X', startX, startY + i, boardWidth);
  }
  return 0;
}
