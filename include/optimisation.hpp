#ifndef DEF_OPTIMISATION_HPP
#define DEF_OPTIMISATION_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "utilitaire.hpp"

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
        bi_vecteur<int> localisation(float x, float y);
        float operator ()(int t, int j, int i){
            if(i>=taille_X || j>=taille_Y){
                cout << "Erreur : indices non-valides"; exit(1);}
            return score[t][j][i];
        }
};

class commandes_discretes{
    public:
    vector<float> commandes; 
};

#endif