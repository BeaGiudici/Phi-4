# Useful functions

import math
import numpy as np


def red_chi_sq(data, model, sigma, dof=2):
    '''
Returns the reduced chi square for an arbitrary
model with dof degree of freedom
    '''
    chi = np.sum(((data-model)/sigma)**2)
    return chi/dof


def constant(x, *par):
    '''
Constant function
    '''
    return 0.0*x + par[0]


def linear(x, *par):
    '''
Function for a linear fit
    '''
    return par[0] + par[1]*x


def quadratic(x, *par):
    '''
Function for a linear fit
    '''
    return par[0] + par[1]*x + par[2]*x*x


def exponential(x, *par):
    '''
Function for an exponential fit
    '''
    return par[0]*np.exp(-x/par[1])
