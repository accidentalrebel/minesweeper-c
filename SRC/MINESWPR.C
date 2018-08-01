#include <STDIO.H>
#include <DOS.H>
#include "SRC/MINESWPR.H"
#include "SRC/LIB/POWERKIT/POWERKIT.H"

int main(){
  testAssembly();
  testGfx();
  return 0;
}

void testAssembly() {
  union REGS in, out;
  in.h.ah = 0x2;
  in.h.dl = 0x42;
  intdos(&in, &out);
  printf("\nCharacter: %d\n", out.h.al);
}
