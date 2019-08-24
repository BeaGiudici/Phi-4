/*******************************************************************************
*
* File leap_frog.c
*
* This program implements the leap frog algorithm, computing the initial and
* final Hamiltonian
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 23/05/2019
* MODIFIED: 29/05/2019
*
*******************************************************************************/

#define CONTROL

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lattice.h"
#include "utility.h"
#include "ranlxd.h"
#include "extras.h"

int main(int argc, char *argv[])
{
    /*Declaring the variables */
    int i;       /*Counter*/
    double dTAU; /*Infinitesimal time interval*/
    double phi_in[V];
    double H_in, H_fin, deltaH, d_field = 0, max_d = 0;
    if (argc != 2)
    {
        fprintf(stderr, "Number of arguments not correct\n");
        fprintf(stderr, "Usage: %s <infile> \n", argv[0]);
        exit(1);
    }

    /*Reading the parameters*/
    read_input(argv[1]);
    rlxd_init(1, seed);

    hopping(hop);

    /*Exctracting the fields as random number between 0 and 1*/
    ranlxd(phi, V);

    /*Inizializing the momenta*/
    momentum_init();

    /*Saving the initial values of the field*/
    for (i = 0; i < V; i++)
    {
        phi_in[i] = phi[i];
    }

    dTAU = (double)hmc_params.tlength / hmc_params.nstep;
    H_in = hamiltonian();

    /*First leap frog*/
    for (i = 0; i < hmc_params.nstep; i++)
    {
        up_momentum(dTAU * 0.5);
        up_field(dTAU);
        up_momentum(dTAU * 0.5);
    }

    H_fin = hamiltonian();
    deltaH = H_fin - H_in;

    /*Printing the results*/
    fprintf(stdout, "Initial Hamiltonian: %f\n", H_in);
    fprintf(stdout, "Final Hamiltonian: %f\n", H_fin);
    fprintf(stdout, "Delta Hamiltonian: %f\n", deltaH);
    fprintf(stdout, "\n");

    /*Checking if the algorithm is right, using reversibility condition*/

    /*Flipping the momenta*/
    for (i = 0; i < V; i++)
    {
        momentum[i] = -1. * momentum[i];
    }

    /*Second leap frog*/
    for (i = 0; i < hmc_params.nstep; i++)
    {
        up_momentum(dTAU * 0.5);
        up_field(dTAU);
        up_momentum(dTAU * 0.5);
    }

    /*Evaluating the distance between fields and momenta*/
    for (i = 0; i < V; i++)
    {
        d_field += fabs(phi[i] - phi_in[i]) / V;
        if (fabs(phi[i] - phi_in[i]) > max_d)
        {
            max_d = fabs(phi[i] - phi_in[i]);
        }
    }

    fprintf(stdout, "Distance as the mean value: %e\n", d_field);
    fprintf(stdout, "Distance as the maximum: %e\n", max_d);
    fprintf(stdout, "Final difference between Hamiltonians: %e\n", fabs(hamiltonian() - H_in));

    return 0;
}