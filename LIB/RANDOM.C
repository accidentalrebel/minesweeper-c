#include "LIB/RANDOM.H"

/* Returns from 1 to 100 */
unsigned int random(unsigned int *seed)
{
  unsigned int max = 0;
  unsigned int random = xorShift(*seed);
  float computation = 0;

  *seed = random;

  max = max - 1; /* We get the highest size of unsigned int */
  computation = (float)random / max;
  computation = computation * 100;
  
  return computation;
}

unsigned int xorShift(unsigned int x)
{
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}
