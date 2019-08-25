/*******************************************************************************
*
* File symm_break.c
*
* Calculating the data for the symmetry breaking
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 13/06/2019
<<<<<<< HEAD
=======
* MODIFIED: 13/06/2019
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
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

#define DBIN 1000 /*Length of a bin*/

int main(int argc, char *argv[])
{
<<<<<<< HEAD
     /*Declaring the variables */
=======
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     int i, j, accepted, k = 0; /*Counters*/
     double dTAU;               /*Infinitesimal time interval*/
     double *mag, *mag2, *mag4;
     int nBin; /*Number of bins after the rebinning*/
     FILE *file;

     if (argc != 3)
     {
          fprintf(stderr, "Number of arguments not correct\n");
          fprintf(stderr, "Usage: %s <infile> <outfile>\n", argv[0]);
          exit(1);
     }

<<<<<<< HEAD
     /*Reading the parameters*/
     read_input(argv[1]);
     accepted = hmc_params.ntraj;

     /*Initializing the generator of random numbers and the matrix hop[][]*/
     rlxd_init(1, seed);
=======
     read_input(argv[1]); /*reading the parameters*/
     accepted = hmc_params.ntraj;
     rlxd_init(1, seed);

>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     hopping(hop);

     dTAU = (double)hmc_params.tlength / hmc_params.nstep;

     /*Initializing the rebinned vector*/
     nBin = hmc_params.ntraj / DBIN;
     mag = malloc(nBin * sizeof(double));
     mag2 = malloc(nBin * sizeof(double));
     mag4 = malloc(nBin * sizeof(double));
<<<<<<< HEAD

     thermalization(dTAU);

     for (j = 0; j < nBin; j++)
     {
          mag[j] = 0.0;
          mag2[j] = 0.0;
          mag4[j] = 0.0;
          for(k=0; k<DBIN; k++){
               if (!MolDyn(dTAU, NULL)) accepted--;

               /*Saving the measurements*/
               mag[j]+= fabs(magnetization()) / DBIN;
               mag2[j] += magnetization() * magnetization() / DBIN;
               mag4[j] += magnetization() * magnetization() * magnetization() * magnetization() / DBIN;
          }
 
=======
     mag[0] = 0.0;
     mag2[0] = 0.0;
     mag4[0] = 0.0;

     thermalization(dTAU);

     for (j = 0; j < hmc_params.ntraj; j++)
     {
          if (!MolDyn(dTAU, NULL))
               accepted--;
          if (j - k * DBIN > DBIN)
          {
               k++;
               mag[k] = 0.0;
               mag2[k] = 0.0;
               mag4[k] = 0.0;
          }
          mag[k] += fabs(magnetization()) / DBIN;
          mag2[k] += magnetization() * magnetization() / DBIN;
          mag4[k] += magnetization() * magnetization() * magnetization() * magnetization() / DBIN;
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     }

     /*Writing the results on a file*/
     file = fopen(argv[2], "w");
     for (i = 0; i < nBin; i++)
     {
          fprintf(file, "%f\t%f\t%f\n", mag[i], mag2[i], mag4[i]);
     }
     fclose(file);

<<<<<<< HEAD
=======
     fprintf(stdout, "Accepted values: %d\n", accepted);
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     fprintf(stdout, "Probability of acceptance: %.2f %%\n", (double)accepted * 100 / hmc_params.ntraj);

     return 0;
}
