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
  float operator()(int angle_voilier, float vitesse_vent) const
  {
    cout << "vitesse bateau (polaire) = " << vitesse_vent/(1+abs(angle_voilier)) << endl;
    return vitesse_vent/(1+abs(angle_voilier));
  }
};

// foncteur pour definir analytiquement le champ de vent
class foncteur_vent
{
public:
  vecteur<float> operator()(float a, float b) const
  {
    return vecteur<float>({sin(a)+float(0.01), 2*sin(b)+float(0.01)});
  }
};

// foncteur pour definir analytiquement le champ de courant
class foncteur_courant
{
public:
  vecteur<float> operator()(float a, float b) const
  {
    return vecteur<float>({sin(a)+float(0.01), 2*sin(b)+float(0.01)});
  }
};

// foncteur pour definir analytiquement la commande
class foncteur_commande
{
public:
  vecteur<float> operator()(float u) const
  {
    return vecteur<float>({cos(u*float(atan(1)*4)/float(180)), sin(u*float(atan(1)*4)/float(180))});
  }
};


#endif