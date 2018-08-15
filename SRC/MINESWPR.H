/*
#define BOARD_WIDTH 60
#define BOARD_HEIGHT 20
*/

#define BOARD_WIDTH 60
#define BOARD_HEIGHT 20
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define STARTING_MINE_COUNT 150
#define CHAR_MINE 232
#define CHAR_FLAG 20
#define CHAR_BORDER 0xF0
#define CHAR_TILE 254

struct Mine
{
  unsigned int col;
  unsigned int row;
};

void countAtPos(unsigned int, unsigned int, unsigned int, unsigned int);
void countAdjacentLines(struct Mine mine, unsigned int, unsigned int);
int floodFill(unsigned int, unsigned int, unsigned int *);
int floodFillDirection(unsigned int, unsigned int, unsigned int *);
