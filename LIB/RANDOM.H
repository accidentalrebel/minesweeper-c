#ifndef RANDOM_H
#define RANDOM_H

unsigned long getInitialSeed();
unsigned int xorShift(unsigned int);
unsigned int random(unsigned long *);
unsigned int randomRange(unsigned long *, unsigned int, unsigned int);
unsigned long xorShiftLong(unsigned long);

#endif
