#ifndef DEF_ROUTE_OPTIMALE_HPP
#define DEF_ROUTE_OPTIMALE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vecteur.hpp"
#include "Fonction_externes.hpp"
#include "Commande_discrete.hpp"
#include "Dynamique.hpp"
#include "HJB.hpp"

using namespace std;

class route_optimale{
    commandes_discretes commandes;
    Grille grille;
    int max_iter = 1000;
    Dynamique_voile fonction;
    HJB HJB;
    commandes_discretes calcul(vecteur<float> x0, int L){
        float vx = 1;
        int iter = 0;
        bi_vecteur<float> x;
        x.pushback(x0);
        while(vx>0 && iter<max_iter){
            int n = x.size()-1;
            vecteur<float> tmp(L);
            float mini = INFINITY;
            float minimiseur;
            vecteur<float> next_pos;
            for(int l=0;l<L;l++){
                next_pos = x[n] + fonction.f(x[n], l/L*360, 0)*grille.resolution;
                minimiseur = interpolation(grille.localisation(next_pos[0], next_pos[1]), next_pos[0], next_pos[1], n, HJB.v, grille);
            }
        }
    }
};

#endif