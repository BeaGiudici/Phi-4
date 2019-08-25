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
<<<<<<< HEAD
 *   bool MolDyn(double tau)
=======
 *   void MolDyn(double tau)
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
 *        Performs the molecular dynamics for one trajectory
 *   
 *  AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
 *  CREATED: 23/05/2019
 *  MODIFIED: 10/08/2019
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
<<<<<<< HEAD
     double H_in, r[1], dH;
=======
     double H_in, H_fin, r[1], dH;
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4

     /*Saving the initial values of the field*/
     for (i = 0; i < V; i++)
     {
          phi_in[i] = phi[i];
     }

     /*Molecular dynamics*/
     momentum_init(); /*Inizializing the momenta*/
<<<<<<< HEAD

     H_in = hamiltonian();
=======
     H_in = hamiltonian();

>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     for (i = 0; i < hmc_params.nstep; i++)
     {
          up_momentum(tau * 0.5);
          up_field(tau);
          up_momentum(tau * 0.5);
     }

<<<<<<< HEAD
     dH = hamiltonian() - H_in;

     if (deltaH != NULL)
     {
          *deltaH = dH;
     }

     /*Accept / Reject*/
     
     ranlxd(r, 1);
     if (dH > 0 && exp(-1. * dH) < r[0])
     {
          for (i = 0; i < V; i++)
          {
               phi[i] = phi_in[i];
          }
          accept = false;
     }
     
=======
     H_fin = hamiltonian();
     dH = H_fin - H_in;
     if (deltaH != NULL)
          *deltaH = dH;

     /*Accept / Reject*/
     if (dH > 0)
     {
          ranlxd(r, 1);
          if (exp(-1 * dH) < r[0])
          {
               accept = false;
               for (i = 0; i < V; i++)
               {
                    phi[i] = phi_in[i];
               }
          }
     }

>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     return accept;
}
