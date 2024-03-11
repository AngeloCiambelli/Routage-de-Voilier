#ifndef DEF_SIMULATEUR_HPP
#define DEF_SIMULATEUR_HPP

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
#include "Route.hpp"
#include "Dynamique.hpp"
#include "Commande.hpp"

using namespace std;

//===========================================================================
//                            Simulateur
//===========================================================================
//
// Classe Simulateur  contenant le pas de temps, le nombre de pas de temps ainsi que la fonction
// générant une Route à partir d’une dynamique
//
// Note: 
//
//===========================================================================
//                 Definition de la classe Simulateur
//===========================================================================

class Simulateur
{       
    public:
    float delta_temps;
    int nb_pas;
    Commande commande;

    // Constructeurs
    Simulateur(const float &delta, const int &nombre_pas, const Commande& com);

    // Fonctions membres
    Route<float> mise_en_route(Route<float> &route, const Dynamique &dynamique);
};

//===========================================================================
//                   Fonctions membres
//===========================================================================

Simulateur::Simulateur(const float &delta, const int &nombre_pas, const Commande& com)
{
    delta_temps=delta; nb_pas=nombre_pas; commande=com;
};

Route<float> Simulateur::mise_en_route(Route<float> &route, const Dynamique &dynamique)
{
    for (int i=0; i<=nb_pas; i++)
    {
        // Definition temporaire de la commande u
        float u;

        // Si les commandes sont stockés analytiquement, 
        // Calculer de la commande apartir de l'ancien angle de vitesse (angle d'arrivée)
        if(commande.stockage=="analytique")
        {
            u = commande.commande_f(angle(route.vitesse[i]));
        } 

        // Si les commandes sont stockées de manière tabulés, extraire la i^eme commande
        else if (commande.stockage=="tabule")
        {
            u = commande.vecteur_commande[i];
        }

        // Vitesse voilier au temps i
        route.vitesse.pushback(dynamique.f(route.position[i], u, i));

        // Nouvelle position au temps i+1
        (route.position).pushback(route.position[i]+(delta_temps*route.vitesse[i]));
        cout << route.position << endl << endl;
    }
    
    return(route);
};

#endif