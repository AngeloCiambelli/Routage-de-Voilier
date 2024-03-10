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
    private:
    Grille grille;
    Flux flux;

    public:
    vecteur<float> v;  // vecteur des scores
    bool resolved=0;  // est-ce que l'on a calculé HJB pour tout t

    HJB(float X, float Y, float Time, float res, float p, Dynamique_voile f); // constructeur par défaut

    HJB(const vecteur<float> &v0, const Grille &g, Dynamique_voile f) : flux(g, f){   // constructeur utile 
        grille = g;

        // Initialisation de v, avec v0 pour t = 0 , 0 pour le reste
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

    void resolve(const int &L); // resolution de HJB pour tout t
};


HJB::HJB(float X, float Y, float Time, float res, float p, Dynamique_voile f): 
grille(X,Y,Time,res,p), v(X*Y*Time), flux(grille, f){ // Initialisation "à la main", à éviter
}


void HJB::resolve(const int &L){
    vecteur<float> F(4);  // vecteur avec les 4 flux nécessaire pour l'iteration sur v
    for(int n=1;n<=int((*this).grille.Temps/(*this).grille.resolution);n++){  // pour chaque pas de temps
        for(int j=0; j<=int((*this).grille.taille_X/(*this).grille.pas); j++){  //pour chaque ligne
            for(int i=0;i<=int((*this).grille.taille_Y/(*this).grille.pas);i++){  //pour chaque point
                float mini = numeric_limits<float>::max();  // minimum initialisé à la valeur maximale possible,
                                                            // de sorte que a<mini quelque soit a
                float minimiseur; // variable dans laquelle on stockera la valeur que l'on veut minimiser
                for(int l=0;l<L;l++){  // pour chaque angle possible
                    F[0] = flux.calcul(float(l)/float(L)*360.-180., float(i)+1./2., float(j), n, v);  // calcul du flux  
                    F[1] = flux.calcul(float(l)/float(L)*360.-180., float(i)-1./2., float(j), n, v);  // et conversion des entiers
                    F[2] = flux.calcul(float(l)/float(L)*360.-180., float(i), float(j)+1./2., n, v);  // vers les degrés allant de -180° à 180°
                    F[3] = flux.calcul(float(l)/float(L)*360.-180., float(i), float(j)-1./2., n, v);
                    minimiseur = (*this).grille.resolution/(*this).grille.pas*(F[0]-F[1]+F[2]-F[3]);
                    if (minimiseur<=mini){  // si la nouvelle valeur est plus petite que la valeur stockée
                        mini = minimiseur;  // on stocke la nouvelle plus petite valeur
                    }
                }
                this->v[(*this).grille.find(i,j,n)] = (*this).v[(*this).grille.find(i,j,n-1)] + mini;  // modification de v (score) avec la nouvelle valeur calculée
            }
        }
    }
    resolved=1;  // l'équation est résolue
}



#endif