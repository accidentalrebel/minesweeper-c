#include <STDIO.H>
#include <DOS.H>
#include "LIB/TXTGFX.H"

void changeDisplayPage(unsigned int pageNum)
{
  union REGS in, out;

  in.h.ah = 0x5;
  in.h.al = pageNum;
  int86(0x10, &in, &out);
}

unsigned int getCurrentDisplayPage()
{
  union REGS in, out;

  in.h.ah = 0xF;
  int86(0x10, &in, &out);

  return out.h.bh;
}

void placeCharAt(char c, unsigned int color, unsigned int x, unsigned int y, unsigned int num, unsigned int pageNum) {
  union REGS in, out;
  
  placeCursorAt(x, y, pageNum);

  in.h.ah = 0x9;
  in.h.al = c;
  in.h.bh = pageNum;
  in.h.bl = color;
  in.x.cx = num;
  int86(0x10, &in, &out);
}

void placeCursorAt(unsigned int x, unsigned int y, unsigned int pageNum) {
  union REGS in, out;
  
  in.h.ah = 0x2;
  in.h.bh = pageNum;
  in.h.dl = x;
  in.h.dh = y;
  int86(0x10, &in, &out);
}

unsigned int getCharAt(unsigned int x, unsigned int y, unsigned int pageNum) {
  union REGS in, out;

  placeCursorAt(x, y, pageNum);

  in.h.ah = 0x8;
  in.h.bh = pageNum;
  int86(0x10, &in, &out);

  return out.h.al;
}

unsigned int getColorAt(unsigned int x, unsigned int y, unsigned int pageNum) {
  union REGS in, out;

  placeCursorAt(x, y, pageNum);

  in.h.ah = 0x8;
  in.h.bh = pageNum;
  int86(0x10, &in, &out);

  return out.h.ah;
}

