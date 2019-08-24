#ifndef EXTRAS_H
#define EXTRAS_H

#include "utility.h"
#include <stdbool.h>

#ifndef INITIAL_C
extern void momentum_init(void);
extern void thermalization(double tau);
#endif

#ifndef INTEGRATOR_C
extern double force(int i);
extern void up_field(double tau);
extern void up_momentum(double tau);
extern bool MolDyn(double tau, double *deltaH);
#endif

#ifndef MEASUREMENTS_C
extern double magnetization(void);
extern double magSus(double mean, double mean2);
extern double cBinder(double mean4, double mean2);
extern double action(void);
extern double hamiltonian(void);
#endif

#endif