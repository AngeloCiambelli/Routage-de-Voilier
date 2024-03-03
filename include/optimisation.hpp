#ifndef DEF_OPTIMISATION_HPP
#define DEF_OPTIMISATION_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "Grille.hpp"
#include "Dynamique.hpp"
#include "Commande_discrete.hpp"

using namespace std;


class Flux{
    public:
    Grille grille;
    Dynamique fonction;
    Flux(const Grille g, const Dynamique f): grille(g),fonction(f){};
    float calcul(float u, float i, float j, int n, vecteur<float> v_prec){
        vecteur<float> xij(2,i*grille.pas);
        xij[1]=j*grille.pas;
        vecteur<float> f = fonction(xij, u);
        if(float(int(i))==i){
            if(f[1]>0){
                return f[1]*v_prec[grille.find(int(j)+1,int(i),n-1)];
            }
            else{
                return f[1]*v_prec[grille.find(int(j),int(i),n-1)];
            }
        }
        else{
            if(f[0]>0){
                return f[0]*v_prec[grille.find(int(j),int(i)+1,n-1)];
            }
            else{
                return f[0]*v_prec[grille.find(int(j),int(i),n-1)];
            }
        }
    }

};



class HJB{
    public:
    vecteur<float> v;
    Grille grille;
    HJB(){};
    HJB(int X, int Y, int Time, float res, float p);
    HJB(vecteur<float> &v0, int Temps, const Grille &grille);
    void resolve(int L, Dynamique fonction);
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

void HJB::resolve(int L, Dynamique fonction){
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

class route_optimale{
    commandes_discretes commandes;
    Grille grille;
    int max_iter = 1000;
    Dynamique fonction;
    commandes_discretes calcul(pair<float, float> x0, int L){
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
                next_pos = x[n] + fonction(x[n], l/L*360);
            }
        }
    }
};

#endif