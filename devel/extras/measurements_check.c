/*******************************************************************************
*
* File measurements_check.c
*
* This program checks that measurements.c implements the basic algorithm
* correctly
*
* AUTHOR: Beatrice Giudici <b.giudici1@campus.unimib.it>
* CREATED: 16/05/2019
*
*******************************************************************************/

#define CONTROL

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "lattice.h"
#include "utility.h"
#include "extras.h"
#include "ranlxd.h"

int main(int argc, char *argv[])
{
    /*Declaring the variables */
    int i;
    double m, expected = 0, H, sus, B;
    FILE *inFile;

    if (argc != 2)
    {
        fprintf(stderr, "Number of arguments not correct\n");
        fprintf(stderr, "Usage: %s <infile> \n", argv[0]);
        exit(1);
    }

    /*Reading the parameters from file */
    read_input(argv[1]);

    hopping(hop);

    /*Initializing the random generator and the initial field*/
    rlxd_init(1, seed);
    for (i = 0; i < V; i++)
    {
        phi[i] = 1.0;
        expected += phi[i];
    }

    /*Generating the momenta with a gaussian distribution*/
    momentum_init();

    /*Magnetization*/
    m = magnetization();
    fprintf(stdout, "Magnetization: %f\n", m);
    fprintf(stdout, "Expected magnetization: %f\n", expected);

    /*Magnetic Susceptibility*/
    sus = magSus(m, m * m);
    fprintf(stdout, "Magnetic Susceptibility: %f\n", sus);
    fprintf(stdout, "Expected magnetic susceptibility: %f\n", (m * m - m * m) / V);

    /*Binder cumulant*/
    B = cBinder(pow(m, 4), m * m);
    fprintf(stdout, "Binder cumulant: %f\n", B);
    fprintf(stdout, "Expected Binder cumulant: %f\n", 1.);

    /*Hamiltonian*/
    H = hamiltonian();
    fprintf(stdout, "Hamiltonian: %f\n", H);

    /*Writing the values of the momenta on a file, in order to use them to draw a histogram*/
    inFile = fopen("../../results/momenta.dat", "w");
    for (i = 0; i < V; i++)
    {
        fprintf(inFile, "%f\n", momentum[i]);
    }
    fclose(inFile);

    return 0;
}