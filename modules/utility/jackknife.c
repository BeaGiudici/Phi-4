/*******************************************************************************
 * 
 * File jackknife.c
 * 
 * Jackknife method funcitons
 * 
 * The externally accessible functions are
 *  
 *   void clustering (doublw *x, double mean, int N)
 *        Cluster of the vector (of dimension N) of variables x, with 
 *        given mean value
 * 
 *   double error_jack(double *x, double mean, int N)
 *        Computing the error with jackknife technique
 *
 *  AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
 *  CREATED: 16/05/2019
 *  MODIFIED: 03/06/2019
 *  
*******************************************************************************/

#define CONTROL

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lattice.h"
#include "ranlxd.h"
#include "utility.h"
#include "extras.h"

void clustering(double *x, double mean, int N)
{
     int i;

     for (i = 0; i < N; i++)
     {
          x[i] = mean - (x[i] - mean) / (N - 1.);
     }
}

double error_jack(double *x, double mean, int N)
{
     int i;
     double err = 0.0;

     for (i = 0; i < N; i++)
     {
          err += (x[i] - mean) * (x[i] - mean) * (N - 1.) / N;
     }
     return sqrt(err);
}