#ifndef LATTICE_H
#define LATTICE_H

/*Defining pi*/
#define PI acos(-1)

/* Dimension of the lattice */
#define D 3
/* spatial extend of the lattice */
<<<<<<< HEAD
#define L 4
=======
#define L 14
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
/* lattice volume, needs to be adjusted according to number of dimensions*/
#define V (L * L * L)

#ifdef CONTROL
#define EXTERN
#undef CONTROL
#else
#define EXTERN extern
#endif

EXTERN double phi[V];
EXTERN int hop[V][2 * D];
EXTERN double momentum[V];

/*data structure to store all the parameters of the algorithm*/
typedef struct
{
     double tlength; /*trajectory length*/
     int nstep;      /*leapfrog steps per trajectory*/
     int ntherm;     /*number of thermalization steps*/
     int ntraj;      /*number of trajectories after thermalization*/
} hmc_params_t;

/*data structure to store all the parameters of the action*/
typedef struct
{
     double kappa;
     double lambda;
} act_params_t;

#ifdef CONTROL
#define EXTERN static
#undef CONTROL
#endif

EXTERN hmc_params_t hmc_params;
EXTERN act_params_t act_params;
EXTERN int seed;

#endif
