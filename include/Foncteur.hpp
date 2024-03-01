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

// foncteur pour definir analytiquement le champ de vent
class foncteur_vent
{
public:
  vecteur<float> operator()(float a, float b) const
  {
    return vecteur{sin(a), sin(b)};
  }
};

// foncteur pour definir analytiquement le champ de courant
class foncteur_courant
{
public:
  vecteur<float> operator()(float a, float b) const
  {
    return vecteur{sin(a)*cos(b), sin(b)*cos(a)};
  }
};

#endif