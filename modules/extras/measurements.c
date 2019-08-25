/*******************************************************************************
 * 
 *  File measurements.c
 * 
 * The externally accessible functions are
 *
 *  double magnetization(void)
 *        This function returns the magnetization as the sum over the field
 *        phi[V] in all the position of the lattice.
 * 
 *  double magSus(double mean_m, double mean_m2)
 *        The funciton returns the magnetic susceptibility, for given values
 *        of the magnetization
 *  
 *  double cBinder(double mean_m4, double mean_m2)
 *        This funciton returns the Binder cumulant
 * 
 *  double hamiltonian(void)
 *        This function returns the value of the Hamiltonian for a system with
 *        a given momentum and field
 *  
 *  AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
 *  CREATED: 16/05/2019
 *  MODIFIED: 10/08/2019
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

double magnetization(void)
{
     double m = 0;
     int i;

     for (i = 0; i < V; i++)
     {
          m += phi[i];
     }
     return m;
}

double magSus(double mean, double mean2)
{
     return (mean2 - mean * mean) / V;
}

double cBinder(double mean4, double mean2)
{
     return mean4 / (mean2 * mean2);
}

double action(void)
{
     int i, mu;
     double phin, S, phi2;
     double kappa = act_params.kappa;
     double lambda = act_params.lambda;
     S = 0;

     /* loop over all sites */
     for (i = 0; i < V; i++)
     {
          /*sum over neighbors in positive direction*/
          phin = 0;
          for (mu = 0; mu < D; mu++)
          {
               phin += phi[hop[i][mu]];
          }
          phi2 = phi[i] * phi[i];
          S += -2 * kappa * phin * phi[i] + phi2 + lambda * (phi2 - 1.0) * (phi2 - 1.0);
     }
     return S;
}

double hamiltonian(void)
{
     double sum = 0, H;
     double S = action();
     int i;

     for (i = 0; i < V; ++i)
     {
          sum += momentum[i] * momentum[i];
     }
     H = sum * 0.5 + S;
     return H;
}
