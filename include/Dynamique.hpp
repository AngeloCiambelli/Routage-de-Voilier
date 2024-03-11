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
    virtual Vecteur<float> f(const Vecteur<float> &y,const float &u, const int &t) const {};
};

class Dynamique_voile : public Dynamique
{
    public:
    Bassin                 bassin;      // Bassin dans lequel on navigue
    Voilier<float, float>  voilier;     // Voilier qu'on utilise

    // Constructeurs
    Dynamique_voile(const Bassin &B, const Voilier<float, float> &v);
    
    //Fonctions membres
    Vecteur<float> f(const Vecteur<float> &y,const float &u, const int &t) const override;
};


class Dynamique_test : public Dynamique
{
    public:
    // Constructeurs
    Dynamique_test(){};

    // Fonctions membres
    Vecteur<float> f(const Vecteur<float> &y,const float &u, const int &t) const override;
};

//===========================================================================
//                 Fonctions membres Dynamique_voile
//===========================================================================

Dynamique_voile::Dynamique_voile(const Bassin &B, const Voilier<float, float> &v) 
{
    bassin = B; voilier = v;
};

Vecteur<float> Dynamique_voile::f(const Vecteur<float> &y,const float &u, const int &t) const
{
    // Déclaration de variables
    Vecteur<float> valeur; // Vecteur vitesse: dy/dt
    Vecteur<float> V_c;    // Vecteur courant en y
    Vecteur<float> V_v;    // Vecteur vent en y

    // Controle pour voir si le voilier s'est échoué (i.e s'il est sorti du bassin)
    if (controle_position(y, bassin)==0){cout << "Le voilier s'est echoué"; exit(1);}

    // Calculer le vecteur courant (V_c) et vent (V_v) à notre position avec la fonction d'interpolation,
    // si le stockage des champs de courant et vent est tabulé.
    if (bassin.stockage=="tabule")
    {
        V_c = interpolation<Vecteur<float>, Bi_vecteur<float>>((bassin.grille).localisation(y[0],y[1]),  
                                        y[0], 
                                        y[1], 
                                        0, 
                                        bassin.champs_courant,
                                        bassin.grille);

        V_v = interpolation<Vecteur<float>, Bi_vecteur<float>>((bassin.grille).localisation(y[0],y[1]),  
                                        y[0], 
                                        y[1], 
                                        0, 
                                        bassin.champs_vent,
                                        bassin.grille);
    }
    
    // Calculer le vecteur courant (V_c) et vent (V_v) à notre position avec les foncteurs,
    // si le stockage des champs de courant et vent est analytique
    else if (bassin.stockage=="analytique")
    {
        V_c = bassin.fonction_courant(y[0], y[1]);
        V_v = bassin.fonction_vent(y[0], y[1]);
    }

    // Calculer la direction du bateau en fonction de l'angle de la commande
    Vecteur<float> W_u({cos(u*atan(float(1))*float(4)/float(180)), sin(u*atan(float(1))*float(4)/float(180))});
    
    // Calcul de l'angle entre le vent et la commande
    float angle_vent_bateau = angle_relatif(angle(V_v), u);

    // Calcul de dy/dt
    valeur = (0.5f*V_c + (W_u*voilier.V_b(angle_vent_bateau,sqrt(V_v|V_v))));

    return(valeur);
};

//===========================================================================
//                 Fonctions membres Dynamique_test
//===========================================================================

Vecteur<float> Dynamique_test::f(const Vecteur<float> &y,const float &u, const int &t) const 
{
    return Vecteur<float>({0,1});
};

#endif