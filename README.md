# Phi-4
Simulation of a scalar phi^4 theory


This directory contains basic routines to start developing
a code for simulating the phi**4 theory with the HMC algorithm
as described during the lectures. 

Here is a short description of the folder content:

main: phi4.c : main program. Compile using make and run as:
      phi4 infile

modules: contains subfolders with the working modules. 

         utility: hopping.c : initializes the hopping field
                  jackknife.c : jackknife method's functions
                  reading.c : functions to read the parameters

         random: ranlxd.c : Luescher's random number generator

         extras: integrator.c : algorithms for the hybrid Monte Carlo
                 measurements.c : all the quantities needed to study 
                                  the symmetry breaking

include: contains the include files:

         extras.h: include for the modules in extras

         lattice.h: contains global variables, the field and
                    its dimensions

         phi4.h: include for the main program

         ranlxd.h: include for ranlxd.c

         utility.h: include for the modules in utility

devel: development folder where you can test your programs

       hmc: check1.c : example of test. Compile using make

script: all the scripts for the symmetry breaking and the
        accept/reject test
