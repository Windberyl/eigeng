#include <math.h>
#include <float.h> /* for DBL_EPSILON */
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#ifndef REAL
#define REAL double
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef ZERO
#define ZERO 0.
#endif

#ifndef ONE
#define ONE 1.
#endif

#ifndef TWO
#define TWO 2.
#endif

#ifndef VEKTOR
#define VEKTOR 0
#endif

#ifndef MACH_EPS
#define MACH_EPS DBL_EPSILON
#endif

#ifndef ABS
#define ABS(x) (((x) >= 0.) ? (x) : -(x))
#endif

#ifndef SQRT
#define SQRT(x) sqrt(x)
#endif

#ifndef SQR
#define SQR(x) ((x) * (x))
#endif

#ifndef SWAP
#define SWAP(typ, a, b) \
    {                   \
        typ t;          \
        t = (a);        \
        (a) = (b);      \
        (b) = t;        \
    }
#endif

#ifndef BASIS
#define BASIS basis()
#endif

#ifndef VMBLOCK
#define VMBLOCK
typedef struct
{
    int n, max;
    REAL *mem;
} vmblock_t;
#endif

#ifndef EIGEN
#define EIGEN
extern int n_eigeng(double *_a, int n, double *evalr, double *evali, double *_evec);
#endif