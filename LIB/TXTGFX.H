#ifndef TXTGFX_H
#define TXTGFX_H

void placeCharAt(char, unsigned int, unsigned int, unsigned int, unsigned int);
void placeCursorAt(unsigned int, unsigned int);
unsigned int getCharAt(unsigned int x, unsigned int y);
unsigned int getColorAt(unsigned int x, unsigned int y);
  
#endif
