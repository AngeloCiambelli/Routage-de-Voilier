#ifndef DEF_FLUX_HPP
#define DEF_FLUX_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "Grille.hpp"
#include "Dynamique.hpp"
#include "Commande_discrete.hpp"

using namespace std;


class Flux{
    private:
    Grille grille;
    Dynamique_voile vitesse;


    public:

    Flux(const Grille &g, const Dynamique_voile &f): grille(g),vitesse(f){}; //constructeur par défaut


    float calcul(float u, float i, float j, int n,const vecteur<float> &v_prec){
        //fonction de calcul du Flux
        if(i<0||j<0||i>grille.taille_X/grille.pas||j>grille.taille_Y/grille.pas){
            return 0.f;}// si on est en dehors de la zone globale, le flux est nul
    
        vecteur<float> xij({float(i)*grille.pas, float(j)*grille.pas});
        vecteur<float> f = vitesse.f(xij, u, n); // calcul de la vitesse du bateau au point étudié, avec la commande u
        
        float tmp;
        if(modf(i, &tmp)==.0f){ // si i est un entier (cf le sujet)
            if(f[1]>0.){  // si la vitesse est positive
                return f[1]*v_prec[grille.find(int(i),int(j)+1,n-1)];
            }
            else{
                return f[1]*v_prec[grille.find(int(i),int(j),n-1)];
            }
        }
        else{
            if(f[0]>0.){
                return f[0]*v_prec[grille.find(int(i)+1,int(j),n-1)];
            }
            else{
                return f[0]*v_prec[grille.find(int(i),int(j),n-1)];
            }
        }
    }

};

#endif

