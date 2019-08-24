/*******************************************************************************
 * 
 *  File reading.c
 * 
 * Functions used to read the input file (normally called infile)
 * 
 * The externally accessible functions are
 *
 *   int get_val(FILE* fp, char *str, char* fmt,  void* val)
 *      Routine which reads one line from the input file.
 *      Format of the lines is <keyword> <value>.
 *      Checks if the keyword in string str matches,
 *      then gets the value according to the format in fmt
 *
 *     
 *   int read_input(char *input, int print)
 *      Parses the input file (format as specified in get_val)
 *      and prints the parameters onto the screen. Currently it reads 
 *      the basic values for the action and also for the future HMC and 
 *      the seed of the random number generator.
 *      
 *   
*******************************************************************************/

#define CONTROL

#include "lattice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_val(FILE *fp, char *str, char *fmt, void *val)
{
     char c[128];

     if (1 != fscanf(fp, "%s", c))
     {
          fprintf(stderr, "Error reading input file at %s\n", str);
          exit(1);
     }

     if (strcmp(str, c) != 0)
     {
          fprintf(stderr, "Error reading input file expected %s found %s\n", str, c);
          exit(1);
     }

     if (1 != fscanf(fp, fmt, val))
     {
          fprintf(stderr, "Error reading input file at %s\n", str);
          fprintf(stderr, "Cannot read value format %s\n", fmt);
          exit(1);
     }

     return 0;
}

int read_input(char *input)
{
     FILE *fp;

     fp = fopen(input, "r");
     if (fp == NULL)
     {
          fprintf(stderr, "Cannot open input file %s \n", input);
          exit(1);
     }

     get_val(fp, "kappa", "%lf", &act_params.kappa);
     get_val(fp, "lambda", "%lf", &act_params.lambda);
     get_val(fp, "ntherm", "%i", &hmc_params.ntherm);
     get_val(fp, "ntraj", "%i", &hmc_params.ntraj);
     get_val(fp, "traj_length", "%lf", &hmc_params.tlength);
     get_val(fp, "nstep", "%i", &hmc_params.nstep);
     get_val(fp, "seed", "%i", &seed);

     fprintf(stderr, "PARAMETERS\n");
     fprintf(stderr, "L              %i\n", L);
     fprintf(stderr, "DIM            %i\n", D);
     fprintf(stderr, "kappa          %f\n", act_params.kappa);
     fprintf(stderr, "lambda         %f\n", act_params.lambda);
     fprintf(stderr, "ntherm         %i\n", hmc_params.ntherm);
     fprintf(stderr, "ntraj          %i\n", hmc_params.ntraj);
     fprintf(stderr, "traj_length    %f\n", hmc_params.tlength);
     fprintf(stderr, "nstep          %i\n", hmc_params.nstep);
     fprintf(stderr, "END PARAMETERS\n");
     fprintf(stderr, "\n");

     return 0;
}