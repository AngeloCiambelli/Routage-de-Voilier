#ifndef DEF_FONCTEUR_HPP
#define DEF_FONCTEUR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vecteur.hpp"
#include "Bi_vecteur.hpp"

using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Classes foncteurs pour générer: 
//      - Les polaires analytiquement
//      - Les champs de courants et les champs de vents
//      - La commande analytiquement
//
//===========================================================================
//                 Definition des classes foncteurs 
//===========================================================================

// Foncteur pour definir analytiquement les polaires
class Foncteur_polaire
{
public:
  float operator()(float angle_voilier_vent, float vitesse_vent) const
  {
    return vitesse_vent/(atan(float(1))*float(4))*(atan(-abs(float(0.05)*angle_voilier_vent)+float(3))+atan(float(1))*float(4)/float(2));
  }
};

// Foncteur pour definir le champ de vent
class Foncteur_vent
{
public:
  Vecteur<float> operator()(float a, float b) const
  {
    return Vecteur<float>({a, sin(a)+sin(b)+float(1)});
  }
};

// Foncteur pour definir le champ de courant
class Foncteur_courant
{
public:
  Vecteur<float> operator()(float a, float b) const
  {
    return Vecteur<float>({a + float(0.4), sin(a)+sin(b)+float(0.8)});
  }
};

// Foncteur pour definir analytiquement la commande (changement d'angle en fonction de l'ancien angle du bateau)
class Foncteur_commande
{
public:
  float operator()(const float &u) const
  {
    return(u); // Conserve le cap (angle d'arrivée) -> In fine, se fait porter par le vent et courant
  }
};

#endif