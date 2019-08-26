/*******************************************************************************
*
* File thermalization.c
*
* This code studies the thermalization of the Markov chain with a 
* cold or a hot start
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 30/05/2019
*
*******************************************************************************/

#define CONTROL

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "lattice.h"
#include "utility.h"
#include "ranlxd.h"
#include "extras.h"

int main(int argc, char *argv[])
{
<<<<<<< HEAD
     /*Declaring the variables */
=======

>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     int i;       /*Counters*/
     double dTAU; /*Infinitesimal time interval*/
     double r[V];
     double S;
<<<<<<< HEAD
     FILE *file;

     /*See if the right number of argument is passed in the command line*/
=======
     FILE *file1;

>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     if (argc != 2)
     {
          fprintf(stderr, "Number of arguments not correct\n");
          fprintf(stderr, "Usage: %s <infile> \n", argv[0]);
          exit(1);
     }

     /*Reading the parameters*/
     read_input(argv[1]);

<<<<<<< HEAD
     /*Initializing the generator of random numbers and the matrix hop[][]*/
=======
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     rlxd_init(1, seed);
     hopping(hop);

     dTAU = (double)hmc_params.tlength / hmc_params.nstep;

<<<<<<< HEAD
     /*Cold start: setting to zero the initial values of the field*/
=======
     /*Cold start*/
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     for (i = 0; i < V; i++)
     {
          phi[i] = 0.0;
     }

<<<<<<< HEAD
     file = fopen("../results/action_cold.dat", "w");
     for (i = 0; i < hmc_params.ntraj; i++)
     {
          S = action();
          fprintf(file, "%f\n", S);
          MolDyn(dTAU, NULL);
     }
     fclose(file);
     fprintf(stderr, "The file 'action_cold.dat' has been created in the directory 'results'.\n");

     /*Hot start: the initial values are generated random in the interval [-7.5, 7.5)*/
     ranlxd(r, V);
     for (i = 0; i < V; i++)
     {
          phi[i] = (double)7.5 * (r[i] - 0.5);
     }

     file = fopen("../results/action_hot.dat", "w");
     for (i = 0; i < hmc_params.ntraj; i++)
     {
          S = action();
          fprintf(file, "%f\n", S);
          MolDyn(dTAU, NULL);
     }
     fclose(file);
=======
     file1 = fopen("../results/action_cold.dat", "w");
     for (i = 0; i < hmc_params.ntraj; i++)
     {
          S = action();
          fprintf(file1, "%f\n", S);
          MolDyn(dTAU, NULL);
     }
     fclose(file1);
     fprintf(stderr, "The file 'action_cold.dat' has been created in the directory 'results'.\n");

     /*Hot start*/
     ranlxd(r, V);
     for (i = 0; i < V; i++)
     { /*Initializing the entries with a random value in [-7.5,7.5)*/
          phi[i] = (double)7.5 * (r[i] - 0.5);
     }

     file1 = fopen("../results/action_hot.dat", "w");
     for (i = 0; i < hmc_params.ntraj; i++)
     {
          S = action();
          fprintf(file1, "%f\n", S);
          MolDyn(dTAU, NULL);
     }
     fclose(file1);
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     fprintf(stderr, "The file 'action_hot.dat' has been created in the directory 'results'.\n");

     return 0;
}
