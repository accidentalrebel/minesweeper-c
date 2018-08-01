#include <stdio.h>
#include <dos.h>

void test(){
  union REGS in, out;
  in.h.ah = 0x2;
  in.h.dl = 0x42;
  intdos(&in, &out);
  printf("\nCharacter: %d\n", out.h.al);
}

int main(){
  test();
  return 0;
}
