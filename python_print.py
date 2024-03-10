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


position =np.array([[1.00,1.31,1.63,1.98,2.33,2.73,3.10,3.57,4.09,4.66,5.32,5.87,6.12,6.38,6.68],[2.00,2.23,2.47,2.73,2.99,3.08,3.34,3.44,3.55,3.66,3.79,4.17,4.54,4.95,5.41]])
# position = position.transpose()
plt.plot(position[0], position[1], 'o-', color='red')

plt.show()