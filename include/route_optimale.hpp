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
    public:
    commandes_discretes commandes;
    Grille grille;
    int max_iter = 1000;
    Dynamique_voile vitesse;
    HJB HJB;
    bi_vecteur<float> positions;
    int n;

    route_optimale(Grille& g, Dynamique_voile& f, vecteur<float>& v0):
    grille(g), vitesse(f), HJB(v0,g,f), max_iter(grille.Temps/grille.resolution){}

    int calcul_n(const vecteur<float> &x0){
        float v0k = 1;
        int i = 0;
        bi_vecteur<int> loca = grille.localisation(x0[0], x0[1]);
        while(i<=max_iter && v0k>0){
            v0k = interpolation<float, vecteur<float>>(loca, x0[0], x0[1], i, HJB.v, grille);
            i++;
        }
        n=i-1;
        if(i>max_iter){throw logic_error("Temps trop court pour trouver une solution convenable.");}
        return (*this).n;
    }

    commandes_discretes calcul(vecteur<float>& x0, int L){
        if(HJB.resolved==0){HJB.resolve(L);}
        print_grille(grille, HJB.v);
        bi_vecteur<int> loca = grille.localisation(x0[0], x0[1]);
        float vx = interpolation<float, vecteur<float>>(loca, x0[0], x0[1], 0, HJB.v, grille);
        int iter = 0;
        n = calcul_n(x0);
        positions.pushback(x0);
        while(vx>0 && iter<=grille.Temps/grille.resolution){
            float mini = numeric_limits<float>::max();;
            float minimiseur;
            vecteur<float> next_pos(2);
            float commande;
            vecteur<float> opti_pos(2);
            bool erreur = 1;
            for(int l=0;l<L;l++){
                vecteur<float> vit = vitesse.f(positions[iter], float(l)/float(L)*360.f-180.f, iter);
                next_pos = positions[iter] + vit*grille.resolution;
                loca = grille.localisation(next_pos[0], next_pos[1]);
                if(loca[0][0]>0 && loca[0][1]>0 && loca[2][0]<grille.taille_X/grille.pas && loca[2][1]<grille.taille_Y/grille.pas){
                    minimiseur = interpolation<float, vecteur<float>>(loca, next_pos[0], next_pos[1], n-iter, HJB.v, grille);
                    if(minimiseur<mini){
                        mini=minimiseur;
                        commande=float(l)/float(L)*360.f-180.f;
                        opti_pos[0] = next_pos[0];
                        opti_pos[1] = next_pos[1];
                        erreur = 0;
                    }
                }
            }
            if(erreur){
                cout<<positions<<endl;
                cout<<commandes<<endl;
                throw logic_error("Le bateau ne veut que sortir de la zone !");}
            positions.pushback(opti_pos);
            commandes.commandes.push_back(commande);
            loca = grille.localisation(opti_pos[0], opti_pos[1]);
            vx = interpolation<float, vecteur<float>>(loca, opti_pos[0], opti_pos[1], 0, HJB.v, grille);
            iter++;
        }
        if(vx>0){cout<<"semi-";}
        return commandes;
    }
};

#endif