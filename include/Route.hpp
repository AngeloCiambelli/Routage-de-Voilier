#ifndef DEF_ROUTE_HPP
#define DEF_ROUTE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vecteur.hpp"*
#include "Bi_vecteur.hpp"

using namespace std;

//===========================================================================
//                            Description
//===========================================================================
//
// Classe de stockage des informations sur la route suivie.
//
// Note: Pas de fichier cpp a cause du template
//
//===========================================================================
//                            Definition de la classe
//===========================================================================

template <typename T>
class route
{
public:
  pair<T, T> depart;
  bi_vecteur<T> position;
  bi_vecteur<T> vitesse;

  route(pair<T, T> _depart, bi_vecteur<T> _position, bi_vecteur<T> _vitesse) : position(), vitesse()
  {
    depart = _depart;
    position = _position;
    vitesse = _vitesse;
  }
};

#endif