/*******************************************************************************
*
* File hybrid_MC.c
*
* This program uses the hybrid Monte Carlo, with the accept/reject algorithm,
* in order to compute the magnetization
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 30/05/2019
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
    double *dH_abs, deltaH, mean_H = 0.0, err_H, mean2_H = 0.0;
    double *expo, mean_expo = 0.0, err_expo, mean2_e = 0.0;
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

    accepted = hmc_params.ntraj; /*This variable keeps track of the accepted configuration 
                                    and its value decreases every time the configuration is not accepted*/

    dTAU = (double)hmc_params.tlength / hmc_params.nstep;
    nBin = hmc_params.ntraj / DBIN;

    /*Initializing the rebinned vector*/
    mag = malloc(nBin * sizeof(double));
    mag2 = malloc(nBin * sizeof(double));
    dH_abs = malloc(nBin * sizeof(double));
    expo = malloc(nBin * sizeof(double));

    thermalization(dTAU);

    /*Proceeding with the molecular dynamics and the rebinning*/
    for (j = 0; j < nBin; j++)
    {
        /*Setting to zero the entries in order to sum over later*/
        mag[j] = 0.0;
        mag2[j] = 0.0;
        expo[j] = 0.0;
        dH_abs[j] = 0.0;

        for (k = 0; k < DBIN; k++)
        {
            if (!MolDyn(dTAU, &deltaH))
                accepted--;

            /*Saving the measurements*/
            mag[j] += fabs(magnetization() / V) / DBIN;
            mag2[j] += (magnetization() * magnetization() / (V * V)) / DBIN;
            expo[j] += exp(-1.0 * deltaH) / DBIN;
            dH_abs[j] += fabs(deltaH) / DBIN;
        }

        /*Computing the means and the means of the squares*/
        mean_m += mag[j] / nBin;
        mean_m2 += mag2[j] / nBin;
        mean_expo += expo[j] / nBin;
        mean_H += dH_abs[j] / nBin;
        mean2_m += mag[j] * mag[j] / nBin;
        mean2_m2 += mag2[j] * mag2[j] / nBin;
        mean2_H += dH_abs[j] * dH_abs[j] / nBin;
        mean2_e += expo[j] * expo[j] / nBin;
    }

    /*Computing the errors*/
    err_m = sqrt((mean2_m - mean_m * mean_m) / nBin);
    err_m2 = sqrt((mean2_m2 - mean_m2 * mean_m2) / nBin);
    err_H = sqrt((mean2_H - mean_H * mean_H) / nBin);
    err_expo = sqrt((mean2_e - mean_expo * mean_expo) / nBin);

    /*Printing all the results (this particular format is useful to write 
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
