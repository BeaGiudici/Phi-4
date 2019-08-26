# This program draws the histogram of the values
# of the momenta, which has to be a gaussian curve

import matplotlib.pyplot as plt
import numpy as np

momenta = np.genfromtxt('../results/momenta.dat', unpack=True)

plt.figure()
plt.hist(momenta, bins=50)

plt.title("Gaussian of the momenta")
plt.xlabel('Momenta')
plt.grid(ls=':')

plt.savefig('graphs/momenta_hist.png', dpi=(200), bbox_inches='tight')
