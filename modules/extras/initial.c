/*******************************************************************************
 * 
 * File initial.c
 * 
 * Collection of functions used for initializing correctly the system
 * 
 * The externally accessible functions are
 * 
 *   void momentum_init(void)
 *        This function fills momenta array with gaussian-distributed 
 *        numbers, for every couple of values generated in [0,1)
 * 
 *   void thermalization(double tau)
 *        Thermalization of the Markov chain, implemented with accept/reject
 *        algorithm
 *   
 *  AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
 *  CREATED: 10/08/2019
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

void momentum_init(void)
{
     int i;
     double x[2];

     for (i = 0; 2 * i < V; i++)
     {
          /*The even entries are filled with the "cosine branch" of the function, while the 
     odd entries are filled with the "sine branch"*/
          ranlxd(x, 2);
          momentum[2 * i] = sqrt(-2. * log(1 - x[0])) * cos(2. * PI * (1 - x[1]));
          if (2 * i + 1 < V)
          {
               momentum[2 * i + 1] = sqrt(-2. * log(1 - x[0])) * sin(2. * PI * (1 - x[1]));
          }
     }
}

void thermalization(double tau)
{
     int i;

     /*Cold start*/
     for (i = 0; i < V; i++)
     {
          phi[i] = 0.0;
     }

     /*Thermalization*/
     for (i = 0; i < 10 * hmc_params.ntherm; i++)
     {
          MolDyn(tau, NULL);
     }
}
