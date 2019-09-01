# Plotting the results of the action for hot and cold start,
# in order to find when the chain is thermalized

import numpy as np
import matplotlib.pyplot as plt


S_hot = np.genfromtxt("../results/action_hot.dat", unpack=True)
S_cold = np.genfromtxt("../results/action_cold.dat", unpack=True)

f1 = plt.figure(1)
plt.plot(S_hot, ls="-", c="red", label="Hot start")
plt.plot(S_cold, ls="-", c="blue", label="Cold start")
plt.title("Thermalization")
plt.xlabel("i")
plt.ylabel("Action")
plt.grid(ls=":")
plt.legend()
plt.text(77, 2250, r"$\lambda = 1.145$")
plt.text(77, 2000, r"$k = 0.18169$")
plt.text(77, 1750, r"$nStep = 20$")

f2 = plt.figure(2)
plt.plot(S_hot[20:200], ls="-", c="red", label="Hot start")
plt.plot(S_cold[20:200], ls="-", c="blue", label="Cold start")
plt.title("Thermalization (zoom)")
plt.xlabel("i")
plt.ylabel("Action")
plt.grid(ls=":")
plt.legend()
plt.text(61, 175, r"$\lambda = 1.145$")
plt.text(61, 150, r"$k = 0.18169$")
plt.text(61, 125, r"$nStep = 20$")


f1.savefig("graphs/thermal_action.png", dpi=(200), bbox_inches="tight")
f2.savefig("graphs/thermal_action_zoom.png", dpi=(200), bbox_inches="tight")
