/*******************************************************************************
*
* File hybrid_MC.c
*
* This program uses the hybrid Monte Carlo, with the accept/reject algorithm,
* in order to compute the magnetization
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 30/05/2019
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

#define DBIN 1000 /*Length of a bin*/

int main(int argc, char *argv[])
{
    /*Declaring the variables */
    int j, accepted, k; /*Counters*/
    double dTAU;        /*Infinitesimal time interval*/
    double *dH, deltaH, mean_H = 0.0, mean2_H = 0.0, err_H;
    double *expo, mean_expo = 0.0, mean2_expo = 0.0, err_expo;
    double *mag2, mean_m2 = 0.0, mean2_m2 = 0.0, err_m2;
    double *mag, mean_m = 0.0, mean2_m = 0.0, err_m;
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

    accepted = hmc_params.ntraj; /*This variable keeps track of the accepted configuration 
                                    and its value decreases every time the configuration is not accepted*/

    dTAU = (double)hmc_params.tlength / hmc_params.nstep;

    /*Initializing the rebinned vector*/
    nBin = hmc_params.ntraj / DBIN;
    mag = malloc(nBin * sizeof(double));
    mag2 = malloc(nBin * sizeof(double));
    dH = malloc(nBin * sizeof(double));
    expo = malloc(nBin * sizeof(double));
    mag[0] = 0.0;
    mag2[0] = 0.0;
    dH[0] = 0.0;
    expo[0] = 0.0;

    thermalization(dTAU);

    /*Setting to zero the counter used for the rebinning*/
    k = 0;

    for (j = 0; j < hmc_params.ntraj; j++)
    {
        if (!MolDyn(dTAU, &deltaH))
            accepted--;

        /*Rebinning: if the index of the loop exceeded the length of a bin,
        the counter k moves to the next one*/
        if (j - k * DBIN > DBIN)
        {
            /*Computing the mean and the mean of the squares*/
            mean_m += mag[k] / nBin;
            mean_m2 += mag2[k] / nBin;
            mean_expo += expo[k] / nBin;
            mean_H += dH[k] / nBin;
            mean2_m += mag[k] * mag[k] / nBin;
            mean2_m2 += mag2[k] * mag2[k] / nBin;
            mean2_expo += expo[k] * expo[k] / nBin;
            mean2_H += dH[k] * dH[k] / nBin;

            /*Update the counter*/
            k++;

            /*Setting the new entries to zero*/
            mag[k] = 0.0;
            mag2[k] = 0.0;
            dH[k] = 0.0;
            expo[k] = 0.0;
        }
        mag[k] += fabs(magnetization() / V) / nBin;
        mag2[k] += (magnetization() * magnetization() / (V * V)) / DBIN;
        dH[k] += fabs(deltaH) / DBIN;
        expo[k] += exp(-1. * deltaH) / DBIN;
    }

    /*Estimating the errors*/
    err_m = sqrt((mean2_m - mean_m * mean_m) / nBin);
    err_m2 = sqrt((mean2_m2 - mean_m2 * mean_m2) / nBin);
    err_expo = sqrt((mean2_expo - mean_expo * mean_expo) / nBin);
    err_H = sqrt((mean2_H - mean_H * mean_H) / nBin);

    /*Printing all the results (this particular formatting is useful to write 
    the .json file in the final simulation)*/
    fprintf(stdout, "\t\"L\" : %i,\n", L);
    fprintf(stdout, "\t\"nStep\" : %i,\n", hmc_params.nstep);
    fprintf(stdout, "\t\"acceptance\" : %f,\n", (double)accepted / hmc_params.ntraj);
    fprintf(stdout, "\t\"magnetization\" : {\"val\" : %f, \"err\" : %f},\n", mean_m, err_m);
    fprintf(stdout, "\t\"mag_sq\" : {\"val\" : %f, \"err\" : %f},\n", mean_m2, err_m2);
    fprintf(stdout, "\t\"deltaH\" : {\"val\" : %f, \"err\" : %f},\n", mean_H, err_H);
    fprintf(stdout, "\t\"exp\" : {\"val\" : %f, \"err\" : %f}\n", mean_expo, err_expo);

    return 0;
}
