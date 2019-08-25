#ifndef UTILITY_H
#define UTILITY_H
#include <stdio.h>
#include <string.h>
#include "lattice.h"
#include <math.h>

#ifndef READING_C
int get_val(FILE *fp, char *str, char *fmt, void *val);
int read_input(char *input);
#endif

#ifndef HOPPING_C
void hopping(int h[V][2 * D]);
#endif

#ifndef JACKKNIFE_C
extern void clustering(double *x, double mean, int N);
extern double error_jack(double *x, double mean, int N);
#endif

#endif