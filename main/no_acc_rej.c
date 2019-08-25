/*******************************************************************************
*
* File no_acc_rej.c
*
* This program uses the hybrid Monte Carlo, without the accept/reject algorithm,
* in order to compute the magnetization; this will be compared with the same
* quantity calculated with hybrid_MC.c (that uses the accept/reject algorithm)
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 01/06/2019
* MODIFIED: 24/08/2019
*
*******************************************************************************/

#define CONTROL

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "lattice.h"
#include "utility.h"
#include "ranlxd.h"
#include "extras.h"

#define DBIN 1000 /*Length of one bin*/

int main(int argc, char *argv[])
{
     /*Declaring the variables */
     int i, j, k; /*Counters*/
     double dTAU; /*Infinitesimal time interval*/
     double *mag2, mean_m2 = 0.0, err_m2, mean2_m2 = 0.0;
     double *mag, mean_m = 0.0, err_m, mean2_m = 0.0;

     int nBin; /*Number of bins after the rebinning*/

     /*See if the right number of argument is passed in the command line*/
     if (argc != 2)
     {
          fprintf(stderr, "Number of arguments not correct\n");
          fprintf(stderr, "Usage: %s <infile> \n", argv[0]);
          exit(1);
     }

     /*Reading the parameters*/
     read_input(argv[1]);

     /*Initializing the generator of random numbers and the matrix hop[][]*/
     rlxd_init(1, seed);
     hopping(hop);

     dTAU = (double)hmc_params.tlength / hmc_params.nstep;
     nBin = hmc_params.ntraj / DBIN;

     /*Initializing the rebinned vector*/

     mag = malloc(nBin * sizeof(double));
     mag2 = malloc(nBin * sizeof(double));

     thermalization(dTAU);

     /*Setting to zero the counter used for the rebinning */
     k = 0;

     for (j = 0; j < nBin; j++)
     {
          /*Setting to zero the entries in order to sum over later*/
          mag[j] = 0.0;
          mag2[j] = 0.0;

          for (k = 0; k < DBIN; k++)
          {

               /*Molecular dynamics*/
               momentum_init(); /*Inizializing the momenta*/

               for (i = 0; i < hmc_params.nstep; i++)
               {
                    up_momentum(dTAU * 0.5);
                    up_field(dTAU);
                    up_momentum(dTAU * 0.5);
               }

               /*Saving the measurements*/
               mag[j] += fabs(magnetization() / V) / DBIN;
               mag2[j] += (magnetization() * magnetization() / (V * V)) / DBIN;
          }
          /*Computing the means and the means of the squares*/
          mean_m += mag[j] / nBin;
          mean_m2 += mag2[j] / nBin;
          mean2_m += mag[j] * mag[j] / nBin;
          mean2_m2 += mag2[j] * mag2[j] / nBin;
     }

     /*Computing the errors*/
     err_m = sqrt((mean2_m - mean_m * mean_m) / nBin);
     err_m2 = sqrt((mean2_m2 - mean_m2 * mean_m2) / nBin);

     /*Printing all the results (this particular formatting is useful to write 
     the .json file in the final simulation)*/
     fprintf(stdout, "\t\"L\" : %i,\n", L);
     fprintf(stdout, "\t\"nStep\" : %i,\n", hmc_params.nstep);
     fprintf(stdout, "\t\"magnetization\" : {\"val\" : %f, \"err\" : %f},\n", mean_m, err_m);
     fprintf(stdout, "\t\"mag_sq\" : {\"val\" : %f, \"err\" : %f},\n", mean_m2, err_m2);

     return 0;
}
