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
#include "Foncteur.hpp"
#include "Commande.hpp"

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
    virtual vecteur<float> f(const vecteur<float> &y,const float &u, const int &t) const {};
};

class Dynamique_voile : public Dynamique
{
    public:
    Bassin bassin;
    Voilier<float, float> voilier;

    Dynamique_voile(const Bassin &B, const Voilier<float, float> &v) {bassin = B; voilier = v;};
    
    vecteur<float> f(const vecteur<float> &y,const float &u, const int &t) const override
    {
        vecteur<float> valeur;
        vecteur<float> V_c;
        vecteur<float> V_v;

        if (controle_position(y, bassin)==0){return vecteur<float>({0,0});}

        if (bassin.stockage=="tabule")
        {
            V_c = interpolation<vecteur<float>, bi_vecteur<float>>((bassin.grille).localisation(y[0],y[1]),  
                                            y[0], 
                                            y[1], 
                                            0, 
                                            bassin.champs_courant,
                                            bassin.grille);

            V_v = interpolation<vecteur<float>, bi_vecteur<float>>((bassin.grille).localisation(y[0],y[1]),  
                                            y[0], 
                                            y[1], 
                                            0, 
                                            bassin.champs_vent,
                                            bassin.grille);
        }
        
        else if (bassin.stockage=="analytique")
        {
            V_c = bassin.fonction_courant(y[0], y[1]);
            V_v = bassin.fonction_vent(y[0], y[1]);
        }

        //Vérification de la contrainte sur la commande
        vecteur<float> W_u({cos(u*atan(float(1))*float(4)/float(180)), sin(u*atan(float(1))*float(4)/float(180))});

        
        cout << "V_c =" <<  V_c << ", V_v =" << V_v << endl;
        foncteur_courant vrai_c;
        foncteur_vent vrai_v;
        cout << "erreur_V_c =" <<  V_c - vrai_c(y[0], y[1]) << ", erreur_V_v =" << V_v - vrai_v(y[0], y[1]) << endl;

        float angle_vent_bateau = abs(angle(V_v)-u);
        cout << "Angle vent bateau=" << angle_vent_bateau << endl;
        valeur = (V_c + (W_u*voilier.V_b(angle_vent_bateau,sqrt(V_v|V_v))));
        cout << "Vitesse bateau=" << valeur <<endl <<endl;
        return(valeur);
    };
};


class Dynamique_test : public Dynamique
{
    public:
    vecteur<float> f(const vecteur<float> &y,const float &u, const int &t) const override 
    {
        return vecteur<float>({0,1});
    }
};


#endif