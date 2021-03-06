#include <STDIO.H>
#include <DOS.H>
#include "LIB/RANDOM.H"

/* Returns from 1 to 100 */
unsigned int random(unsigned long *seed)
{
  unsigned long max = 0;
  unsigned long random = xorShiftLong(*seed);
  float computation = 0;

  if ( random != NULL && random != 0 ) {
    *seed = random;
  }
  /*printf("\nSeed: %u", *seed);*/
  
  max = max - 1; /* We get the highest capacity of the variable */
  computation = (float)random / max;
  computation = computation * 100;
  
  return computation;
}

/*
  randomRange(132416, 50, 75);
 */
unsigned int randomRange(unsigned long *seed, unsigned int min, unsigned int max)
{
  unsigned int num, range;

  num = random(seed);
  range = max - min;
  
  return min + ((num * range) / 100);
}

unsigned long xorShiftLong(unsigned long x)
{
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}

unsigned long getInitialSeed()
{
  union REGS in, out;
  unsigned long initialSeed;
 
  in.h.ah = 0x2c;
  intdos(&in, &out);

  initialSeed = (out.h.cl + 1) * (out.h.cl + 1) * (out.h.dh + 1)  * (out.h.dl + 1) * 10000;

  return initialSeed;
}
