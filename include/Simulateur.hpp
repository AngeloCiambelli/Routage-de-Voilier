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
// générant une route à partir d’une dynamique
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

    Simulateur(const float &delta, const int &nombre_pas){delta_temps=delta; nb_pas=nombre_pas;};
    route<float> mise_en_route(route<float> &route, const Dynamique &dynamique, const Commande & commande)
    {
        for (int i=0; i<=nb_pas; i++)
        {   
            cout << "route vitesse" << route.vitesse[i] << endl;
            float u = angle(route.vitesse[i]);
            
            cout << "Angle bateau" << u << endl;
            // Vitesse voilier au temps i
            route.vitesse.pushback(dynamique.f(route.position[i], u, i, commande));

            // Nouvelle position au temps i+1
            (route.position).pushback(route.position[i]+(delta_temps*route.vitesse[i]));
            cout << "positions =" << route.position << endl;
        }
        
        return(route);
    };
};

#endif