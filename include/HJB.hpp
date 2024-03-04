#ifndef DEF_HJB_HPP
#define DEF_HJB_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vecteur.hpp"
#include "Grille.hpp"
#include "Dynamique.hpp"
#include "Flux.hpp"
#include "Fonction_externes.hpp"

using namespace std;


class HJB{
    public:
    vecteur<float> v;
    Grille grille;
    HJB(){};
    HJB(int X, int Y, int Time, float res, float p);
    HJB(vecteur<float> &v0, int Temps, const Grille &grille);
    void resolve(const int &L, const Dynamique_voile &fonction);
};


HJB::HJB(int X, int Y, int Time, float res, float p){
    // Initialisation "à la main", à éviter
    vecteur<float> v(X*Y*Time);
    Grille grille(X, Y, Time, res, p);
}

HJB::HJB(vecteur<float> &v0, int Temps, const Grille &g){
    Grille grille(g.taille_X, g.taille_Y, Temps, g.resolution, g.pas);
    vecteur<float> v(grille.taille_X*grille.taille_Y*grille.Temps);
    for(int j=0; j<grille.taille_X; j++){
        for(int i=0;i<grille.taille_Y;i++){
            v[grille.find(i,j,0)] = v0[grille.find(i,j,0)];
        }
    }
}

void HJB::resolve(const int &L, const Dynamique_voile &fonction){
    vecteur<vecteur<float>> F(L, vecteur<float>(4));
    Flux flux(grille, fonction);
    for(int n=1;n<grille.Temps;n++){
        for(int j=0; j<grille.taille_X; j++){
            for(int i=0;i<grille.taille_Y;i++){
                for(int l=0;l<L;l++){
                    F[l][0] = flux.calcul(l/L*360, i+1/2, j, n, v);
                    F[l][1] = flux.calcul(l/L*360, i-1/2, j, n, v);
                    F[l][2] = flux.calcul(l/L*360, i, j+1/2, n, v);
                    F[l][3] = flux.calcul(l/L*360, i, j-1/2, n, v);
                }
                float mini = INFINITY;
                float minimiseur;
                for(int ind;ind<L;ind++){
                    minimiseur = grille.resolution/grille.pas*(F[ind][0]-F[ind][1]+F[ind][2]-F[ind][3]);
                    if (minimiseur<mini){
                        mini = minimiseur;
                    }
                }
                v[grille.find(i,j,n)]=v[grille.find(i,j,n-1)]+mini;
            }
        }
    }
}



#endif