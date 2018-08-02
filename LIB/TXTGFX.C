#include <STDIO.H>
#include <DOS.H>
#include "LIB/TXTGFX.H"

void placeCharAt(char c, unsigned int color, unsigned int x, unsigned int y, unsigned int num) {
  union REGS in, out;
  
  placeCursorAt(x, y);

  in.h.ah = 0x9;
  in.h.al = c;
  in.h.bh = 0x0;
  in.h.bl = color;
  in.x.cx = num;
  int86(0x10, &in, &out);
}

void placeCursorAt(unsigned int x, unsigned int y) {
  union REGS in, out;
  
  in.h.ah = 0x2;
  in.x.bx = 0x0;
  in.h.dl = x;
  in.h.dh = y;
  int86(0x10, &in, &out);
}
