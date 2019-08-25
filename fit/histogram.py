<<<<<<< HEAD
# This program draws the histogram of the values
# of the momenta, which has to be a gaussian curve
=======
# This program draw the histogram of the values of the momenta, which has to be a gaussian
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4

import matplotlib.pyplot as plt
import numpy as np

momenta = np.genfromtxt('../results/momenta.dat', unpack=True)
<<<<<<< HEAD

plt.figure()
plt.hist(momenta, bins=50)

plt.title("Gaussian of the momenta")
plt.xlabel('Momenta')
plt.grid(ls=':')

=======
plt.figure()
plt.hist(momenta, bins=50)
plt.title("Gaussian of the momenta")
plt.xlabel('Momenta')
plt.grid(ls=':')
>>>>>>> 16d13066fcae8d7c4cd1975c4b6fa202534775d4
plt.savefig('graphs/momenta_hist.png', dpi=(200), bbox_inches='tight')
