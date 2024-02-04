#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "routage_voilier.hpp"

using namespace std;

class grille{
    public:
    int taille_X;
    int taille_Y;
    int Temps;
    vecteur<vecteur<vecteur<float>>> score;
    grille(int X, int Y, int T);
};
