# Plotting the results of the magnetizations for hot and cold start, in order to find Ntherm

import numpy as np
import matplotlib.pyplot as plt


S_hot = np.genfromtxt("../results/action_hot.dat", unpack=True)
S_cold = np.genfromtxt("../results/action_cold.dat", unpack=True)

f1 = plt.figure(1)
plt.plot(S_hot, ls='-', c='red', label='Hot start')
plt.plot(S_cold, ls='-', c='blue', label='Cold start')
plt.title('Thermalization')
plt.xlabel('i')
plt.ylabel('Action')
plt.grid(ls=':')
plt.legend()
plt.text(77, 2500, r'$\lambda = 1.145$')
plt.text(77, 2250, r'$k = 0.18169$')
plt.text(77, 2000, r'$nStep = 20$')

f2 = plt.figure(2)
plt.plot(S_hot[20:200], ls='-', c='red', label='Hot start')
plt.plot(S_cold[20:200], ls='-', c='blue', label='Cold start')
plt.title('Thermalization (zoom)')
plt.xlabel('i')
plt.ylabel('Action')
plt.grid(ls=':')
plt.legend()
plt.text(61, 400, r'$\lambda = 1.145$')
plt.text(61, 350, r'$k = 0.18169$')
plt.text(61, 300, r'$nStep = 20$')


f1.savefig('graphs/thermal_action.png', dpi=(200), bbox_inches='tight')
f2.savefig('graphs/thermal_action_zoom.png', dpi=(200), bbox_inches='tight')
