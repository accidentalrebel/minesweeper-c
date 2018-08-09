#include <STDIO.H>
#include <DOS.H>
#include "LIB/MOUSE.H"

void initMouse() {
  union REGS in, out;

  /* Checks for the driver */
  
  in.x.ax = 0;
  int86(0x33, &in, &out);

  if ( out.x.ax == 0 ) {
    printf("\n\nERROR!!! Mouse driver not detected!!!");
    return;
  }

  /* Show the mouse */
  in.x.ax = 0x1;
  int86(0x33, &in, &out);
}

void setMousePos(unsigned int col, unsigned int row) {
  union REGS reg;
  
  reg.x.ax = 0x4;
  reg.x.cx = col;
  reg.x.dx = row;
  int86(0x33, &reg, &reg);
}

unsigned int getMouseButtonDown(unsigned int buttonNum) {
  union REGS in, out;

  in.x.ax = 0x5;
  in.x.bx = buttonNum;
  int86(0x33, &in, &out);

  if ( out.x.bx > 0 ) {
    printf("\nAX: %u", out.x.ax);
    printf("\nBX: %u", out.x.bx);
    printf("\nCX: %u", out.x.cx);
    printf("\nDX: %u", out.x.dx);

    if ( out.x.ax == (1 << buttonNum)) {
      return 1;
    }
  }

  return 0;
}

unsigned int getMouseButtonUp(unsigned int buttonNum) {
  union REGS in, out;

  in.x.ax = 0x6;
  in.x.bx = buttonNum;
  int86(0x33, &in, &out);

  if ( out.x.bx > 0 ) {
    printf("\nAX: %u", out.x.ax);
    printf("\nBX: %u", out.x.bx);
    printf("\nCX: %u", out.x.cx);
    printf("\nDX: %u", out.x.dx); 
    
    if ( out.x.ax == (1 << buttonNum) ) {
      return 1;
    }
  }

  return 0;
}

