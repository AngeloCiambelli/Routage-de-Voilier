#ifndef DEF_OPTIMISATION_HPP
#define DEF_OPTIMISATION_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "Grille.hpp"
#include "Dynamique.hpp"

using namespace std;


class Flux{
    public:
    Grille<float> v;
    dynamique fonction;
    Flux(){};
    float calcul(float u, float i, float j, int n, Grille<float> v_prec){
        Grille<float> tmp(v_prec.taille_X, v_prec.taille_Y, 1, 1, v_prec.pas);
        tmp.valeur[0] = v_prec.valeur[n-1];
        v = tmp;
        pair<float,float> xij;
        xij = pair(i*v.pas,j*v.pas);
        vecteur<float> f = fonction(xij, u);
        if(float(int(i))==i){
            if(f[1]>0){
                return f[1]*v(0,int(i),int(j)+1);
            }
            else{
                return f[1]*v(0,int(i),int(j));
            }
        }
        else{
            if(f[0]>0){
                return f[0]*v(0,int(i)+1,int(j));
            }
            else{
                return f[0]*v(0,int(i),int(j));
            }
        }
    }

// };



class HJB{
    public:
    Grille<float> v;
    HJB(){};
    HJB(int X, int Y, int Time, float res, float p);
    HJB(Grille<float> &v0, int Temps);
    void resolve(int L);
};


HJB::HJB(int X, int Y, int Time, float res, float p){
    // Initialisation "à la main", à éviter
    Grille<float> tmp(X, Y, Time, res, p);
    v = tmp;
}

HJB::HJB(Grille<float> &v0, int Temps){
    Grille<float> tmp(v0.taille_X, v0.taille_Y, Temps, v0.resolution, v0.pas);
    v = tmp;
    for(int j=0; j<v.taille_X; j++){
        for(int i=0;i<v.taille_Y;i++){
            v.valeur[0][j][i] = v0(0,j,i);
        }
    }
}

void HJB::resolve(int L){
    vecteur<vecteur<float>> F(L, vecteur<float>(4));
    Flux flux;
    for(int n=1;n<v.Temps;n++){
        for(int j=0; j<v.taille_X; j++){
            for(int i=0;i<v.taille_Y;i++){
                for(int l=0;l<L;l++){
                    F[l][0] = flux.calcul(l/L*360, i+1/2, j, n, v);
                    F[l][1] = flux.calcul(l/L*360, i-1/2, j, n, v);
                    F[l][2] = flux.calcul(l/L*360, i, j+1/2, n, v);
                    F[l][3] = flux.calcul(l/L*360, i, j-1/2, n, v);
                }
                float mini = INFINITY;
                float minimiseur;
                for(int ind;ind<L;ind++){
                    minimiseur = v.resolution/v.pas*(F[ind][0]-F[ind][1]+F[ind][2]-F[ind][3]);
                    if (minimiseur<mini){
                        mini = minimiseur;
                    }
                }
                v.valeur[n][j][i]=v(n-1,j,i)+mini;
                mini.clear;
                minimiseur.clear;
            }
        }
    }
}

class route_optimale{
    commandes_discretes commandes;
    Grille<float> grille;
    int max_iter = 1000;
    dynamique fonction;
    commandes_discretes calcul(pair<float, float> x0, int L){
        float vx = 1;
        int iter = 0;
        bi_vecteur<float> x;
        bi_vecteur.pushback(x0);
        while(vx>0 && iter<max_iter){
            n = x.size()-1
            vecteur<float> tmp(L);
            float mini = INFINITY;
            float minimiseur;
            pair<float, float> next_pos;
            for(int l=0;l<L;l++){
                next_pos = x[n] + fonction(x[n], l/L*360)
            }
            tmp.clear;
        }
    }
};

#endif