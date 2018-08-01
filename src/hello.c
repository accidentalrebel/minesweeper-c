#include <stdio.h>
#include <dos.h>

void test()
{
  union REGS in, out;

  int oldMode;
  printf("Hello");

  in.h.ah=0xf;
  int86(0x10, &in, &out);
  oldMode=out.h.al;

  printf("OldMode: %d", oldMode);
}

int main()
{
  test();
  return 0;
}
