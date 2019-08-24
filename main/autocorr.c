/********************************************************************
*
* File autocorr.c
*
* Study of the autocorrelation function for the magnetization
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 16/06/2019
* MODIFIED: 10/08/2019
*
********************************************************************/

#define CONTROL

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lattice.h"
#include "utility.h"
#include "ranlxd.h"
#include "extras.h"

#define N_MAX 1500

int main(int argc, char *argv[])
{
     /*Declaring the variables */
     double *mag, *gamma, mean = 0.0, mean2 = 0.0;
     double dTAU; /*Infinitesimal time interval*/
     int i, j;
     FILE *file;

     if (argc != 3)
     {
          fprintf(stderr, "Number of arguments not correct\n");
          fprintf(stderr, "Usage: %s <infile> <outfile>\n", argv[0]);
          exit(1);
     }

     /*Reading the parameters*/
     read_input(argv[1]);

     rlxd_init(1, seed);
     hopping(hop);

     dTAU = (double)hmc_params.tlength / hmc_params.nstep;

     /*Initializing the vectors*/
     mag = malloc(hmc_params.ntraj * sizeof(double));
     gamma = malloc(N_MAX * sizeof(double));

     thermalization(dTAU);

     for (j = 0; j < hmc_params.ntraj; j++)
     {
          MolDyn(dTAU, NULL);

          /*Collecting the values of the magnetization, its mean and the mean 
          of its squares in order to evaluate the autocorrelation function */
          mag[j] = magnetization();
          mean += mag[j] / hmc_params.ntraj;
          mean2 += mag[j] * mag[j] / hmc_params.ntraj;
     }

     /*Autocorrelation function*/
     for (i = 0; i < N_MAX; i++)
     {
          gamma[i] = 0.0;
          for (j = 0; j < hmc_params.ntraj - N_MAX; j++)
          {
               gamma[i] += (mag[j] * mag[j + i] - mean * mean) / (mean2 - mean * mean);
          }
          gamma[i] /= (hmc_params.ntraj - N_MAX);
     }

     /*Writing the results on a file */
     file = fopen(argv[2], "w");
     for (i = 0; i < N_MAX; i++)
     {
          fprintf(file, "%d %f\n", i, gamma[i]);
     }
     fclose(file);

     fprintf(stderr, "The output file has been written.\n");

     return 0;
}