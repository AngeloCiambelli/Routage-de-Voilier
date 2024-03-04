#ifndef DEF_DYNAMIQUE_HPP
#define DEF_DYNAMIQUE_HPP

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
#include "Bassin.hpp"
#include "Voilier.hpp"
#include "Fonction_externes.hpp"

using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Classe dynamique implémentant la dynamique du système, proposant en particulier 
// l’évaluation de la fonction f(y, u, t).
//
// Note: 
//
//===========================================================================
//                 Definition de la class Dynamique
//===========================================================================

class Dynamique
{
    public:
    virtual vecteur<float> f()=0;
};

class Dynamique_voile : public Dynamique
{
    public:
    bassin bassin;
    Voilier<float, float> voilier;
    
    vecteur<float> f(const vecteur<float> &y,const float &u, const int &t)
    {
        vecteur<float> valeur;
        vecteur<float> V_c = interpolation<vecteur<float>, bi_vecteur<float>>((bassin.grille).localisation(y[0],y[1]),  
                                           y[0], 
                                           y[1], 
                                           0, 
                                           bassin.champs_courant,
                                           bassin.grille);

        vecteur<float> V_v = interpolation<vecteur<float>, bi_vecteur<float>>((bassin.grille).localisation(y[0],y[1]),  
                                           y[0], 
                                           y[1], 
                                           0, 
                                           bassin.champs_vent,
                                           bassin.grille);

        vecteur<float> W_u({cos(u), sin(u)}); 

        valeur = V_c + (W_u|voilier.V_b(acos(V_v[0]/sqrt(V_v|V_v))-u,sqrt(V_v|V_v)));

        return(valeur);
    };
};


class Dynamique_test : public Dynamique
{
    public:
    vecteur<float> f(){return vecteur<float>({1,1});}
};


#endif