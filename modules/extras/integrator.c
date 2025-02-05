/*******************************************************************************
 * 
 * File integrator.c
 * 
 * Ensemble of function for the molecular dynamics
 * 
 * The externally accessible functions are
 *
 *   double force(int i)
 *        This function finds the force given by Hamilton equations
 * 
 *   void up_field(double tau)
 *        Update of the field during leap frog integration, given the length
 *        of the step, tau
 * 
 *   void up_momentum(double tau)
 *        Update of the momentum during leap frog integration, given the length
 *        of the step, tau
 *   
 *   bool MolDyn(double tau)
 *        Performs the molecular dynamics for one trajectory
 *   
 *  AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
 *  CREATED: 23/05/2019
 *  
*******************************************************************************/

#define CONTROL

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "lattice.h"
#include "ranlxd.h"
#include "utility.h"
#include "extras.h"

double force(int i)
{
     double phi_pos = 0, phi_neg = 0, F = 0;
     double kappa = act_params.kappa;
     double lambda = act_params.lambda;
     int mu;

     /*Summing all the fileds in positive and negative directions*/
     for (mu = 0; mu < D; mu++)
     {
          phi_pos += phi[hop[i][mu]];
          phi_neg += phi[hop[i][mu + D]];
     }
     F = -2. * kappa * (phi_pos + phi_neg) + 2. * phi[i] + 4. * lambda * phi[i] * (phi[i] * phi[i] - 1.);
     return F;
}

void up_field(double tau)
{
     int i;

     for (i = 0; i < V; i++)
     {
          phi[i] = phi[i] + momentum[i] * tau;
     }
}

void up_momentum(double tau)
{
     int i;

     for (i = 0; i < V; i++)
     {
          momentum[i] = momentum[i] - tau * force(i);
     }
}

bool MolDyn(double tau, double *deltaH)
{
     int i;
     bool accept = true;
     double phi_in[V];
     double H_in, r[1], dH;

     /*Saving the initial values of the field*/
     for (i = 0; i < V; i++)
     {
          phi_in[i] = phi[i];
     }

     /*Molecular dynamics*/
     momentum_init(); /*Inizializing the momenta*/

     H_in = hamiltonian();
     for (i = 0; i < hmc_params.nstep; i++)
     {
          up_momentum(tau * 0.5);
          up_field(tau);
          up_momentum(tau * 0.5);
     }

     dH = hamiltonian() - H_in;

     /*If a pointer is passes as argument, the value of dH is assigned to the pointed variable*/
     if (deltaH != NULL)
     {
          *deltaH = dH;
     }

     /*Accept / Reject*/

     ranlxd(r, 1);
     /*If dH > 0 or, if dH < 0, exp(-dH) > r, the new configuration is accepted*/
     if (exp(-1. * dH) < r[0])
     {
          for (i = 0; i < V; i++)
          {
               phi[i] = phi_in[i];
          }
          accept = false;
     }

     return accept;
}
