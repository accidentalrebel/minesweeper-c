#define boardWidth 60
#define boardHeight 20
#define screenWidth 80
#define screenHeight 25
#define startingMineCount 230
#define CHAR_MINE '0'
#define CHAR_BORDER 0xF0
#define CHAR_BLANK 0xF9

struct Mine
{
  unsigned int col;
  unsigned int row;
};

void countAtPos(unsigned int, unsigned int, unsigned int, unsigned int);
void countAdjacentLines(struct Mine mine, unsigned int, unsigned int);
