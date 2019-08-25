# Comparing the magnetization and the Hamiltonian, computed with and without the
# accept/reject algorithm at a fixed spatial extend of the lattice.
# At the end, there is also a study of the acceptance probability of the accept/reject method

import math
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
import json
import functions as f

L = 4
data_AR = json.load(open('../results/accRej.json', 'r'))
data_no_AR = json.load(open('../results/no_accRej.json', 'r'))
step = np.array([line["nStep"]
                 for line in filter(lambda item: item["L"] == L, data_AR)])
x = 1./(step*step)  # dTau**2

# ABSOLUTE MAGNETIZATION
print('\t ABSOLUTE MAGNETIZATION \t')

f1 = plt.figure()

# Plotting data without accept/reject
mag = np.array([line["magnetization"]["val"]
                for line in filter(lambda item: item["L"] == L, data_no_AR)])
err = np.array([line["magnetization"]["err"]
                for line in filter(lambda item: item["L"] == L, data_no_AR)])

plt.errorbar(x, mag, yerr=err, ls='', marker='.', markersize=1,
             color='r', elinewidth=0.5, capsize=2.5, ecolor='r', label='Without Accept/Reject')
# Linear fit
best, covar = curve_fit(f.linear, x, mag, sigma=err, p0=(0.22, 0.1))
plt.plot(x, f.linear(x, *best), ls='--', c='red', linewidth=0.65)
deg = len(mag) - len(best) #Here and below: degrees of freedom for the
                           #reduced chi-squared

#Print the results of the fit
print("WITHOUT ACCEPT/REJECT")
print('Parameters: ', best)
print("Parameters' Std Error: ", np.sqrt(np.diag(covar)))
print('Covariance: ', covar)
print('Reduced chi-squared: ', f.red_chi_sq(mag, f.linear(x, *best), err, dof=deg))
print('\n')

# Plotting data with accept/reject
mag = np.array([line["magnetization"]["val"]
                for line in filter(lambda item: item["L"] == L, data_AR)])
err = np.array([line["magnetization"]["err"]
                for line in filter(lambda item: item["L"] == L, data_AR)])
plt.errorbar(x, mag, yerr=err, ls='', marker='.', markersize=1,
             color='b', elinewidth=0.5, capsize=2.5, ecolor='b', label='With Accept/Reject')
# Linear fit
best, covar = curve_fit(f.constant, x, mag, sigma=err, p0=(0.37544641))
plt.plot(x, f.constant(x, *best), ls='--', c='b', linewidth=0.65)
deg = len(mag) - len(best)

#Print the results of the fit
print("WITH ACCEPT/REJECT")
print('Parameters: ', best)
print("Parameters' Std Error: ", np.sqrt(np.diag(covar)))
print('Covariance: ', covar)
print('Reduced chi-squared: ', f.red_chi_sq(mag, f.constant(x, *best), err, dof=deg))
print('\n')

plt.title('Comparing |m| with and without Accept/Reject')
plt.grid(ls=':')
plt.xlabel(r'$\delta \tau^2$')
plt.ylabel(r'$\langle | m | \rangle$')
plt.legend()

# SQUARED MAGNETIZATION
print('\t SQUARED MAGNETIZATION \t')

f2 = plt.figure()

# Plotting data without accept/reject
mag = np.array([line["mag_sq"]["val"]
                for line in filter(lambda item: item["L"] == L, data_no_AR)])
err = np.array([line["mag_sq"]["err"]
                for line in filter(lambda item: item["L"] == L, data_no_AR)])

plt.errorbar(x, mag, yerr=err, ls='', marker='.', markersize=1,
             color='r', elinewidth=0.5, capsize=2.5, ecolor='r', label='Without Accept/Reject')
# Linear fit
best, covar = curve_fit(f.linear, x, mag, sigma=err, p0=(0.22, 0.1))
plt.plot(x, f.linear(x, *best), ls='--', c='red', linewidth=0.65)
deg = len(mag) - len(best)

#Print the results of the fit
print("WITHOUT ACCEPT/REJECT")
print('Parameters: ', best)
print("Parameters' Std Error: ", np.sqrt(np.diag(covar)))
print('Covariance: ', covar)
print('Reduced chi-squared: ', f.red_chi_sq(mag, f.linear(x, *best), err, dof=deg))
print('\n')

# Plotting data with accept/reject
mag = np.array([line["mag_sq"]["val"]
                for line in filter(lambda item: item["L"] == L, data_AR)])
err = np.array([line["mag_sq"]["err"]
                for line in filter(lambda item: item["L"] == L, data_AR)])
plt.errorbar(x, mag, yerr=err, ls='', marker='.', markersize=1,
             color='b', elinewidth=0.5, capsize=2.5, ecolor='b', label='With Accept/Reject')
# Linear fit
best, covar = curve_fit(f.constant, x, mag, sigma=err, p0=(0.18287383))
plt.plot(x, f.constant(x, *best), ls='--', c='b', linewidth=0.65)
deg = len(mag) - len(best)

#Print the results of the fit
print("WITH ACCEPT/REJECT")
print('Parameters: ', best)
print("Parameters' Std Error: ", np.sqrt(np.diag(covar)))
print('Covariance: ', covar)
print('Reduced chi-squared: ', f.red_chi_sq(mag, f.constant(x, *best), err, dof=deg))
print('\n')

plt.title(r'Comparing $m^2$ with and without Accept/Reject')
plt.grid(ls=':')
plt.xlabel(r'$\delta \tau^2$')
plt.ylabel(r'$\langle m^2 \rangle$')
plt.legend()

# HAMILTONIAN
print('\t HAMILTONIAN \t')
f3 = plt.figure()

dT = 1./step
H = np.array([line["deltaH"]["val"]
              for line in filter(lambda item: item["L"] == L, data_AR)])
err = np.array([line["deltaH"]["err"]
                for line in filter(lambda item: item["L"] == L, data_AR)])
plt.errorbar(dT, H, yerr=err, ls='', marker='.', markersize=1,
             color='b', elinewidth=0.5, capsize=2.5, ecolor='b')
# Linear fit
best, covar = curve_fit(f.quadratic, dT, H, sigma=err, p0=(1.0, -0.01, 10.))
y = np.linspace(min(dT), max(dT), 100)
plt.plot(y, f.quadratic(y, *best), ls='--', c='r', linewidth=0.65)
deg = len(H) - len(best)

#Print the results of the fit
print('Parameters: ', best)
print("Parameters' Std Error: ", np.sqrt(np.diag(covar)))
print('Covariance: ', covar)
print('Reduced chi-squared: ',
      f.red_chi_sq(H, f.quadratic(dT, *best), err, dof=deg))
print('\n')

plt.title('Variation of the Hamiltonian')
plt.grid(ls=':')
plt.xlabel(r'$\delta \tau^2$')
plt.ylabel(r'$|\Delta H|$')

# EXPONENTIAL
f4 = plt.figure()
exp = np.array([line["exp"]["val"]
                for line in filter(lambda item: item["L"] == L, data_AR)])
err = np.array([line["exp"]["err"]
                for line in filter(lambda item: item["L"] == L, data_AR)])

plt.errorbar(x, exp, yerr=err, ls='', marker='.', markersize=1,
             color='b', elinewidth=0.5, capsize=2.5, ecolor='b')

# Linear fit
best, covar = curve_fit(f.constant, x, exp, p0=(1.0), sigma=err)
plt.plot(x, f.constant(x, *best), ls='--', c='r', linewidth=0.65)
deg = len(exp) - len(best)

#Print the results of the fit
print('\t EXPONENTIAL \t')
print('Parameters: ', best)
print("Parameters' Std Error: ", np.sqrt(np.diag(covar)))
print('Covariance: ', covar)
print('Reduced chi-squared: ', f.red_chi_sq(H,
                                            f.constant(x, *best), err, dof=deg))

plt.title('Behaviour of the exponential')
plt.grid(ls=':')
plt.xlabel(r'$\delta \tau^2$')
plt.ylabel(r'$e^{-\Delta H}$')

# STUDY OF THE ACCEPTANCE

f5 = plt.figure()
plt.title('Acceptance behavior')
plt.xlabel('nStep')
plt.ylabel('Acceptance probability')
plt.grid(ls=':')
for l in range(4, 13, 4):
    acc = np.array([line["acceptance"]
                    for line in filter(lambda item: item["L"] == l, data_AR)])
    plt.plot(step, acc, ls='-', marker='x', markersize=3,
             linewidth=0.8, label='L / a = %i' % l)
    plt.legend()
    if l == 12:
        l = 14
        acc = np.array([line["acceptance"]
                        for line in filter(lambda item: item["L"] == l, data_AR)])
        plt.plot(step, acc, ls='-', marker='x', markersize=3,
                 linewidth=0.8, label='L / a = %i' % l)
        plt.legend()
plt.plot(step, np.full(len(step), 0.9), ls='--', c='r', linewidth=0.7)

f1.savefig('graphs/mag_acc_rej.png', dpi=(200), bbox_inches='tight')
f2.savefig('graphs/mag2_acc_rej.png', dpi=(200), bbox_inches='tight')
f3.savefig('graphs/deltaH.png', dpi=(200), bbox_inches='tight')
f4.savefig('graphs/expo.png', dpi=(200), bbox_inches='tight')
f5.savefig('graphs/acceptance.png', dpi=(200), bbox_inches='tight')
