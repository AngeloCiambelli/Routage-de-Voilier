#ifndef DEF_HJB_HPP
#define DEF_HJB_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits>
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
    Flux flux;

    HJB(float X, float Y, float Time, float res, float p, Dynamique_voile f);
    HJB(const vecteur<float> &v0, const Grille &g, Dynamique_voile f) : flux(g, f){
        grille = g;
        int taille = (int(grille.taille_X/grille.pas)+1)*
                     (int(grille.taille_Y/grille.pas)+1)*
                     (int(grille.Temps/grille.resolution)+1);
        int fin = 0;
        v.reserve(taille);
        for(int j=0; j<=int(grille.taille_Y/grille.pas); j++){
            for(int i=0;i<=int(grille.taille_X/grille.pas);i++){
                v.push_back(v0[grille.find(i,j,0)]);
                fin++;
            }
        }
        for(int i=fin+1; i<=taille; i++){
            v.push_back(0.f);
        }
    }

    void resolve(const int &L);
};


HJB::HJB(float X, float Y, float Time, float res, float p, Dynamique_voile f): 
grille(X,Y,Time,res,p), v(X*Y*Time), flux(grille, f){ // Initialisation "à la main", à éviter
}


void HJB::resolve(const int &L){
    vecteur<vecteur<float>> F(L, vecteur<float>(4));
    for(int n=1;n<=int((*this).grille.Temps/(*this).grille.resolution);n++){
        for(int j=0; j<=int((*this).grille.taille_X/(*this).grille.pas); j++){
            for(int i=0;i<=int((*this).grille.taille_Y/(*this).grille.pas);i++){
                float mini = numeric_limits<float>::max();
                float minimiseur;
                for(int l=0;l<L;l++){
                    F[l][0] = flux.calcul(float(l)/float(L)*360., float(i)+1./2., float(j), n, v);
                    F[l][1] = flux.calcul(float(l)/float(L)*360., float(i)-1./2., float(j), n, v);
                    F[l][2] = flux.calcul(float(l)/float(L)*360., float(i), float(j)+1./2., n, v);
                    F[l][3] = flux.calcul(float(l)/float(L)*360., float(i), float(j)-1./2., n, v);
                    minimiseur = (*this).grille.resolution/(*this).grille.pas*(F[l][0]-F[l][1]+F[l][2]-F[l][3]);
                    if (minimiseur<=mini){
                        mini = minimiseur;
                    }
                }
                this->v[(*this).grille.find(i,j,n)] = (*this).v[(*this).grille.find(i,j,n-1)] + mini;
            }
        }
    }
}



#endif