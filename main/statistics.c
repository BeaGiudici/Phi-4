/*******************************************************************************
*
* File statistics.c
*
* This program carries out the statistics for the final results of the
* simulations
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 13/06/2019
* MODIFIED: 10/08/2019
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

/*Defining the struct used to collect the results*/
typedef struct
{
     double value;
     double error;
} MEASURE;

typedef struct
{
     double kappa;
     MEASURE mag;
     MEASURE mag2;
     MEASURE sus;
     MEASURE binder;
} RESULTS;

int main(int argc, char *argv[])
{
<<<<<<< HEAD
     /*Declaring the variables */
=======
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     RESULTS res;
     double *m, *m2, *m4, *s, *bnd;
     double mean_m4 = 0.0;
     int nBin;
     int i;  /*Counter*/
     int ct; /*Needed because fscaf returns an integer 
			(the compiler gives me an error otherwise)*/
     FILE *file_in;

<<<<<<< HEAD
     /*See if the right number of argument is passed in the command line*/
=======
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     if (argc != 3)
     {
          fprintf(stderr, "Number of arguments not correct\n");
          fprintf(stderr, "Usage: %s <infile> <readfile>\n", argv[0]);
          exit(1);
     }

     read_input(argv[1]); /*reading the parameters*/
     res.kappa = act_params.kappa;

     /*Initializing the vectors*/
     nBin = hmc_params.ntraj / DBIN;
     m = malloc(nBin * sizeof(double));
     m2 = malloc(nBin * sizeof(double));
     m4 = malloc(nBin * sizeof(double));
     s = malloc(nBin * sizeof(double));
     bnd = malloc(nBin * sizeof(double));

     /*Initializing the means to zero*/
     res.mag.value = 0.0;
     res.mag2.value = 0.0;
     res.sus.value = 0.0;
     res.binder.value = 0.0;

     /*Read the file*/
     file_in = fopen(argv[2], "r");
     for (i = 0; i < nBin; i++)
     {
          ct = fscanf(file_in, "%lf\t%lf\t%lf", &m[i], &m2[i], &m4[i]);
          if (feof(file_in))
               break;
          /*Check if the data are stored as expected*/
          if (ct != 3)
          {
               puts("Unexpected error in input data.");
               return 1;
          }
          res.mag.value += m[i] / nBin;
          res.mag2.value += m2[i] / nBin;
          mean_m4 += m4[i] / nBin;
     }
     fclose(file_in);

     /*Clustering*/
     clustering(m, res.mag.value, nBin);
     clustering(m2, res.mag2.value, nBin);
     clustering(m4, mean_m4, nBin);

     /*Computing the errors*/
     res.mag.error = error_jack(m, res.mag.value, nBin);
     res.mag2.error = error_jack(m2, res.mag2.value, nBin);

     /*Jackknife over the secondary variables*/
     res.sus.value = magSus(res.mag.value, res.mag2.value);
     res.binder.value = cBinder(mean_m4, res.mag2.value);

     for (i = 0; i < nBin; i++)
     {
          s[i] = magSus(m[i], m2[i]);
          bnd[i] = cBinder(m4[i], m2[i]);
     }

     res.sus.error = error_jack(s, res.sus.value, nBin);
     res.binder.error = error_jack(bnd, res.binder.value, nBin);

<<<<<<< HEAD
     /*Printing all the results (this particular formatting is useful to write 
     the .json file in the final simulation)*/
=======
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
     printf("\t\"L\" : %i,\n", L);
     printf("\t\"kappa\" : %f,\n", res.kappa);
     printf("\t\"magnetization\" : {\"val\" : %f, \"err\" : %f},\n", res.mag.value / V, res.mag.error / V);
     printf("\t\"magnetization2\" : {\"val\" : %f, \"err\" : %f},\n", res.mag2.value / (V * V), res.mag2.error / (V * V));
     printf("\t\"susceptibility\" : {\"val\" : %f, \"err\" : %f},\n", res.sus.value, res.sus.error);
     printf("\t\"binder\" : {\"val\" : %f, \"err\" : %f}\n", res.binder.value, res.binder.error);

     return 0;
}
