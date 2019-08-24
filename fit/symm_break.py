import math
import matplotlib.pyplot as plt
import numpy as np
import json
import sys

if len(sys.argv) == 1:
    file = '../results/SB_results.json'
else:
    file = sys.argv[1]

f1 = plt.figure(1)
plt.title('Magnetization')
plt.xlabel('k')
plt.ylabel(r'$\langle |m| \rangle$ / V')
plt.grid(ls=':')

f2 = plt.figure(2)
plt.title('Susceptibility')
plt.xlabel('k')
plt.ylabel(r'$\chi$')
plt.grid(ls=':')
plt.semilogy()

f3 = plt.figure(3)
plt.title('Binder cumulant')
plt.xlabel('k')
plt.ylabel('U')
plt.grid(ls=':')

f4 = plt.figure(4)
plt.title('Squared magnetization')
plt.xlabel('k')
plt.ylabel(r'$\langle m^2 \rangle / V^2$')
plt.grid(ls=':')

data = json.load(open(file, 'r'))
for L in range(4, 15, 2):
    k = np.array([line["kappa"]
                  for line in filter(lambda item: item["L"] == L, data)])
    mag = np.array([line["magnetization"]["val"]
                    for line in filter(lambda item: item["L"] == L, data)])
    err_m = np.array([line["magnetization"]["err"]
                      for line in filter(lambda item: item["L"] == L, data)])
    mag2 = np.array([line["magnetization2"]["val"]
                     for line in filter(lambda item: item["L"] == L, data)])
    err_m2 = np.array([line["magnetization2"]["err"]
                       for line in filter(lambda item: item["L"] == L, data)])
    sus = np.array([line["susceptibility"]["val"]
                    for line in filter(lambda item: item["L"] == L, data)])
    err_s = np.array([line["susceptibility"]["err"]
                      for line in filter(lambda item: item["L"] == L, data)])
    binder = np.array([line["binder"]["val"]
                       for line in filter(lambda item: item["L"] == L, data)])
    err_b = np.array([line["binder"]["err"]
                      for line in filter(lambda item: item["L"] == L, data)])

    # Plotting the magnetization
    plt.figure(1)
    plt.errorbar(k, mag, yerr=err_m, ls='-', lw=0.65, marker='.', markersize=1,
                 elinewidth=0.5, capsize=2.5, label='L / a = %i' % L)
    plt.legend()

    # Plotting the susceptibility
    plt.figure(2)
    plt.errorbar(k, sus, yerr=err_s, ls='-', lw=0.65, marker='.', markersize=1,
                 elinewidth=0.5, capsize=2.5, label='L / a = %i' % L)
    plt.legend()

    # Plotting the binder cumulant
    plt.figure(3)
    plt.errorbar(k, binder, yerr=err_b, ls='-', lw=0.65, marker='.', markersize=1,
                 elinewidth=0.5, capsize=2.5, label='L / a = %i' % L)
    plt.legend()

    plt.figure(4)
    plt.errorbar(k, mag2, yerr=err_m2, ls='-', lw=0.65, marker='.', markersize=1,
                 elinewidth=0.5, capsize=2.5, label='L / a = %i' % L)
    plt.legend()

if k[0] == 0.18:
    f1.savefig('graphs/magnetization_zoom.png', dpi=(200), bbox_inches='tight')
    f2.savefig('graphs/susceptibility_zoom.png',
               dpi=(200), bbox_inches='tight')
    f3.savefig('graphs/binder_zoom.png', dpi=(200), bbox_inches='tight')
    f4.savefig('graphs/mag2_zoom.png', dpi=(200), bbox_inches='tight')
else:
    f1.savefig('graphs/magnetization.png', dpi=(200), bbox_inches='tight')
    f2.savefig('graphs/susceptibility.png', dpi=(200), bbox_inches='tight')
    f3.savefig('graphs/binder.png', dpi=(200), bbox_inches='tight')
    f4.savefig('graphs/mag2.png', dpi=(200), bbox_inches='tight')
