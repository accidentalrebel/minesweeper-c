#include <STDIO.H>
#include <DOS.H>
#include <ALLOC.H>
#include "SRC/MINESWPR.H"
#include "LIB/TXTGFX.H"
#include "LIB/RANDOM.H"
#include "LIB/MOUSE.H"

int main() {
  unsigned int i, col, row, currentChar, currentColor;
  unsigned long *pCurrentSeed = 0;
  unsigned long currentSeed;

  struct Mine mines[startingMineCount];
  
  union REGS in, out;
  
  unsigned int startX = (screenWidth / 2) - (boardWidth / 2);
  unsigned int startY = (screenHeight / 2) - (boardHeight / 2);

  /* Initializations */
  initMouse();
  showMouseCursor();
  setMousePos(0, 0);

  changeDisplayPage(0);

  /* Flushes the display pages to black */
  placeCharAt(0x0, 0x0F, 0, 0, screenWidth * screenHeight, 0);
  placeCharAt(0x0, 0x0F, 0, 0, screenWidth * screenHeight, 1);

  /* Draw the back board */
  for ( i = 0 ; i < boardHeight + 2 ; i++ ) {
    placeCharAt(CHAR_BORDER, 0x30, startX - 1, startY + i - 1, boardWidth + 2, 0);
  }

  /* Draw the actual board */
  for ( i = 0 ; i < boardHeight ; i++ ){ 
    placeCharAt(CHAR_BLANK, 0x43, startX, startY + i, boardWidth, 0);
  }

  currentSeed = getInitialSeed();
  pCurrentSeed = &currentSeed;

  for ( i = 0 ; i < startingMineCount ; i++ ) {

    while ( 1 ) {
      col = randomRange(pCurrentSeed, 0, boardWidth);
      row = randomRange(pCurrentSeed, 0, boardHeight);
      
      mines[i].col = col;
      mines[i].row = row;

      currentChar = getCharAt(startX + col, startY + row, 1);
      if ( currentChar != CHAR_MINE ) {
 	placeCharAt(CHAR_MINE, 0x03, startX + col, startY + row, 1, 1);
	break;
      }
    }
  }

  for ( i = 0 ; i < startingMineCount; i++ ) {
    
    /* printf("Mine %u (%u, %u)", i, col, row); */
    countAdjacentLines(mines[i], startX, startY);
  }

  /*
    We are just simulating a mouse click
   */
  
  /*i = getCharAt(startX + 0, startX + 0, 1);*/

  changeDisplayPage(0);

  while (1) {
    
    if ( getMouseButtonDown(0)) {
      hideMouseCursor();
    }
    else if ( getMouseButtonUp(0)) {
      getMouseCoordinate(&col, &row);
      /*
      printf("Col: %u, Row: %u", col, row);
      */

      currentChar = getCharAt(col, row, 1);
      currentColor = getColorAt(col, row, 1);
      placeCharAt(currentChar, currentColor, col, row, 1, 0);
      showMouseCursor();

      if ( currentChar == CHAR_MINE ) {
	break;
      }
    }

    if ( getMouseButtonDown(1) ) {
      hideMouseCursor();
      changeDisplayPage(1);
    }
    else if ( getMouseButtonUp(1)) {
      changeDisplayPage(0);
      showMouseCursor();
    }

    /*
    if ( getMouseButtonUp(1)) {
      printf("RIGHT PRESSED\n");
      changeDisplayPage(1);
      break;
    }
    */
  }

  changeDisplayPage(0);
  hideMouseCursor();
  
  return 0;
}

void countAdjacentLines(struct Mine mine, unsigned int startX, unsigned int startY) {
  unsigned int col, row;

  col = mine.col;
  row = mine.row;
  
  countAtPos(col, row - 1, startX, startY);
  countAtPos(col + 1, row - 1, startX, startY);
  countAtPos(col + 1, row, startX, startY);
  countAtPos(col + 1, row + 1, startX, startY);
  countAtPos(col, row + 1, startX, startY);
  countAtPos(col - 1, row + 1, startX, startY);
  countAtPos(col - 1, row, startX, startY);
  countAtPos(col - 1, row - 1, startX, startY);
}

void countAtPos(unsigned int col, unsigned int row, unsigned int startX, unsigned int startY)
{
  unsigned int currentChar, currentColor, count;
  
  currentChar = getCharAt(startX + col, startY + row, 1);

  if ( currentChar == 0 ) {
    count = 0;
  }
  if ( (currentChar >= '0') && (currentChar <= '9') ) {
    count = currentChar - '0';
  }
  ++count;
  
  if ( currentChar != CHAR_MINE && currentChar != CHAR_BORDER ) {
    currentColor = getColorAt(startX + col, startY + row, 1);
    placeCharAt(count + '0', currentColor, startX + col, startY + row, 1, 1);    
  }
}
