#include <STDIO.H>
#include <DOS.H>
#include <ALLOC.H>
#include "SRC/MINESWPR.H"
#include "LIB/TXTGFX.H"
#include "LIB/RANDOM.H"
#include "LIB/MOUSE.H"

int main() {
  unsigned int i, col, row, currentChar, currentColor, mineCount, tilesOpenedCount;
  unsigned long currentSeed;

  struct Mine mines[STARTING_MINE_COUNT];
  struct Mine currentMine;

  union REGS in, out;
  
  unsigned int startX = (SCREEN_WIDTH / 2) - (BOARD_WIDTH / 2);
  unsigned int startY = (SCREEN_HEIGHT / 2) - (BOARD_HEIGHT / 2);

  mineCount = STARTING_MINE_COUNT;
  if ( mineCount > BOARD_WIDTH * BOARD_HEIGHT ) {
    mineCount = BOARD_WIDTH * BOARD_HEIGHT;
  }

  /* Initializations */
  tilesOpenedCount = 0;
  initMouse();
  showMouseCursor();
  setMousePos(0, 0);

  changeDisplayPage(0);

  /* Flushes the display pages to black */
  placeCharAt(0x0, 0x0F, 0, 0, SCREEN_WIDTH * SCREEN_HEIGHT, 0);
  placeCharAt(0x0, 0x0F, 0, 0, SCREEN_WIDTH * SCREEN_HEIGHT, 1);

  /* Draw the back board */
  for ( i = 0 ; i < BOARD_HEIGHT + 2 ; i++ ) {
    placeCharAt(CHAR_BORDER, 0x78, startX - 1, startY + i - 1, BOARD_WIDTH + 2, 0);
  }

  /* Draw the actual board */
  for ( i = 0 ; i < BOARD_HEIGHT ; i++ ){ 
    placeCharAt(CHAR_BLANK, 0x08, startX, startY + i, BOARD_WIDTH, 0);
  }

  currentSeed = getInitialSeed();

  for ( i = 0 ; i < mineCount ; i++ ) {

    while ( 1 ) {
      col = randomRange(&currentSeed, 0, BOARD_WIDTH);
      row = randomRange(&currentSeed, 0, BOARD_HEIGHT);
      
      mines[i].col = col;
      mines[i].row = row;

      currentChar = getCharAt(startX + col, startY + row, 1);
      if ( currentChar != CHAR_MINE ) {
 	placeCharAt(CHAR_MINE, 0x4F, startX + col, startY + row, 1, 1);
	break;
      }
    }
  }

  for ( i = 0 ; i < mineCount; i++ ) {
    countAdjacentLines(mines[i], startX, startY);
  }

  /*
    We are just simulating a mouse click
   */
  changeDisplayPage(0);

  while (1) {
    
    if ( getMouseButtonDown(0)) {
      hideMouseCursor();
    }
    else if ( getMouseButtonUp(0)) {
      getMouseCoordinate(&col, &row);

      if ( (col >= startX && col <= startX + BOARD_WIDTH - 1)
	   && (row >= startY && row <= startY + BOARD_HEIGHT - 1)) {

	currentChar = getCharAt(col, row, 0);
      	if ( currentChar == CHAR_BLANK ) {
	  ++tilesOpenedCount;
	}

	/*
	  Checks for win condition
	 */
	if ( tilesOpenedCount >= (BOARD_WIDTH * BOARD_HEIGHT) - mineCount ) {
	  changeDisplayPage(0);
	  printf("WIN CONDITION");
	  break;
	}
	
	currentChar = getCharAt(col, row, 1);
	currentColor = getColorAt(col, row, 1);
	placeCharAt(currentChar, currentColor, col, row, 1, 0);
	showMouseCursor();

	/*
	  Handles if you clicked on a mine.
	 */
	if ( currentChar == CHAR_MINE ) {
	  for ( i = 0 ; i < mineCount ; i++ ) {
	    currentMine = mines[i];
	  
	    col = currentMine.col;
	    row = currentMine.row;

	    currentChar = getCharAt(col + startX, row + startY, 1);
	    currentColor = getColorAt(col + startX, row + startY, 1);
	    placeCharAt(currentChar, currentColor, col + startX, row + startY, 1, 0);
	  }
	
	  break;
	}
	else if ( !(currentChar >= '0' && currentChar <= '9') ) {
	  floodFill(col, row, &tilesOpenedCount);
	}
      }
      else {
	showMouseCursor();
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
  }

  changeDisplayPage(0);
  hideMouseCursor();
  
  return 0;
}

int floodFillDirection(unsigned int col, unsigned int row, unsigned int * tilesOpenedCount) {
  unsigned int frontChar, backChar, currentColor, newCol, newRow;

  newCol = col;
  newRow = row;

  frontChar = getCharAt(newCol, newRow, 0);
  if ( frontChar == CHAR_BORDER || frontChar != CHAR_BLANK ) {
    return 0;
  }

  backChar = getCharAt(newCol, newRow, 1);
  currentColor = getColorAt(newCol, newRow, 1);
  placeCharAt(backChar, currentColor, newCol, newRow, 1, 0);

  ++(*tilesOpenedCount);
  
  if ( backChar >= '0' && backChar <= '9' ) {
    return 0;
  }

  floodFill(newCol, newRow, tilesOpenedCount);
}

int floodFill(unsigned int col, unsigned int row, unsigned int * tilesOpenedCount) {
  floodFillDirection(col, row - 1, tilesOpenedCount);
  floodFillDirection(col + 1, row, tilesOpenedCount);
  floodFillDirection(col, row + 1, tilesOpenedCount);
  floodFillDirection(col - 1, row, tilesOpenedCount);
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

void countAtPos(unsigned int col, unsigned int row, unsigned int startX, unsigned int startY) {
  unsigned int currentChar, currentColor, count;

  currentChar = getCharAt(startX + col, startY + row, 0);
  if ( currentChar == CHAR_BORDER ) {
    return;
  }

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
