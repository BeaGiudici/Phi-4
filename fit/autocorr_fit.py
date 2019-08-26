# This program draws the graph of the autocorrelation
# function for L = 4 and L = 14

import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
from functions import exponential

fig = plt.figure()
with open("fit_results/gamma_fit.dat", "w") as f:

    for L in [4, 14]:
        i, gamma = np.genfromtxt("../results/gamma%i.dat" % L, unpack=True)
        plt.plot(i, gamma, ls='', marker='.',
                 markersize=2.5, label='L / a = %i' % L)
        # Fitting the curve
        best, covar = curve_fit(exponential, i, gamma, p0=(1, 1))
        par_err = np.sqrt(np.diag(covar))

        x = np.linspace(0, len(i), 100)
        plt.plot(x, exponential(x, *best), ls='--', lw=1, c='green')

        plt.title("Autocorrelation")
        plt.xlabel(r"$i$")
        plt.ylabel(r"$\Gamma$")
        plt.grid(linestyle=':')
        plt.legend()
        plt.text(800, 0.8, r'$\lambda = 1.145$')
        plt.text(800, 0.7, r'$k = 0.18169$')
        plt.text(800, 0.6, r'$nStep = 20$')

# Writing the results of the fit on a file

print('Fit results for L = %i\n' % L)
print('A = %f +- %f\n' % (best[0], par_err[0]))
print('TAU = %f +- %f\n\n' % (best[1], par_err[1]))

fig.savefig('graphs/autocorr.png', dpi=(200), bbox_inches='tight')
