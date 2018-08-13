/*
#define BOARD_WIDTH 60
#define BOARD_HEIGHT 20
*/

#define BOARD_WIDTH 5
#define BOARD_HEIGHT 5
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define STARTING_MINE_COUNT 3
#define CHAR_MINE 232
#define CHAR_BORDER 0xF0
#define CHAR_BLANK 254

struct Mine
{
  unsigned int col;
  unsigned int row;
};

void countAtPos(unsigned int, unsigned int, unsigned int, unsigned int);
void countAdjacentLines(struct Mine mine, unsigned int, unsigned int);
