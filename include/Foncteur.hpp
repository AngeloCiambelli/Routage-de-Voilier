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
// Classes foncteurs pour générer les champs de courants et les chamsp de vents
//
// Note: 
//
//===========================================================================
//                 Definition des classes foncteurs 
//===========================================================================

// foncteur pour definir analytiquement les polaires
class foncteur_polaire
{
public:
  float operator()(float angle_voilier, float vitesse_vent) const
  {
    //cout << "vitesse bateau (polaire) = " << vitesse_vent/(float(1)+abs(angle_voilier)) << endl;
    return vitesse_vent/atan(1.f)*4.f*(atan(-1.f*abs(0.05f*angle_voilier)+3.f)+atan(1.f)*4./2.f);
  }
};

// foncteur pour definir analytiquement le champ de vent
class foncteur_vent
{
public:
  vecteur<float> operator()(float a, float b) const
  {
    return vecteur<float>({a, sin(a)+sin(b)+float(1)});
  }
};

// foncteur pour definir analytiquement le champ de courant
class foncteur_courant
{
public:
  vecteur<float> operator()(float a, float b) const
  {
    return vecteur<float>({a + float(0.4), sin(a)+sin(b)+float(0.8)});
  }
};

// foncteur pour definir analytiquement la commande (changement d'angle en fonction de l'ancien angle du bateau)
class foncteur_commande
{
public:
  float operator()(float u) const
  {
    return u;
  }
};


#endif