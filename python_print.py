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


position =np.array([[0.50,0.67,0.86,1.08,1.35,1.61,1.93,2.28,2.59,2.99,3.38,3.81,4.28,4.81,5.41,5.89,6.42,6.98],
                    [2.00,2.16,2.32,2.48,2.71,2.86,3.15,3.40,3.68,3.84,4.01,4.15,4.26,4.35,4.46,4.66,4.92,5.28]])
plt.plot(position[0], position[1], 'o-', color='red')

plt.show()