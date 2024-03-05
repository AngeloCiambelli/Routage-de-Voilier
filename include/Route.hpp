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
#include "Vecteur.hpp"
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
  vecteur<T> depart;
  vecteur<T> vitesse_initiale;
  bi_vecteur<T> position;
  bi_vecteur<T> vitesse;

  route(vecteur<T> _depart, vecteur<T> _vitesse_initiale, bi_vecteur<T> _position, bi_vecteur<T> _vitesse) : position(), vitesse()
  {
    depart = _depart;
    vitesse_initiale = _vitesse_initiale;;

    position = _position;
    position.pushback(_depart);

    vitesse = _vitesse;
    vitesse.pushback(_vitesse_initiale);
  }
};

#endif