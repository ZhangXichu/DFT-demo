// precompute some constants
#ifndef MACROS_H
#define MACROS_H

#include <math.h>

#define Ai(k, N) -cos(((M_PI) * (k)) / (N))
#define Ar(k, N) -sin(((M_PI) * (k)) / (N))
#define Bi(k, N) cos(((M_PI) * (k)) / (N))
#define Br(k, N) sin(((M_PI) * (k)) / (N))

#endif