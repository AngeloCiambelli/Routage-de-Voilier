#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "routage_voilier.hpp"

using namespace std;

class grille{
    protected:
        int taille_X;
        int taille_Y;
        int Temps;
        float pas;
        float resolution;
    public:
        vecteur<vecteur<vecteur<float>>> score;
        grille(int X, int Y, int T, float res, float p);
        vecteur<int> localisation(int x, int y);
};
