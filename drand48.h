#ifndef _DRAND48_H__
#define _DRAND48_H__

#include <math.h>
#include <stdlib.h>

void _dorand48(unsigned short[3]);

void
_dorand48(unsigned short xseed[3]);

double
_erand48(unsigned short xseed[3]);

void
srand48(long seed);

long
lrand48(void);

double
drand48(void);

#endif // _DRAND48_H__