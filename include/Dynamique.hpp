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
    vecteur<float> operator ()(vecteur<float> xi, float u){};
};

#endif