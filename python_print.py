import matplotlib.pyplot as plt
import numpy as np

################################################################################
#
#            fichier pour la visualisation de trajectoire du bateau
#
#
###############################################################################

X_vent = np.loadtxt(open("output\X_courant", "rb"), delimiter=",", skiprows=0)
Y_vent = np.loadtxt(open("output\Y_vent", "rb"), delimiter=",", skiprows=0)
X_courant = np.loadtxt(open("output\X_courant", "rb"), delimiter=",", skiprows=0)
Y_courant = np.loadtxt(open("output\Y_courant", "rb"), delimiter=",", skiprows=0)

x=np.linspace(0,10, int(10.5/0.5))
y=np.linspace(0,10, int(10.5/0.5))

def v(x,y):  # fonction de score
    b = 40.
    c = 10
    return np.heaviside(b/(c**2)*(x-2/3*c)**2 + b/(c**2)*(y-2/3*c)**2 - 1, 0)

xx, yy = np.meshgrid(x,y)

color = np.array('g')
colors = np.repeat(color, len(x)**2)

plt.quiver(xx, yy, Y_vent, X_vent, color='g' , scale=90, width=0.002, alpha=1)
plt.quiver(xx, yy, Y_courant, X_courant,color='b', scale=90, width=0.002, alpha=1)

plt.pcolormesh(xx,yy,v(xx,yy), alpha=0.2)

## copier-coller dans l'array ci-dessous
position =np.array([[1.00,1.25,1.55,1.89,2.28,2.72,3.19,3.63,4.13,4.71,5.37,5.87],[8.00,8.07,8.14,8.22,8.32,8.42,8.53,8.44,8.35,8.23,8.10,7.76]])


# position = position.transpose()
plt.plot(position[0], position[1], 'o-', color='red')

plt.show()