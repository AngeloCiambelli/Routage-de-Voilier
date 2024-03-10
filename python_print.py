import matplotlib.pyplot as plt
import numpy as np

X_vent = np.loadtxt(open("output\X_courant", "rb"), delimiter=",", skiprows=0)
Y_vent = np.loadtxt(open("output\Y_vent", "rb"), delimiter=",", skiprows=0)
X_courant = np.loadtxt(open("output\X_courant", "rb"), delimiter=",", skiprows=0)
Y_courant = np.loadtxt(open("output\Y_courant", "rb"), delimiter=",", skiprows=0)

x=np.linspace(0,10, int(10.5/0.5))
y=np.linspace(0,10, int(10.5/0.5))

def v(x,y):
    b = 30.
    c = 10
    return np.heaviside(b/(c**2)*abs(x-2/3*c) + b/(c**2)*abs(y-2/3*c) - 1, 0)

xx, yy = np.meshgrid(x,y)

color = np.array('g')
colors = np.repeat(color, len(x)**2)

plt.quiver(xx, yy, Y_vent, X_vent, color='g' , scale=90, width=0.002, alpha=1)
plt.quiver(xx, yy, Y_courant, X_courant,color='b', scale=90, width=0.002, alpha=1)

plt.pcolormesh(xx,yy,v(xx,yy), alpha=0.2)

position = [[1.00,1.42,1.92,2.49,3.13,3.84,4.46,5.00,5.59,6.01],[1.00,1.19,1.39,1.59,1.90,2.15,2.60,3.08,3.57,4.08]]
plt.plot(position[0], position[1], 'o-', color='red')

plt.show()