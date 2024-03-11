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
class Route
{
public:
  Vecteur<T> depart;
  Vecteur<T> vitesse_initiale;
  Bi_vecteur<T> position;
  Bi_vecteur<T> vitesse;

  //Constructeur
  Route(Vecteur<T> _depart, Vecteur<T> _vitesse_initiale, Bi_vecteur<T> _position, Bi_vecteur<T> _vitesse);
};

//===========================================================================
//                            Fonctions membres
//===========================================================================

template<typename T>
Route<T>::Route(Vecteur<T> _depart, Vecteur<T> _vitesse_initiale, Bi_vecteur<T> _position, Bi_vecteur<T> _vitesse) : position(), vitesse()
{
  depart = _depart;
  vitesse_initiale = _vitesse_initiale;;

  position = _position;
  position.pushback(_depart);

  vitesse = _vitesse;
  vitesse.pushback(_vitesse_initiale);
}

#endif